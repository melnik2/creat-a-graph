//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <fstream>       // read-save file
#include <math.h>       // ceil
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>
#include <cstring>
#include<algorithm>

#include "Unit48.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "sDialogs"
#pragma resource "*.dfm"
TForm1 *Form1;

using namespace std;

FILE *fp;

int rw1; // rows
int clm1; // column
int sum1; // sum
int x=0;
int y=0;
char cd1;
int cnt1=0;
int cnt2=0;
int cnt3=0;
int cnt4=0;
int grn1;
int grn2;
int itr1;
int n;
int max1;
int max2;

int *iMark1 = new int [n];
char *str1 = new char[4];
char *str2 = new char[4];
char *str3 = new char[4];
char *s3 = new char[8];
char *cx1=new char[4];
int *iMark2;

int func1();

AnsiString FileName1;
AnsiString FileName2;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
//fhftfh
}

void __fastcall TForm1::TrackMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
max1=0;
max2=TrackBar3->Position;

for (int i=2*(grn1-1); i<=2*(grn2-1); i+=2){ //cnt1+cnt2,rw1
y=iMark2[i+1];
max1=max(abs(y),max1);
}

TrackBar3->Min=max1/10;
TrackBar3->Max=10*max1;
TrackBar3->Position=max2;

if(CheckBox1->Checked == true)Memo1->Clear();
Series1->Clear();
Series2->Clear();
Series3->Clear();
Series4->Clear();

for (int i=2*(grn1-1); i<=2*(grn2-1); i+=2){ //cnt1+cnt2,rw1
x=iMark2[i];
y=iMark2[i+1];
itoa(x, str1, 10);
itoa(y, str3, 10);
strcpy(s3, str1);
strcat(s3, str2);
strcat(s3, str3);
if(CheckBox1->Checked == true)Memo1->Lines->Add(s3);
Series1->Add(y,x,clBlue);
Series2->Add(0,x,clGreen);
 }

Series3->AddXY(0,max2,0,clSilver);
Series4->AddXY(0,-max2,0,clSilver);

for (int i=0; i<4; i++){
str1[i]=0;
str3[i]=0;
 }
for (int i=0; i<8; i++){
s3[i]=0;
 }
}

void __fastcall TForm1::TrackBar1Change(TObject *Sender)
{
grn1=TrackBar1->Position-itr1+1;
grn2=TrackBar1->Position+itr1;

Label5->Caption=TrackBar1->Position;
Label9->Caption= IntToStr(grn1);
Label10->Caption= IntToStr(grn2);

((THackTrackBar*)TrackBar1)->OnMouseUp = TrackMouseUp;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar2Change(TObject *Sender)
{
itr1=TrackBar2->Position;

grn1=TrackBar1->Position-itr1+1;
grn2=TrackBar1->Position+itr1;

Label9->Caption= IntToStr(grn1);
Label10->Caption= IntToStr(grn2);

 TrackBar1->Min=itr1;
 TrackBar1->Max=rw1-itr1;

 Label23->Caption=TrackBar2->Position;
 Label6->Caption=IntToStr(2*itr1)+"/"+IntToStr(itr1);

 Label5->Caption=TrackBar1->Position;
 Label11->Caption=TrackBar1->Min;
 Label12->Caption=TrackBar1->Max;
 ((THackTrackBar*)TrackBar2)->OnMouseUp = TrackMouseUp;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar3Change(TObject *Sender)
{
 ((THackTrackBar*)TrackBar3)->OnMouseUp = TrackMouseUp;
}
//---------------------------------------------------------------------------

int func1(){
ifstream file1 (FileName2.c_str());
while((cd1 = file1.get())!= EOF){
switch (cd1) {
case '\t': 
cnt1++;
break;
case '\n':
cnt2++;
break;
default:
break;
 }
}
file1.clear();
file1.close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Open1Click(TObject *Sender)
{

SelectDirectory("","",FileName1);
sOpenDialog1->Execute();
sOpenDialog1->InitialDir = FileName1;
//ShowMessage(sOpenDialog1->FileName);
FileName2=sOpenDialog1->FileName;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{

ifstream file3 (FileName2.c_str());
if((file3)!=NULL)   Label1->Caption="File - OK";
else Label1->Caption="File - BAD";
file3.clear();
file3.close();

func1();

rw1=cnt2;
clm1=(cnt1+cnt2)/cnt2;
sum1=cnt1+cnt2;

Label2->Caption="Rows "+IntToStr(rw1);
Label3->Caption="Column "+IntToStr(clm1);
Label4->Caption="Sum "+IntToStr(sum1);


itr1= 0.01*rw1;
Label6->Caption=IntToStr(2*itr1)+"/"+IntToStr(itr1);
TrackBar1->Min=itr1;
TrackBar1->Max=rw1-itr1;
TrackBar1->Position=10*itr1;
TrackBar2->Position=0.5*rw1-1;
Label5->Caption=IntToStr(10*itr1);
grn1=TrackBar1->Position-itr1+1;
grn2=TrackBar1->Position+itr1;
TrackBar2->Min=0.01*rw1;
TrackBar2->Max=0.5*rw1;

Label10->Caption=IntToStr(rw1);
Label11->Caption=TrackBar1->Min;
Label12->Caption=TrackBar1->Max;
Label21->Caption=TrackBar2->Min;
Label22->Caption=TrackBar2->Max;
Label23->Caption=0.1*rw1;

delete [] iMark1;
int *iMark1 = new int [cnt1+cnt2+1];

ifstream file2 (FileName2.c_str());
while((cd1 = file2.get())!= EOF){
switch (cd1) {
case '\t':
iMark1[cnt4] = atoi (cx1);
cnt3=0;
cnt4++;

for (int i=0; i<4; i++){
cx1[i]=0;
}

break;
case '\n':
iMark1[cnt4] = atoi (cx1);
cnt3=0;
cnt4++;

for (int i=0; i<4; i++){
cx1[i]=0;
}

break;
default:
cx1[cnt3]= cd1;
cnt3++;
break;
 }
}
file2.clear();
file2.close();

iMark2=iMark1;

Memo1->Clear();
str2="	";

for (int i=0; i<cnt1+cnt2; i+=2){
y=iMark1[i+1];
max1=max(abs(y),max1);
}

TrackBar3->Min=max1/10;
TrackBar3->Max=10*max1;
TrackBar3->Position=max1;

for (int i=0; i<cnt1+cnt2; i+=2){ //cnt1+cnt2,rw1
x=iMark1[i];
y=iMark1[i+1];
itoa(x, str1, 10);
itoa(y, str3, 10);
strcpy(s3, str1);
strcat(s3, str2);
strcat(s3, str3);
Series1->Add(y,x,clBlue);
Series2->Add(0,x,clGreen);
 }

Series3->AddXY(0,max1,0,clSilver);
Series4->AddXY(0,-max1,0,clSilver);

for (int i=0; i<4; i++){
str1[i]=0;
str3[i]=0;
 }
for (int i=0; i<8; i++){
s3[i]=0;
 }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Exit1Click(TObject *Sender)
{
 Form1->Close();
}
//---------------------------------------------------------------------------

