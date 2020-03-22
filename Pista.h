//Clase Pista
//Representa cada elemento de la lista de reproducción
//---------------------------------------------------------------------------

#ifndef PistaH
#define PistaH
//---------------------------------------------------------------------------
#endif

#include <vcl.h>
#include <string>

//---------------------------------------------------------------------------

using namespace std;

class Pista {
        string RutaArchivo;
        unsigned int DuracionMS;
        AnsiString Duracion;
        AnsiString CriterioComp;
        AnsiString Artista;
        AnsiString Album;
        AnsiString Titulo;
        AnsiString Anio;
public:
        void setRuta(const char *RutaDelArchivo){ RutaArchivo = RutaDelArchivo;};
        string getRuta(){ return RutaArchivo;};
        void setDuracion(unsigned int Milisegundos);
        unsigned int getDuracionMS(){ return DuracionMS;};
        AnsiString getDuracion(){ return Duracion;};
        friend bool operator < (const Pista &P1, const Pista &P2);
        friend bool operator > (const Pista &P1, const Pista &P2);
        void setCriterioTitulo();
        void setCriterioArtista();
        void setCriterioAnio();
        void setCriterioAlbum();
        void liberarCriterio();
        void cargar_datos(char *ar, char *al, char *ti, char *an);
        AnsiString obtener_artista(){ return Artista;};
        AnsiString obtener_album(){ return Album;};
        AnsiString obtener_titulo(){ return Titulo;};
        AnsiString obtener_anio(){ return Anio;};
};

