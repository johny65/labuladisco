//---------------------------------------------------------------------------

#ifndef ListaRepH
#define ListaRepH
//---------------------------------------------------------------------------
#endif

#include "Pista.h"
#include "Guardando.h"
#include "Sistema.h"

#include <ComCtrls.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

//---------------------------------------------------------------------------

using namespace std;

class ListaRep {
        vector<Pista> Lista;
        Sistema *control;
public:
        void Inicializar(Sistema *VariableSistema);
        void GuardarListaLabula(char *NombreArchivo);
        void GuardarListaM3u(char *NombreArchivo);
        void GuardarListaPls(char *NombreArchivo);
        void AgregarArchivos(char *ListaDeArchivos, int n, TListView *list);
        void AbrirListaLabula(char *NombreArchivo, TListView *list);
        void AbrirListaM3u(char *NombreArchivo, TListView *list);
        void AbrirListaPls(char *NombreArchivo, TListView *list);
        void Eliminar(TListView *list);
        void Limpiar();
        Pista operator [](int indice);
        void Liberar();
        void ordenar_titulo(TListView *list);
        void ordenar_artista(TListView *list);
        void ordenar_anio(TListView *list);
        void ordenar_album(TListView *list);
};

