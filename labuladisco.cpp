//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Main.cpp", frmMain);
USEFORM("formEspere.cpp", frmEspere);
USEFORM("formCd.cpp", frmCd);
USEFORM("formOpciones.cpp", frmOpciones);
USEFORM("formAcerca.cpp", frmAcerca);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR lpszArgs, int)
{
        try
        {
                 Application->Hint = lpszArgs;
                 Application->Initialize();
                 Application->Title = "LaBulaDisco Reproductor de Audio";
                 Application->CreateForm(__classid(TfrmMain), &frmMain);
                 Application->CreateForm(__classid(TfrmEspere), &frmEspere);
                 Application->CreateForm(__classid(TfrmCd), &frmCd);
                 Application->CreateForm(__classid(TfrmOpciones), &frmOpciones);
                 Application->CreateForm(__classid(TfrmAcerca), &frmAcerca);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
