//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "formEspere.h"
#include "formCd.h"
#include "formOpciones.h"
#include "formAcerca.h"

#include "ListaRep.h"

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <FileCtrl.hpp>
#include <dir.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"

using namespace std;

TfrmMain *frmMain;


//variables globales---------------------------------------------------------
//(las variables para las opciones están en Main.h)
Sistema Sonido;
int indice, indiceActual;
string CancionActual, Cartel;
ListaRep Lista;
TListItem *ItemPlaying;


//funciones------------------------------------------------------------------

void ActCancionActual();
void DetenerReproduccion();
void IniciarReproduccion(int i);


//implementaciones-----------------------------------------------------------

void ActCancionActual()
{
        if (frmMain->list1->Items->Item[indiceActual]->SubItems->Strings[2] == "")
                CancionActual += frmMain->list1->Items->Item[indiceActual]->SubItems->Strings[0].c_str();
        else {
                CancionActual = frmMain->list1->Items->Item[indiceActual]->SubItems->Strings[2].c_str();
                CancionActual += " - ";
                CancionActual += frmMain->list1->Items->Item[indiceActual]->SubItems->Strings[0].c_str();
        }
        CancionActual += " (";
        CancionActual += frmMain->list1->Items->Item[indiceActual]->SubItems->Strings[1].c_str();
        CancionActual += ")";
}


void DetenerReproduccion()
{
        frmMain->Timer1->Enabled = false;
        Sonido.Detener();
        frmMain->scroll1->Position = 0;
        frmMain->scroll1->Enabled = false;
        frmMain->tray1->Hint = CancionActual.c_str(); frmMain->tray1->Hint = frmMain->tray1->Hint + " (Detenido)... ";
        Cartel = frmMain->tray1->Hint.c_str();
        frmMain->lbl2->Caption = "-- --";
        if (ItemPlaying != NULL) ItemPlaying->ImageIndex = 0;
        frmMain->lblBits->Caption = "";
        frmMain->lblHz->Caption = "";
        frmMain->lblMonoEstereo->Caption = "";
        frmMain->lblKbps->Caption = "";

}


void IniciarReproduccion(int i)
{
        if (!Sonido.Reproducir(Lista[i].getRuta().c_str())) return;
        Sonido.SetVolumen(frmMain->scrollVol->Position);
        Sonido.SetBalance(frmMain->trackPan->Position);

        frmMain->scroll1->Enabled = true;
        frmMain->scroll1->Max = Lista[i].getDuracionMS();

        frmMain->Timer1->Enabled = true;

        ActCancionActual();
        Cartel = CancionActual + " --- ";

        int canales, bits;
        float frecuencia;
        Sonido.GetInfoFormato(&canales, &bits, &frecuencia);
        frmMain->lblBits->Caption = bits; frmMain->lblBits->Caption = frmMain->lblBits->Caption + " bits";
        frmMain->lblHz->Caption = frecuencia;
        //mono o estéreo?
        if (canales==2)
                frmMain->lblMonoEstereo->Caption = "Estéreo";
        else if (canales==1)
                frmMain->lblMonoEstereo->Caption = "Mono";

}









//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::cmdPlayClick(TObject *Sender)
{
        if (scroll1->Enabled==true) //está pausado o reproduciéndose
        {
                if(Sonido.GetPausa()==true){ //está pausado, continuar la reproducción
                        Sonido.Continuar();
                        Timer1->Enabled = true;
                        if (ItemPlaying != NULL) ItemPlaying->ImageIndex = 1;
                        tray1->Hint = CancionActual.c_str();
                        Cartel = tray1->Hint.c_str(); Cartel += " --- ";
                }
                else{ //está reproduciendo, que empiece de nuevo
                        if (list1->Items->Count==0) return; //si la lista está vacía no hace nada
                        IniciarReproduccion(indice);
                        if (ItemPlaying != NULL) ItemPlaying->ImageIndex = 0;
                        indiceActual = indice;
                        ItemPlaying = list1->Items->Item[indiceActual];
                        ItemPlaying->ImageIndex = 1;
                        tray1->Hint = CancionActual.c_str();
                }
        }
        else //está detenido
        {
                if (list1->Items->Count==0) return; //si la lista está vacía no hace nada
                IniciarReproduccion(indice);
                indiceActual = indice;
                ItemPlaying = list1->Items->Item[indiceActual];
                ItemPlaying->ImageIndex = 1;
                tray1->Hint = Cartel.c_str();
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::scroll1Change(TObject *Sender)
{
        if (tiempo==true) //tiempo transcurrido
        {
                lbl2->Caption = (scroll1->Position/1000)/60;
                lbl2->Caption = lbl2->Caption + ":";
                if (((scroll1->Position/1000)%60)>9)
                        lbl2->Caption = lbl2->Caption + (scroll1->Position/1000)%60;
                else
                        lbl2->Caption = lbl2->Caption + "0" + (scroll1->Position/1000)%60;
        }
        else //tiempo restante
        {
                lbl2->Caption = "- ";
                lbl2->Caption = lbl2->Caption + ((scroll1->Max - scroll1->Position)/1000)/60;
                lbl2->Caption = lbl2->Caption + ":";
                if ((((scroll1->Max - scroll1->Position)/1000)%60)>9)
                        lbl2->Caption = lbl2->Caption + ((scroll1->Max - scroll1->Position)/1000)%60;
                else
                        lbl2->Caption = lbl2->Caption + "0" + ((scroll1->Max - scroll1->Position)/1000)%60;
        }

        //pasar a la siguiente canción
        if (scroll1->Position==scroll1->Max)
        {
                if (indiceActual<(list1->Items->Count-1)) //si no está en la última canción
                {
                        scroll1->Position = 0;
                        lbl2->Caption = "0:00";
                        indiceActual++;
                        IniciarReproduccion(indiceActual);
                        if (ItemPlaying != NULL) ItemPlaying->ImageIndex = 0;
                        ItemPlaying = list1->Items->Item[indiceActual];
                        ItemPlaying->ImageIndex = 1;
                        tray1->Hint = CancionActual.c_str();
                }
                else //terminó la lista
                {
                        DetenerReproduccion();
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::cmdStopClick(TObject *Sender)
{
        if (scroll1->Enabled == false) return; //si no hay nada reproduciéndose, que no haga nada
        DetenerReproduccion();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::cmdPausaClick(TObject *Sender)
{
        if (scroll1->Enabled == false) return; //si la reproducción está detenida, no hace nada

        if (Sonido.GetPausa()==false){
                Sonido.Pausar();
                Timer1->Enabled = false;
                if (ItemPlaying != NULL) ItemPlaying->ImageIndex = 2;
                tray1->Hint = CancionActual.c_str(); tray1->Hint = tray1->Hint + " (Pausado)... ";
                Cartel = tray1->Hint.c_str();
        }
        else {
                Sonido.Continuar();
                Timer1->Enabled = true;
                if (ItemPlaying != NULL) ItemPlaying->ImageIndex = 1;
                tray1->Hint = CancionActual.c_str();
                Cartel = tray1->Hint.c_str(); Cartel += " --- ";
        }

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Timer1Timer(TObject *Sender)
{
        scroll1->Position = Sonido.GetPosicion();
        lblKbps->Caption = Sonido.GetKbps();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::scroll1Scroll(TObject *Sender,
      TScrollCode ScrollCode, int &ScrollPos)
{
        Sonido.SetPosicion(scroll1->Position);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::cmdAgregarClick(TObject *Sender)
{
        open1->Title = "Seleccionar archivo(s) para agregar a la lista";
        if (open1->Execute()==true){ //no apretó Cancelar
                frmEspere->Show(); frmEspere->Repaint();
                Lista.AgregarArchivos(open1->Files->Text.c_str(), open1->Files->Count, list1);
                frmEspere->Close();
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::list1DblClick(TObject *Sender)
{
        if (list1->SelCount == 0) return; //si no hay nada seleccionado que no haga nada

        if (ItemPlaying != NULL) ItemPlaying->ImageIndex = 0;
        indiceActual = list1->ItemIndex;
        ItemPlaying = list1->Items->Item[indiceActual];
        IniciarReproduccion(indiceActual);
        ItemPlaying->ImageIndex = 1;
        tray1->Hint = CancionActual.c_str();
        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
        //iniciar controles comunes
        InitCommonControls();

        //encontrar la ruta del programa
        string temp = Application->ExeName.c_str();
        temp = temp.substr(0, temp.rfind("\\")+1);
        ExeDir = new char[temp.length()+1];
        strcpy(ExeDir, temp.c_str());

        //cargar las opciones
        AnsiString r = ExeDir; r += "pref.cfg";
        int n;
        ifstream opciones(r.c_str(), ios::binary);
        opciones.seekg(0, ios::beg);
        opciones.read((char*)&recordar_lista, 1);
        opciones.read((char*)&tiempo, 1);
        opciones.read((char*)&n, sizeof(int));
        scrollVol->Position = n;
        opciones.read((char*)&n, sizeof(int));
        trackPan->Position = n;
        TColor color;
        opciones.read((char*)&color, sizeof(TColor));
        frmMain->Color = color;
        opciones.read((char*)&n, sizeof(int));
        lbl2->Font->Size = n;
        opciones.read((char*)&n, sizeof(int));
        lblPistaActual->Font->Size = n;
        opciones.read((char*)&confirmar_salir, 1);        
        opciones.close();

        indice = indiceActual = 0;
        Cartel = "Bienvenido a LaBulaDisco Reproductor de Audio 0.1b --- ";
        lbl2->Caption = "-- --";

        mnuTiempoT->Checked = tiempo;
        mnuTiempoR->Checked = !tiempo;
        scrollVol->Hint = "Volumen: "; scrollVol->Hint += scrollVol->Position;

        Sonido.Inicializar();
        Lista.Inicializar(&Sonido);

        if (Application->Hint != ""){
                AnsiString abriendo = Application->Hint;
                Application->Hint = "";
                if (abriendo[1] == '\"' && abriendo[abriendo.Length()] == '\"')
                        abriendo = abriendo.SubString(2, abriendo.Length()-2);
                cmdLimpiarClick(Sender);
                Lista.AbrirListaLabula(abriendo.c_str(), list1);
                cmdPlayClick(Sender);
        }
        else if (recordar_lista == true){
                AnsiString l = ExeDir; l += "default.lbd";
                Lista.AbrirListaLabula(l.c_str(), list1);
        }

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::cmdSigClick(TObject *Sender)
{
        if (indiceActual<(list1->Items->Count)-1) //si no está en la última canción
        {
                indiceActual++;
                IniciarReproduccion(indiceActual);
                if (ItemPlaying != NULL) ItemPlaying->ImageIndex = 0;
                ItemPlaying = list1->Items->Item[indiceActual];
                ItemPlaying->ImageIndex = 1;
                tray1->Hint = CancionActual.c_str();
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::cmdAntClick(TObject *Sender)
{
        if (indiceActual !=0) //si no está en la primer canción
        {
                indiceActual--;
                IniciarReproduccion(indiceActual);
                if (ItemPlaying != NULL) ItemPlaying->ImageIndex = 0;
                ItemPlaying = list1->Items->Item[indiceActual];
                ItemPlaying->ImageIndex = 1;
                tray1->Hint = CancionActual.c_str();

        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::TmrCartelTimer(TObject *Sender)
{
        char aux = Cartel[0];
        Cartel.erase(0,1);
        Cartel+=aux;
        lblPistaActual->Caption = Cartel.c_str();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::CmdGuardarClick(TObject *Sender)
{
        if (list1->Items->Count == 0){
                Application->MessageBoxA("La lista de reproducción está vacía.", "Lista vacía", MB_ICONINFORMATION | MB_OK);
                return;
        }

        if (save1->Execute()) //no apretó cancelar
        {
                if (save1->FilterIndex == 1) //eligió m3u
                        Lista.GuardarListaM3u(save1->FileName.c_str());
                else if (save1->FilterIndex == 2) //eligió pls
                        Lista.GuardarListaPls(save1->FileName.c_str());
                else if (save1->FilterIndex == 3) //eligió labula
                        Lista.GuardarListaLabula(save1->FileName.c_str());
        } //del if

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::cmdCDAClick(TObject *Sender)
{
       frmMain->Hide();
       frmCd->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::list1KeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        switch (Key){
                //apreté Supr
                case VK_DELETE: mnuEliminarClick(Sender); break;
                //apreté Enter
                case VK_RETURN: list1DblClick(Sender); break;
                //apreté Espacio
                case VK_SPACE: if (ItemPlaying != NULL) ItemPlaying->Focused = true;
        }

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::list1SelectItem(TObject *Sender, TListItem *Item,
      bool Selected)
{
        if (list1->SelCount!=0)
                indice=list1->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::trackPanChange(TObject *Sender)
{
        Sonido.SetBalance(trackPan->Position);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::scrollVolChange(TObject *Sender)
{
        Sonido.SetVolumen(scrollVol->Position);
        if (scrollVol->Position == 0){
                imgVol->Visible = false;
                imgNoVol->Visible = true;
        }
        else {
                imgVol->Visible = true;
                imgNoVol->Visible = false;
        }
        scrollVol->Hint = "Volumen: "; scrollVol->Hint += scrollVol->Position;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::cmdLimpiarClick(TObject *Sender)
{
        list1->Clear();
        Lista.Limpiar();
        indice = indiceActual = 0; //reiniciar los índices
        ItemPlaying = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuEliminarClick(TObject *Sender)
{
        //si no hay nada seleccionado no hace nada
        if (list1->SelCount == 0) return;

        //eliminar los elementos de la lista
        int seleccionados=list1->SelCount;
        for (int i=1; i<=seleccionados; i++){
                if (list1->Selected == ItemPlaying)
                        ItemPlaying = NULL;
        }
        Lista.Eliminar(list1);

        //acomodar el índice actual
        if (list1->Items->Count == 0) //si eliminé todos los elementos, que reinicie los índices
                indice = indiceActual = 0;
        else {
                if (ItemPlaying != NULL)
                        indiceActual = ItemPlaying->Index;
                else
                        indiceActual = list1->ItemFocused->Index;
        }

        //acomodar los números de la lista
        for (int i=0; i<list1->Items->Count; i++)
                list1->Items->Item[i]->Caption = i+1;

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuLimpiarClick(TObject *Sender)
{
        cmdLimpiarClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::popListPopup(TObject *Sender)
{
        mnuEliminar->Enabled = true;
        mnuPlay->Enabled = true;
        if (list1->SelCount == 0){
                mnuEliminar->Enabled = false;
                mnuPlay->Enabled = false;
        }

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuAgregarClick(TObject *Sender)
{
        cmdAgregarClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuPlayClick(TObject *Sender)
{
        list1DblClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::cmdAbrirClick(TObject *Sender)
{
        open1->Title = "Abrir archivo(s)";
        if (open1->Execute())
        {
                cmdLimpiarClick(Sender);
                frmEspere->Show(); frmEspere->Repaint();
                Lista.AgregarArchivos(open1->Files->Text.c_str(), open1->Files->Count, list1);
                frmEspere->Close();
                cmdPlayClick(Sender);
        }

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::cmdAbrirListaClick(TObject *Sender)
{
        if (open2->Execute())
        {
                if (open2->FilterIndex == 1) //formato m3u
                {
                        frmEspere->Show(); frmEspere->Repaint();
                        Lista.AbrirListaM3u(open2->FileName.c_str(), list1);
                        frmEspere->Close();
                }
                else if (open2->FilterIndex == 2) //formato pls
                {
                        frmEspere->Show(); frmEspere->Repaint();
                        Lista.AbrirListaPls(open2->FileName.c_str(), list1);
                        frmEspere->Close();
                }
                else if (open2->FilterIndex == 3){ //formato labula
                        Lista.AbrirListaLabula(open2->FileName.c_str(), list1);
                }
        }

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::lbl2Click(TObject *Sender)
{
        tiempo = !tiempo;
        mnuTiempoT->Checked=!mnuTiempoT->Checked;
        mnuTiempoR->Checked=!mnuTiempoR->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::imgVolClick(TObject *Sender)
{
        scrollVol->Position = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::cmdAgregarDirClick(TObject *Sender)
{
        AnsiString carpeta = "";
        if (SelectDirectory("Selecciona una carpeta para agregar", "", carpeta)){
                if (carpeta[carpeta.Length()] != '\\')
                        carpeta+='\\';
                string carpeta_asterisco = carpeta.c_str(); carpeta_asterisco+='*';
                ffblk estruct;
                int res, n=0;
                string archivos = ""; //acá se van a acumular todos los archivos de la carpeta

                res = findfirst(carpeta_asterisco.c_str(), &estruct, FA_RDONLY | FA_HIDDEN | FA_SYSTEM | FA_ARCH); //busco el primer archivo
                while(!res) //mientras encuentre archivos
                {
                        if (estruct.ff_attrib&FA_ARCH) //si es un archivo
                        {
                                archivos+=carpeta.c_str();
                                archivos+=estruct.ff_name;
                                archivos+="\r\n";
                                n++;
                        }
                        res = findnext(&estruct); //busco el siguiente archivo
                }

                //ahora agregar los archivos
                char *la = new char[archivos.length()+1];
                strcpy(la, archivos.c_str());
                frmEspere->Show(); frmEspere->Repaint();
                Lista.AgregarArchivos(la, n, list1);
                delete[] la;
                frmEspere->Close();
        }

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuAbrirClick(TObject *Sender)
{
        cmdAbrirClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuAbrirListaClick(TObject *Sender)
{
        cmdAbrirListaClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuGuardarListaClick(TObject *Sender)
{
        CmdGuardarClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuSalirClick(TObject *Sender)
{
        cmdSalirClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuReproducirClick(TObject *Sender)
{
        cmdPlayClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuPausarClick(TObject *Sender)
{
        cmdPausaClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuSigClick(TObject *Sender)
{
        cmdSigClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuAntClick(TObject *Sender)
{
        cmdAntClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuDetenerClick(TObject *Sender)
{
        cmdStopClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuTiempoTClick(TObject *Sender)
{
        lbl2Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuTiempoRClick(TObject *Sender)
{
        lbl2Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormClose(TObject *Sender, TCloseAction &Action)
{
        /*variables de opciones:
                - bool recordar_lista
                - bool tiempo
                - int vol
                - int balance
                - TColor color;
                - int tam_tiempo
                - int tam_cartel
                - bool confirmar_salir
        */

        Sonido.Detener();

        //guardar las opciones
        AnsiString r = ExeDir; r += "pref.cfg";
        int temp;
        ofstream salida(r.c_str(), ios::binary);
        salida.seekp(0, ios::beg);
        salida.write((char*)&recordar_lista, 1);
        salida.write((char*)&tiempo, 1);
        temp = scrollVol->Position;
        salida.write((char*)&temp, sizeof(int));
        temp = trackPan->Position;
        salida.write((char*)&temp, sizeof(int));
        TColor color = frmMain->Color;
        salida.write((char*)&color, sizeof(TColor));
        temp = lbl2->Font->Size;
        salida.write((char*)&temp, sizeof(int));
        temp = lblPistaActual->Font->Size;
        salida.write((char*)&temp, sizeof(int));
        salida.write((char*)&confirmar_salir, 1);
        salida.close();

        if (recordar_lista == true){
                AnsiString l = ExeDir; l += "default.lbd";
                if (list1->Items->Count == 0){
                        ofstream lr(l.c_str(), ios::binary | ios::trunc);
                        char header[4] = "LBD";
                        lr.seekp(0, ios::beg);
                        lr.write(header, 4);
                        int cant = 0;
                        lr.write((char*)&cant, sizeof(int));
                        lr.close();
                }
                else Lista.GuardarListaLabula(l.c_str());
        }

        delete[] ExeDir;
        Application->Terminate();

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::cmdSalirClick(TObject *Sender)
{

        frmMain->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuPrefClick(TObject *Sender)
{
        frmOpciones->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::imgBalIzqClick(TObject *Sender)
{
        trackPan->Position = -100;        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::imgBalDerClick(TObject *Sender)
{
        trackPan->Position = 100;        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuBalanceCentrarClick(TObject *Sender)
{
        trackPan->Position = 0;        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuBalanceIzquierdaClick(TObject *Sender)
{
        trackPan->Position = -100;        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuBalanceDerechaClick(TObject *Sender)
{
        trackPan->Position = 100;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::tray1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        if (Button == mbLeft)
                tray1->Restore();

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuTraySalirClick(TObject *Sender)
{
        cmdSalirClick(Sender);        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuTrayShowClick(TObject *Sender)
{
        tray1->Restore();        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuTrayPlayClick(TObject *Sender)
{
        cmdPlayClick(Sender);        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuTrayPausaClick(TObject *Sender)
{
        cmdPausaClick(Sender);        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuTrayStopClick(TObject *Sender)
{
        cmdStopClick(Sender);        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuTrayAntClick(TObject *Sender)
{
        cmdAntClick(Sender);        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuTraySigClick(TObject *Sender)
{
        cmdSigClick(Sender);        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuAgregarArchClick(TObject *Sender)
{
        cmdAgregarClick(Sender);                
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::AgregarCarpeta1Click(TObject *Sender)
{
        cmdAgregarDirClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuOrdenarArtistaClick(TObject *Sender)
{
        if (list1->Items->Count == 0) return;
        Lista.ordenar_artista(list1);
        ItemPlaying = NULL;
        indice = indiceActual = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuOrdenarTituloClick(TObject *Sender)
{
        if (list1->Items->Count == 0) return;
        Lista.ordenar_titulo(list1);
        ItemPlaying = NULL;
        indice = indiceActual = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuOrdenarAlbumClick(TObject *Sender)
{
        if (list1->Items->Count == 0) return;
        Lista.ordenar_album(list1);
        ItemPlaying = NULL;
        indice = indiceActual = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuOrdenarAnioClick(TObject *Sender)
{
        if (list1->Items->Count == 0) return;
        Lista.ordenar_anio(list1);
        ItemPlaying = NULL;
        indice = indiceActual = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::list1ColumnClick(TObject *Sender,
      TListColumn *Column)
{
        switch (Column->Index){
                case 1: mnuOrdenarTituloClick(Sender); break;
                case 3: mnuOrdenarArtistaClick(Sender); break;
                case 4: mnuOrdenarAlbumClick(Sender); break;
                case 5: mnuOrdenarAnioClick(Sender);
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuAcercaClick(TObject *Sender)
{
        frmAcerca->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormCloseQuery(TObject *Sender, bool &CanClose)
{
        if (confirmar_salir == true){
                if (Application->MessageBoxA("¿Desea cerrar el programa?", "Confirmación", MB_ICONQUESTION | MB_YESNO) == IDYES){
                        CanClose = true;
                }
                else CanClose = false;
        }

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuManualClick(TObject *Sender)
{
        string archivo = ExeDir;
        archivo += "Manual de Usuario.chm";
        ShellExecute(0, "open", archivo.c_str(), 0, 0, 1);

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mnuManualRefClick(TObject *Sender)
{
        string archivo = ExeDir;
        archivo += "Manual de Referencia.pdf";
        ShellExecute(0, "open", archivo.c_str(), 0, 0, 1);

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::cmdAyudaClick(TObject *Sender)
{
        mnuManualClick(Sender);        
}
//---------------------------------------------------------------------------

