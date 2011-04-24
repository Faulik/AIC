//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Chart.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Series.hpp>
#include <TeeFunci.hpp>
#include <msxmldom.hpp>
#include <XMLDoc.hpp>
#include <xmldom.hpp>
#include <XMLIntf.hpp>
#include "trayicon.h"
#include <Buttons.hpp>
#include <Menus.hpp>
#include <jpeg.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdIcmpClient.hpp>
#include <IdRawBase.hpp>
#include <IdRawClient.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TIdIcmpClient *ICMP;
        TTimer *Timer1;
        TLabel *Label1;
        TLabel *Label2;
        TChart *Chart1;
        TLineSeries *Series1;
        TTimer *Timer2;
        TLabel *Label3;
        TTrayIcon *TrayIcon1;
        TPopupMenu *PopupMenu1;
        TMenuItem *StayOnTop1;
        TXMLDocument *XMLDocument1;
        TImage *Image1;
        TMenuItem *Close1;
        TMenuItem *Hide1;
        void __fastcall ICMPReply(TComponent *ASender,
          const TReplyStatus &AReplyStatus);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Chart1BeforeDrawAxes(TObject *Sender);
        void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall Timer2Timer(TObject *Sender);
        void __fastcall TrayIcon1Click(TObject *Sender);
        void __fastcall Close1Click(TObject *Sender);
        void __fastcall Hide1Click(TObject *Sender);
        void __fastcall StayOnTop1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
double MaxPing;
double MasPing[50];
        __fastcall TForm1(TComponent* Owner);
protected:
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
