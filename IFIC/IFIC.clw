; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CIFICImport
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ific.h"
LastPage=0
CDK=Y

ClassCount=11
Class1=CAccessLevels
Class2=CAgreement
Class3=CCountryList
Class4=CEditGrid
Class5=CEditWnd
Class6=CFileDlg
Class7=CIFICImport
Class8=CPropSelect
Class9=CSelRecord
Class10=CServSelect
Class11=CSRSImport

ResourceCount=8
Resource1=IDD_AGREEMENTS
Resource2=IDD_COUNTSELECT
Resource3=IDD_PROPSELECT
Resource4=IDD_SERVSELECT
Resource5=IDD_QueryDLG
Resource6=IDD_SelectRecord
Resource7=IDD_ACCESSLEVEL
Resource8=IDD_SRSDLG

[CLS:CAccessLevels]
Type=0
BaseClass=CDialog
HeaderFile=AccessLevels.h
ImplementationFile=AccessLevels.cpp

[CLS:CAgreement]
Type=0
BaseClass=CDialog
HeaderFile=Agreement.h
ImplementationFile=Agreement.cpp

[CLS:CCountryList]
Type=0
BaseClass=CDialog
HeaderFile=CountryList.h
ImplementationFile=CountryList.cpp

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

[CLS:CFileDlg]
Type=0
BaseClass=CDialog
HeaderFile=FileDlg.h
ImplementationFile=FileDlg.cpp

[CLS:CIFICImport]
Type=0
BaseClass=CDialog
HeaderFile=IFICImport.h
ImplementationFile=IFICImport.cpp
LastObject=IDC_BROWSE
Filter=D
VirtualFilter=dWC

[CLS:CPropSelect]
Type=0
BaseClass=CDialog
HeaderFile=PropSelect.h
ImplementationFile=PropSelect.cpp

[CLS:CSelRecord]
Type=0
BaseClass=CDialog
HeaderFile=SelRecord.h
ImplementationFile=SelRecord.cpp

[CLS:CServSelect]
Type=0
BaseClass=CDialog
HeaderFile=ServSelect.h
ImplementationFile=ServSelect.cpp

[CLS:CSRSImport]
Type=0
BaseClass=CDialog
HeaderFile=SRSImport.h
ImplementationFile=SRSImport.cpp

[DLG:IDD_ACCESSLEVEL]
Type=1
Class=CAccessLevels
ControlCount=18
Control1=ID_DELETE,button,1342242816
Control2=IDC_STATIC2,button,1342177287
Control3=IDC_STATIC1,static,1342308354
Control4=IDC_STATIC3,static,1342308354
Control5=IDC_USERADD,edit,1350631552
Control6=IDC_PASSADD,edit,1350631552
Control7=IDC_STATIC4,button,1342177287
Control8=IDC_STATIC5,static,1342308354
Control9=IDC_STATIC6,static,1342308354
Control10=IDC_PASSMOD,edit,1350631552
Control11=IDC_USERMOD,combobox,1344340227
Control12=IDC_ACCESSLEVEL,combobox,1344339971
Control13=IDC_STATIC7,static,1342308354
Control14=ID_SAVE,button,1342242816
Control15=IDCANCEL,button,1342242816
Control16=IDC_NEW,button,1342308361
Control17=IDC_MODIFY,button,1342177289
Control18=IDC_ENABLED,button,1342242819

[DLG:IDD_AGREEMENTS]
Type=1
Class=CAgreement
ControlCount=30
Control1=IDC_STATIC1,static,1342308354
Control2=IDC_STATIC2,static,1342308354
Control3=IDC_STATIC3,static,1342308354
Control4=IDC_STATIC4,static,1342308354
Control5=IDC_TYPE_lbl,static,1342308354
Control6=IDC_STATIC6,static,1342308354
Control7=IDC_AGNAME,edit,1484849280
Control8=IDC_AGSERV,edit,1484849280
Control9=IDC_AGCOUNTRIES,edit,1484849280
Control10=IDC_AGPROP,edit,1484849280
Control11=IDC_STATIC,button,1342177287
Control12=IDC_AGNEW,button,1342242827
Control13=IDC_AGMOD,button,1342242816
Control14=IDC_AGSAVE,button,1476460555
Control15=IDC_AGPREV,button,1476460555
Control16=IDC_AGNEXT,button,1342242827
Control17=IDC_AGCANCEL,button,1476460544
Control18=IDC_AGDELETE,button,1342242827
Control19=IDC_AGFIRST,button,1476460555
Control20=IDC_AGLAST,button,1342242827
Control21=IDC_RECORDCOUNT,edit,1476460673
Control22=IDC_AGMODEL,combobox,1476460803
Control23=IDC_AGTYPE,combobox,1476460803
Control24=IDC_SERVLIST,button,1476460544
Control25=IDC_COUNTLIST,button,1476460544
Control26=IDC_MODELLIST,button,1476460544
Control27=IDC_PREFCOUNTRY,button,1476460544
Control28=IDC_AGPLUS,button,1476460555
Control29=IDC_AGMINUS,button,1476460555
Control30=IDC_AGLIST,{0ECD9B64-23AA-11D0-B351-00A0C9055D8E},1342242816

[DLG:IDD_COUNTSELECT]
Type=1
Class=CCountryList
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_COUNTRIES,listbox,1353777417

[DLG:IDD_FileDLG]
Type=1
Class=CFileDlg

[DLG:IDD_QueryDLG]
Type=1
Class=CIFICImport
ControlCount=50
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC1,button,1342177287
Control4=IDC_STATIC2,button,1342177287
Control5=IDC_STATIC3,button,1342177287
Control6=IDC_FMTV,button,1342242819
Control7=IDC_LFMF,button,1208025091
Control8=IDC_FXM,button,1342242819
Control9=IDC_ADMLIST,listbox,1352728835
Control10=IDC_ADMSEL,listbox,1352728835
Control11=IDC_AdmAdd,button,1342242816
Control12=IDC_AdmAddAll,button,1073807360
Control13=IDC_AdmRemove,button,1342242816
Control14=IDC_AdmClear,button,1342242816
Control15=IDC_FreqCond,listbox,1352728833
Control16=IDC_PROGRESS,msctls_progress32,1350565889
Control17=IDC_STATIC9,static,1342308354
Control18=IDC_STATION_CLASS,combobox,1344340227
Control19=IDC_FRAGMENT,combobox,1344340227
Control20=IDC_ClassSel,listbox,1353777411
Control21=IDC_ClassAdd,button,1342242816
Control22=IDC_ClassRemove,button,1342242816
Control23=IDC_ClassClear,button,1342242816
Control24=IDC_FragAdd,button,1342242816
Control25=IDC_FragRemove,button,1342242816
Control26=IDC_FragClear,button,1342242816
Control27=IDC_FragSel,listbox,1353777411
Control28=IDC_STATIC7,button,1342177287
Control29=IDC_STATIC5,button,1342177287
Control30=IDC_FreqCondSel,listbox,1353777411
Control31=IDC_STATIC4,static,1342308352
Control32=IDC_STATIC,static,1342308352
Control33=IDC_STATIC,static,1342308352
Control34=IDC_FreqAdd,button,1342242816
Control35=IDC_FreqRem,button,1342242816
Control36=IDC_F1,edit,1350631552
Control37=IDC_F2,edit,1484849280
Control38=IDC_F1U,combobox,1344339971
Control39=IDC_F2U,combobox,1478557699
Control40=IDC_STATIC6,button,1342177287
Control41=IDC_ID,edit,1350631552
Control42=IDC_IDAdd,button,1342242816
Control43=IDC_IDRemove,button,1342242816
Control44=IDC_IDSel,listbox,1353777411
Control45=IDC_DIGITAL,button,1476460547
Control46=IDC_STATIC,button,1073872903
Control47=IDC_MDB,button,1073741833
Control48=IDC_SQLITE,button,1073741833
Control49=IDC_DB3_FILE,edit,1216348288
Control50=IDC_BROWSE,button,1073741824

[DLG:IDD_PROPSELECT]
Type=1
Class=CPropSelect
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_PROPS,listbox,1353777409

[DLG:IDD_SelectRecord]
Type=1
Class=CSelRecord
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_ADODC1,{67397AA3-7FB1-11D0-B148-00A0C922E820},1073741824
Control4=IDC_DATAGRID2,{CDE57A43-8B86-11D0-B3C6-00A0C90AEA82},1342242816

[DLG:IDD_SERVSELECT]
Type=1
Class=CServSelect
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SERVICES,listbox,1353777417

[DLG:IDD_SRSDLG]
Type=1
Class=CSRSImport
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=ID_STATIC1,button,1342177287
Control4=ID_STATIC2,button,1342177287
Control5=IDC_ADMLIST,listbox,1352728835
Control6=IDC_ADMSEL,listbox,1352728835
Control7=IDC_AdmAdd,button,1342242816
Control8=IDC_AdmAddAll,button,1073807360
Control9=IDC_AdmRemove,button,1342242816
Control10=IDC_AdmClear,button,1342242816
Control11=IDC_PROGRESS,msctls_progress32,1350565889
Control12=ID_STATIC3,static,1342308354
Control13=IDC_MDB_FILE,edit,1484849280
Control14=IDC_BROWSE,button,1342242816

