//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "formAcerca.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmAcerca *frmAcerca;
//---------------------------------------------------------------------------
__fastcall TfrmAcerca::TfrmAcerca(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmAcerca::Button1Click(TObject *Sender)
{
        frmAcerca->Close();
}
//---------------------------------------------------------------------------

