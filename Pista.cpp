//---------------------------------------------------------------------------

#pragma hdrstop

#include "Pista.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------

void Pista::setDuracion(unsigned int Milisegundos)
{
        DuracionMS = Milisegundos;
        Duracion = (Milisegundos/1000)/60;
        Duracion += ":";
        if (((Milisegundos/1000)%60)<10){
                Duracion += "0";
                Duracion += (Milisegundos/1000)%60;
        }
        else
                Duracion += (Milisegundos/1000)%60;
}

void Pista::liberarCriterio()
{
        CriterioComp = "";
}


bool operator < (const Pista &P1, const Pista &P2)
{
        return (P1.CriterioComp < P2.CriterioComp);
}


bool operator > (const Pista &P1, const Pista &P2)
{
        return (P1.CriterioComp > P2.CriterioComp);
}


void Pista::cargar_datos(char *ar, char *al, char *ti, char *an)
{
        Artista = ar;
        Album = al;
        Titulo = ti;
        Anio = an;
}


void Pista::setCriterioTitulo()
{
        CriterioComp = Titulo.LowerCase();
}


void Pista::setCriterioArtista()
{
        CriterioComp = Artista.LowerCase();
}


void Pista::setCriterioAnio()
{
        CriterioComp = Anio.LowerCase();
}


void Pista::setCriterioAlbum()
{
        CriterioComp = Album.LowerCase();

}

