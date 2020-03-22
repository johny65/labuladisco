;NSIS Modern User Interface version 1.70

;--------------------------------
;Includes

  !include "MUI.nsh"
  !include "FileFunc.nsh"
  !insertmacro RefreshShellIcons
  !insertmacro un.RefreshShellIcons

;--------------------------------
;General

  !define APP "LaBulaDisco Reproductor de Audio 0.1b"
  !define EXE "labuladisco.exe"
  !define AYUDA "Manual de Usuario.chm"
  !define AYUDA2 "Manual de Referencia.pdf"
  !define REG "labuladisco"
  !define VERSION "0.1.0.0"
  !define VERSION2 "0.1b"

  ;Nombre y archivo
  Name "${APP}"
  OutFile "x.exe"

  ;Default installation folder
  InstallDir "$PROGRAMFILES\${APP}"

  ;Ícono para la instalación
  !define MUI_ICON ico.ico
  !define MUI_UNICON des.ico

  ;Agregar estilos visuales
  XPStyle on

  ;Pedir privilegios de root para Vista
  RequestExecutionLevel user


;--------------------------------
;Opciones de interfaz

  ;!define MUI_HEADERIMAGE
  !define MUI_ABORTWARNING
  !define MUI_FINISHPAGE_NOAUTOCLOSE
  ;!define MUI_UNFINISHPAGE_NOAUTOCLOSE
  !define MUI_FINISHPAGE_RUN "$INSTDIR\${EXE}"
  !define MUI_FINISHPAGE_RUN_TEXT "Ejecutar ${APP}"
  !define MUI_FINISHPAGE_SHOWREADME "$INSTDIR\${AYUDA}"
  !define MUI_FINISHPAGE_SHOWREADME_TEXT "Ver el Manual de Usuario"
  !define MUI_WELCOMEPAGE_TITLE_3LINES
  !define MUI_FINISHPAGE_TITLE_3LINES
  !define MUI_WELCOMEFINISHPAGE_BITMAP setup.bmp


;--------------------------------
;Páginas

  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_LICENSE "licencia.rtf"
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  !insertmacro MUI_PAGE_FINISH
  
  ;!insertmacro MUI_UNPAGE_WELCOME
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  ;!insertmacro MUI_UNPAGE_FINISH

;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "Spanish"


;--------------------------------
;Version Information

  VIProductVersion "${VERSION}"
  VIAddVersionKey /LANG=${LANG_SPANISH} "ProductName" "${APP}"
  VIAddVersionKey /LANG=${LANG_SPANISH} "Comments" "Reproductor de audio"
  VIAddVersionKey /LANG=${LANG_SPANISH} "CompanyName" "Juan Bertinetti - Facundo Curie"
  VIAddVersionKey /LANG=${LANG_SPANISH} "LegalCopyright" "2008"
  VIAddVersionKey /LANG=${LANG_SPANISH} "FileDescription" "Instalación de LaBulaDisco Reproductor de Audio"
  VIAddVersionKey /LANG=${LANG_SPANISH} "FileVersion" "${VERSION2}"


;--------------------------------
;Installer Sections

Section ""

  SetDetailsView show

  SetOutPath "$INSTDIR"
  File "archivos\${EXE}"
  File "archivos\${AYUDA}"
  File "archivos\${AYUDA2}"
  File "archivos\labuladisco.exe.manifest"
  File "archivos\fmodex.dll"
  File "archivos\default.lbd"
  File "archivos\pref.cfg"
  File "archivos\borlndmm.dll"
  File "archivos\cc3260mt.dll"
  File "archivos\qtintf.dll"
  File "archivos\stlpmt45.dll"
  File "archivos\lbd.ico"


  ;Asociar archivo .lbd
  ;---------------------
  WriteRegStr HKCR ".lbd" "" "labuladisco"
  WriteRegStr HKCR "labuladisco" "" "Lista de reproducción de LaBulaDisco"
  WriteRegStr HKCR "labuladisco\DefaultIcon" "" "$INSTDIR\lbd.ico"
  WriteRegStr HKCR "labuladisco\shell\open\command" "" '"$INSTDIR\${EXE}" "%1"'
  ${RefreshShellIcons}

  
  ;---------------------
  ;Para la desinstalación

  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${REG}" "DisplayName" "${APP}"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${REG}" "DisplayIcon" "$INSTDIR\${EXE}"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${REG}" "UninstallString" '"$INSTDIR\Uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${REG}" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${REG}" "NoRepair" 1

  WriteUninstaller "$INSTDIR\Uninstall.exe"



  ;---------------------
  ;accesos directos

  CreateDirectory "$SMPROGRAMS\${APP}"
  CreateShortCut "$SMPROGRAMS\${APP}\Manual de Usuario.lnk" "$INSTDIR\${AYUDA}" "" "$INSTDIR\${AYUDA}" 0
  CreateShortCut "$SMPROGRAMS\${APP}\Manual de Referencia.lnk" "$INSTDIR\${AYUDA2}" "" "$INSTDIR\${AYUDA2}" 0
  CreateShortCut "$SMPROGRAMS\${APP}\Desinstalar ${APP}.lnk" "$INSTDIR\Uninstall.exe" "" "$INSTDIR\Uninstall.exe" 0
  CreateShortCut "$SMPROGRAMS\${APP}\${APP}.lnk" "$INSTDIR\${EXE}" "" "$INSTDIR\${EXE}" 0
  CreateShortCut "$DESKTOP\${APP}.lnk" "$INSTDIR\${EXE}" "" "$INSTDIR\${EXE}" 0


SectionEnd


;--------------------------------
;Uninstaller Section

Section "Uninstall"

  SetDetailsView show

  Delete "$INSTDIR\Unistall.exe"
  Delete "$INSTDIR\${EXE}"
  Delete "$INSTDIR\${AYUDA}"
  Delete "$INSTDIR\${AYUDA2}"
  Delete "$INSTDIR\labuladisco.exe.manifest"
  Delete "$INSTDIR\fmodex.dll"
  Delete "$INSTDIR\default.lbd"
  Delete "$INSTDIR\pref.cfg"
  Delete "$INSTDIR\borlndmm.dll"
  Delete "$INSTDIR\cc3260mt.dll"
  Delete "$INSTDIR\qtintf.dll"
  Delete "$INSTDIR\stlpmt45.dll"
  Delete "$INSTDIR\lbd.ico"

  RmDir /r "$INSTDIR"

  Delete "$SMPROGRAMS\${APP}\*.*"
  Delete "$DESKTOP\${APP}.lnk"

  RmDir "$SMPROGRAMS\${APP}"

  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${REG}"
  DeleteRegKey HKCR ".lbd"
  DeleteRegKey HKCR "labuladisco"
  ${un.RefreshShellIcons}

SectionEnd
