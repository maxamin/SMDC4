# Microsoft Developer Studio Project File - Name="Administrative" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Administrative - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Administrative.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Administrative.mak" CFG="Administrative - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Administrative - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Administrative - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Administrative - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 E:\ITU\progs\Administrative-RRC06\Release\idwm32d.lib E:\ITU\progs\Administrative-RRC06\Release\ESantDLL.lib e:\ITU\progs\Administrative-RRC06\Release\CNT.lib E:\ITU\progs\Administrative-RRC06\Release\spromeps.lib wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Administrative - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR /YX"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 c:\ITU\progs\Administrative-4-2\Debug\idwm32d.lib c:\ITU\progs\Administrative-4-2\Debug\ESantDLL.lib c:\ITU\progs\Administrative-4-2\Debug\spromeps.lib c:\ITU\progs\Administrative-4-2\Debug\CNT_lang.lib wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:2.0 /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"MSVCRT.LIB" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "Administrative - Win32 Release"
# Name "Administrative - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Administrative.cpp
# End Source File
# Begin Source File

SOURCE=.\Administrative.def
# End Source File
# Begin Source File

SOURCE=.\Administrative.rc
# End Source File
# Begin Source File

SOURCE=.\AntPattern.cpp
# End Source File
# Begin Source File

SOURCE=.\Audit.cpp
# End Source File
# Begin Source File

SOURCE=.\CatSelect.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomReport.cpp
# End Source File
# Begin Source File

SOURCE=.\EditGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\EditWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\ESAntPat.cpp
# End Source File
# Begin Source File

SOURCE=.\ESNotice.cpp
# End Source File
# Begin Source File

SOURCE=.\font.cpp
# End Source File
# Begin Source File

SOURCE=.\GrpDetails.cpp
# End Source File
# Begin Source File

SOURCE=.\LeftView.cpp
# End Source File
# Begin Source File

SOURCE=.\LockDefs.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MoveStation.cpp
# End Source File
# Begin Source File

SOURCE=.\mshflexgrid.cpp
# End Source File
# Begin Source File

SOURCE=.\msmask.cpp
# End Source File
# Begin Source File

SOURCE=.\MyMultiDocTemplate.cpp
# End Source File
# Begin Source File

SOURCE=.\Notice.cpp
# End Source File
# Begin Source File

SOURCE=.\PaymentDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\picture.cpp
# End Source File
# Begin Source File

SOURCE=.\Receivers.cpp
# End Source File
# Begin Source File

SOURCE=.\recordset.cpp
# End Source File
# Begin Source File

SOURCE=.\RightGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TreeSearch.cpp
# End Source File
# Begin Source File

SOURCE=.\treeviewDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\treeviewView.cpp
# End Source File
# Begin Source File

SOURCE=.\TxRxFilterDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\TxRxFiltersSet.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Administrative.h
# End Source File
# Begin Source File

SOURCE=.\AntPattern.h
# End Source File
# Begin Source File

SOURCE=.\Audit.h
# End Source File
# Begin Source File

SOURCE=.\BR_TYPES.H
# End Source File
# Begin Source File

SOURCE=.\BRFORTYP.H
# End Source File
# Begin Source File

SOURCE=.\CatSelect.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\CustomReport.h
# End Source File
# Begin Source File

SOURCE=.\EditGrid.h
# End Source File
# Begin Source File

SOURCE=.\EditWnd.h
# End Source File
# Begin Source File

SOURCE=.\ESAntPat.h
# End Source File
# Begin Source File

SOURCE=.\ESNotice.h
# End Source File
# Begin Source File

SOURCE=.\font.h
# End Source File
# Begin Source File

SOURCE=.\GrpDetails.h
# End Source File
# Begin Source File

SOURCE=.\IDWM32.H
# End Source File
# Begin Source File

SOURCE=.\LeftView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MoveStation.h
# End Source File
# Begin Source File

SOURCE=.\mshflexgrid.h
# End Source File
# Begin Source File

SOURCE=.\msmask.h
# End Source File
# Begin Source File

SOURCE=.\MyMultiDocTemplate.h
# End Source File
# Begin Source File

SOURCE=.\Notice.h
# End Source File
# Begin Source File

SOURCE=.\PaymentDlg.h
# End Source File
# Begin Source File

SOURCE=.\picture.h
# End Source File
# Begin Source File

SOURCE=.\Receivers.h
# End Source File
# Begin Source File

SOURCE=.\recordset.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RightGrid.h
# End Source File
# Begin Source File

SOURCE=.\Sproeval.h
# End Source File
# Begin Source File

SOURCE=.\SPROMEPS.H
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\test6.h
# End Source File
# Begin Source File

SOURCE=.\TreeSearch.h
# End Source File
# Begin Source File

SOURCE=.\treeviewDoc.h
# End Source File
# Begin Source File

SOURCE=.\treeviewView.h
# End Source File
# Begin Source File

SOURCE=.\TxRxFilterDLG.h
# End Source File
# Begin Source File

SOURCE=.\TxRxFiltersSet.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\active.ico
# End Source File
# Begin Source File

SOURCE=.\res\add1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\add2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\add3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Administrative.rc2
# End Source File
# Begin Source File

SOURCE=.\res\allotmen.ico
# End Source File
# Begin Source File

SOURCE=.\res\antenna1.ico
# End Source File
# Begin Source File

SOURCE=.\res\contour.ico
# End Source File
# Begin Source File

SOURCE=.\res\delete1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\delete2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\delete3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\eantup1.ico
# End Source File
# Begin Source File

SOURCE=.\res\first1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\first2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\first3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00005.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00006.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00007.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00008.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00009.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00010.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00011.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00012.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00013.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00014.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\inactive.ico
# End Source File
# Begin Source File

SOURCE=.\res\invoice1.ico
# End Source File
# Begin Source File

SOURCE=.\res\last1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\last2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\last3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\minus1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\minus2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\minus3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\next1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\next2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\next3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\plus1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\plus2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\plus3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\prev1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\prev2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\receiver.ico
# End Source File
# Begin Source File

SOURCE=.\res\save1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\save2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\save3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\station.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\treeview.ico
# End Source File
# Begin Source File

SOURCE=.\res\treeviewDoc.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
