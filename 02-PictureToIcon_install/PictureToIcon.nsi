; 该脚本使用 HM VNISEdit 脚本编辑器向导产生

; 安装程序初始定义常量
!define PRODUCT_NAME "PictureToIcon"
!define PRODUCT_VERSION "1.1"
!define PRODUCT_PUBLISHER "afeiya"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\PictureToIcon.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

SetCompressor lzma

; ------ MUI 现代界面定义 (1.67 版本以上兼容) ------
!include "MUI.nsh"

; MUI 预定义常量
!define MUI_ABORTWARNING
!define MUI_ICON "..\01-helloworld_MinGW\setup.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; 欢迎页面
!insertmacro MUI_PAGE_WELCOME
; 许可协议页面
!insertmacro MUI_PAGE_LICENSE "..\02-PictureToIcon_MSVC\COPYING"
; 安装目录选择页面
!insertmacro MUI_PAGE_DIRECTORY
; 安装过程页面
!insertmacro MUI_PAGE_INSTFILES
; 安装完成页面
!define MUI_FINISHPAGE_RUN "$INSTDIR\PictureToIcon.exe"
!insertmacro MUI_PAGE_FINISH

; 安装卸载过程页面
!insertmacro MUI_UNPAGE_INSTFILES

; 安装界面包含的语言设置
!insertmacro MUI_LANGUAGE "SimpChinese"

; 安装预释放文件
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS
; ------ MUI 现代界面定义结束 ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "PictureToIcon_Setup_1.1.exe"
InstallDir "$PROGRAMFILES\PictureToIcon"
InstallDirRegKey HKLM "${PRODUCT_UNINST_KEY}" "UninstallString"
ShowInstDetails show
ShowUnInstDetails show
BrandingText " "

Section "MainSection" SEC01
  SetOutPath "$INSTDIR"
  SetOverwrite ifnewer
  File "..\02-PictureToIcon_MSVC\COPYING"
  CreateDirectory "$SMPROGRAMS\PictureToIcon"
  CreateShortCut "$SMPROGRAMS\PictureToIcon\PictureToIcon.lnk" "$INSTDIR\PictureToIcon.exe"
  CreateShortCut "$DESKTOP\PictureToIcon.lnk" "$INSTDIR\PictureToIcon.exe"
  File "..\02-PictureToIcon_MSVC\D3Dcompiler_47.dll"
  SetOutPath "$INSTDIR\iconengines"
  File "..\02-PictureToIcon_MSVC\iconengines\qsvgicon.dll"
  SetOutPath "$INSTDIR\imageformats"
  File "..\02-PictureToIcon_MSVC\imageformats\qgif.dll"
  File "..\02-PictureToIcon_MSVC\imageformats\qicns.dll"
  File "..\02-PictureToIcon_MSVC\imageformats\qico.dll"
  File "..\02-PictureToIcon_MSVC\imageformats\qjpeg.dll"
  File "..\02-PictureToIcon_MSVC\imageformats\qsvg.dll"
  File "..\02-PictureToIcon_MSVC\imageformats\qtga.dll"
  File "..\02-PictureToIcon_MSVC\imageformats\qtiff.dll"
  File "..\02-PictureToIcon_MSVC\imageformats\qwbmp.dll"
  File "..\02-PictureToIcon_MSVC\imageformats\qwebp.dll"
  SetOutPath "$INSTDIR"
  File "..\02-PictureToIcon_MSVC\libEGL.dll"
  File "..\02-PictureToIcon_MSVC\libgcc_s_seh-1.dll"
  File "..\02-PictureToIcon_MSVC\libGLESv2.dll"
  File "..\02-PictureToIcon_MSVC\libstdc++-6.dll"
  File "..\02-PictureToIcon_MSVC\libwinpthread-1.dll"
  File "..\02-PictureToIcon_MSVC\opengl32sw.dll"
  File "..\02-PictureToIcon_MSVC\PictureToIcon.exe"
  SetOutPath "$INSTDIR\platforms"
  File "..\02-PictureToIcon_MSVC\platforms\qwindows.dll"
  SetOutPath "$INSTDIR"
  File "..\02-PictureToIcon_MSVC\Qt5Core.dll"
  File "..\02-PictureToIcon_MSVC\Qt5Gui.dll"
  File "..\02-PictureToIcon_MSVC\Qt5Svg.dll"
  File "..\02-PictureToIcon_MSVC\Qt5Widgets.dll"
  SetOutPath "$INSTDIR\styles"
  File "..\02-PictureToIcon_MSVC\styles\qwindowsvistastyle.dll"
  SetOutPath "$INSTDIR\translations"
  File "..\02-PictureToIcon_MSVC\translations\qt_ar.qm"
  File "..\02-PictureToIcon_MSVC\translations\qt_bg.qm"
  File "..\02-PictureToIcon_MSVC\translations\qt_ca.qm"
  File "..\02-PictureToIcon_MSVC\translations\qt_cs.qm"
  File "..\02-PictureToIcon_MSVC\translations\qt_da.qm"
  File "..\02-PictureToIcon_MSVC\translations\qt_de.qm"
  File "..\02-PictureToIcon_MSVC\translations\qt_en.qm"
  File "..\02-PictureToIcon_MSVC\translations\qt_es.qm"
  File "..\02-PictureToIcon_MSVC\translations\qt_fi.qm"
  File "..\02-PictureToIcon_MSVC\translations\qt_fr.qm"
  File "..\02-PictureToIcon_MSVC\translations\qt_gd.qm"
  File "..\02-PictureToIcon_MSVC\translations\qt_he.qm"
  File "..\02-PictureToIcon_MSVC\translations\qt_hu.qm"
  File "..\02-PictureToIcon_MSVC\translations\qt_it.qm"
  File "..\02-PictureToIcon_MSVC\translations\qt_ja.qm"
  File "..\02-PictureToIcon_MSVC\translations\qt_ko.qm"
  File "..\02-PictureToIcon_MSVC\translations\qt_lv.qm"
  File "..\02-PictureToIcon_MSVC\translations\qt_pl.qm"
  File "..\02-PictureToIcon_MSVC\translations\qt_ru.qm"
  File "..\02-PictureToIcon_MSVC\translations\qt_sk.qm"
  File "..\02-PictureToIcon_MSVC\translations\qt_tr.qm"
  File "..\02-PictureToIcon_MSVC\translations\qt_uk.qm"
  File "..\02-PictureToIcon_MSVC\translations\qt_zh_TW.qm"
  SetOutPath "$INSTDIR"
  File "..\02-PictureToIcon_MSVC\vc_redist.x64.exe"
SectionEnd

Section -AdditionalIcons
  CreateShortCut "$SMPROGRAMS\PictureToIcon\Uninstall.lnk" "$INSTDIR\uninst.exe"
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\PictureToIcon.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\PictureToIcon.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd

/******************************
 *  以下是安装程序的卸载部分  *
 ******************************/

Section Uninstall
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\vc_redist.x64.exe"
  Delete "$INSTDIR\translations\qt_zh_TW.qm"
  Delete "$INSTDIR\translations\qt_uk.qm"
  Delete "$INSTDIR\translations\qt_tr.qm"
  Delete "$INSTDIR\translations\qt_sk.qm"
  Delete "$INSTDIR\translations\qt_ru.qm"
  Delete "$INSTDIR\translations\qt_pl.qm"
  Delete "$INSTDIR\translations\qt_lv.qm"
  Delete "$INSTDIR\translations\qt_ko.qm"
  Delete "$INSTDIR\translations\qt_ja.qm"
  Delete "$INSTDIR\translations\qt_it.qm"
  Delete "$INSTDIR\translations\qt_hu.qm"
  Delete "$INSTDIR\translations\qt_he.qm"
  Delete "$INSTDIR\translations\qt_gd.qm"
  Delete "$INSTDIR\translations\qt_fr.qm"
  Delete "$INSTDIR\translations\qt_fi.qm"
  Delete "$INSTDIR\translations\qt_es.qm"
  Delete "$INSTDIR\translations\qt_en.qm"
  Delete "$INSTDIR\translations\qt_de.qm"
  Delete "$INSTDIR\translations\qt_da.qm"
  Delete "$INSTDIR\translations\qt_cs.qm"
  Delete "$INSTDIR\translations\qt_ca.qm"
  Delete "$INSTDIR\translations\qt_bg.qm"
  Delete "$INSTDIR\translations\qt_ar.qm"
  Delete "$INSTDIR\styles\qwindowsvistastyle.dll"
  Delete "$INSTDIR\Qt5Widgets.dll"
  Delete "$INSTDIR\Qt5Svg.dll"
  Delete "$INSTDIR\Qt5Gui.dll"
  Delete "$INSTDIR\Qt5Core.dll"
  Delete "$INSTDIR\platforms\qwindows.dll"
  Delete "$INSTDIR\PictureToIcon.exe"
  Delete "$INSTDIR\opengl32sw.dll"
  Delete "$INSTDIR\libwinpthread-1.dll"
  Delete "$INSTDIR\libstdc++-6.dll"
  Delete "$INSTDIR\libGLESv2.dll"
  Delete "$INSTDIR\libgcc_s_seh-1.dll"
  Delete "$INSTDIR\libEGL.dll"
  Delete "$INSTDIR\imageformats\qwebp.dll"
  Delete "$INSTDIR\imageformats\qwbmp.dll"
  Delete "$INSTDIR\imageformats\qtiff.dll"
  Delete "$INSTDIR\imageformats\qtga.dll"
  Delete "$INSTDIR\imageformats\qsvg.dll"
  Delete "$INSTDIR\imageformats\qjpeg.dll"
  Delete "$INSTDIR\imageformats\qico.dll"
  Delete "$INSTDIR\imageformats\qicns.dll"
  Delete "$INSTDIR\imageformats\qgif.dll"
  Delete "$INSTDIR\iconengines\qsvgicon.dll"
  Delete "$INSTDIR\D3Dcompiler_47.dll"
  Delete "$INSTDIR\COPYING"

  Delete "$SMPROGRAMS\PictureToIcon\Uninstall.lnk"
  Delete "$DESKTOP\PictureToIcon.lnk"
  Delete "$SMPROGRAMS\PictureToIcon\PictureToIcon.lnk"

  RMDir "$SMPROGRAMS\PictureToIcon"
  RMDir "$INSTDIR\translations"
  RMDir "$INSTDIR\styles"
  RMDir "$INSTDIR\platforms"
  RMDir "$INSTDIR\imageformats"
  RMDir "$INSTDIR\iconengines"

  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd

#-- 根据 NSIS 脚本编辑规则，所有 Function 区段必须放置在 Section 区段之后编写，以避免安装程序出现未可预知的问题。--#

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "您确实要完全移除 $(^Name) ，及其所有的组件？" IDYES +2
  Abort
FunctionEnd

Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) 已成功地从您的计算机移除。"
FunctionEnd
