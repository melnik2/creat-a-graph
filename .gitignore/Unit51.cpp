
#include <vcl.h>
#pragma hdrstop
#include <fstream>       // read-save file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utilcls.h>
#include<algorithm>

#include "Unit51.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "sDialogs"
#pragma resource "*.dfm"

TForm1 *Form1;

using namespace std;

FILE *file1;

Variant mExcel;
String strA1, stred1, stred2;

int arr1n[9];

int in1,in2;
int x,y;

char ca1, ca2;

char *str1 = new char[4];
char *str2 = "	";
char *str3 = new char[4];
char *s3 = new char[8];

int *iMarkX;
int *iMarkY;
char *iMarkW;

int min1;
int idn1,idn2;

void func1(int i);
int* func2(char a1, char a2);

int grn1;
int grn2;
int itr1;
int n;
int max1;
int max2;

int *iMark1;
int *iMark2;

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
arr1n[0]=arr1n[1]=arr1n[2]=arr1n[3]=arr1n[4]=arr1n[5]=arr1n[6]=arr1n[7]=arr1n[8]=1;

for (int i=0; i<8; i++){
func1(i);
ComboBox1->Items->Add(stred1), ComboBox2->Items->Add(stred1);
}
 Memo1->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{

  if(CheckBox1->Checked == true) Memo1->Clear();
  Series1->Clear();
  Series2->Clear();
  Series3->Clear();
  Series4->Clear();

  stred2=ComboBox1->Text;
  iMarkW=stred2.c_str();
  ca1=iMarkW[0];
  stred2=ComboBox2->Text;
  iMarkW=stred2.c_str();
  ca2=iMarkW[0];
  delete [] iMarkW;

  delete [] iMarkX;
  delete [] iMarkY;

  func2(ca1, ca2); //A B - idn

 mExcel = CreateOleObject("Excel.Application");
 mExcel.OlePropertyGet("WorkBooks").OleProcedure("Open", FileName2.c_str());
 Label1->Caption="Excel open";
 ProgressBar1->Position=1;
 while ((strA1 =mExcel.OlePropertyGet("Cells", arr1n[idn1-1], idn1).OlePropertyGet("Value")).Length()!=0) arr1n[idn1-1]++;
 Label1->Caption="in1 received";
 ProgressBar1->Position=2;
 while ((strA1 =mExcel.OlePropertyGet("Cells", arr1n[idn2-1], idn2).OlePropertyGet("Value")).Length()!=0) arr1n[idn2-1]++;
 Label1->Caption="int2 received";
 ProgressBar1->Position=3;

 in1 = arr1n[idn1-1]-1;
 in2 = arr1n[idn2-1]-1;
 arr1n[idn1-1]=arr1n[idn2-1]=1;

 min1=in1;
 min1=min(min1,in2);

 int *iMarkX = new int [min1];
 int *iMarkY = new int [min1];
 Label1->Caption="XY create";
 ProgressBar1->Position=4;

 for (int i=0; i<min1; i++){
 iMarkX[i] = mExcel.OlePropertyGet("Cells", i+1, idn1).OlePropertyGet("Value");
 }
 Label1->Caption="X received";
 ProgressBar1->Position=5;
 for (int i=0; i<min1; i++){
 iMarkY[i] = mExcel.OlePropertyGet("Cells", i+1, idn2).OlePropertyGet("Value");
 }
 Label1->Caption="Y received";
 ProgressBar1->Position=6;

 mExcel.OleProcedure("Quit");
 Label1->Caption="Excel closed";
 ProgressBar1->Position=0;

  for(int i=0;i<min1;i++){
  x=iMarkX[i];
  y=iMarkY[i];
  if(CheckBox1->Checked == true){
  itoa(x, str1, 10);
  itoa(y, str3, 10);
  strcpy(s3, str1);
  strcat(s3, str2);
  strcat(s3, str3);
  Memo1->Lines->Add(s3);
  }
  Series1->Add(y,x,clBlue);
  Series2->Add(0,x,clGreen);
  }
 Label1->Caption="inform";

  for (int i=0; i<4; i++){
  str1[i]=0;
  str3[i]=0;
  }
  for (int i=0; i<8; i++){
  s3[i]=0;
  }

for (int i=0; i<min1; i++){
y=iMarkY[i];
max1=max(abs(y),max1);
}

TrackBar3->Min=max1/10;
TrackBar3->Max=10*max1;
TrackBar3->Position=max1;

Series3->AddXY(0,max1,0,clSilver);
Series4->AddXY(0,-max1,0,clSilver);

itr1= 0.01*min1;
Label6->Caption="range "+IntToStr(2*itr1)+"/"+IntToStr(itr1);
TrackBar1->Min=itr1;
TrackBar1->Max=min1-itr1;
TrackBar1->Position=10*itr1;
TrackBar2->Position=0.5*min1-1;
Label5->Caption=IntToStr(10*itr1);
grn1=TrackBar1->Position-itr1+1;
grn2=TrackBar1->Position+itr1;
TrackBar2->Min=0.01*min1;
TrackBar2->Max=0.5*min1;

Label10->Caption=IntToStr(min1);
Label11->Caption=TrackBar1->Min;
Label12->Caption=TrackBar1->Max;
Label21->Caption=TrackBar2->Min;
Label22->Caption=TrackBar2->Max;
Label23->Caption=0.1*min1;

delete [] iMark1;
delete [] iMark2;

iMark1=iMarkX;
iMark2=iMarkY;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::TrackMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{

max1=0;
max2=TrackBar3->Position;

for (int i=grn1-1; i<grn2; i++){
y=iMark2[i];
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

  int size1=0;
  for (int i=grn1-1; i<grn2; i++){
  x=iMark1[i];
  y=iMark2[i];
  if(CheckBox1->Checked == true){
  itoa(x, str1, 10);
  itoa(y, str3, 10);
  strcpy(s3, str1);
  strcat(s3, str2);
  strcat(s3, str3);
  Memo1->Lines->Add(s3);
  switch (size1){
  case 0:
  if (i>0.1*grn2) ProgressBar1->Position=1, size1=1;
  break;
  case 1:
  if (i>0.3*grn2) ProgressBar1->Position=2, size1=2;
  break;
  case 2:
  if (i>0.5*grn2) ProgressBar1->Position=3, size1=3;
  break;
  case 3:
  if (i>0.7*grn2) ProgressBar1->Position=4, size1=4;
  break;
  case 4:
  if (i>0.9*grn2) ProgressBar1->Position=0, size1=5;
  break;
    }
  }
  Series1->Add(y,x,clBlue);
  Series2->Add(0,x,clGreen);
  }

  for (int i=0; i<4; i++){
  str1[i]=0;
  str3[i]=0;
  }
  for (int i=0; i<8; i++){
  s3[i]=0;
  }
  
  Series3->AddXY(0,max2,0,clSilver);
  Series4->AddXY(0,-max2,0,clSilver);
}
//---------------------------------------------------------------------------
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
 TrackBar1->Max=min1-itr1;

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
int* func2(char a1, char a2){

  switch (a1){
  case 'A':
  idn1=1;
  break;
  case 'B':
  idn1=2;
  break;
  case 'C':
  idn1=3;
  break;
  case 'D':
  idn1=4;
  break;
  case 'E':
  idn1=5;
  break;
  case 'F':
  idn1=6;
  break;
  case 'G':
  idn1=7;
  break;
  case 'H':
  idn1=8;
  break;
  }
  
  switch (a2){
  case 'A':
  idn2=1;
  break;
  case 'B':
  idn2=2;
  break;
  case 'C':
  idn2=3;
  break;
  case 'D':
  idn2=4;
  break;
  case 'E':
  idn2=5;
  break;
  case 'F':
  idn2=6;
  break;
  case 'G':
  idn2=7;
  break;
  case 'H':
  idn2=8;
  break;
  }
}


void __fastcall TForm1::Open1Click(TObject *Sender)
{
SelectDirectory("","",FileName1);
sOpenDialog1->Execute();
sOpenDialog1->InitialDir = FileName1;
//ShowMessage(sOpenDialog1->FileName);
FileName2=sOpenDialog1->FileName;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::E1Click(TObject *Sender)
{
AnsiString excl1 = (AnsiString)mExcel;
if (excl1!="") mExcel.OleProcedure("Quit");
 Form1->Close();
}
//---------------------------------------------------------------------------

