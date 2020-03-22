//---------------------------------------------------------------------------

#ifndef formCdH
#define formCdH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <MPlayer.hpp>
//---------------------------------------------------------------------------
class TfrmCd : public TForm
{
__published:	// IDE-managed Components
        TMediaPlayer *MediaPlayer1;
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmCd(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCd *frmCd;
//---------------------------------------------------------------------------
#endif
