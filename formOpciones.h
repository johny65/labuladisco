//---------------------------------------------------------------------------

#ifndef formOpcionesH
#define formOpcionesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TfrmOpciones : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TBevel *Bevel1;
        TGroupBox *GroupBox1;
        TButton *cmdOk;
        TButton *cmdCancelar;
        TCheckBox *chkRecordarLista;
        TGroupBox *GroupBox2;
        TRadioButton *rbdCrema;
        TRadioButton *rbdRojo;
        TRadioButton *rbdAzul;
        TRadioButton *rbdBlanco;
        TRadioButton *rbdVerde;
        TGroupBox *GroupBox3;
        TLabel *Label2;
        TEdit *txtTamTiempo;
        TLabel *Label3;
        TEdit *txtTamEtiqueta;
        TImage *Image1;
        TBevel *Bevel2;
        TCheckBox *chkConfirmar;
        void __fastcall cmdCancelarClick(TObject *Sender);
        void __fastcall cmdOkClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall txtTamTiempoExit(TObject *Sender);
        void __fastcall txtTamTiempoKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall txtTamEtiquetaExit(TObject *Sender);
        void __fastcall txtTamEtiquetaKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmOpciones(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmOpciones *frmOpciones;
//---------------------------------------------------------------------------
#endif
