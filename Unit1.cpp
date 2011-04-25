//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#include <iostream>
#include <string>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
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
Application->ProcessMessages();
Series1->AddY(result.ToDouble());
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
ICMP->Ping();
Timer2->OnTimer;
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
ReleaseCapture();
SendMessage(Form1->Handle, WM_NCLBUTTONDOWN, HTCAPTION, 0);

}
//---------------------------------------------------------------------------


void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
XMLDocument1->LoadFromFile("http://www.aionlegend.ru/xml/status.xml");
XMLDocument1->Active = true;
Label3->Caption="Online:"+XMLDocument1->DocumentElement->ChildNodes->Nodes[WideString("servers")]->ChildNodes->Nodes[WideString("game")]->GetAttribute(WideString("online"));
Form2->Label1->Caption="Online:"+XMLDocument1->DocumentElement->ChildNodes->Nodes[WideString("servers")]->ChildNodes->Nodes[WideString("game")]->GetAttribute(WideString("online"));
if((String)XMLDocument1->DocumentElement->ChildNodes->Nodes[WideString("login")]->GetAttribute(WideString("status"))!="on" || (int)XMLDocument1->DocumentElement->ChildNodes->Nodes[WideString("servers")]->ChildNodes->Nodes[WideString("game")]->GetAttribute(WideString("online"))==0 )
Form2->Color=clRed;
else Form2->Color=clLime;
Label4->Caption="Siel:"+XMLDocument1->DocumentElement->ChildNodes->Nodes[WideString("servers")]->ChildNodes->Nodes[WideString("game")]->GetAttribute(WideString("status"));
Label5->Caption="Login:"+XMLDocument1->DocumentElement->ChildNodes->Nodes[WideString("login")]->GetAttribute(WideString("status"));
XMLDocument1->Active = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TrayIcon1Click(TObject *Sender)
{
Form2->Show();
}
//--------------------------------------------------------------------------
void __fastcall TForm1::Close1Click(TObject *Sender)
{
Form2->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Hide1Click(TObject *Sender)
{
Form1->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
ReleaseCapture();
SendMessage(Form1->Handle, WM_NCLBUTTONDOWN, HTCAPTION, 0);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StayOnTop2Click(TObject *Sender)
{
StayOnTop2->Checked=!StayOnTop2->Checked;
if(StayOnTop2->Checked==true)
Form2->FormStyle=fsStayOnTop;
else Form2->FormStyle=fsNormal;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Show1Click(TObject *Sender)
{
Litlebar1->Checked=!Litlebar1->Checked;
if(Litlebar1->Checked==true)
Form2->Show();
else Form2->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Close2Click(TObject *Sender)
{
Form2->Hide();
Litlebar1->Checked=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Show2Click(TObject *Sender)
{
Form1->Show();
}
//---------------------------------------------------------------------------

