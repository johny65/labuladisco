//---------------------------------------------------------------------------

#ifndef formEspereH
#define formEspereH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmEspere : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
private:	// User declarations
public:		// User declarations
        __fastcall TfrmEspere(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmEspere *frmEspere;
//---------------------------------------------------------------------------
#endif
