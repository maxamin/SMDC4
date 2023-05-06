# Microsoft Developer Studio Project File - Name="ArgusWFdll" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ArgusWFdll - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ArgusWFdll.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ArgusWFdll.mak" CFG="ArgusWFdll - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ArgusWFdll - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ArgusWFdll - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ArgusWFdll - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x429 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x429 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "ArgusWFdll - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x429 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x429 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ArgusWFdll - Win32 Release"
# Name "ArgusWFdll - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ArgusDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ArgusView.cpp
# End Source File
# Begin Source File

SOURCE=.\ArgusWFdll.cpp
# End Source File
# Begin Source File

SOURCE=.\ArgusWFdll.def
# End Source File
# Begin Source File

SOURCE=.\ArgusWFdll.rc
# End Source File
# Begin Source File

SOURCE=.\BEpolar.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\FrqTime.cpp
# End Source File
# Begin Source File

SOURCE=.\MyMultiDocTemplate.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ArgusDoc.h
# End Source File
# Begin Source File

SOURCE=.\ArgusView.h
# End Source File
# Begin Source File

SOURCE=.\ArgusWFdll.h
# End Source File
# Begin Source File

SOURCE=.\BEpolar.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\ColorListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\FrqTime.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MyMultiDocTemplate.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SMS4DC.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\argustyp.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ArgusWFdll.rc2
# End Source File
# Begin Source File

SOURCE=.\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\first1.bmp
# End Source File
# Begin Source File

SOURCE=.\first2.bmp
# End Source File
# Begin Source File

SOURCE=.\first3.bmp
# End Source File
# Begin Source File

SOURCE=.\first4.bmp
# End Source File
# Begin Source File

SOURCE=.\idr_argu.cur
# End Source File
# Begin Source File

SOURCE=.\idr_argu.ico
# End Source File
# Begin Source File

SOURCE=.\last1.bmp
# End Source File
# Begin Source File

SOURCE=.\last2.bmp
# End Source File
# Begin Source File

SOURCE=.\last3.bmp
# End Source File
# Begin Source File

SOURCE=.\last4.bmp
# End Source File
# Begin Source File

SOURCE=.\next1.bmp
# End Source File
# Begin Source File

SOURCE=.\next2.bmp
# End Source File
# Begin Source File

SOURCE=.\next3.bmp
# End Source File
# Begin Source File

SOURCE=.\next4.bmp
# End Source File
# Begin Source File

SOURCE=.\pre1.bmp
# End Source File
# Begin Source File

SOURCE=.\pre2.bmp
# End Source File
# Begin Source File

SOURCE=.\pre3.bmp
# End Source File
# Begin Source File

SOURCE=.\pre4.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
