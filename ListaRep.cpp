//---------------------------------------------------------------------------

#pragma hdrstop

#include "ListaRep.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------

void ListaRep::Inicializar(Sistema *VariableSistema)
{
        control = VariableSistema;
}


void ListaRep::GuardarListaLabula(char *NombreArchivo)
{
        string nombrearchivo = NombreArchivo;
        AnsiString aux = nombrearchivo.substr(nombrearchivo.length()-4, 4).c_str();
        aux = aux.LowerCase();
        if (aux!=".lbd")
                nombrearchivo+=".lbd";
        ofstream salida(nombrearchivo.c_str(), ios::binary | ios::trunc);
        if (!salida.is_open()){
                Application->MessageBoxA("No se pudo guardar el archivo.", "Error", MB_ICONERROR);
                return;
        }

        char header[4] = "LBD";
        salida.seekp(0, ios::beg);
        salida.write(header, 4);
        int cant = Lista.size();
        salida.write((char*)&cant, sizeof(int));
        Guardando temp; //"Guardando" tipo especial para guardar la lista
        for (int i=0; i<cant; i++){
                strcpy(temp.ColumnaTitulo, Lista[i].obtener_titulo().c_str());
                strcpy(temp.ColumnaDuracion, Lista[i].getDuracion().c_str());
                strcpy(temp.ColumnaArtista, Lista[i].obtener_artista().c_str());
                strcpy(temp.ColumnaAlbum, Lista[i].obtener_album().c_str());
                strcpy(temp.ColumnaAnio, Lista[i].obtener_anio().c_str());
                temp.DuracionMS = Lista[i].getDuracionMS();
                strcpy(temp.Ruta, Lista[i].getRuta().c_str());

        /*      strcpy(temp.ColumnaTitulo, list->Items->Item[i]->SubItems->Strings[0].c_str());
                strcpy(temp.ColumnaDuracion, list->Items->Item[i]->SubItems->Strings[1].c_str());
                strcpy(temp.ColumnaArtista, list->Items->Item[i]->SubItems->Strings[2].c_str());
                strcpy(temp.ColumnaAlbum, list->Items->Item[i]->SubItems->Strings[3].c_str());
                strcpy(temp.ColumnaAnio, list->Items->Item[i]->SubItems->Strings[4].c_str());
                temp.DuracionMS = Lista[i].getDuracionMS();
                strcpy(temp.Ruta, Lista[i].getRuta().c_str());
        */

                salida.write((char*)&temp, sizeof(Guardando));
        }
        salida.close();

} //fin GuardarListaLabula


void ListaRep::AbrirListaLabula(char *NombreArchivo, TListView *list)
{
        ifstream entrada(NombreArchivo, ios::binary);
        if (!entrada.is_open()){
                Application->MessageBoxA("No se pudo abrir el archivo.", "Error", MB_ICONERROR);
                return;
        }
        char header[4];
        int cont;
        entrada.seekg(0, ios::beg);
        entrada.read(header, 4);
        if (strcmp(header, "LBD") != 0){
                Application->MessageBoxA("Archivo de lista de reproducción inválido.", "Error", MB_ICONERROR);
                return;
        }
        entrada.read((char*)&cont, sizeof(int));

        Guardando temp;
        for (int i=0; i<cont; i++){
                Pista cancion;
                entrada.read((char*)&temp, sizeof(Guardando));
                cancion.setRuta(temp.Ruta);
                cancion.setDuracion(temp.DuracionMS);
                cancion.cargar_datos(temp.ColumnaArtista, temp.ColumnaAlbum, temp.ColumnaTitulo, temp.ColumnaAnio);
                list->AddItem(list->Items->Count+1, list);
                list->Items->Item[list->Items->Count-1]->SubItems->Add(temp.ColumnaTitulo);
                list->Items->Item[list->Items->Count-1]->SubItems->Add(temp.ColumnaDuracion);
                list->Items->Item[list->Items->Count-1]->SubItems->Add(temp.ColumnaArtista);
                list->Items->Item[list->Items->Count-1]->SubItems->Add(temp.ColumnaAlbum);
                list->Items->Item[list->Items->Count-1]->SubItems->Add(temp.ColumnaAnio);
                Lista.push_back(cancion);
        }
        entrada.close();

} //fin AbrirListaLabula


void ListaRep::GuardarListaM3u(char *NombreArchivo)
{
        string nombrearchivo = NombreArchivo;
        AnsiString aux = nombrearchivo.substr(nombrearchivo.length()-4, 4).c_str();
        aux = aux.LowerCase();
        if (aux!=".m3u")
                nombrearchivo+=".m3u";
        string ruta_de_guardado = nombrearchivo.substr(0, nombrearchivo.rfind("\\"));
        ofstream salida(nombrearchivo.c_str(), ios::trunc);
        if (!salida.is_open()){
                Application->MessageBoxA("No se pudo guardar el archivo.", "Error", MB_ICONERROR);
                return;
        }

        salida<<"#EXTM3U\n";
        for (unsigned int i=0; i<Lista.size(); i++)
        {
                salida<<"#EXTINF:"<<Lista[i].getDuracionMS()/1000<<',';
                if (Lista[i].obtener_artista() == "") //no tiene artista
                        salida<<Lista[i].obtener_titulo().c_str()<<'\n';
                else
                        salida<<Lista[i].obtener_artista().c_str()<<" - "<<Lista[i].obtener_titulo().c_str()<<'\n';
                int p = Lista[i].getRuta().rfind("\\");
                string ruta_dela_cancion = Lista[i].getRuta().substr(0, p);
                if (ruta_dela_cancion == ruta_de_guardado)
                        salida<<Lista[i].getRuta().substr(p+1, Lista[i].getRuta().length())<<'\n';
                else
                        salida<<Lista[i].getRuta().c_str()<<'\n';
        }
        salida.close();
}


void ListaRep::GuardarListaPls(char *NombreArchivo)
{
        string nombrearchivo = NombreArchivo;
        AnsiString aux = nombrearchivo.substr(nombrearchivo.length()-4, 4).c_str();
        aux = aux.LowerCase();
        if (aux!=".pls")
                nombrearchivo+=".pls";
        string ruta_de_guardado = nombrearchivo.substr(0, nombrearchivo.rfind("\\"));
        ofstream salida(nombrearchivo.c_str(), ios::trunc);
        if (!salida.is_open()){
                Application->MessageBoxA("No se pudo guardar el archivo.", "Error", MB_ICONERROR);
                return;
        }

        salida<<"[playlist]\n";
        for (unsigned int i=0; i<Lista.size(); i++)
        {
                salida<<"File"<<i+1<<"=";
                int p = Lista[i].getRuta().rfind("\\");
                string ruta_dela_cancion = Lista[i].getRuta().substr(0, p);
                if (ruta_dela_cancion == ruta_de_guardado)
                        salida<<Lista[i].getRuta().substr(p+1, Lista[i].getRuta().length())<<'\n';
                else
                        salida<<Lista[i].getRuta().c_str()<<'\n';
                salida<<"Title"<<i+1<<"=";
                if (Lista[i].obtener_artista() == "") //no tiene artista
                        salida<<Lista[i].obtener_titulo().c_str()<<'\n';
                else
                        salida<<Lista[i].obtener_artista().c_str()<<" - "<<Lista[i].obtener_titulo().c_str()<<'\n';
                salida<<"Length"<<i+1<<"="<<Lista[i].getDuracionMS()/1000<<'\n';
        }
        salida<<"NumberOfEntries="<<Lista.size()<<'\n';
        salida<<"Version=2\n";
        salida.close();

}


void ListaRep::Eliminar(TListView *list)
{
        int seleccionados=list->SelCount;
        for (int i=1; i<=seleccionados; i++){
                vector<Pista>::iterator it = Lista.begin() + list->Selected->Index;
                list->Selected->Delete();
                Lista.erase(it);
        }
}


void ListaRep::AgregarArchivos(char *ListaDeArchivos, int n, TListView *list)
{
        string archivos = ListaDeArchivos;
        unsigned int pos=0;
        for (int i=0; i<n; i++)
        {
                Pista cancion;

                //extraer cada archivo en aux
                pos = archivos.find("\r\n",0);
                string aux = archivos.substr(0, pos);
                archivos.erase(0,pos+2);

                //obtener las tags
                char artista[1000], titulo[1000], album[1000], anio[1000];
                if (!control->GetTags(aux.c_str(), artista, titulo, album, anio)) continue;
                if (strcmp(titulo, "")==0){
                        string pordefecto = aux.substr(aux.rfind("\\")+1, aux.length());
                        if (pordefecto.rfind(".")!=0)
                                pordefecto = pordefecto.substr(0, pordefecto.rfind("."));
                        strcpy(titulo, pordefecto.c_str());
                }

                //agregar a la lista
                cancion.setRuta(aux.c_str());
                cancion.setDuracion(control->GetDuracion(cancion.getRuta().c_str()));
                cancion.cargar_datos(artista, album, titulo, anio);
                list->AddItem(list->Items->Count+1, list);
                list->Items->Item[list->Items->Count-1]->SubItems->Add(titulo);
                list->Items->Item[list->Items->Count-1]->SubItems->Add(cancion.getDuracion().c_str());
                list->Items->Item[list->Items->Count-1]->SubItems->Add(artista);
                list->Items->Item[list->Items->Count-1]->SubItems->Add(album);
                list->Items->Item[list->Items->Count-1]->SubItems->Add(anio);
                Lista.push_back(cancion);
        }
}


void ListaRep::AbrirListaM3u(char *NombreArchivo, TListView *list)
{
        ifstream entrada(NombreArchivo);
        if (!entrada.is_open()){
                Application->MessageBoxA("No se pudo abrir el archivo.", "Error", MB_ICONERROR);
                return;
        }
        string listarep = "", datos;
        int cont=0;
        getline(entrada, datos);
        if (datos != "#EXTM3U"){
                Application->MessageBoxA("Archivo de lista de reproducción inválido.", "Error", MB_ICONERROR);
                return;
        }
        while (getline(entrada, datos))
        {
                getline(entrada, datos);
                listarep += datos + "\r\n";
                cont++;
        }
        char *lr = new char[listarep.length()+1];
        strcpy(lr, listarep.c_str());
        AgregarArchivos(lr, cont, list);
        entrada.close();
        delete[] lr;
}


void ListaRep::AbrirListaPls(char *NombreArchivo, TListView *list)
{
        ifstream entrada(NombreArchivo);
        if (!entrada.is_open()){
                Application->MessageBoxA("No se pudo abrir el archivo.", "Error", MB_ICONERROR);
                return;
        }
        string listarep="", aux;
        stringstream datos;
        int cont=0;
        getline(entrada, aux);
        if (aux != "[playlist]"){
                Application->MessageBoxA("Archivo de lista de reproducción inválido.", "Error", MB_ICONERROR);
                return;
        }
        //cargo todo el archivo en "datos"
        while (getline(entrada, aux))
                datos<<aux<<'\n';
        if (datos.str().find("Version=2") == string::npos){
                Application->MessageBoxA("Archivo de lista de reproducción inválido.", "Error", MB_ICONERROR);
                return;
        }
        while (getline(datos, aux)){
                if (aux.substr(0, 4) == "File"){
                        listarep += aux.substr(aux.find("=")+1, aux.length()) + "\r\n";
                        cont++;
                }
        }
        char *lr = new char[listarep.length()+1];
        strcpy(lr, listarep.c_str());
        AgregarArchivos(lr, cont, list);
        entrada.close();
        delete[] lr;

}


void ListaRep::Limpiar()
{
        Lista.clear();
}


Pista ListaRep::operator [](int indice)
{
        return Lista[indice];
}


void ListaRep::Liberar()
{
        for (unsigned int i=0; i<Lista.size(); i++)
                Lista[i].liberarCriterio();
}


void ListaRep::ordenar_titulo(TListView *list)
{
        for (unsigned int i=0; i<Lista.size(); i++)
                Lista[i].setCriterioTitulo();
        sort(Lista.begin(), Lista.end());
        Liberar();

        //reorganizar la lista
        list->Clear();
        for (unsigned int i=0; i<Lista.size(); i++){
                list->AddItem(list->Items->Count+1, list);
                list->Items->Item[list->Items->Count-1]->SubItems->Add(Lista[i].obtener_titulo());
                list->Items->Item[list->Items->Count-1]->SubItems->Add(Lista[i].getDuracion());
                list->Items->Item[list->Items->Count-1]->SubItems->Add(Lista[i].obtener_artista());
                list->Items->Item[list->Items->Count-1]->SubItems->Add(Lista[i].obtener_album());
                list->Items->Item[list->Items->Count-1]->SubItems->Add(Lista[i].obtener_anio());
        }
}


void ListaRep::ordenar_artista(TListView *list)
{
        for (unsigned int i=0; i<Lista.size(); i++)
                Lista[i].setCriterioArtista();
        sort(Lista.begin(), Lista.end());
        Liberar();

        //reorganizar la lista
        list->Clear();
        for (unsigned int i=0; i<Lista.size(); i++){
                list->AddItem(list->Items->Count+1, list);
                list->Items->Item[list->Items->Count-1]->SubItems->Add(Lista[i].obtener_titulo());
                list->Items->Item[list->Items->Count-1]->SubItems->Add(Lista[i].getDuracion());
                list->Items->Item[list->Items->Count-1]->SubItems->Add(Lista[i].obtener_artista());
                list->Items->Item[list->Items->Count-1]->SubItems->Add(Lista[i].obtener_album());
                list->Items->Item[list->Items->Count-1]->SubItems->Add(Lista[i].obtener_anio());
        }
}


void ListaRep::ordenar_album(TListView *list)
{
        for (unsigned int i=0; i<Lista.size(); i++)
                Lista[i].setCriterioAlbum();
        sort(Lista.begin(), Lista.end());
        Liberar();

        //reorganizar la lista
        list->Clear();
        for (unsigned int i=0; i<Lista.size(); i++){
                list->AddItem(list->Items->Count+1, list);
                list->Items->Item[list->Items->Count-1]->SubItems->Add(Lista[i].obtener_titulo());
                list->Items->Item[list->Items->Count-1]->SubItems->Add(Lista[i].getDuracion());
                list->Items->Item[list->Items->Count-1]->SubItems->Add(Lista[i].obtener_artista());
                list->Items->Item[list->Items->Count-1]->SubItems->Add(Lista[i].obtener_album());
                list->Items->Item[list->Items->Count-1]->SubItems->Add(Lista[i].obtener_anio());
        }
}


void ListaRep::ordenar_anio(TListView *list)
{
        for (unsigned int i=0; i<Lista.size(); i++)
                Lista[i].setCriterioAnio();
        sort(Lista.begin(), Lista.end());
        Liberar();

        //reorganizar la lista
        list->Clear();
        for (unsigned int i=0; i<Lista.size(); i++){
                list->AddItem(list->Items->Count+1, list);
                list->Items->Item[list->Items->Count-1]->SubItems->Add(Lista[i].obtener_titulo());
                list->Items->Item[list->Items->Count-1]->SubItems->Add(Lista[i].getDuracion());
                list->Items->Item[list->Items->Count-1]->SubItems->Add(Lista[i].obtener_artista());
                list->Items->Item[list->Items->Count-1]->SubItems->Add(Lista[i].obtener_album());
                list->Items->Item[list->Items->Count-1]->SubItems->Add(Lista[i].obtener_anio());
        }
}


