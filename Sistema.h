//Clase Sistema
//Clase principal que controla todas las funciones de
//reproducción.
//---------------------------------------------------------------------------

#ifndef SistemaH
#define SistemaH
//---------------------------------------------------------------------------
#endif

#include "include\fmod.h"
#include "include\fmod_errors.h"
#pragma comment(lib, "lib\fmodex_bc.lib")

//---------------------------------------------------------------------------

void ERRCHECK(FMOD_RESULT result);

class Sistema {
        FMOD_RESULT result;
        FMOD_SYSTEM *system;
        FMOD_SOUND *sound;
        FMOD_CHANNEL *canal;
public:
        void Inicializar();
        bool Reproducir(const char *RutaArchivo);
        void Detener();
        void Pausar();
        void Continuar();
        bool GetPausa();
        bool GetTags(const char *RutaArchivo, char *Artista, char *Titulo, char *Album, char *Anio);
        unsigned int GetDuracion(const char *RutaArchivo);
        unsigned int GetPosicion();
        void SetPosicion(unsigned int PosicionMS);
        void SetVolumen(float Vol);
        void SetBalance(float Pan);
        float UsoCPU();
        void GetInfoFormato(int *Canales, int *Kbps, float *Hz);
        unsigned int GetKbps();
};
