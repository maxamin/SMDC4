; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTreeSearch
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "administrative.h"
LastPage=0
CDK=Y

ClassCount=23
Class1=CAdministrativeApp
Class2=CAntPattern
Class3=CAudit
Class4=CCatSelect
Class5=CChildFrame
Class6=CCustomReport
Class7=CEditGrid
Class8=CEditWnd
Class9=CESAntPat
Class10=CESNotice
Class11=CGrpDetails
Class12=CLeftView
Class13=CMainFrame
Class14=CMoveStation
Class15=CNotice
Class16=CPaymentDlg
Class17=CReceivers
Class18=CRightGrid
Class19=CTreeviewDoc
Class20=CTreeviewView
Class21=CTxRxFilterDLG
Class22=CTxRxFiltersSet

ResourceCount=30
Resource1=IDR_BILLING_MENU
Resource2=IDD_SRS_NOTICE
Resource3=IDD_GRID
Resource4=IDR_ALLOT_MENU
Resource5=IDR_TREEVITYPE
Resource6=IDR_ANTENNA_MENU
Resource7=IDR_FREQUENCY_MENU
Resource8=IDR_ESANT_MENU
Resource9=IDR_OWNER_MENU
Resource10=IDD_TREE_SEARCH
Resource11=IDD_NOTICE
Resource12=IDD_MOVE_STATION
Resource13=IDR_CONTOUR_MENU
Resource14=IDD_AuditTrail
Resource15=IDD_ES_ANT_PAT
Resource16=IDR_RECEIVER_MENU
Resource17=IDR_LICENSE_MENU
Resource18=IDR_STATION_MENU
Resource19=IDR_EQUIPMENT_MENU
Resource20=IDD_GrpDetails
Resource21=IDD_ADD_RECEIVER
Resource22=IDD_EQ_CAT
Resource23=IDD_PAYMENT
Resource24=IDD_ANT_PATTERN
Resource25=IDR_ES_MENU
Resource26=IDD_CUSTOM_REPORT
Resource27=IDD_TxRxFilterDLG
Resource28=IDR_GROUP_MENU
Resource29=IDD_ABOUTBOX
Class23=CTreeSearch
Resource30=IDR_MAINFRAME

[CLS:CAdministrativeApp]
Type=0
BaseClass=CWinApp
HeaderFile=Administrative.h
ImplementationFile=Administrative.cpp

[CLS:CAntPattern]
Type=0
BaseClass=CDialog
HeaderFile=AntPattern.h
ImplementationFile=AntPattern.cpp

[CLS:CAudit]
Type=0
BaseClass=CDialog
HeaderFile=Audit.h
ImplementationFile=Audit.cpp

[CLS:CCatSelect]
Type=0
BaseClass=CDialog
HeaderFile=CatSelect.h
ImplementationFile=CatSelect.cpp

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp

[CLS:CCustomReport]
Type=0
BaseClass=CDialog
HeaderFile=CustomReport.h
ImplementationFile=CustomReport.cpp
LastObject=IDC_ALL
Filter=D
VirtualFilter=dWC

[CLS:CEditGrid]
Type=0
BaseClass=CWnd
HeaderFile=EditGrid.h
ImplementationFile=EditGrid.cpp

[CLS:CEditWnd]
Type=0
BaseClass=CEdit
HeaderFile=EditWnd.h
ImplementationFile=EditWnd.cpp

[CLS:CESAntPat]
Type=0
BaseClass=CDialog
HeaderFile=ESAntPat.h
ImplementationFile=ESAntPat.cpp

[CLS:CESNotice]
Type=0
BaseClass=CDialog
HeaderFile=ESNotice.h
ImplementationFile=ESNotice.cpp

[CLS:CGrpDetails]
Type=0
BaseClass=CDialog
HeaderFile=GrpDetails.h
ImplementationFile=GrpDetails.cpp

[CLS:CLeftView]
Type=0
BaseClass=CTreeView
HeaderFile=LeftView.h
ImplementationFile=LeftView.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CMoveStation]
Type=0
BaseClass=CDialog
HeaderFile=MoveStation.h
ImplementationFile=MoveStation.cpp

[CLS:CNotice]
Type=0
BaseClass=CDialog
HeaderFile=Notice.h
ImplementationFile=Notice.cpp

[CLS:CPaymentDlg]
Type=0
BaseClass=CDialog
HeaderFile=PaymentDlg.h
ImplementationFile=PaymentDlg.cpp

[CLS:CReceivers]
Type=0
BaseClass=CDialog
HeaderFile=Receivers.h
ImplementationFile=Receivers.cpp

[CLS:CRightGrid]
Type=0
BaseClass=CDialog
HeaderFile=RightGrid.h
ImplementationFile=RightGrid.cpp

[CLS:CTreeviewDoc]
Type=0
BaseClass=CDocument
HeaderFile=treeviewDoc.h
ImplementationFile=treeviewDoc.cpp

[CLS:CTreeviewView]
Type=0
BaseClass=CFormView
HeaderFile=treeviewView.h
ImplementationFile=treeviewView.cpp

[CLS:CTxRxFilterDLG]
Type=0
BaseClass=CDialog
HeaderFile=TxRxFilterDLG.h
ImplementationFile=TxRxFilterDLG.cpp

[CLS:CTxRxFiltersSet]
Type=0
HeaderFile=TxRxFiltersSet.h
ImplementationFile=TxRxFiltersSet.cpp

[DB:CTxRxFiltersSet]
DB=1

[DLG:IDD_ANT_PATTERN]
Type=1
Class=CAntPattern
ControlCount=2
Control1=IDC_H_PATTERN,button,1342177287
Control2=IDC_V_PATTERN,button,1342177287

[DLG:IDD_AuditTrail]
Type=1
Class=CAudit
ControlCount=8
Control1=IDC_AuditRefresh,button,1342242817
Control2=IDC_AuditGrid,{0ECD9B64-23AA-11D0-B351-00A0C9055D8E},1342242816
Control3=IDC_UserName,combobox,1344339971
Control4=IDC_ACTION,combobox,1344339971
Control5=IDC_Table,combobox,1344339971
Control6=IDC_STATIC1,static,1342308352
Control7=IDC_STATIC2,static,1342308352
Control8=IDC_STATIC3,static,1342308352

[DLG:IDD_EQ_CAT]
Type=1
Class=CCatSelect
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_MSHFLEXGRID1,{0ECD9B64-23AA-11D0-B351-00A0C9055D8E},1342242816
Control4=IDC_AddPattern,button,1073807360

[DLG:IDD_CUSTOM_REPORT]
Type=1
Class=CCustomReport
ControlCount=26
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC8,button,1342308359
Control4=IDC_LICENSED,button,1342242825
Control5=IDC_UNLICENSED,button,1342242825
Control6=IDC_ALL,button,1342242825
Control7=IDC_STATIC1,static,1342308352
Control8=IDC_STATIC2,static,1342308352
Control9=IDC_OWNER,combobox,1344340227
Control10=IDC_LICENSE,combobox,1344340227
Control11=IDC_STATIC3,button,1342177287
Control12=IDC_FIXED,button,1342242819
Control13=IDC_LANDMOBILE,button,1342242819
Control14=IDC_BROADCASTING,button,1342242819
Control15=IDC_STATIC4,button,1342177287
Control16=IDC_FreqCond,listbox,1352728833
Control17=IDC_FreqCondSel,listbox,1352728833
Control18=IDC_STATIC5,static,1342308352
Control19=IDC_STATIC6,static,1342308352
Control20=IDC_STATIC7,static,1342308352
Control21=IDC_F1,edit,1350631552
Control22=IDC_F2,edit,1484849280
Control23=IDC_F1U,combobox,1344339970
Control24=IDC_F2U,combobox,1478557698
Control25=IDC_FreqAdd,button,1342242816
Control26=IDC_FreqRem,button,1342242816

[DLG:IDD_ES_ANT_PAT]
Type=1
Class=CESAntPat
ControlCount=25
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_ESAntPatt,edit,1350631552
Control4=IDC_STATIC3,static,1342308352
Control5=IDC_STATIC5,button,1342177287
Control6=IDC_PATTERN,button,1073741833
Control7=IDC_COEFF,button,1073741833
Control8=IDC_STATIC2,button,1342177287
Control9=IDC_STATIC4,button,1342177287
Control10=IDC_CoeffA,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC6,button,1342177287
Control13=IDC_CoeffB,edit,1350631552
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC7,button,1342177287
Control16=IDC_CoeffC,edit,1350631552
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC8,button,1342177287
Control19=IDC_CoeffD,edit,1350631552
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC9,button,1342177287
Control22=IDC_Phi1,edit,1350631552
Control23=IDC_STATIC11,static,1342308352
Control24=IDC_STATIC1,static,1342308352
Control25=IDC_ER,edit,1484849280

[DLG:IDD_SRS_NOTICE]
Type=1
Class=CESNotice
ControlCount=22
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_NTC_ID_lbl,static,1342308352
Control4=IDC_NTC_ID,edit,1484849280
Control5=IDC_NTC_TYPE_lbl,static,1342308352
Control6=IDC_NTC_TYPE,edit,1484849280
Control7=IDC_NTC_REFID_lbl,static,1342308352
Control8=IDC_NTC_REFID,edit,1350631552
Control9=IDC_NTC_DATE_lbl,static,1342308352
Control10=IDC_NTC_DATE,SysDateTimePick32,1342242848
Control11=IDC_NTC_PROV_lbl,static,1342308352
Control12=IDC_NTC_ACTION_lbl,static,1342308352
Control13=IDC_NTC_ACTION,combobox,1344339971
Control14=IDC_NTC_ADM_lbl,static,1342308352
Control15=IDC_NTC_ADM,edit,1350631552
Control16=IDC_NTC_SUB_lbl,static,1342308352
Control17=IDC_NTC_SUB,combobox,1344339971
Control18=IDC_NTC_RR_lbl,static,1073872896
Control19=IDC_NTC_RR,combobox,1075904515
Control20=IDC_NTC_TGTNTC_lbl,static,1342308352
Control21=IDC_NTC_TGTNTC,edit,1350631552
Control22=IDC_NTC_PROV,combobox,1344340227

[DLG:IDD_GrpDetails]
Type=1
Class=CGrpDetails
ControlCount=5
Control1=IDCANCEL,button,1342242816
Control2=IDC_GRID,{0ECD9B64-23AA-11D0-B351-00A0C9055D8E},1342242816
Control3=IDC_ADDREC,button,1342242827
Control4=IDC_DELREC,button,1342242827
Control5=IDC_SAVE,button,1342242827

[DLG:IDD_MOVE_STATION]
Type=1
Class=CMoveStation
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIONS,{0ECD9B64-23AA-11D0-B351-00A0C9055D8E},1342242816

[DLG:IDD_NOTICE]
Type=1
Class=CNotice
ControlCount=13
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_NOTICE_DATE,SysDateTimePick32,1342242848
Control4=IDC_ACTION,combobox,1344340227
Control5=IDC_STATICS1,static,1342308354
Control6=IDC_STATICS2,static,1342308354
Control7=IDC_T14,button,1208025091
Control8=IDC_RESUB,combobox,1344340227
Control9=IDC_STATICS3,static,1342308354
Control10=IDC_PUBREQ,combobox,1344340227
Control11=IDC_STATICS4,static,1342308354
Control12=IDC_ADMIN,edit,1350631552
Control13=IDC_STATIC,static,1342308352

[DLG:IDD_PAYMENT]
Type=1
Class=CPaymentDlg
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC1,static,1342308352
Control4=IDC_PAYMENT_NO,edit,1350631552
Control5=IDC_STATIC4,static,1342308352
Control6=IDC_PAY_DATE,SysDateTimePick32,1342242848
Control7=IDC_STATIC2,static,1342308352
Control8=IDC_PAYMENT_DESC,edit,1350631552
Control9=IDC_STATIC3,static,1342308352
Control10=IDC_PAYMENT_VAL,edit,1350639744

[DLG:IDD_ADD_RECEIVER]
Type=1
Class=CReceivers
ControlCount=50
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_POINT,button,1342177289
Control5=IDC_RECEIVER_STATIONS,{0ECD9B64-23AA-11D0-B351-00A0C9055D8E},1342242816
Control6=IDC_STATIC,button,1342177287
Control7=IDC_MULTIPOINT,button,1342177289
Control8=IDC_STATIC,button,1342177287
Control9=IDC_CIRCLE,button,1342177289
Control10=IDC_STATIC8,static,1342308354
Control11=IDC_STATIC9,static,1342308354
Control12=IDC_STATIC10,static,1342308354
Control13=IDC_CEN_LAT,edit,1484849280
Control14=IDC_CEN_LON,edit,1484849280
Control15=IDC_REC_RADIUS,edit,1484849280
Control16=IDC_STATIC1,static,1342308352
Control17=IDC_STATIC2,static,1342308352
Control18=IDC_HOP_ID,edit,1484857472
Control19=IDC_LINK_ID,edit,1484857472
Control20=IDC_STATIC5,static,1342308352
Control21=IDC_STATIC6,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_LAT2,edit,1484849280
Control29=IDC_LON2,edit,1484849280
Control30=IDC_LAT3,edit,1484849280
Control31=IDC_LON3,edit,1484849280
Control32=IDC_LAT4,edit,1484849280
Control33=IDC_LON4,edit,1484849280
Control34=IDC_LAT5,edit,1484849280
Control35=IDC_LON5,edit,1484849280
Control36=IDC_LAT6,edit,1484849280
Control37=IDC_LON6,edit,1484849280
Control38=IDC_LAT1,edit,1484849280
Control39=IDC_LON1,edit,1484849280
Control40=IDC_ANT_LIST,button,1342177287
Control41=IDC_TX_ANTENNA,{0ECD9B64-23AA-11D0-B351-00A0C9055D8E},1342242816
Control42=IDC_STATIC11,static,1342308352
Control43=IDC_STATIC3,static,1342308354
Control44=IDC_NOISE_TEMP,edit,1484857472
Control45=IDC_STATIC4,static,1342308352
Control46=IDC_STATIC,button,1342177287
Control47=IDC_ZONE_LIST,combobox,1478557955
Control48=IDC_POINTS,combobox,1478557699
Control49=IDC_STATIC7,static,1342308352
Control50=IDC_ZONE,button,1342177289

[DLG:IDD_GRID]
Type=1
Class=CRightGrid
ControlCount=21
Control1=IDC_GRID,{0ECD9B64-23AA-11D0-B351-00A0C9055D8E},1342242816
Control2=IDC_EDITBOX,{C932BA85-4374-101B-A56C-00AA003668DC},1073807360
Control3=IDC_SAVE_BUTTON,button,1342242816
Control4=IDC_COMBO1,combobox,1075904515
Control5=IDC_GRID_TITLE,static,1342308352
Control6=IDC_ATTACH,button,1342242816
Control7=IDC_COMBO2,combobox,1075904515
Control8=IDC_COMBO3,combobox,1075904515
Control9=IDC_COMBO4,combobox,1075904515
Control10=IDC_COMBO5,combobox,1075904515
Control11=IDC_COMBO6,combobox,1075904515
Control12=IDC_DATEPICKER,SysDateTimePick32,1073807393
Control13=IDC_TIMEPICKER,SysDateTimePick32,1073807401
Control14=IDC_EDIT_BUTTON,button,1342242816
Control15=IDC_CANCEL_BUTTON,button,1342242816
Control16=IDC_COMBO7,combobox,1075904515
Control17=IDC_ANTENNA,button,1073807360
Control18=IDC_NORMALEDIT,edit,1082196096
Control19=IDC_COMBO8,combobox,1075904515
Control20=IDC_COMBO9,combobox,1075904515
Control21=IDC_COMBO10,combobox,1075904515

[DLG:IDD_TxRxFilterDLG]
Type=1
Class=CTxRxFilterDLG
ControlCount=12
Control1=IDC_EDIT_Channelsep,edit,1082196096
Control2=IDC_COMBO_fu,combobox,1344339970
Control3=IDC_MSHFLEXGRID1,{0ECD9B64-23AA-11D0-B351-00A0C9055D8E},1342242816
Control4=IDOK,button,1342242817
Control5=IDC_BUTTON_Draw,button,1342242816
Control6=IDCANCEL,button,1342242816
Control7=IDC_STATIC1,static,1073872896
Control8=IDC_STATIC2,static,1342308352
Control9=IDC_STATIC,static,1342177298
Control10=IDC_STATIC,static,1342177298
Control11=IDC_STATIC,static,1342177298
Control12=IDC_STATIC,static,1342177298

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_WINDOW_SPLIT
Command9=ID_VIEW_LARGEICON
Command10=ID_VIEW_SMALLICON
Command11=ID_VIEW_LIST
Command12=ID_VIEW_DETAILS
Command13=ID_VIEW_BYNAME
Command14=ID_VIEW_AUTOARRANGE
Command15=ID_VIEW_LINEUP
Command16=ID_APP_ABOUT
CommandCount=16

[DLG:IDD_ABOUTBOX]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_VIEW_LARGEICON
Command9=ID_VIEW_SMALLICON
Command10=ID_VIEW_LIST
Command11=ID_VIEW_DETAILS
Command12=ID_APP_ABOUT
CommandCount=12

[MNU:IDR_TREEVITYPE]
Type=1
Class=?
Command1=ID_ADDOWNER
Command2=ID_ADD_ALLOTMENT
Command3=ID_SMS4DC_SEARCH
Command4=ID_DELETESELECTION
Command5=ID_TREE_REFRESH
Command6=ID_EXPIREDLICENSES
Command7=ID_TOTALSTATIONS
Command8=ID_CUSTOM_REPORT
CommandCount=8

[MNU:IDR_OWNER_MENU]
Type=1
Class=?
Command1=ID_EDITOWNER
Command2=ID_DELETEOWNER
Command3=ID_ADDLICENSE
CommandCount=3

[MNU:IDR_LICENSE_MENU]
Type=1
Class=?
Command1=ID_EDITLICENSE
Command2=ID_DELETELICENSE
Command3=ID_LICENSE_COPYTOARCHIVE
Command4=ID_CANCELLIC
Command5=ID_ADD_FX
Command6=ID_ADD_BC
Command7=ID_ADD_LM
Command8=ID_ADD_ML
Command9=ID_ADD_ES
Command10=ID_LICENSE_ADDALLOTMENT
Command11=ID_IMPORT_TECH
Command12=ID_LICENSE_MOVEALLOTMENT
Command13=ID_LICENSE_PASTE
Command14=ID_LICENSE_PRINTLICENSE
Command15=ID_LICENSE_PRINTSUMMARY
CommandCount=15

[MNU:IDR_STATION_MENU]
Type=1
Class=?
Command1=ID_EDITSTATION
Command2=ID_DELETESTATION
Command3=ID_DUPLICATESTATION
Command4=ID_MOVESTATION
Command5=ID_ADDEQUIPMENT
Command6=ID_STATION_NOTICE
CommandCount=6

[MNU:IDR_EQUIPMENT_MENU]
Type=1
Class=?
Command1=ID_EDITEQUIPMENT
Command2=ID_DELETEEQUIPMENT
Command3=ID_ADDANTENNA
Command4=ID_ADDFREQUENCY
CommandCount=4

[MNU:IDR_BILLING_MENU]
Type=1
Class=?
Command1=ID_ADDINVOICE
Command2=ID_ADDPAYMENT
CommandCount=2

[MNU:IDR_FREQUENCY_MENU]
Type=1
Class=?
Command1=ID_EDITFREQUENCY
Command2=ID_DELETEFREQUENCY
Command3=ID_FREQUENCY_FILTERTX
Command4=ID_FREQUENCY_FILTERRX
Command5=ID_FREQUENCY_COORDINATION
Command6=ID_FREQUENCY_SERVICEAREA
CommandCount=6

[MNU:IDR_ANTENNA_MENU]
Type=1
Class=?
Command1=ID_EDITANTENNA
Command2=ID_DELETEANTENNA
Command3=ID_ANTENNA_PATTERN
CommandCount=3

[MNU:IDR_RECEIVER_MENU]
Type=1
Class=?
Command1=ID_DELETE_RECEIVER
CommandCount=1

[MNU:IDR_GROUP_MENU]
Type=1
Class=?
Command1=ID_GROUP_EMISSIONS
Command2=ID_GROUP_FREQUENCY
Command3=ID_GROUP_SPECIALSECTION
Command4=ID_GROUP_COORDINATION
Command5=ID_GROUP_CLASSOFSTATION
Command6=ID_GROUP_FILTER
Command7=ID_GROUP_DELETE
CommandCount=7

[MNU:IDR_ES_MENU]
Type=1
Class=?
Command1=ID_EARTHSTATION_DELETE
Command2=ID_EARTHSTATION_DUPLICATE
Command3=ID_EARTHSTATION_MOVE
Command4=ID_ADDBEAMUP
Command5=ID_ADDBEAMDOWN
Command6=ID_EARTHSTATION_HORIZONTALELEVATION
Command7=ID_EARTHSTATION_MINIMUMELEVANGLES
Command8=ID_EARTHSTATION_NOTICE
CommandCount=8

[MNU:IDR_ESANT_MENU]
Type=1
Class=?
Command1=ID_ESANTENNA_DELETE
Command2=ID_ADDGROUP
Command3=ID_ESANTENNA_SHOWPATTERN
CommandCount=3

[MNU:IDR_CONTOUR_MENU]
Type=1
Class=?
Command1=ID_EDITCONTOUR
Command2=ID_DELETECONTOUR
Command3=ID_CONTOUR_POINTS
Command4=ID_CONTOUR_ELECTRONICNOTICE
CommandCount=4

[MNU:IDR_ALLOT_MENU]
Type=1
Class=?
Command1=ID_EDITALLOT
Command2=ID_DELETEALLOT
Command3=ID_ADDCONTOUR
Command4=ID_ATTACHCONTOUR
Command5=ID_ALLOT_COORDINATION
Command6=ID_ALLOTMENT_ELECTRONICNOTICE
CommandCount=6

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_TREE_SEARCH]
Type=1
Class=CTreeSearch
ControlCount=11
Control1=IDOK,button,1342242816
Control2=IDCANCEL,button,1073741824
Control3=IDC_SEARCH_TEXT,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,button,1342308359
Control6=IDC_BEGINS_WITH,button,1342242825
Control7=IDC_ENDS_WITH,button,1342242825
Control8=IDC_ANYWHERE,button,1342242825
Control9=IDC_EXACT_MATCH,button,1342242825
Control10=IDC_SEARCH_RESULT,SysTreeView32,1082130451
Control11=IDC_DO_SEARCH,button,1342242817

[CLS:CTreeSearch]
Type=0
HeaderFile=TreeSearch.h
ImplementationFile=TreeSearch.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_SEARCH_RESULT
VirtualFilter=dWC

