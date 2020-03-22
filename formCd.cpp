//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "formCd.h"
#include "Main.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmCd *frmCd;
//---------------------------------------------------------------------------
__fastcall TfrmCd::TfrmCd(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmCd::FormCloseQuery(TObject *Sender, bool &CanClose)
{
        if (Application->MessageBoxA("¿Confirma que desea salir del modo CD de Audio?", "Confirmación", MB_ICONQUESTION | MB_YESNO) == IDYES){
                CanClose = true;
                MediaPlayer1->Stop();
                frmMain->Show();
        }
        else CanClose = false;

}
//---------------------------------------------------------------------------

