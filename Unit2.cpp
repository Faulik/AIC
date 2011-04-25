//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
TIniFile *Ini = new TIniFile("c:/AicOptions.ini");
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormMouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
ReleaseCapture();
SendMessage(Form2->Handle, WM_NCLBUTTONDOWN, HTCAPTION, 0);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
Form1->TrayIcon1->Visible = false;
Ini->WriteInteger("Position","Top",Form2->Top);
Ini->WriteInteger("Position","Left",Form2->Left);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormCreate(TObject *Sender)
{
if(Ini->SectionExists("Position")){
Form2->Top=Ini->ReadInteger("Position","Top",0);
Form2->Left=Ini->ReadInteger("Position","Left",0);
}
 SetWindowLong(Application->Handle, GWL_EXSTYLE, WS_EX_TOOLWINDOW);
 }
//---------------------------------------------------------------------------
