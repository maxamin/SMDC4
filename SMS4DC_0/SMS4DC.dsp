# Microsoft Developer Studio Project File - Name="SMS4DC" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SMS4DC - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SMS4DC.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SMS4DC.mak" CFG="SMS4DC - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SMS4DC - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SMS4DC - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SMS4DC - Win32 Release"

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
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x429 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x429 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "SMS4DC - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /YX"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x429 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x429 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 OPENGL32.LIB GLU32.LIB C:\Br_soft\System32\Idwm32d.LIB F:\map1\SMS4DC_0\bin\FplanDLL.lib F:\map1\SMS4DC_0\bin\Lic.lib F:\map1\SMS4DC_0\bin\IFIC.lib F:\map1\SMS4DC_0\bin\P618DLL.lib F:\map1\SMS4DC_0\bin\Art5NDLL.lib F:\map1\SMS4DC_0\bin\spromeps.lib wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib F:\map1\SMS4DC_0\bin\CNT_lang.lib F:\map1\SMS4DC_0\bin\GoogleFileDLL.lib F:\map1\SMS4DC_0\bin\argusO_smsRDLL.lib F:\map1\SMS4DC_0\bin\GSPorderDLL.lib F:\map1\SMS4DC_0\bin\ORtabDLL.lib F:\map1\SMS4DC_0\bin\STorderDLL.lib F:\map1\SMS4DC_0\bin\SUorderDLL.lib F:\map1\SMS4DC_0\bin\ThalesGenChkDLL.lib F:\map1\SMS4DC_0\bin\ThalesChkDLL.lib F:\map1\SMS4DC_0\bin\ThalesResDLL.lib F:\map1\SMS4DC_0\bin\ThalesOccDLL.lib F:\map1\SMS4DC_0\bin\ThalesReqDLL.lib F:\map1\SMS4DC_0\bin\ThalesAtrDLL.lib F:\map1\SMS4DC_0\bin\List_DataBase.lib F:\map1\SMS4DC_0\bin\ThalesReqAutoDLL.lib F:\map1\SMS4DC_0\bin\ThalesMstationDLL.lib F:\map1\SMS4DC_0\bin\ConvertAntDLL.lib F:\map1\SMS4DC_0\bin\Audit.lib F:\map1\SMS4DC_0\bin\APP7DLL.lib F:\map1\SMS4DC_0\bin\P452V15DLL.lib F:\map1\SMS4DC_0\bin\P530V15DLL.lib F:\map1\SMS4DC_0\bin\P1546V5DLL.lib F:\map1\SMS4DC_0\bin\P1812V3DLL.lib F:\map1\SMS4DC_0\bin\HCM_SMS4DCDLL.lib F:\map1\SMS4DC_0\bin\P526V14DLL.lib msimg32.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"MSVCRT.LIB" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "SMS4DC - Win32 Release"
# Name "SMS4DC - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\_recordset.cpp
# End Source File
# Begin Source File

SOURCE=.\AddESStationDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\AddFreqDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\AddStationDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\AddStationRecSet.cpp
# End Source File
# Begin Source File

SOURCE=.\adodc.cpp
# End Source File
# Begin Source File

SOURCE=.\Allocations_DrawDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Allocations_DrawFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Allocations_DrawView.cpp
# End Source File
# Begin Source File

SOURCE=.\Ant3DDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Ant3DFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Ant3DPropDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\Ant3DView.cpp
# End Source File
# Begin Source File

SOURCE=.\AntennaFormDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\AntennaFormFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\AntennaFormView.cpp
# End Source File
# Begin Source File

SOURCE=.\ANTpatternDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\AP7_CordContourDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\AP7_ESantPattern.cpp
# End Source File
# Begin Source File

SOURCE=.\AP7_OptionsDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\Ap7_StyleDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\AP7EarthStationDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\AP7ESDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\Area3DDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Area3DFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Area3DPropDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\Area3DView.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseGLView.cpp
# End Source File
# Begin Source File

SOURCE=.\BestServerDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\BorderMLDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\BorderRadiusDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\BorderRep1DLG.cpp
# End Source File
# Begin Source File

SOURCE=.\BorderStyleDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrmArea.cpp
# End Source File
# Begin Source File

SOURCE=.\CircleRadiusDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\Code2NameCTY.cpp
# End Source File
# Begin Source File

SOURCE=.\column.cpp
# End Source File
# Begin Source File

SOURCE=.\columns.cpp
# End Source File
# Begin Source File

SOURCE=.\Contour_DEMDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Contour_DEMFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Contour_DEMView.cpp
# End Source File
# Begin Source File

SOURCE=.\ContourDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\CoordinatesDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\CountrySelectionDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\CoverageDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\DataBaseDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\DataBaseLDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\dataformatdisp.cpp
# End Source File
# Begin Source File

SOURCE=.\datagrid.cpp
# End Source File
# Begin Source File

SOURCE=.\DGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\DLLwrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\EditGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\EditWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\EffectiveHeigthDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\EffectiveHeigthFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\EffectiveHeigthSet.cpp
# End Source File
# Begin Source File

SOURCE=.\EffectiveHeigthView.cpp
# End Source File
# Begin Source File

SOURCE=.\Fassign1DLG.cpp
# End Source File
# Begin Source File

SOURCE=.\Fassign2DLG.cpp
# End Source File
# Begin Source File

SOURCE=.\field.cpp
# End Source File
# Begin Source File

SOURCE=.\fields.cpp
# End Source File
# Begin Source File

SOURCE=.\FileDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FileDLG_ChangedType.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\font.cpp
# End Source File
# Begin Source File

SOURCE=.\FresnelDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\FXM_F_D_rngDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\GE06cvaDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\GE06intDLG1.cpp
# End Source File
# Begin Source File

SOURCE=.\GE06repDLG1.cpp
# End Source File
# Begin Source File

SOURCE=.\GE06srvDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\GE84_EUDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\GE84_EUIDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\GE84_F_D_rngeDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\GE84_Functions.cpp
# End Source File
# Begin Source File

SOURCE=.\GE84BC2BCDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\GE89_EuDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\GE89_Functions.cpp
# End Source File
# Begin Source File

SOURCE=.\GE89_FXDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\GE89_FXM2BTDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\GE89_rangeDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\GridStepDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\HATA_Functions.cpp
# End Source File
# Begin Source File

SOURCE=.\HATADLG.cpp
# End Source File
# Begin Source File

SOURCE=.\HeffDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\HorizonDistanceDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\HorizonElevationDataDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\HorizonElevationDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\HTML_Report.cpp
# End Source File
# Begin Source File

SOURCE=.\IDWMMapDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\IDWMMapFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\IDWMMapView.cpp
# End Source File
# Begin Source File

SOURCE=.\Int_BC2BC_FreeDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Int_BC2BC_FreeFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Int_BC2BC_FreeView.cpp
# End Source File
# Begin Source File

SOURCE=.\Int_BT2BT_FreeDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Int_BT2BT_FreeFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Int_BT2BT_FreeView.cpp
# End Source File
# Begin Source File

SOURCE=.\Int_ES2ESoutDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\Int_Functions.cpp
# End Source File
# Begin Source File

SOURCE=.\Int_FX2FXDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\Int_FX2FXIDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\Int_FX2FXparDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\Int_FX2FXvparDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\Int_ParametersDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\InterModDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\IntES2ESparDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\iter.cpp
# End Source File
# Begin Source File

SOURCE=.\KFactor.cpp
# End Source File
# Begin Source File

SOURCE=.\LegendDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\LockDefs.cpp
# End Source File
# Begin Source File

SOURCE=.\LoSDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MainMapDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\MainMapFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MainMapView.cpp
# End Source File
# Begin Source File

SOURCE=.\mArray.cpp
# End Source File
# Begin Source File

SOURCE=.\MonitoringThDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\msflexgrid.cpp
# End Source File
# Begin Source File

SOURCE=.\MyDocManager.cpp
# End Source File
# Begin Source File

SOURCE=.\MyMultiDocTemplate.cpp
# End Source File
# Begin Source File

SOURCE=.\NFDmobile_Functions.cpp
# End Source File
# Begin Source File

SOURCE=.\NormalizeDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\OverlayDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\P154606_Functions.cpp
# End Source File
# Begin Source File

SOURCE=.\P1546_Functions.cpp
# End Source File
# Begin Source File

SOURCE=.\P1546DLG.cpp
# End Source File
# Begin Source File

SOURCE=.\P1812DLG.cpp
# End Source File
# Begin Source File

SOURCE=.\P370_Functions.cpp
# End Source File
# Begin Source File

SOURCE=.\P370DLG.cpp
# End Source File
# Begin Source File

SOURCE=.\P452_Functions.cpp
# End Source File
# Begin Source File

SOURCE=.\P452DLG.cpp
# End Source File
# Begin Source File

SOURCE=.\P527_526_Functions.cpp
# End Source File
# Begin Source File

SOURCE=.\P530_Functions.cpp
# End Source File
# Begin Source File

SOURCE=.\P530availabilityDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\P530DLG.cpp
# End Source File
# Begin Source File

SOURCE=.\P530RefPointsDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\picture.cpp
# End Source File
# Begin Source File

SOURCE=.\PowerCalculatorDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_Free_AreaDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_Free_AreaView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_Free_LineDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_Free_LineView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_Free_NetBDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_Free_NetBFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_Free_NetBView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_Free_NetFDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_Free_NetFFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_Free_NetFView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_Free_PolygonDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_Free_PolygonView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_HATA_AreaDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_HATA_AreaFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_HATA_AreaView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_HATA_NetBDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_HATA_NetBFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_HATA_NetBView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_HATA_NetFDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_HATA_NetFFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_HATA_NetFView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_LoS_AreaDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_LoS_AreaFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_LoS_AreaView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_LoS_LineDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_LoS_LineFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_LoS_LineView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_LoS_PolygonDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_LoS_PolygonFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_LoS_PolygonView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_AreaDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_AreaFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_AreaView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_LineDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_LineFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_LineView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_LinkDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_LinkFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_LinkView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_NetBDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_NetBFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_NetBView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_NetFDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_NetFFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_NetFView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_PolygonDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_PolygonFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_PolygonView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_AreaDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_AreaFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_AreaView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_LineDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_LineFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_LineView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_LinkDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_LinkFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_LinkView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_NetBDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_NetBFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_NetBView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_NetFDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_NetFFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_NetFView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_PolygonDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_PolygonFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_PolygonView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_AreaDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_AreaFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_AreaView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_LineDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_LineFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_LineView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_LinkDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_LinkFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_LinkView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_NetBDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_NetBFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_NetBView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_NetFDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_NetFFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_NetFView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_PolygonDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_PolygonFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_PolygonView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P452_LinkDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P452_LinkFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P452_LinkView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P526_LinkDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P526_LinkFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P526_LinkView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P526V14_LinkDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P526V14_LinkFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P526V14_LinkView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P530_LinkDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P530_LinkFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_P530_LinkView.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_Smooth_LinkDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_Smooth_LinkFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_Smooth_LinkView.cpp
# End Source File
# Begin Source File

SOURCE=.\ProfileDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ProfilePolygonDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ProfilePolygonView.cpp
# End Source File
# Begin Source File

SOURCE=.\ProfileView.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgressBar.cpp
# End Source File
# Begin Source File

SOURCE=.\properties.cpp
# End Source File
# Begin Source File

SOURCE=.\property.cpp
# End Source File
# Begin Source File

SOURCE=.\RGNtableDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\RGNtableFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\RGNtableSet.cpp
# End Source File
# Begin Source File

SOURCE=.\RGNtableView.cpp
# End Source File
# Begin Source File

SOURCE=.\rowcursor.cpp
# End Source File
# Begin Source File

SOURCE=.\selbookmarks.cpp
# End Source File
# Begin Source File

SOURCE=.\SmoothDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\SMS4DC.cpp
# End Source File
# Begin Source File

SOURCE=.\SMS4DC.rc
# End Source File
# Begin Source File

SOURCE=.\SMS4DCDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\SMS4DCView.cpp
# End Source File
# Begin Source File

SOURCE=.\SMS4DCView2.cpp
# End Source File
# Begin Source File

SOURCE=.\split.cpp
# End Source File
# Begin Source File

SOURCE=.\splits.cpp
# End Source File
# Begin Source File

SOURCE=.\SRVtableDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\SRVtableFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\SRVtableSet.cpp
# End Source File
# Begin Source File

SOURCE=.\SRVtableView.cpp
# End Source File
# Begin Source File

SOURCE=.\ST61_Functions.cpp
# End Source File
# Begin Source File

SOURCE=.\StartDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\StationsTableDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\StationsTableFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\StationsTableView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\stddataformatsdisp.cpp
# End Source File
# Begin Source File

SOURCE=.\SymbolDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\Tile.cpp
# End Source File
# Begin Source File

SOURCE=.\TxRxFilterDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\TxRxFiltersSet.cpp
# End Source File
# Begin Source File

SOURCE=.\UTM.cpp
# End Source File
# Begin Source File

SOURCE=.\VectorDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\VectorHandlingDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\VectorHandlingFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\VectorHandlingView.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\_recordset.h
# End Source File
# Begin Source File

SOURCE=.\AddESStationDLG.h
# End Source File
# Begin Source File

SOURCE=.\AddFreqDLG.h
# End Source File
# Begin Source File

SOURCE=.\AddStationDLG.h
# End Source File
# Begin Source File

SOURCE=.\AddStationRecSet.h
# End Source File
# Begin Source File

SOURCE=.\adodc.h
# End Source File
# Begin Source File

SOURCE=.\Allocations_DrawDoc.h
# End Source File
# Begin Source File

SOURCE=.\Allocations_DrawFrm.h
# End Source File
# Begin Source File

SOURCE=.\Allocations_DrawView.h
# End Source File
# Begin Source File

SOURCE=.\Ant3DDoc.h
# End Source File
# Begin Source File

SOURCE=.\Ant3DFrm.h
# End Source File
# Begin Source File

SOURCE=.\Ant3DPropDLG.h
# End Source File
# Begin Source File

SOURCE=.\Ant3DView.h
# End Source File
# Begin Source File

SOURCE=.\AntennaFormDoc.h
# End Source File
# Begin Source File

SOURCE=.\AntennaFormFrm.h
# End Source File
# Begin Source File

SOURCE=.\AntennaFormView.h
# End Source File
# Begin Source File

SOURCE=.\ANTpatternDLG.h
# End Source File
# Begin Source File

SOURCE=.\AP7_CordContourDLG.h
# End Source File
# Begin Source File

SOURCE=.\AP7_ESantPattern.h
# End Source File
# Begin Source File

SOURCE=.\AP7_OptionsDLG.h
# End Source File
# Begin Source File

SOURCE=.\Ap7_StyleDLG.h
# End Source File
# Begin Source File

SOURCE=.\AP7EarthStationDLG.h
# End Source File
# Begin Source File

SOURCE=.\AP7ESDLG.h
# End Source File
# Begin Source File

SOURCE=.\Area3DDoc.h
# End Source File
# Begin Source File

SOURCE=.\Area3DFrm.h
# End Source File
# Begin Source File

SOURCE=.\Area3DPropDLG.h
# End Source File
# Begin Source File

SOURCE=.\Area3DView.h
# End Source File
# Begin Source File

SOURCE=.\BaseGLView.h
# End Source File
# Begin Source File

SOURCE=.\BestServerDLG.h
# End Source File
# Begin Source File

SOURCE=.\BorderMLDLG.h
# End Source File
# Begin Source File

SOURCE=.\BorderRadiusDLG.h
# End Source File
# Begin Source File

SOURCE=.\BorderRep1DLG.h
# End Source File
# Begin Source File

SOURCE=.\BorderStyleDLG.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrmArea.h
# End Source File
# Begin Source File

SOURCE=.\CircleRadiusDLG.h
# End Source File
# Begin Source File

SOURCE=.\Code2NameCTY.h
# End Source File
# Begin Source File

SOURCE=.\column.h
# End Source File
# Begin Source File

SOURCE=.\columns.h
# End Source File
# Begin Source File

SOURCE=.\Contour_DEMDoc.h
# End Source File
# Begin Source File

SOURCE=.\Contour_DEMFrm.h
# End Source File
# Begin Source File

SOURCE=.\Contour_DEMView.h
# End Source File
# Begin Source File

SOURCE=.\ContourDLG.h
# End Source File
# Begin Source File

SOURCE=.\CoordinatesDLG.h
# End Source File
# Begin Source File

SOURCE=.\CountrySelectionDLG.h
# End Source File
# Begin Source File

SOURCE=.\CoverageDLG.h
# End Source File
# Begin Source File

SOURCE=.\DataBaseDLG.h
# End Source File
# Begin Source File

SOURCE=.\DataBaseLDLG.h
# End Source File
# Begin Source File

SOURCE=.\dataformatdisp.h
# End Source File
# Begin Source File

SOURCE=.\datagrid.h
# End Source File
# Begin Source File

SOURCE=.\DGrid.h
# End Source File
# Begin Source File

SOURCE=.\DLLwrapper.h
# End Source File
# Begin Source File

SOURCE=.\EditGrid.h
# End Source File
# Begin Source File

SOURCE=.\EditWnd.h
# End Source File
# Begin Source File

SOURCE=.\EffectiveHeigthDoc.h
# End Source File
# Begin Source File

SOURCE=.\EffectiveHeigthFrm.h
# End Source File
# Begin Source File

SOURCE=.\EffectiveHeigthSet.h
# End Source File
# Begin Source File

SOURCE=.\EffectiveHeigthView.h
# End Source File
# Begin Source File

SOURCE=.\Fassign1DLG.h
# End Source File
# Begin Source File

SOURCE=.\Fassign2DLG.h
# End Source File
# Begin Source File

SOURCE=.\field.h
# End Source File
# Begin Source File

SOURCE=.\fields.h
# End Source File
# Begin Source File

SOURCE=.\FileDlg.h
# End Source File
# Begin Source File

SOURCE=.\FileDLG_ChangedType.h
# End Source File
# Begin Source File

SOURCE=.\FolderDLG.h
# End Source File
# Begin Source File

SOURCE=.\font.h
# End Source File
# Begin Source File

SOURCE=.\FresnelDLG.h
# End Source File
# Begin Source File

SOURCE=.\FXM_F_D_rngDLG.h
# End Source File
# Begin Source File

SOURCE=.\GE06cvaDLG.h
# End Source File
# Begin Source File

SOURCE=.\GE06intDLG1.h
# End Source File
# Begin Source File

SOURCE=.\GE06repDLG1.h
# End Source File
# Begin Source File

SOURCE=.\GE06srvDLG.h
# End Source File
# Begin Source File

SOURCE=.\GE84_EUDLG.h
# End Source File
# Begin Source File

SOURCE=.\GE84_EUIDLG.h
# End Source File
# Begin Source File

SOURCE=.\GE84_F_D_rngeDLG.h
# End Source File
# Begin Source File

SOURCE=.\GE84_Functions.h
# End Source File
# Begin Source File

SOURCE=.\GE84BC2BCDLG.h
# End Source File
# Begin Source File

SOURCE=.\GE89_EuDLG.h
# End Source File
# Begin Source File

SOURCE=.\GE89_Functions.h
# End Source File
# Begin Source File

SOURCE=.\GE89_FXDLG.h
# End Source File
# Begin Source File

SOURCE=.\GE89_FXM2BTDLG.h
# End Source File
# Begin Source File

SOURCE=.\GE89_rangeDLG.h
# End Source File
# Begin Source File

SOURCE=.\GridStepDLG.h
# End Source File
# Begin Source File

SOURCE=.\HATA_Functions.h
# End Source File
# Begin Source File

SOURCE=.\HATADLG.h
# End Source File
# Begin Source File

SOURCE=.\HeffDLG.h
# End Source File
# Begin Source File

SOURCE=.\HorizonDistanceDLG.h
# End Source File
# Begin Source File

SOURCE=.\HorizonElevationDataDLG.h
# End Source File
# Begin Source File

SOURCE=.\HorizonElevationDLG.h
# End Source File
# Begin Source File

SOURCE=.\HTML_Report.h
# End Source File
# Begin Source File

SOURCE=.\IDWMMapDoc.h
# End Source File
# Begin Source File

SOURCE=.\IDWMMapFrm.h
# End Source File
# Begin Source File

SOURCE=.\IDWMMapView.h
# End Source File
# Begin Source File

SOURCE=.\Int_BC2BC_FreeDoc.h
# End Source File
# Begin Source File

SOURCE=.\Int_BC2BC_FreeFrm.h
# End Source File
# Begin Source File

SOURCE=.\Int_BC2BC_FreeView.h
# End Source File
# Begin Source File

SOURCE=.\Int_BT2BT_FreeDoc.h
# End Source File
# Begin Source File

SOURCE=.\Int_BT2BT_FreeFrm.h
# End Source File
# Begin Source File

SOURCE=.\Int_BT2BT_FreeView.h
# End Source File
# Begin Source File

SOURCE=.\Int_ES2ESoutDLG.h
# End Source File
# Begin Source File

SOURCE=.\Int_Functions.h
# End Source File
# Begin Source File

SOURCE=.\Int_FX2FXDLG.h
# End Source File
# Begin Source File

SOURCE=.\Int_FX2FXIDLG.h
# End Source File
# Begin Source File

SOURCE=.\Int_FX2FXparDLG.h
# End Source File
# Begin Source File

SOURCE=.\Int_FX2FXvparDLG.h
# End Source File
# Begin Source File

SOURCE=.\Int_ParametersDLG.h
# End Source File
# Begin Source File

SOURCE=.\InterModDLG.h
# End Source File
# Begin Source File

SOURCE=.\IntES2ESparDLG.h
# End Source File
# Begin Source File

SOURCE=.\iter.h
# End Source File
# Begin Source File

SOURCE=.\KFactor.h
# End Source File
# Begin Source File

SOURCE=.\LegendDLG.h
# End Source File
# Begin Source File

SOURCE=.\LockDefs.h
# End Source File
# Begin Source File

SOURCE=.\LoSDLG.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MainMapDoc.h
# End Source File
# Begin Source File

SOURCE=.\MainMapFrm.h
# End Source File
# Begin Source File

SOURCE=.\MainMapView.h
# End Source File
# Begin Source File

SOURCE=.\mArray.h
# End Source File
# Begin Source File

SOURCE=.\memdc.h
# End Source File
# Begin Source File

SOURCE=.\MonitoringThDLG.h
# End Source File
# Begin Source File

SOURCE=.\msflexgrid.h
# End Source File
# Begin Source File

SOURCE=.\MyDocManager.h
# End Source File
# Begin Source File

SOURCE=.\MyMultiDocTemplate.h
# End Source File
# Begin Source File

SOURCE=.\NFDmobile_Functions.h
# End Source File
# Begin Source File

SOURCE=.\NormalizeDLG.h
# End Source File
# Begin Source File

SOURCE=.\OverlayDLG.h
# End Source File
# Begin Source File

SOURCE=.\P154606_Functions.h
# End Source File
# Begin Source File

SOURCE=.\P1546_Functions.h
# End Source File
# Begin Source File

SOURCE=.\P1546DLG.h
# End Source File
# Begin Source File

SOURCE=.\P1812DLG.h
# End Source File
# Begin Source File

SOURCE=.\P370_Functions.h
# End Source File
# Begin Source File

SOURCE=.\P370DLG.h
# End Source File
# Begin Source File

SOURCE=.\P452_Functions.h
# End Source File
# Begin Source File

SOURCE=.\P452DLG.h
# End Source File
# Begin Source File

SOURCE=.\P527_526_Functions.h
# End Source File
# Begin Source File

SOURCE=.\P530_Functions.h
# End Source File
# Begin Source File

SOURCE=.\P530availabilityDLG.h
# End Source File
# Begin Source File

SOURCE=.\P530DLG.h
# End Source File
# Begin Source File

SOURCE=.\P530RefPointsDLG.h
# End Source File
# Begin Source File

SOURCE=.\picture.h
# End Source File
# Begin Source File

SOURCE=.\PowerCalculatorDLG.h
# End Source File
# Begin Source File

SOURCE=.\Pro_Free_AreaDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_Free_AreaView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_Free_LineDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_Free_LineView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_Free_NetBDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_Free_NetBFrm.h
# End Source File
# Begin Source File

SOURCE=.\Pro_Free_NetBView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_Free_NetFDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_Free_NetFFrm.h
# End Source File
# Begin Source File

SOURCE=.\Pro_Free_NetFView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_Free_PolygonDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_Free_PolygonView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_HATA_AreaDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_HATA_AreaFrm.h
# End Source File
# Begin Source File

SOURCE=.\Pro_HATA_AreaView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_HATA_NetBDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_HATA_NetBFrm.h
# End Source File
# Begin Source File

SOURCE=.\Pro_HATA_NetBView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_HATA_NetFDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_HATA_NetFFrm.h
# End Source File
# Begin Source File

SOURCE=.\Pro_HATA_NetFView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_LoS_AreaDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_LoS_AreaFrm.h
# End Source File
# Begin Source File

SOURCE=.\Pro_LoS_AreaView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_LoS_LineDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_LoS_LineFrm.h
# End Source File
# Begin Source File

SOURCE=.\Pro_LoS_LineView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_LoS_PolygonDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_LoS_PolygonFrm.h
# End Source File
# Begin Source File

SOURCE=.\Pro_LoS_PolygonView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_AreaDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_AreaFrm.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_AreaView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_LineDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_LineFrm.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_LineView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_LinkDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_LinkFrm.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_LinkView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_NetBDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_NetBFrm.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_NetBView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_NetFDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_NetFFrm.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_NetFView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_PolygonDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_PolygonFrm.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1546_PolygonView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_AreaDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_AreaFrm.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_AreaView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_LineDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_LineFrm.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_LineView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_LinkDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_LinkFrm.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_LinkView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_NetBDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_NetBFrm.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_NetBView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_NetFDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_NetFFrm.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_NetFView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_PolygonDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_PolygonFrm.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P1812_PolygonView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_AreaDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_AreaFrm.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_AreaView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_LineDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_LineFrm.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_LineView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_LinkDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_LinkFrm.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_LinkView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_NetBDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_NetBFrm.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_NetBView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_NetFDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_NetFFrm.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_NetFView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_PolygonDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_PolygonFrm.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P370_PolygonView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P452_LinkDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P452_LinkFrm.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P452_LinkView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P526_LinkDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P526_LinkFrm.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P526_LinkView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P526V14_LinkDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P526V14_LinkFrm.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P526V14_LinkView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P530_LinkDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P530_LinkFrm.h
# End Source File
# Begin Source File

SOURCE=.\Pro_P530_LinkView.h
# End Source File
# Begin Source File

SOURCE=.\Pro_Smooth_LinkDoc.h
# End Source File
# Begin Source File

SOURCE=.\Pro_Smooth_LinkFrm.h
# End Source File
# Begin Source File

SOURCE=.\Pro_Smooth_LinkView.h
# End Source File
# Begin Source File

SOURCE=.\ProfileDoc.h
# End Source File
# Begin Source File

SOURCE=.\ProfilePolygonDoc.h
# End Source File
# Begin Source File

SOURCE=.\ProfilePolygonView.h
# End Source File
# Begin Source File

SOURCE=.\ProfileView.h
# End Source File
# Begin Source File

SOURCE=.\ProgressBar.h
# End Source File
# Begin Source File

SOURCE=.\properties.h
# End Source File
# Begin Source File

SOURCE=.\property.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RGNtableDoc.h
# End Source File
# Begin Source File

SOURCE=.\RGNtableFrm.h
# End Source File
# Begin Source File

SOURCE=.\RGNtableSet.h
# End Source File
# Begin Source File

SOURCE=.\RGNtableView.h
# End Source File
# Begin Source File

SOURCE=.\rowcursor.h
# End Source File
# Begin Source File

SOURCE=.\selbookmarks.h
# End Source File
# Begin Source File

SOURCE=.\SmoothDLG.h
# End Source File
# Begin Source File

SOURCE=.\SMS4DC.h
# End Source File
# Begin Source File

SOURCE=.\SMS4DCDoc.h
# End Source File
# Begin Source File

SOURCE=.\SMS4DCView.h
# End Source File
# Begin Source File

SOURCE=.\split.h
# End Source File
# Begin Source File

SOURCE=.\splits.h
# End Source File
# Begin Source File

SOURCE=.\Sproeval.h
# End Source File
# Begin Source File

SOURCE=.\SPROMEPS.H
# End Source File
# Begin Source File

SOURCE=.\SRVtableDoc.h
# End Source File
# Begin Source File

SOURCE=.\SRVtableFrm.h
# End Source File
# Begin Source File

SOURCE=.\SRVtableSet.h
# End Source File
# Begin Source File

SOURCE=.\SRVtableView.h
# End Source File
# Begin Source File

SOURCE=.\ST61_Functions.h
# End Source File
# Begin Source File

SOURCE=.\StartDLG.h
# End Source File
# Begin Source File

SOURCE=.\StationsTableDoc.h
# End Source File
# Begin Source File

SOURCE=.\StationsTableFrm.h
# End Source File
# Begin Source File

SOURCE=.\StationsTableView.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\stddataformatsdisp.h
# End Source File
# Begin Source File

SOURCE=.\SymbolDLG.h
# End Source File
# Begin Source File

SOURCE=.\Tile.h
# End Source File
# Begin Source File

SOURCE=.\TxRxFilterDLG.h
# End Source File
# Begin Source File

SOURCE=.\TxRxFiltersSet.h
# End Source File
# Begin Source File

SOURCE=.\UTM.h
# End Source File
# Begin Source File

SOURCE=.\VectorDLG.h
# End Source File
# Begin Source File

SOURCE=.\VectorHandlingDoc.h
# End Source File
# Begin Source File

SOURCE=.\VectorHandlingFrm.h
# End Source File
# Begin Source File

SOURCE=.\VectorHandlingView.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\3dgarro.cur
# End Source File
# Begin Source File

SOURCE=.\res\allocati.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ARW11NE.ICO
# End Source File
# Begin Source File

SOURCE=.\res\ARW11SW.ICO
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor2.cur
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

SOURCE=.\res\EARTH.ICO
# End Source File
# Begin Source File

SOURCE=.\res\edit1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\edit2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\edit3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\folder.ico
# End Source File
# Begin Source File

SOURCE=.\res\group.ico
# End Source File
# Begin Source File

SOURCE=.\res\handno.cur
# End Source File
# Begin Source File

SOURCE=.\res\harrow.cur
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

SOURCE=.\res\ico00015.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00016.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00017.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00018.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00019.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00020.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00021.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00022.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00023.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00024.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00025.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00026.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00027.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00028.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00029.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00030.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00031.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00032.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00033.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00034.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00035.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00036.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00037.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00038.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00039.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00040.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00041.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00042.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00043.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00044.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00045.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00046.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00047.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00048.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_f.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_sms4.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_test.ico
# End Source File
# Begin Source File

SOURCE=".\res\ITU-BDT.BMP"
# End Source File
# Begin Source File

SOURCE=.\res\itu_50x57.bmp
# End Source File
# Begin Source File

SOURCE=.\res\list1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\list2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\load1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\load2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\notice.ICO
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

SOURCE=.\res\SMS4DC.ico
# End Source File
# Begin Source File

SOURCE=.\res\SMS4DC.rc2
# End Source File
# Begin Source File

SOURCE=.\res\SMS4DCDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\SMS4DCtyp.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sort_az1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sort_az2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sort_za1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sort_za2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section SMS4DC : {00000569-0000-0010-8000-00AA006D2EA4}
# 	2:5:Class:CField
# 	2:10:HeaderFile:field.h
# 	2:8:ImplFile:field.cpp
# End Section
# Section SMS4DC : {00000504-0000-0010-8000-00AA006D2EA4}
# 	2:5:Class:CProperties
# 	2:10:HeaderFile:properties.h
# 	2:8:ImplFile:properties.cpp
# End Section
# Section SMS4DC : {CDE57A52-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:CSelBookmarks
# 	2:10:HeaderFile:selbookmarks.h
# 	2:8:ImplFile:selbookmarks.cpp
# End Section
# Section SMS4DC : {00000564-0000-0010-8000-00AA006D2EA4}
# 	2:5:Class:CFields
# 	2:10:HeaderFile:fields.h
# 	2:8:ImplFile:fields.cpp
# End Section
# Section SMS4DC : {00000503-0000-0010-8000-00AA006D2EA4}
# 	2:5:Class:CProperty
# 	2:10:HeaderFile:property.h
# 	2:8:ImplFile:property.cpp
# End Section
# Section SMS4DC : {67397AA3-7FB1-11D0-B148-00A0C922E820}
# 	2:21:DefaultSinkHeaderFile:adodc.h
# 	2:16:DefaultSinkClass:CAdodc
# End Section
# Section SMS4DC : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
# Section SMS4DC : {CDE57A41-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:CDataGrid
# 	2:10:HeaderFile:datagrid.h
# 	2:8:ImplFile:datagrid.cpp
# End Section
# Section SMS4DC : {9F6AA700-D188-11CD-AD48-00AA003C9CB6}
# 	2:5:Class:CRowCursor
# 	2:10:HeaderFile:rowcursor.h
# 	2:8:ImplFile:rowcursor.cpp
# End Section
# Section SMS4DC : {CDE57A50-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:CColumns
# 	2:10:HeaderFile:columns.h
# 	2:8:ImplFile:columns.cpp
# End Section
# Section SMS4DC : {CDE57A54-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:CSplit
# 	2:10:HeaderFile:split.h
# 	2:8:ImplFile:split.cpp
# End Section
# Section SMS4DC : {00000556-0000-0010-8000-00AA006D2EA4}
# 	2:5:Class:C_Recordset
# 	2:10:HeaderFile:_recordset.h
# 	2:8:ImplFile:_recordset.cpp
# End Section
# Section SMS4DC : {E675F3F0-91B5-11D0-9484-00A0C91110ED}
# 	2:5:Class:CDataFormatDisp
# 	2:10:HeaderFile:dataformatdisp.h
# 	2:8:ImplFile:dataformatdisp.cpp
# End Section
# Section SMS4DC : {99FF4676-FFC3-11D0-BD02-00C04FC2FB86}
# 	2:5:Class:CStdDataFormatsDisp
# 	2:10:HeaderFile:stddataformatsdisp.h
# 	2:8:ImplFile:stddataformatsdisp.cpp
# End Section
# Section SMS4DC : {CDE57A4F-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:CColumn
# 	2:10:HeaderFile:column.h
# 	2:8:ImplFile:column.cpp
# End Section
# Section SMS4DC : {47A738F1-7FAF-11D0-B148-00A0C922E820}
# 	2:5:Class:CAdodc
# 	2:10:HeaderFile:adodc.h
# 	2:8:ImplFile:adodc.cpp
# End Section
# Section SMS4DC : {5F4DF280-531B-11CF-91F6-C2863C385E30}
# 	2:5:Class:CMSFlexGrid
# 	2:10:HeaderFile:msflexgrid.h
# 	2:8:ImplFile:msflexgrid.cpp
# End Section
# Section SMS4DC : {CDE57A43-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:21:DefaultSinkHeaderFile:datagrid.h
# 	2:16:DefaultSinkClass:CDataGrid
# End Section
# Section SMS4DC : {CDE57A53-8B86-11D0-B3C6-00A0C90AEA82}
# 	2:5:Class:CSplits
# 	2:10:HeaderFile:splits.h
# 	2:8:ImplFile:splits.cpp
# End Section
# Section SMS4DC : {6262D3A0-531B-11CF-91F6-C2863C385E30}
# 	2:21:DefaultSinkHeaderFile:msflexgrid.h
# 	2:16:DefaultSinkClass:CMSFlexGrid
# End Section
# Section SMS4DC : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
