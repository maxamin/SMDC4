; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CThalesDrawView
LastTemplate=CListCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "thalesdrawdll.h"
LastPage=0

ClassCount=8
Class1=CChildFrame
Class2=CThalesDrawDLLApp
Class3=CThalesDrawDoc
Class4=CThalesDrawView

ResourceCount=8
Resource1=IDD_DIALOG_TBE (English (U.S.))
Class5=CFrqTime
Resource2=IDD_DIALOG_FrqTime (English (U.S.))
Class6=CTBEpolar
Resource3=IDR_THALESTYPE (English (U.S.))
Resource4=IDD_DIALOG_FrqTimeList
Resource5="IDD_FILEDIALOG_CHECK"
Resource6=IDD_DIALOG_FrqTimeList (English (U.S.))
Class7=CFrqTimeList
Class8=CColorListCtrl
Resource7=IDD_DIALOG_TBE
Resource8=IDR_THALESTYPE

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
LastObject=CChildFrame
Filter=M
VirtualFilter=mfWC

[CLS:CThalesDrawDLLApp]
Type=0
BaseClass=CWinApp
HeaderFile=ThalesDrawDLL.h
ImplementationFile=ThalesDrawDLL.cpp

[CLS:CThalesDrawDoc]
Type=0
BaseClass=CDocument
HeaderFile=ThalesDrawDoc.h
ImplementationFile=ThalesDrawDoc.cpp

[CLS:CThalesDrawView]
Type=0
BaseClass=CView
HeaderFile=ThalesDrawView.h
ImplementationFile=ThalesDrawView.cpp
Filter=C
VirtualFilter=VWC
LastObject=CThalesDrawView

[MNU:IDR_THALESTYPE (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_SAVE
Command3=ID_FILE_SAVE_AS
Command4=ID_FILE_PRINT
Command5=ID_FILE_PRINT_PREVIEW
Command6=ID_FILE_PRINT_SETUP
Command7=ID_APP_EXIT
Command8=ID_TOOLS_COLORMAP_TOPO0
Command9=ID_TOOLS_COLORMAP_TOPO1
Command10=ID_TOOLS_COLORMAP_JET
Command11=ID_TOOLS_COLORMAP_GRAY
Command12=ID_TOOLS_COLORMAP_PINK
Command13=ID_TOOLS_COLORMAP_COPPER
Command14=ID_TOOLS_COLORMAP_GLOBE
Command15=ID_TOOLS_BACKGROUNDCOLOR
Command16=ID_TOOLS_AXISCOLOR
Command17=ID_TOOLS_TEXTCOLOR
Command18=ID_TOOLS_Grid
Command19=ID_BUTTON_LinewidthP
Command20=ID_BUTTON_LinewidthN
Command21=ID_TOOLS_MODE_LINE
Command22=ID_TOOLS_MODE_BARCHART
Command23=ID_TOOLS_VALUE_OCCUPANCYRATE
Command24=ID_TOOLS_VALUE_GLOBALRATE
Command25=ID_TOOLS_VALUE_MAXLEVEL
Command26=ID_TOOLS_VALUE_AVELEVEL
Command27=ID_TOOLS_VALUE_BEARING_DIRECTION
Command28=ID_TOOLS_VALUE_BEARING_QUALITY
Command29=ID_TOOLS_VALUE_BANDWIDTH_BETAMETHOD
Command30=ID_TOOLS_VALUE_BANDWIDTH_XDBMETHOD
Command31=ID_TOOLS_VALUE_MODULATIONRATE
Command32=ID_TOOLS_VALUE_FREQUENCYDRIFTING
Command33=ID_TOOLS_VALUE_FIELDSTRENGTH
Command34=ID_TOOLS_3D
Command35=ID_TOOLS_2DFREQVALUE
Command36=ID_BUTTON_TimeSelect
Command37=ID_TOOLS_2DTIMEVALUE
Command38=ID_BUTTON_FrqSelect
Command39=ID_BUTTON_ShowLegend
CommandCount=39

[TB:IDR_THALESTYPE (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_SAVE
Command3=ID_FILE_PRINT
Command4=ID_FILE_PRINT_PREVIEW
Command5=ID_TOOLS_MODE_BARCHART
Command6=ID_TOOLS_MODE_LINE
Command7=ID_TOOLS_3D
Command8=ID_TOOLS_2DFREQVALUE
Command9=ID_BUTTON_TimeSelect
Command10=ID_TOOLS_2DTIMEVALUE
Command11=ID_BUTTON_FrqSelect
Command12=ID_TOOLS_Grid
Command13=ID_BUTTON_polar
Command14=ID_BUTTON_ShowLegend
Command15=ID_BUTTON_LinewidthP
Command16=ID_BUTTON_LinewidthN
CommandCount=16

[DLG:IDD_DIALOG_FrqTime (English (U.S.))]
Type=1
Class=CFrqTime
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1073741824
Control3=IDC_MSFLEXGRID1,{6262D3A0-531B-11CF-91F6-C2863C385E30},1342242816

[CLS:CFrqTime]
Type=0
HeaderFile=FrqTime.h
ImplementationFile=FrqTime.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_BUTTON_TimeSelect

[DLG:IDD_DIALOG_TBE (English (U.S.))]
Type=1
Class=CTBEpolar
ControlCount=20
Control1=IDOK,button,1073741825
Control2=IDCANCEL,button,1073741824
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC_D,static,1342308353
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC_Q,static,1342308353
Control7=IDC_STATIC_L0,static,1342308354
Control8=IDC_STATIC_L,static,1342308353
Control9=IDC_RADIO1,button,1342177289
Control10=IDC_RADIO2,button,1342177289
Control11=IDC_STATIC,static,1342177287
Control12=IDC_STATIC,static,1342177287
Control13=IDC_STATIC,static,1342308352
Control14=IDC_COMBO_Fr,combobox,1344339971
Control15=IDC_STATIC_Time,static,1342308352
Control16=IDC_COMBO_Time,combobox,1344339971
Control17=IDC_CHECK1,button,1342242819
Control18=IDC_STATIC,static,1342177287
Control19=IDC_STATIC,static,1342177287
Control20=IDC_STATIC_R,static,1342308353

[CLS:CTBEpolar]
Type=0
HeaderFile=TBEpolar.h
ImplementationFile=TBEpolar.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_BUTTON_polar
VirtualFilter=dWC

[MNU:IDR_THALESTYPE]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_SAVE
Command3=ID_FILE_SAVE_AS
Command4=ID_FILE_PRINT
Command5=ID_FILE_PRINT_PREVIEW
Command6=ID_FILE_PRINT_SETUP
Command7=ID_APP_EXIT
Command8=ID_TOOLS_COLORMAP_TOPO0
Command9=ID_TOOLS_COLORMAP_TOPO1
Command10=ID_TOOLS_COLORMAP_JET
Command11=ID_TOOLS_COLORMAP_GRAY
Command12=ID_TOOLS_COLORMAP_PINK
Command13=ID_TOOLS_COLORMAP_COPPER
Command14=ID_TOOLS_COLORMAP_GLOBE
Command15=ID_TOOLS_BACKGROUNDCOLOR
Command16=ID_TOOLS_AXISCOLOR
Command17=ID_TOOLS_TEXTCOLOR
Command18=ID_TOOLS_Grid
Command19=ID_BUTTON_LinewidthP
Command20=ID_BUTTON_LinewidthN
Command21=ID_TOOLS_MODE_LINE
Command22=ID_TOOLS_MODE_BARCHART
Command23=ID_TOOLS_VALUE_OCCUPANCYRATE
Command24=ID_TOOLS_VALUE_GLOBALRATE
Command25=ID_TOOLS_VALUE_MAXLEVEL
Command26=ID_TOOLS_VALUE_AVELEVEL
Command27=ID_TOOLS_VALUE_BEARING_DIRECTION
Command28=ID_TOOLS_VALUE_BEARING_QUALITY
Command29=ID_TOOLS_VALUE_BANDWIDTH_BETAMETHOD
Command30=ID_TOOLS_VALUE_BANDWIDTH_XDBMETHOD
Command31=ID_TOOLS_VALUE_MODULATIONRATE
Command32=ID_TOOLS_VALUE_FREQUENCYDRIFTING
Command33=ID_TOOLS_VALUE_FIELDSTRENGTH
Command34=ID_TOOLS_3D
Command35=ID_TOOLS_2DFREQVALUE
Command36=ID_BUTTON_TimeSelect
Command37=ID_TOOLS_2DTIMEVALUE
Command38=ID_BUTTON_FrqSelect
Command39=ID_BUTTON_ShowLegend
CommandCount=39

[DLG:IDD_DIALOG_TBE]
Type=1
Class=CTBEpolar
ControlCount=21
Control1=IDOK,button,1073741825
Control2=IDCANCEL,button,1073741824
Control3=IDC_STATICb1,static,1342308352
Control4=IDC_STATIC_D,static,1342308353
Control5=IDC_STATICb2,static,1342308352
Control6=IDC_STATIC_Q,static,1342308353
Control7=IDC_STATIC_L0,static,1342308354
Control8=IDC_STATIC_L,static,1342308353
Control9=IDC_RADIO1,button,1342177289
Control10=IDC_RADIO2,button,1342177289
Control11=IDC_STATIC,static,1342177287
Control12=IDC_STATIC,static,1342177287
Control13=IDC_STATICb3,static,1342308354
Control14=IDC_COMBO_Fr,combobox,1344339971
Control15=IDC_STATIC_Time,static,1342308354
Control16=IDC_COMBO_Time,combobox,1344339971
Control17=IDC_CHECK1,button,1342242819
Control18=IDC_STATIC,static,1342177287
Control19=IDC_STATIC,static,1342177287
Control20=IDC_STATIC_R,static,1342308353
Control21=IDC_BUTTON_googleEarth,button,1342251008

[TB:IDR_THALESTYPE]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_SAVE
Command3=ID_FILE_PRINT
Command4=ID_FILE_PRINT_PREVIEW
Command5=ID_TOOLS_MODE_BARCHART
Command6=ID_TOOLS_MODE_LINE
Command7=ID_TOOLS_3D
Command8=ID_TOOLS_2DFREQVALUE
Command9=ID_BUTTON_TimeSelect
Command10=ID_TOOLS_2DTIMEVALUE
Command11=ID_BUTTON_FrqSelect
Command12=ID_TOOLS_Grid
Command13=ID_BUTTON_polar
Command14=ID_BUTTON_ShowLegend
Command15=ID_BUTTON_LinewidthP
Command16=ID_BUTTON_LinewidthN
CommandCount=16

[DLG:IDD_DIALOG_FrqTimeList]
Type=1
Class=CFrqTimeList
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1073741824
Control3=IDC_LIST1,SysListView32,1342242821

[CLS:CFrqTimeList]
Type=0
HeaderFile=FrqTimeList.h
ImplementationFile=FrqTimeList.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_BUTTON_TimeSelect

[DLG:IDD_DIALOG_FrqTimeList (English (U.S.))]
Type=1
Class=CFrqTimeList
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1073741824
Control3=IDC_LIST1,SysListView32,1342242821

[ACL:IDR_THALESTYPE (English (U.S.))]
Type=1
Class=?
Command1=ID_BUTTON_LinewidthP
Command2=ID_TOOLS_Grid
Command3=ID_BUTTON_ShowLegend
Command4=ID_BUTTON_LinewidthN
Command5=ID_FILE_OPEN
CommandCount=5

[CLS:CColorListCtrl]
Type=0
HeaderFile=ColorListCtrl.h
ImplementationFile=ColorListCtrl.cpp
BaseClass=CListCtrl
Filter=W

[ACL:IDR_THALESTYPE]
Type=1
Class=?
Command1=ID_BUTTON_LinewidthP
Command2=ID_TOOLS_Grid
Command3=ID_BUTTON_ShowLegend
Command4=ID_BUTTON_LinewidthN
Command5=ID_FILE_OPEN
CommandCount=5

[DLG:"IDD_FILEDIALOG_CHECK"]
Type=1
Class=?
ControlCount=1
Control1=IDC_CHECK_ShowGoogle,button,1342242819

