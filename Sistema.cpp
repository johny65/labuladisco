//---------------------------------------------------------------------------

#pragma hdrstop

#include "Sistema.h"

#include <string.h>
#include <qdialogs.hpp>

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------

void ERRCHECK(FMOD_RESULT result)
{
        if (result != FMOD_OK)
                ShowMessage(FMOD_ErrorString(result));
}

/*void Sistema::Apagar()
{
        result = FMOD_Sound_Release(sound);
        ERRCHECK(result);
        result = FMOD_System_Close(system);
        ERRCHECK(result);
        result = FMOD_System_Release(system);
        ERRCHECK(result);
}
*/

void Sistema::Inicializar()
{
        //crea el objeto principal "system"
        result = FMOD_System_Create(&system);

        //inicializa FMOD
        result = FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, 0);
}

bool Sistema::Reproducir(const char *RutaArchivo)
{
        //carga el sonido
        result = FMOD_System_CreateStream(system, RutaArchivo, FMOD_DEFAULT | FMOD_LOWMEM, 0, &sound); // FMOD_DEFAULT es lo mismo que: FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE.
        if (result!=FMOD_OK) return false;

        //lo reproduce
        result = FMOD_System_PlaySound(system, FMOD_CHANNEL_REUSE, sound, false, &canal); //reproduce la canción
        if (result!=FMOD_OK) return false;

        return true;
}

void Sistema::Detener()
{
        result = FMOD_Channel_Stop(canal);
}

void Sistema::Pausar()
{
        result = FMOD_Channel_SetPaused(canal, true);
}

void Sistema::Continuar()
{
        result = FMOD_Channel_SetPaused(canal, false);
}

bool Sistema::GetPausa()
{
        int pausado;
        result = FMOD_Channel_GetPaused(canal, &pausado);
        FMOD_BOOL r=pausado;
        return r;
}

unsigned int Sistema::GetPosicion()
{
        unsigned int pos;
        result = FMOD_Channel_GetPosition(canal, &pos, FMOD_TIMEUNIT_MS);
        return pos;
}

void Sistema::SetPosicion(unsigned int PosicionMS)
{
        result = FMOD_Channel_SetPosition(canal, PosicionMS, FMOD_TIMEUNIT_MS);
}

bool Sistema::GetTags(const char *RutaArchivo, char *Artista, char *Titulo, char *Album, char *Anio)
{
        //carga el sonido
        result = FMOD_System_CreateStream(system, RutaArchivo, FMOD_DEFAULT | FMOD_LOWMEM | FMOD_OPENONLY, 0, &sound); // FMOD_DEFAULT es lo mismo que: FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE.
        if (result != FMOD_OK)
                return false;

        //obtiene las tags
        FMOD_TAG tag;
        FMOD_SOUND_TYPE tipo;

        result = FMOD_Sound_GetFormat(sound, &tipo, 0, 0, 0);
        switch (tipo){
                case FMOD_SOUND_TYPE_MPEG: { //mp3
                        //título
                        result = FMOD_Sound_GetTag(sound, "TIT2", 0, &tag);
                        if (result == FMOD_ERR_TAGNOTFOUND){ //si no está en id3v2, buscar en id3v1
                                result = FMOD_Sound_GetTag(sound, "TITLE", 0, &tag);
                                if (result == FMOD_ERR_TAGNOTFOUND) //si tampoco está en id3v1, dejarlo en blanco
                                        strcpy(Titulo, "");
                                else
                                        strcpy(Titulo, (char*)tag.data);
                        }
                        else strcpy(Titulo, (char*)tag.data);
                        //artista
                        result = FMOD_Sound_GetTag(sound, "TPE1", 0, &tag);
                        if (result == FMOD_ERR_TAGNOTFOUND){
                                result = FMOD_Sound_GetTag(sound, "ARTIST", 0, &tag);
                                if (result == FMOD_ERR_TAGNOTFOUND)
                                        strcpy(Artista, "");
                                else
                                        strcpy(Artista, (char*)tag.data);
                        }
                        else strcpy(Artista, (char*)tag.data);
                        //álbum
                        result = FMOD_Sound_GetTag(sound, "TALB", 0, &tag);
                        if (result == FMOD_ERR_TAGNOTFOUND){
                                result = FMOD_Sound_GetTag(sound, "ALBUM", 0, &tag);
                                if (result == FMOD_ERR_TAGNOTFOUND)
                                        strcpy(Album, "");
                                else
                                        strcpy(Album, (char*)tag.data);
                        }
                        else strcpy(Album, (char*)tag.data);
                        //año
                        result = FMOD_Sound_GetTag(sound, "TYER", 0, &tag);
                        if (result == FMOD_ERR_TAGNOTFOUND){
                                result = FMOD_Sound_GetTag(sound, "YEAR", 0, &tag);
                                if (result == FMOD_ERR_TAGNOTFOUND)
                                        strcpy(Anio, "");
                                else
                                        strcpy(Anio, (char*)tag.data);
                        }
                        else strcpy(Anio, (char*)tag.data);

                        break;
                }
                case FMOD_SOUND_TYPE_FLAC: { //flac
                        //título
                        result = FMOD_Sound_GetTag(sound, "TITLE", 0, &tag);
                        if (result == FMOD_ERR_TAGNOTFOUND)
                                strcpy(Titulo, "");
                        else
                                strcpy(Titulo, (char*)tag.data);
                        //artista
                        result = FMOD_Sound_GetTag(sound, "ARTIST", 0, &tag);
                        if (result == FMOD_ERR_TAGNOTFOUND)
                                strcpy(Artista, "");
                        else
                                strcpy(Artista, (char*)tag.data);
                        //álbum
                        result = FMOD_Sound_GetTag(sound, "ALBUM", 0, &tag);
                        if (result == FMOD_ERR_TAGNOTFOUND)
                                strcpy(Album, "");
                        else
                                strcpy(Album, (char*)tag.data);
                        //año
                        result = FMOD_Sound_GetTag(sound, "DATE", 0, &tag);
                        if (result == FMOD_ERR_TAGNOTFOUND)
                                strcpy(Anio, "");
                        else
                                strcpy(Anio, (char*)tag.data);

                        break;
                }
                case FMOD_SOUND_TYPE_PLAYLIST: { //listas de reproducción, se agregan aparte
                        return false;
                }
                default: {
                        strcpy(Titulo, "");
                        strcpy(Artista, "");
                        strcpy(Album, "");
                        strcpy(Anio, "");
                }

        }

        //libera el sonido
        result = FMOD_Sound_Release(sound);
        return true;
}

unsigned int Sistema::GetDuracion(const char *RutaArchivo)
{
        unsigned int ms;
        FMOD_SOUND *temp;

        //carga el sonido
        result = FMOD_System_CreateStream(system, RutaArchivo, FMOD_DEFAULT | FMOD_LOWMEM | FMOD_OPENONLY, 0, &temp); // FMOD_DEFAULT es lo mismo que: FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE.

        //obtiene la duración
        result = FMOD_Sound_GetLength(temp, &ms, FMOD_TIMEUNIT_MS); //duración de la canción en milisegundos

        //libera el sonido
        result = FMOD_Sound_Release(temp);

        return ms;
}

void Sistema::SetVolumen(float Vol)
{
        result = FMOD_Channel_SetVolume(canal, Vol/100);
}

void Sistema::SetBalance(float Pan)
{
        result = FMOD_Channel_SetPan(canal, Pan/100);
}

float Sistema::UsoCPU()
{
        float uso;
        result = FMOD_System_GetCPUUsage(system, 0, 0, 0, &uso);
        return uso;
}

void Sistema::GetInfoFormato(int *Canales, int *Kbps, float *Hz)
{
        result = FMOD_Sound_GetFormat(sound, 0, 0, Canales, Kbps);
        result = FMOD_Channel_GetFrequency(canal, Hz);
}

unsigned int Sistema::GetKbps()
{
        unsigned int kbps;
        result = FMOD_Channel_GetPosition(canal, &kbps, FMOD_TIMEUNIT_RAWBYTES);
        if (GetPosicion()!=0)
                kbps = kbps / GetPosicion() * 8;
        else
                kbps = kbps / (GetPosicion()+1) * 8;
        return kbps;
}

