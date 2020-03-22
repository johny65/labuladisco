//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "formOpciones.h"
#include "Main.h"

#include <fstream>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

using namespace std;

TfrmOpciones *frmOpciones;
//---------------------------------------------------------------------------
__fastcall TfrmOpciones::TfrmOpciones(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmOpciones::cmdCancelarClick(TObject *Sender)
{
        frmOpciones->Close();

}
//---------------------------------------------------------------------------

void __fastcall TfrmOpciones::cmdOkClick(TObject *Sender)
{
        //actualizo las variables de opciones
        frmMain->recordar_lista = chkRecordarLista->Checked;
        frmMain->confirmar_salir = chkConfirmar->Checked;

        if (rbdCrema->Checked == true)
                frmMain->Color = clCream;
        else if (rbdRojo->Checked == true)
                frmMain->Color = clRed;
        else if (rbdAzul->Checked == true)
                frmMain->Color = clBlue;
        else if (rbdBlanco->Checked == true)
                frmMain->Color = clWhite;
        else if (rbdVerde->Checked == true)
                frmMain->Color = clGreen;

        frmMain->lbl2->Font->Size = txtTamTiempo->Text.ToInt();
        frmMain->lblPistaActual->Font->Size = txtTamEtiqueta->Text.ToInt();

        frmOpciones->Close();

}
//---------------------------------------------------------------------------

void __fastcall TfrmOpciones::FormShow(TObject *Sender)
{
        //transfiero las variables de opciones
        txtTamTiempo->Text=frmMain->lbl2->Font->Size;
        txtTamEtiqueta->Text=frmMain->lblPistaActual->Font->Size;
        chkRecordarLista->Checked = frmMain->recordar_lista;
        chkConfirmar->Checked = frmMain->confirmar_salir;
        switch (frmMain->Color){
                case clCream: rbdCrema->Checked = true; break;
                case clRed: rbdRojo->Checked = true; break;
                case clBlue: rbdAzul->Checked = true; break;
                case clWhite: rbdBlanco->Checked = true; break;
                case clGreen: rbdVerde->Checked = true; break;
        }

}
//---------------------------------------------------------------------------

void __fastcall TfrmOpciones::txtTamTiempoExit(TObject *Sender)
{
        if (txtTamTiempo->Text == ""){
                Application->MessageBoxA("Este campo no puede estar vacío. Ingrese un valor.", "Error", MB_ICONEXCLAMATION);
                txtTamTiempo->SetFocus();
                txtTamTiempo->Text=frmMain->lbl2->Font->Size;
        }
        else if (!(txtTamTiempo->Text.ToInt() <= 31 && txtTamTiempo->Text.ToInt() > 0)){
                Application->MessageBoxA("El tamaño máximo de fuente permitido en este campo es 31.", "Error", MB_ICONEXCLAMATION);
                txtTamTiempo->SetFocus();
        }

}
//---------------------------------------------------------------------------

void __fastcall TfrmOpciones::txtTamTiempoKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key == VK_RETURN || Key == VK_BACK || Key == VK_DELETE || Key == VK_HOME || Key == VK_END|| Key == VK_DOWN || Key == VK_UP || Key == VK_LEFT || Key == VK_RIGHT)
                return;

        if (!(Key >= 48 && Key <= 57) && !(Key >= 96 && Key <= 105)) {
                Application->MessageBoxA("Caracter inválido. Sólo se permiten enteros positivos.", "Error", MB_ICONEXCLAMATION);
                txtTamTiempo->Clear();
                txtTamTiempo->SetFocus();
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmOpciones::txtTamEtiquetaExit(TObject *Sender)
{
        if (txtTamEtiqueta->Text == ""){
                Application->MessageBoxA("Este campo no puede estar vacío. Ingrese un valor.", "Error", MB_ICONEXCLAMATION);
                txtTamEtiqueta->SetFocus();
                txtTamEtiqueta->Text=frmMain->lblPistaActual->Font->Size;
        }
        else if (!(txtTamEtiqueta->Text.ToInt() <= 10 && txtTamEtiqueta->Text.ToInt() > 0)){
                Application->MessageBoxA("El tamaño máximo de fuente permitido en este campo es 10.", "Error", MB_ICONEXCLAMATION);
                txtTamEtiqueta->SetFocus();
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmOpciones::txtTamEtiquetaKeyUp(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
        if (Key == VK_RETURN || Key == VK_BACK || Key == VK_DELETE || Key == VK_HOME || Key == VK_END|| Key == VK_DOWN || Key == VK_UP || Key == VK_LEFT || Key == VK_RIGHT)
                return;

        if (!(Key >= 48 && Key <= 57) && !(Key >= 96 && Key <= 105)) {
                Application->MessageBoxA("Caracter inválido. Sólo se permiten enteros positivos.", "Error", MB_ICONEXCLAMATION);
                txtTamEtiqueta->Clear();
                txtTamEtiqueta->SetFocus();
        }
}
//---------------------------------------------------------------------------

