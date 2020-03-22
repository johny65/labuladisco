//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <Graphics.hpp>
#include <jpeg.hpp>
#include <MPlayer.hpp>
#include "trayicon.h"
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
        TScrollBar *scroll1;
        TTimer *Timer1;
        TOpenDialog *open1;
        TLabel *lblPistaActual;
        TTimer *TmrCartel;
        TSaveDialog *save1;
        TSpeedButton *cmdPlay;
        TSpeedButton *cmdStop;
        TSpeedButton *cmdPausa;
        TSpeedButton *cmdAnt;
        TSpeedButton *cmdSig;
        TListView *list1;
        TImageList *LImagenes;
        TTrackBar *trackPan;
        TTrackBar *scrollVol;
        TLabel *lblKbps;
        TPopupMenu *popList;
        TMenuItem *mnuEliminar;
        TMenuItem *mnuLimpiar;
        TMenuItem *N1;
        TMenuItem *mnuAgregar;
        TMenuItem *mnuPlay;
        TLabel *lblMonoEstereo;
        TLabel *lblBits;
        TLabel *lblHz;
        TOpenDialog *open2;
        TLabel *lbl2;
        TMainMenu *MainMenu1;
        TMenuItem *mnuArchivo;
        TMenuItem *mnuAbrir;
        TMenuItem *mnuAbrirLista;
        TMenuItem *mnuGuardarLista;
        TMenuItem *mnuSalir;
        TMenuItem *mnuControl;
        TMenuItem *mnuReproducir;
        TMenuItem *mnuPausar;
        TMenuItem *mnuSig;
        TMenuItem *mnuAnt;
        TMenuItem *mnuDetener;
        TMenuItem *mnuOpciones;
        TMenuItem *mnuPref;
        TMenuItem *mnuVer;
        TMenuItem *mnuTiempoT;
        TMenuItem *mnuTiempoR;
        TMenuItem *mnuAyuda;
        TMenuItem *mnuManual;
        TMenuItem *mnuManualRef;
        TMenuItem *mnuAcerca;
        TBevel *Bevel1;
        TImage *imgVol;
        TImage *imgNoVol;
        TImage *imgBalIzq;
        TImage *imgBalDer;
        TLabel *Label1;
        TLabel *Label2;
        TSpeedButton *cmdAbrir;
        TSpeedButton *CmdGuardar;
        TSpeedButton *cmdLimpiar;
        TSpeedButton *cmdAgregarDir;
        TSpeedButton *cmdCDA;
        TSpeedButton *cmdAgregar;
        TSpeedButton *cmdAbrirLista;
        TSpeedButton *cmdSalir;
        TSpeedButton *cmdAyuda;
        TImageList *imgMenu;
        TMenuItem *N2;
        TLabel *Label3;
        TLabel *Label4;
        TPopupMenu *popBalance;
        TMenuItem *mnuBalanceCentrar;
        TMenuItem *N3;
        TMenuItem *mnuBalanceIzquierda;
        TMenuItem *mnuBalanceDerecha;
        TTrayIcon *tray1;
        TPopupMenu *popTray;
        TMenuItem *mnuTrayPlay;
        TMenuItem *mnuTrayPausa;
        TMenuItem *mnuTrayStop;
        TMenuItem *mnuTrayAnt;
        TMenuItem *mnuTraySig;
        TMenuItem *N4;
        TMenuItem *mnuTrayShow;
        TMenuItem *N5;
        TMenuItem *mnuTraySalir;
        TMenuItem *mnuAgregarArch;
        TMenuItem *AgregarCarpeta1;
        TMenuItem *mnuOrdenar;
        TMenuItem *mnuOrdenarTitulo;
        TMenuItem *mnuOrdenarArtista;
        TMenuItem *mnuOrdenarAlbum;
        TMenuItem *mnuOrdenarAnio;
        TMenuItem *N6;
        void __fastcall cmdPlayClick(TObject *Sender);
        void __fastcall scroll1Change(TObject *Sender);
        void __fastcall cmdStopClick(TObject *Sender);
        void __fastcall cmdPausaClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall scroll1Scroll(TObject *Sender,
          TScrollCode ScrollCode, int &ScrollPos);
        void __fastcall cmdAgregarClick(TObject *Sender);
        void __fastcall list1DblClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall cmdSigClick(TObject *Sender);
        void __fastcall cmdAntClick(TObject *Sender);
        void __fastcall TmrCartelTimer(TObject *Sender);
        void __fastcall CmdGuardarClick(TObject *Sender);
        void __fastcall cmdCDAClick(TObject *Sender);
        void __fastcall list1KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall list1SelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
        void __fastcall trackPanChange(TObject *Sender);
        void __fastcall scrollVolChange(TObject *Sender);
        void __fastcall cmdLimpiarClick(TObject *Sender);
        void __fastcall mnuEliminarClick(TObject *Sender);
        void __fastcall mnuLimpiarClick(TObject *Sender);
        void __fastcall popListPopup(TObject *Sender);
        void __fastcall mnuAgregarClick(TObject *Sender);
        void __fastcall mnuPlayClick(TObject *Sender);
        void __fastcall cmdAbrirClick(TObject *Sender);
        void __fastcall cmdAbrirListaClick(TObject *Sender);
        void __fastcall lbl2Click(TObject *Sender);
        void __fastcall imgVolClick(TObject *Sender);
        void __fastcall cmdAgregarDirClick(TObject *Sender);
        void __fastcall mnuAbrirClick(TObject *Sender);
        void __fastcall mnuAbrirListaClick(TObject *Sender);
        void __fastcall mnuGuardarListaClick(TObject *Sender);
        void __fastcall mnuSalirClick(TObject *Sender);
        void __fastcall mnuReproducirClick(TObject *Sender);
        void __fastcall mnuPausarClick(TObject *Sender);
        void __fastcall mnuSigClick(TObject *Sender);
        void __fastcall mnuAntClick(TObject *Sender);
        void __fastcall mnuDetenerClick(TObject *Sender);
        void __fastcall mnuTiempoTClick(TObject *Sender);
        void __fastcall mnuTiempoRClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall cmdSalirClick(TObject *Sender);
        void __fastcall mnuPrefClick(TObject *Sender);
        void __fastcall imgBalIzqClick(TObject *Sender);
        void __fastcall imgBalDerClick(TObject *Sender);
        void __fastcall mnuBalanceCentrarClick(TObject *Sender);
        void __fastcall mnuBalanceIzquierdaClick(TObject *Sender);
        void __fastcall mnuBalanceDerechaClick(TObject *Sender);
        void __fastcall tray1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall mnuTraySalirClick(TObject *Sender);
        void __fastcall mnuTrayShowClick(TObject *Sender);
        void __fastcall mnuTrayPlayClick(TObject *Sender);
        void __fastcall mnuTrayPausaClick(TObject *Sender);
        void __fastcall mnuTrayStopClick(TObject *Sender);
        void __fastcall mnuTrayAntClick(TObject *Sender);
        void __fastcall mnuTraySigClick(TObject *Sender);
        void __fastcall mnuAgregarArchClick(TObject *Sender);
        void __fastcall AgregarCarpeta1Click(TObject *Sender);
        void __fastcall mnuOrdenarArtistaClick(TObject *Sender);
        void __fastcall mnuOrdenarTituloClick(TObject *Sender);
        void __fastcall mnuOrdenarAlbumClick(TObject *Sender);
        void __fastcall mnuOrdenarAnioClick(TObject *Sender);
        void __fastcall list1ColumnClick(TObject *Sender,
          TListColumn *Column);
        void __fastcall mnuAcercaClick(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall mnuManualClick(TObject *Sender);
        void __fastcall mnuManualRefClick(TObject *Sender);
        void __fastcall cmdAyudaClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmMain(TComponent* Owner);

        //variables globales
        char *ExeDir;
        bool tiempo;
        bool recordar_lista;
        bool confirmar_salir;

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
