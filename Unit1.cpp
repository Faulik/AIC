//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#include <urlmon.h>
#include <iostream>
#include <string>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
TForm1 *Form1;


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{}
void __fastcall TForm1::ICMPReply(TComponent *ASender,
      const TReplyStatus &AReplyStatus)
{
AnsiString sTime, result;
     if(AReplyStatus.MsRoundTripTime == 0)
        {sTime = "<1";}
        else
        {sTime = "=";}
     result = IntToStr(AReplyStatus.MsRoundTripTime);
     Label1->Caption=("Ping" + sTime + result + " ms");
for(int i=48;i>0;i--){
        MasPing[i]=MasPing[i-1];
}
MasPing[0]=result.ToDouble();
MaxPing=0;
for(int i=0;i<50;i++){
        if(MasPing[i]>MaxPing)MaxPing=MasPing[i];
}
Series1->AddY(result.ToDouble());
Application->ProcessMessages();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
ICMP->Ping();
Application->ProcessMessages();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
Form1->Left=GetSystemMetrics(SM_CXSCREEN)-Form1->Width;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Chart1BeforeDrawAxes(TObject *Sender)
{
while(Chart1->RightAxis->Maximum<MaxPing){
Chart1->RightAxis->Maximum+=50;
Chart1->RightAxis->Increment=(int)Chart1->RightAxis->Maximum/10;
}
while(Chart1->RightAxis->Maximum>MaxPing+50){
Chart1->RightAxis->Maximum-=50;
Chart1->RightAxis->Increment=(int)Chart1->RightAxis->Maximum/10;
}
if(Series1->XValues->Count()>=50){
Chart1->BottomAxis->Maximum++;
 Chart1->BottomAxis->Minimum++;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
Perform(WM_NCLBUTTONDOWN,HTCAPTION,NULL);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
XMLDocument1->LoadFromFile("http://www.aionlegend.ru/xml/status.xml");
XMLDocument1->Active = true;
Label3->Caption="Online:"+XMLDocument1->DocumentElement->ChildNodes->Nodes[WideString("servers")]->ChildNodes->Nodes[WideString("game")]->GetAttribute(WideString("online"));
Label4->Caption="Siel:"+XMLDocument1->DocumentElement->ChildNodes->Nodes[WideString("servers")]->ChildNodes->Nodes[WideString("game")]->GetAttribute(WideString("status"));
Label5->Caption="Login:"+XMLDocument1->DocumentElement->ChildNodes->Nodes[WideString("login")]->GetAttribute(WideString("status"));
XMLDocument1->Active = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TrayIcon1Click(TObject *Sender)
{
Form1->Show();
}
//--------------------------------------------------------------------------
void __fastcall TForm1::Close1Click(TObject *Sender)
{
 Form1->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Hide1Click(TObject *Sender)
{
Form1->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StayOnTop1Click(TObject *Sender)
{
StayOnTop1->Checked=!StayOnTop1->Checked;
if(StayOnTop1->Checked==true)
Form1->FormStyle=fsStayOnTop;
else Form1->FormStyle=fsNormal;
}
//---------------------------------------------------------------------------

