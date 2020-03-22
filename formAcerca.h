//---------------------------------------------------------------------------

#ifndef formAcercaH
#define formAcercaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TfrmAcerca : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TButton *Button1;
        TLabel *Label4;
        TLabel *Label5;
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmAcerca(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAcerca *frmAcerca;
//---------------------------------------------------------------------------
#endif
