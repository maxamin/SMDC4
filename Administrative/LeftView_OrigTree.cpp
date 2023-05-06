// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "ChildFrm.h"
#include "Notice.h"

#include "treeviewDoc.h"
#include "treeviewview.h"
#include "LeftView.h"
#include "PaymentDlg.h"
#include "MSHFlexGrid.h"
#include <afxdb.h>
#include <windowsx.h>
#include <math.h>
#include "AntPattern.h"
#include "MoveStation.h"
#include "TxRxFilterDLG.h"
#include "CatSelect.h"
#include "GrpDetails.h"
#include "spromeps.h"              /* SuperPro API function prototypes     */

extern "C" {
#include "idwm32.h"
}
//#include "AuditTrail.h"
#include "test6.h"
#include "ESNotice.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL CheckLock();

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	//{{AFX_MSG_MAP(CLeftView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_NOTIFY_REFLECT(NM_SETFOCUS, OnSetfocus)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_COMMAND(ID_LICENSE_PRINTLICENSE, OnLicensePrintlicense)
	ON_COMMAND(ID_ADDPAYMENT, OnAddpayment)
	ON_COMMAND(ID_LICENSE_NOTICE, OnLicenseNotice)
	ON_COMMAND(ID_STATION_NOTICE, OnStationNotice)
	ON_COMMAND(ID_DELETE_RECEIVER, OnDeleteReceiver)
	ON_COMMAND(ID_EDITOWNER, OnEditOwner)
	ON_COMMAND(ID_EDITANTENNA, OnEditantenna)
	ON_COMMAND(ID_EDITEQUIPMENT, OnEditequipment)
	ON_COMMAND(ID_EDITFREQUENCY, OnEditfrequency)
	ON_COMMAND(ID_EDITLICENSE, OnEditlicense)
	ON_COMMAND(ID_EDITSTATION, OnEditstation)
	ON_COMMAND(ID_ADDOWNER, OnAddOwner)
	ON_COMMAND(ID_ADDLICENSE, OnAddLicense)
	ON_COMMAND(ID_ADDANTENNA, OnAddAntenna)
	ON_COMMAND(ID_ADDEQUIPMENT, OnAddEquipment)
	ON_COMMAND(ID_ADDFREQUENCY, OnAddFrequency)
	ON_COMMAND(ID_DELETEFREQUENCY, OnDeleteFrequency)
	ON_COMMAND(ID_DELETEANTENNA, OnDeleteAntenna)
	ON_COMMAND(ID_DELETEEQUIPMENT, OnDeleteEquipment)
	ON_COMMAND(ID_DELETESTATION, OnDeleteStation)
	ON_COMMAND(ID_DELETELICENSE, OnDeleteLicense)
	ON_COMMAND(ID_LICENSE_PRINTSUMMARY, OnLicensePrintSummary)
	ON_COMMAND(ID_ANTENNA_PATTERN, OnAntennaPattern)
	ON_COMMAND(ID_ADD_FX, OnAddFx)
	ON_COMMAND(ID_ADD_LM, OnAddLm)
	ON_COMMAND(ID_ADD_BC, OnAddBc)
	ON_COMMAND(ID_ADD_ML, OnAddMl)
	ON_COMMAND(ID_IMPORT_TECH, OnImportTech)
	ON_COMMAND(ID_FREQUENCY_FILTERTX, OnFrequencyFilterTX)
	ON_COMMAND(ID_FREQUENCY_FILTERRX, OnFrequencyFilterRX)
	ON_COMMAND(ID_ADDINVOICE, OnAddInvoice)
	ON_UPDATE_COMMAND_UI(ID_ADDOWNER, OnUpdateAddowner)
	ON_UPDATE_COMMAND_UI(ID_DELETESTATION, OnUpdateDeletestation)
	ON_UPDATE_COMMAND_UI(ID_ADDEQUIPMENT, OnUpdateAddequipment)
	ON_UPDATE_COMMAND_UI(ID_DELETE_RECEIVER, OnUpdateDeleteReceiver)
	ON_UPDATE_COMMAND_UI(ID_DELETEOWNER, OnUpdateDeleteowner)
	ON_UPDATE_COMMAND_UI(ID_EDITOWNER, OnUpdateEditowner)
	ON_UPDATE_COMMAND_UI(ID_ADDLICENSE, OnUpdateAddlicense)
	ON_UPDATE_COMMAND_UI(ID_EDITSTATION, OnUpdateEditstation)
	ON_UPDATE_COMMAND_UI(ID_EDITANTENNA, OnUpdateEditantenna)
	ON_UPDATE_COMMAND_UI(ID_DELETEANTENNA, OnUpdateDeleteantenna)
	ON_UPDATE_COMMAND_UI(ID_EDITLICENSE, OnUpdateEditlicense)
	ON_UPDATE_COMMAND_UI(ID_DELETELICENSE, OnUpdateDeletelicense)
	ON_UPDATE_COMMAND_UI(ID_CANCELLIC, OnUpdateCancellic)
	ON_UPDATE_COMMAND_UI(ID_ADD_FX, OnUpdateAddFx)
	ON_UPDATE_COMMAND_UI(ID_ADD_BC, OnUpdateAddBc)
	ON_UPDATE_COMMAND_UI(ID_ADD_LM, OnUpdateAddLm)
	ON_UPDATE_COMMAND_UI(ID_ADD_ML, OnUpdateAddMl)
	ON_UPDATE_COMMAND_UI(ID_IMPORT_TECH, OnUpdateImportTech)
	ON_UPDATE_COMMAND_UI(ID_EDITFREQUENCY, OnUpdateEditfrequency)
	ON_UPDATE_COMMAND_UI(ID_DELETEFREQUENCY, OnUpdateDeletefrequency)
	ON_UPDATE_COMMAND_UI(ID_FREQUENCY_FILTERTX, OnUpdateFrequencyFiltertx)
	ON_UPDATE_COMMAND_UI(ID_FREQUENCY_FILTERRX, OnUpdateFrequencyFilterrx)
	ON_UPDATE_COMMAND_UI(ID_ADDFREQUENCY, OnUpdateAddfrequency)
	ON_UPDATE_COMMAND_UI(ID_ADDANTENNA, OnUpdateAddantenna)
	ON_UPDATE_COMMAND_UI(ID_DELETEEQUIPMENT, OnUpdateDeleteequipment)
	ON_UPDATE_COMMAND_UI(ID_EDITEQUIPMENT, OnUpdateEditequipment)
	ON_UPDATE_COMMAND_UI(ID_ADDINVOICE, OnUpdateAddinvoice)
	ON_UPDATE_COMMAND_UI(ID_ADDPAYMENT, OnUpdateAddpayment)
	ON_COMMAND(ID_CANCELLIC, OnCancellic)
	ON_COMMAND(ID_LICENSE_COPYTOARCHIVE, OnLicenseCopytoarchive)
	ON_COMMAND(ID_TREE_REFRESH, OnTreeRefresh)
	ON_COMMAND(ID_GROUP_EMISSIONS, OnGroupEmissions)
	ON_COMMAND(ID_GROUP_FREQUENCY, OnGroupFrequency)
	ON_COMMAND(ID_GROUP_COORDINATION, OnGroupCoordination)
	ON_COMMAND(ID_GROUP_FILTER, OnGroupFilter)
	ON_COMMAND(ID_GROUP_CLASSOFSTATION, OnGroupClassofstation)
	ON_COMMAND(ID_EARTHSTATION_HORIZONTALELEVATION, OnEarthstationHorizontalelevation)
	ON_COMMAND(ID_EARTHSTATION_MINIMUMELEVANGLES, OnEarthstationMinimumelevangles)
	ON_COMMAND(ID_ADD_ES, OnAddEs)
	ON_COMMAND(ID_ADDBEAMUP, OnAddbeamup)
	ON_COMMAND(ID_ADDBEAMDOWN, OnAddbeamdown)
	ON_COMMAND(ID_ADDGROUP, OnAddgroup)
	ON_COMMAND(ID_GROUP_SPECIALSECTION, OnGroupSpecialsection)
	ON_COMMAND(ID_GROUP_DELETE, OnGroupDelete)
	ON_COMMAND(ID_ESANTENNA_DELETE, OnEsantennaDelete)
	ON_COMMAND(ID_EARTHSTATION_DELETE, OnEarthstationDelete)
	ON_COMMAND(ID_EARTHSTATION_NOTICE, OnEarthstationNotice)
	ON_COMMAND(ID_FREQUENCY_COORDINATION, OnFrequencyCoordination)
	ON_COMMAND(ID_ESANTENNA_SHOWPATTERN, OnEsantennaShowpattern)
	ON_COMMAND(ID_DELETEOWNER, OnDeleteOwner)
	ON_COMMAND(ID_CONTOUR_POINTS, OnContourPoints)
	ON_UPDATE_COMMAND_UI(ID_ADD_ALLOTMENT, OnUpdateAddAllotment)
	ON_COMMAND(ID_ADD_ALLOTMENT, OnAddAllotment)
	ON_COMMAND(ID_EDITALLOT, OnEditAllot)
	ON_UPDATE_COMMAND_UI(ID_EDITALLOT, OnUpdateEditAllot)
	ON_UPDATE_COMMAND_UI(ID_DELETEALLOT, OnUpdateDeleteAllot)
	ON_COMMAND(ID_DELETEALLOT, OnDeleteAllot)
	ON_UPDATE_COMMAND_UI(ID_ADDCONTOUR, OnUpdateAddContour)
	ON_COMMAND(ID_ADDCONTOUR, OnAddContour)
	ON_UPDATE_COMMAND_UI(ID_DELETECONTOUR, OnUpdateDeleteContour)
	ON_COMMAND(ID_DELETECONTOUR, OnDeleteContour)
	ON_UPDATE_COMMAND_UI(ID_ADDBEAMDOWN, OnUpdateAddbeamdown)
	ON_UPDATE_COMMAND_UI(ID_ADDBEAMUP, OnUpdateAddbeamup)
	ON_UPDATE_COMMAND_UI(ID_ADD_ES, OnUpdateAddEs)
	ON_UPDATE_COMMAND_UI(ID_ADDGROUP, OnUpdateAddgroup)
	ON_UPDATE_COMMAND_UI(ID_ATTACHCONTOUR, OnUpdateAttachContour)
	ON_COMMAND(ID_ATTACHCONTOUR, OnAttachContour)
	ON_COMMAND(ID_ALLOTMENT_ELECTRONICNOTICE, OnAllotmentElectronicnotice)
	ON_UPDATE_COMMAND_UI(ID_LICENSE_ADDALLOTMENT, OnUpdateLicenseAddallotment)
	ON_COMMAND(ID_LICENSE_ADDALLOTMENT, OnLicenseAddallotment)
	ON_COMMAND(ID_LICENSE_MOVEALLOTMENT, OnLicenseMoveallotment)
	ON_UPDATE_COMMAND_UI(ID_LICENSE_MOVEALLOTMENT, OnUpdateLicenseMoveallotment)
	ON_UPDATE_COMMAND_UI(ID_FREQUENCY_SERVICEAREA, OnUpdateFrequencyServicearea)
	ON_COMMAND(ID_FREQUENCY_SERVICEAREA, OnFrequencyServicearea)
	ON_COMMAND(ID_ALLOT_COORDINATION, OnAllotCoordination)
	ON_COMMAND(ID_CONTOUR_ELECTRONICNOTICE, OnContourElectronicnotice)
	ON_UPDATE_COMMAND_UI(ID_DELETESELECTION, OnUpdateDeleteselection)
	ON_COMMAND(ID_DELETESELECTION, OnDeleteselection)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView construction/destruction

CLeftView::CLeftView()
{
	// TODO: add construction code here

	m_ImageList=new CImageList;
}

CLeftView::~CLeftView()
{
	delete m_ImageList;
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

void CLeftView::OnDraw(CDC* pDC)
{
	CTreeviewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


/////////////////////////////////////////////////////////////////////////////
// CLeftView printing

BOOL CLeftView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLeftView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLeftView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
	if(CheckLock()!=SP_SUCCESS)
	{
		AfxMessageBox(_T("No Hardware lock found!"));
		exit(1);
	}
	m_UserName=((CSMS4DCApp *)AfxGetApp())->m_UserName;
	m_UserLevel=((CSMS4DCApp *)AfxGetApp())->m_UserLevel;
	m_Lang=((CSMS4DCApp *)AfxGetApp())->m_Lang;
	m_CDBSTR=((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
/*	CDatabase DB;
	DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
	CRecordset RS;
	RS.m_pDatabase=&DB;
	RS.Open(CRecordset::snapshot,"select * from dt");
	CString SQL,dt;
	RS.GetFieldValue((short)0,dt);
	RS.Close();
	CTime DT=CTime::GetCurrentTime();
	if(dt.Left(10)>DT.Format("%Y-%m-%d %H"))
	{
		//AfxMessageBox(dt+" | "+DT.Format("%Y-%m-%d %H:%M:%S"));
//		DB.ExecuteSQL("delete * from frequency");
//		DB.ExecuteSQL("delete * from station");
//		DB.ExecuteSQL("delete * from bcstation");
//		DB.ExecuteSQL("delete * from equipment");
//		DB.ExecuteSQL("delete * from eqcat");
//		DB.ExecuteSQL("delete * from antenna");
//		DB.ExecuteSQL("delete * from antcat");
//		DB.ExecuteSQL("delete * from owner");
//		DB.ExecuteSQL("delete * from license");
		DB.ExecuteSQL("update users set Enabled=false");
//		SQL.Format("update dt set dt='2000-01-01'");
//		DB.ExecuteSQL(SQL);
	}
	else
	{
		SQL.Format("update dt set dt='%s'",DT.Format("%Y-%m-%d %H"));
		DB.ExecuteSQL(SQL);
	}
	DB.Close();*/
	BuildTree(1);
	IssueInvoices();	
}

void CLeftView::BuildTree(int times)
{
//	AddSt("AbnYamin",35.741069,51.442758,50,3300,100,30,-3,17,90,5,"H",3,0.35,"FX","F3E--",8.5,1200,
//		"E:\\ITU\\Installation\\Antenna\\ant_ALE8500_806.ant");
//	AddSt2("saman",35.741069,51.442758,1400,66,"Satellite","IRN",100,150,10,"S");
	if(times==1)
	{
		m_ImageList->Create(16, 16, ILC_COLOR8, 0, 4);
		m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_SMS));    //0
		m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_OWNER));		//1
		m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_LICENSE));	//2
		m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_STATION));	//3
		m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_BC));		//4
		m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_MOBILE));	//5
		m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_EQUIPMENT));	//6
		m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_FREQUENCY));	//7
		m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_ANTENNA));	//8
		m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_INVOICE));	//9
		m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_PAYMENT));	//10
		m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_RECEIVER));	//11
		m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_UNLICENSED));//12
		m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_ACTIVE));//13
		m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_INACTIVE));//14
		m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_ESTATION));//15
		m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_EANTUP));//16
		m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_EANTDN));//17
		m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_GROUP));//18
		m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_ALLOTMENT));//19
		m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_CONTOUR));//20
		GetTreeCtrl().SetImageList(m_ImageList,TVSIL_NORMAL);	
	}
	LONG style = ::GetWindowLong(GetTreeCtrl().m_hWnd, GWL_STYLE);

	::SetWindowLong(GetTreeCtrl().m_hWnd, GWL_STYLE, style | TVS_HASBUTTONS | TVS_HASLINES | TVS_SHOWSELALWAYS | TVS_CHECKBOXES);
//	SetWindowLong(GetTreeCtrl().m_hWnd,GWL_STYLE,TVS_HASBUTTONS |TVS_HASLINES);
	CString SQL, FldVal;
	int image;
	CDatabase	DB;
	CRecordset	RS,RS1,RS2,RS3,RS4, RS5, RS6;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	RS3.m_pDatabase=&DB;
	HTREEITEM root=GetTreeCtrl().InsertItem(_T("Administrative data"),SMS4DC,SMS4DC);
//////////////////////////////////////////////// Unlicensed /////////////////////////////
	HTREEITEM UnLic=GetTreeCtrl().InsertItem(_T("Anonymous Stations"),UNLICENSED,UNLICENSED,root);
//	RS.Open(CRecordset::dynaset,_T("Select * from Station where LicID=-1"));
//	while(true)
	{
		image=STATION;
		SQL=_T("Select * from Station where LicID=-1 order by classstation,SiteName");
		RS3.Open(CRecordset::dynaset,SQL);
		while(!RS3.IsEOF())
		{
			CString FldVal,StClass;
			RS3.GetFieldValue(_T("SiteName"),FldVal);
			RS3.GetFieldValue(_T("ClassStation"),StClass);
			HTREEITEM root4=GetTreeCtrl().InsertItem(StClass.Left(2)+_T(" Station: ")+FldVal,image,image,UnLic);

			RS4.m_pDatabase=&DB;
			RS3.GetFieldValue(_T("StID"),FldVal);
			SQL=_T("Select * from Equipment,EqCat where Equipment.EqCatID=EqCat.EqCatID and StID=") + FldVal;
			GetTreeCtrl().SetItem(root4,TVIF_PARAM,NULL,0,0,0,0,atol(FldVal));
			RS4.Open(CRecordset::dynaset,SQL);
			while(!RS4.IsEOF())
			{
				CString FldVal;
				RS4.GetFieldValue(_T("EqName"),FldVal);
				HTREEITEM root5=GetTreeCtrl().InsertItem(_T("Equipment: ")+FldVal,EQUIPMENT,EQUIPMENT,root4);

				RS5.m_pDatabase=&DB;
				RS4.GetFieldValue("EqID",FldVal);
				GetTreeCtrl().SetItem(root5,TVIF_PARAM,NULL,0,0,0,0,atol(FldVal));
				SQL=_T("Select * from Frequency where EqID=") + FldVal;
				RS5.Open(CRecordset::dynaset,SQL);
				while(!RS5.IsEOF())
				{
					CString Freq, FldVal;
					RS5.GetFieldValue(_T("Frequency"),FldVal);
					Freq.Format("%f",atof(FldVal)/1000000.);
					Freq.TrimLeft(" ");
					Freq.TrimRight("0");
					Freq+=" MHz";
					HTREEITEM root6=GetTreeCtrl().InsertItem(_T("Frequency: ")+Freq,FREQUENCY,FREQUENCY,root5);
					RS5.GetFieldValue("FreqID",FldVal);
					GetTreeCtrl().SetItem(root6,TVIF_PARAM,NULL,0,0,0,0,atol(FldVal));

					SQL=_T("Select * from Link where TXID=") + FldVal;
					RS6.m_pDatabase=&DB;
					RS6.Open(CRecordset::dynaset,SQL);
					while(!RS6.IsEOF())
					{
						CString FldVal;
						RS6.GetFieldValue("GeoType",FldVal);
						HTREEITEM Node=GetTreeCtrl().InsertItem(_T("Receiver: ")+FldVal,RECEIVER,RECEIVER,root6);
						RS6.GetFieldValue("ReceiverID",FldVal);
						GetTreeCtrl().SetItem(Node,TVIF_PARAM,NULL,0,0,0,0,atol(FldVal));
						RS6.MoveNext();
					}
					RS6.Close();
				RS5.MoveNext();
				}
				RS5.Close();
				SQL=_T("Select * from Antenna ,AntCat where Antenna.AntCatID=AntCat.AntCatID and EqID=") + FldVal;
				RS5.Open(CRecordset::dynaset,SQL);
				while(!RS5.IsEOF())
				{
					CString FldVal;
					RS5.GetFieldValue("AntName",FldVal);
					HTREEITEM Node=GetTreeCtrl().InsertItem("Antenna: "+FldVal,ANTENNA,ANTENNA,root5);
					RS5.GetFieldValue("AntID",FldVal);
					GetTreeCtrl().SetItem(Node,TVIF_PARAM,NULL,0,0,0,0,atol(FldVal));
					RS5.MoveNext();
				}
				RS5.Close();
				
				RS4.MoveNext();
			}
			RS4.Close();

			RS3.MoveNext();
		}
		RS3.Close();
	}
//	RS.Close();
//	RS.Open(CRecordset::dynaset,_T("Select * from Mobiles where LicID=-1"));
//	while(true)
	{
		image=STATION;
		SQL=_T("Select * from Mobiles where LicID=-1 order by MobName");
		RS3.Open(CRecordset::dynaset,SQL);
		while(!RS3.IsEOF())
		{
			CString FldVal;
			RS3.GetFieldValue(_T("MobName"),FldVal);
			HTREEITEM root4=GetTreeCtrl().InsertItem(_T("ML station: ")+FldVal,MOBILE,MOBILE,UnLic);
			RS4.m_pDatabase=&DB;
			RS3.GetFieldValue(_T("MobID"),FldVal);
			GetTreeCtrl().SetItem(root4,TVIF_PARAM,NULL,0,0,0,0,atol(FldVal));
			SQL=_T("Select * from Equipment ,EqCat where Equipment.EqCatID=EqCat.EqCatID and MobID=") + FldVal;
			RS4.Open(CRecordset::dynaset,SQL);
			while(!RS4.IsEOF())
			{
				CString FldVal;
				RS4.GetFieldValue(_T("EqName"),FldVal);
				HTREEITEM root5=GetTreeCtrl().InsertItem(_T("Equipment: ")+FldVal,EQUIPMENT,EQUIPMENT,root4);
				RS5.m_pDatabase=&DB;
				RS4.GetFieldValue(_T("EqID"),FldVal);
				GetTreeCtrl().SetItem(root5,TVIF_PARAM,NULL,0,0,0,0,atol(FldVal));
				SQL=_T("Select * from Frequency where EqID=") + FldVal;
				RS5.Open(CRecordset::dynaset,SQL);
				while(!RS5.IsEOF())
				{
					CString Freq, FldVal;
					RS5.GetFieldValue(_T("Frequency"),FldVal);
					Freq.Format(_T("%f"),atof(FldVal)/1000000.);
					Freq.TrimLeft(_T(" "));
					Freq.TrimRight(_T("0"));
					Freq+=_T(" MHz");
					HTREEITEM root6=GetTreeCtrl().InsertItem(_T("Frequency: ")+Freq,FREQUENCY,FREQUENCY,root5);
					RS5.GetFieldValue(_T("FreqID"),FldVal);
					GetTreeCtrl().SetItem(root6,TVIF_PARAM,NULL,0,0,0,0,atol(FldVal));

					SQL=_T("Select * from Link where TXID=") + FldVal;
					RS6.m_pDatabase=&DB;
					RS6.Open(CRecordset::dynaset,SQL);
					while(!RS6.IsEOF())
					{
						CString FldVal;
						RS6.GetFieldValue("GeoType",FldVal);
						HTREEITEM Node=GetTreeCtrl().InsertItem("Receiver: "+FldVal,RECEIVER,RECEIVER,root6);
						RS6.GetFieldValue("ReceiverID",FldVal);
						GetTreeCtrl().SetItem(Node,TVIF_PARAM,NULL,0,0,0,0,atol(FldVal));
						RS6.MoveNext();
					}
					RS6.Close();
				RS5.MoveNext();
				}
				RS5.Close();
				SQL="Select * from Antenna ,AntCat where Antenna.AntCatID=AntCat.AntCatID and EqID=" + FldVal;
				RS5.Open(CRecordset::dynaset,SQL);
				while(!RS5.IsEOF())
				{
					CString FldVal;
					RS5.GetFieldValue("AntName",FldVal);
					HTREEITEM Node=GetTreeCtrl().InsertItem("Antenna: "+FldVal,ANTENNA,ANTENNA,root5);
					RS5.GetFieldValue("AntID",FldVal);
					GetTreeCtrl().SetItem(Node,TVIF_PARAM,NULL,0,0,0,0,atol(FldVal));
					RS5.MoveNext();
				}
				RS5.Close();
				RS4.MoveNext();
			}
			RS4.Close();
			RS3.MoveNext();
		}
		RS3.Close();
	}
//	RS.Close();
//	RS.Open(CRecordset::dynaset,_T("Select * from BC where LicID=-1"));
//	while(true)
	{
		image=BC;
		SQL=_T("Select * from BCStation where LicID=-1 order by classstation,SiteName");
		RS3.Open(CRecordset::dynaset,SQL);
		while(!RS3.IsEOF())
		{
			CString FldVal,StClass;
			RS3.GetFieldValue(_T("SiteName"),FldVal);
			RS3.GetFieldValue(_T("ClassStation"),StClass);
			HTREEITEM root4=GetTreeCtrl().InsertItem(StClass.Left(2)+_T(" Station: ")+FldVal,image,image,UnLic);

			RS4.m_pDatabase=&DB;
			RS3.GetFieldValue("StID",FldVal);
			SQL="Select * from Equipment,EqCat where Equipment.EqCatID=EqCat.EqCatID and BCID=" + FldVal;
			GetTreeCtrl().SetItem(root4,TVIF_PARAM,NULL,0,0,0,0,atol(FldVal));
			RS4.Open(CRecordset::dynaset,SQL);
			while(!RS4.IsEOF())
			{
				CString FldVal;
				RS4.GetFieldValue("EqName",FldVal);
				HTREEITEM root5=GetTreeCtrl().InsertItem("Equipment: "+FldVal,EQUIPMENT,EQUIPMENT,root4);

				RS5.m_pDatabase=&DB;
				RS4.GetFieldValue("EqID",FldVal);
				GetTreeCtrl().SetItem(root5,TVIF_PARAM,NULL,0,0,0,0,atol(FldVal));
				SQL="Select * from Frequency where EqID=" + FldVal;
				RS5.Open(CRecordset::dynaset,SQL);
				while(!RS5.IsEOF())
				{
					CString Freq, FldVal;
					RS5.GetFieldValue("Frequency",FldVal);
					Freq.Format("%f",atof(FldVal)/1000000.);
					Freq.TrimLeft();
					Freq.TrimRight(_T("0"));
					Freq+=_T(" MHz");
					HTREEITEM root6=GetTreeCtrl().InsertItem(_T("Frequency: ")+Freq,FREQUENCY,FREQUENCY,root5);
					RS5.GetFieldValue("FreqID",FldVal);
					GetTreeCtrl().SetItem(root6,TVIF_PARAM,NULL,0,0,0,0,atol(FldVal));

					SQL=_T("Select * from Link where TXID=") + FldVal;
					RS6.m_pDatabase=&DB;
					RS6.Open(CRecordset::dynaset,SQL);
					while(!RS6.IsEOF())
					{
						CString FldVal;
						RS6.GetFieldValue(_T("GeoType"),FldVal);
						HTREEITEM Node=GetTreeCtrl().InsertItem(_T("Receiver: ")+FldVal,RECEIVER,RECEIVER,root6);
						RS6.GetFieldValue(_T("ReceiverID"),FldVal);
						GetTreeCtrl().SetItem(Node,TVIF_PARAM,NULL,0,0,0,0,atol(FldVal));
						RS6.MoveNext();
					}
					RS6.Close();
				RS5.MoveNext();
				}
				RS5.Close();
				SQL=_T("Select * from Antenna ,AntCat where Antenna.AntCatID=AntCat.AntCatID and EqID=") + FldVal;
				RS5.Open(CRecordset::dynaset,SQL);
				while(!RS5.IsEOF())
				{
					CString FldVal;
					RS5.GetFieldValue(_T("AntName"),FldVal);
					HTREEITEM Node=GetTreeCtrl().InsertItem("Antenna: "+FldVal,ANTENNA,ANTENNA,root5);
					RS5.GetFieldValue(_T("AntID"),FldVal);
					GetTreeCtrl().SetItem(Node,TVIF_PARAM,NULL,0,0,0,0,atol(FldVal));
					RS5.MoveNext();
				}
				RS5.Close();
				
				RS4.MoveNext();
			}
			RS4.Close();

			RS3.MoveNext();
		}
		RS3.Close();
	}
//	RS.Close();
	{
	//	CDatabase ES_DB;
	//	ES_DB.Open(_T("ES"),false,false,_T("ODBC;"),false);
		RS3.m_pDatabase=&DB;
		image=ESTATION;
		SQL=_T("Select * from e_stn WHERE licid=-1 order by Stn_Name");
		RS3.Open(CRecordset::dynaset,SQL);
		while(!RS3.IsEOF())
		{
			CString FldVal,ntc_id;
			RS3.GetFieldValue(_T("stn_name"),FldVal);
			RS3.GetFieldValue(_T("ntc_id"),ntc_id);
			FldVal+=_T("-")+ntc_id;
			HTREEITEM root4=GetTreeCtrl().InsertItem(_T("ES Station: ")+FldVal,image,image,UnLic);

			GetTreeCtrl().SetItem(root4,TVIF_PARAM,NULL,0,0,0,0,atol(ntc_id));
			RS4.m_pDatabase=&DB;
			SQL=_T("Select * from e_ant where ntc_id=") + ntc_id;
			RS4.Open(CRecordset::dynaset,SQL);
			while(!RS4.IsEOF())
			{
				CString FldVal,AntID,emi_rcp;
				RS4.GetFieldValue(_T("beam_name"),FldVal);
				RS4.GetFieldValue(_T("emi_rcp"),emi_rcp);
				HTREEITEM root5;
				if(emi_rcp==_T("R"))
					root5=GetTreeCtrl().InsertItem(_T("Beam: ")+FldVal,EANTDN,EANTDN,root4);
				else
					root5=GetTreeCtrl().InsertItem(_T("Beam: ")+FldVal,EANTUP,EANTUP,root4);
				RS4.GetFieldValue(_T("AntID"),AntID);
				GetTreeCtrl().SetItem(root5,TVIF_PARAM,NULL,0,0,0,0,atol(AntID));

				RS5.m_pDatabase=&DB;
				SQL=_T("Select * from grp where AntID=") + AntID;
				RS5.Open(CRecordset::dynaset,SQL);
				while(!RS5.IsEOF())
				{
					CString GroupID, FldVal;
					RS5.GetFieldValue(_T("grp_id"),GroupID);
					HTREEITEM root6=GetTreeCtrl().InsertItem(_T("Group: ")+GroupID,GROUP,GROUP,root5);
					GetTreeCtrl().SetItem(root6,TVIF_PARAM,NULL,0,0,0,0,atol(GroupID));
/*
					SQL="Select * from Link where TXID=" + FldVal;
					RS6.m_pDatabase=&DB;
					RS6.Open(CRecordset::dynaset,SQL);
					while(!RS6.IsEOF())
					{
						CString FldVal;
						RS6.GetFieldValue("GeoType",FldVal);
						HTREEITEM Node=GetTreeCtrl().InsertItem("Receiver: "+FldVal,RECEIVER,RECEIVER,root6);
						RS6.GetFieldValue("ReceiverID",FldVal);
						GetTreeCtrl().SetItem(Node,TVIF_PARAM,NULL,0,0,0,0,atol(FldVal));
						RS6.MoveNext();
					}
					RS6.Close();*/
				RS5.MoveNext();
				}
				RS5.Close();
/*				SQL="Select * from Antenna ,AntCat where Antenna.AntCatID=AntCat.AntCatID and EqID=" + FldVal;
				RS5.Open(CRecordset::dynaset,SQL);
				while(!RS5.IsEOF())
				{
					CString FldVal;
					RS5.GetFieldValue("AntName",FldVal);
					HTREEITEM Node=GetTreeCtrl().InsertItem("Antenna: "+FldVal,ANTENNA,ANTENNA,root5);
					RS5.GetFieldValue("AntID",FldVal);
					GetTreeCtrl().SetItem(Node,TVIF_PARAM,NULL,0,0,0,0,atol(FldVal));
					RS5.MoveNext();
				}
				RS5.Close();
*/				
				RS4.MoveNext();
			}
			RS4.Close();

			RS3.MoveNext();
		}
		RS3.Close();
	}
		// Allotments
	{
		RS3.m_pDatabase=&DB;
		image=ALLOTMENT;
		SQL=_T("Select * from rrc_allotment WHERE licid=-1 order by allot_name");
		RS3.Open(CRecordset::dynaset,SQL);
		while(!RS3.IsEOF())
		{
			CString FldVal,TerraKey, AllotKey;
			RS3.GetFieldValue(_T("allot_name"),FldVal);
			RS3.GetFieldValue(_T("terrakey"),TerraKey);
			RS3.GetFieldValue(_T("allotkey"),AllotKey);
			FldVal+=_T("-")+AllotKey;
			HTREEITEM root4=GetTreeCtrl().InsertItem(_T("RRC06 Allotment: ")+FldVal,image,image,UnLic);

			GetTreeCtrl().SetItem(root4,TVIF_PARAM,NULL,0,0,0,0,atol(AllotKey));
			RS4.m_pDatabase=&DB;
			SQL=_T("Select * from rrc_sub_area,rrc_contour where rrc_sub_area.contourkey=rrc_contour.contourkey and allotkey=") + AllotKey;
			RS4.Open(CRecordset::dynaset,SQL);
			while(!RS4.IsEOF())
			{
				CString ContourID,ContourKey,emi_rcp;
				RS4.GetFieldValue(_T("contour_id"),ContourID);
				RS4.GetFieldValue(_T("contourkey"),ContourKey);
				HTREEITEM root5;
				root5=GetTreeCtrl().InsertItem(_T("Contour: ")+ContourKey,CONTOUR,CONTOUR,root4);
				//RS4.GetFieldValue(_T("AntID"),AntID);
				GetTreeCtrl().SetItem(root5,TVIF_PARAM,NULL,0,0,0,0,atol(ContourKey));

/*				RS5.m_pDatabase=&DB;
				SQL=_T("Select * from grp where AntID=") + AntID;
				RS5.Open(CRecordset::dynaset,SQL);
				while(!RS5.IsEOF())
				{
					CString GroupID, FldVal;
					RS5.GetFieldValue(_T("grp_id"),GroupID);
					HTREEITEM root6=GetTreeCtrl().InsertItem(_T("Group: ")+GroupID,GROUP,GROUP,root5);
					GetTreeCtrl().SetItem(root6,TVIF_PARAM,NULL,0,0,0,0,atol(GroupID));
				RS5.MoveNext();
				}
				RS5.Close();*/
				RS4.MoveNext();
			}
			RS4.Close();

			RS3.MoveNext();
		}
		RS3.Close();
	}

//////////////////////////////////////////////// Licensed /////////////////////////////
	if(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=2)
	{

	int LicType=ACTIVE;
	HTREEITEM Licensed;
	RS1.m_pDatabase=&DB;
again:
	if(LicType==ACTIVE)
	{
		Licensed=GetTreeCtrl().InsertItem(_T("Active Licenses"),ACTIVE,ACTIVE,root);
		//RS1.Open(CRecordset::dynaset,_T("Select distinct Owner.* from Owner,License where owner.id=license.admid and license.archive=no"));
	//	RS1.Open(CRecordset::dynaset,_T("Select * from Owner where ID not in (Select distinct Owner.ID from Owner,License where owner.id=license.admid and license.archive=yes)"));
		RS1.Open(CRecordset::dynaset,_T("Select * from Owner order by admname"));
	}
	else
	{
		Licensed=GetTreeCtrl().InsertItem(_T("Archived Licenses"),INACTIVE,INACTIVE,root);
		//RS1.Open(CRecordset::dynaset,_T("Select distinct Owner.* from Owner,License where owner.id=license.admid and license.archive=yes"));
		RS1.Open(CRecordset::dynaset,_T("Select * from Owner order by admname"));
	}
	while(!RS1.IsEOF())
	{
		CString FldVal;
		RS1.GetFieldValue(_T("AdmName"),FldVal);
		HTREEITEM root2=GetTreeCtrl().InsertItem(_T("Owner: ")+FldVal,OWNER,OWNER,Licensed);

		RS1.GetFieldValue(_T("ID"),FldVal);
		GetTreeCtrl().SetItem(root2,TVIF_PARAM,NULL,0,0,0,0,atol(FldVal));
		RS2.m_pDatabase=&DB;
		if(LicType==ACTIVE)
			SQL=_T("Select * from License,SrvType where License.Archive=no and License.SrvID=SrvType.SrvID and AdmID=") + FldVal + _T(" order by LicNo");
		else
			SQL=_T("Select * from License,SrvType where License.Archive=yes and License.SrvID=SrvType.SrvID and AdmID=") + FldVal + _T(" order by LicNo");
		RS2.Open(CRecordset::dynaset,SQL);
		while(!RS2.IsEOF())
		{
			CString FldVal, SrvType, LicID;
			int image;
			RS2.GetFieldValue(_T("SrvType"),SrvType);
			RS2.GetFieldValue(_T("LicNo"),FldVal);
			HTREEITEM root3=GetTreeCtrl().InsertItem(_T("License: ")+FldVal,LICENSE,LICENSE,root2);

			RS2.GetFieldValue(_T("LicID"),LicID);
			GetTreeCtrl().SetItem(root3,TVIF_PARAM,NULL,0,0,0,0,atol(LicID));
			RS3.m_pDatabase=&DB;

///// invoices and payments
			HTREEITEM root4;
	//		root4=GetTreeCtrl().InsertItem("Invoices",INVOICE,INVOICE,root3);
	//		GetTreeCtrl().SetItem(root4,TVIF_PARAM,NULL,0,0,0,0,atol(FldVal));
			root4=GetTreeCtrl().InsertItem("Billing History",PAYMENT,PAYMENT,root3);
			GetTreeCtrl().SetItem(root4,TVIF_PARAM,NULL,0,0,0,0,atol(LicID));
/////

			if(SrvType=="Fixed")
			{
				image=STATION;
				SQL=_T("Select * from Station where LicID=") + LicID + _T(" order by classstation,SiteName");
			}
			else if(SrvType==_T("Land mobile"))
			{
				image=STATION;
				SQL=_T("Select * from Mobiles where LicID=") + LicID + _T(" order by MobName");
				RS3.Open(CRecordset::dynaset,SQL);
				while(!RS3.IsEOF())
				{
					CString FldVal;
					RS3.GetFieldValue(_T("MobName"),FldVal);
					HTREEITEM root4=GetTreeCtrl().InsertItem(_T("ML station: ")+FldVal,MOBILE,MOBILE,root3);
					RS4.m_pDatabase=&DB;
					RS3.GetFieldValue("MobID",FldVal);
					GetTreeCtrl().SetItem(root4,TVIF_PARAM,NULL,0,0,0,0,atol(FldVal));
					SQL="Select * from Equipment ,EqCat where Equipment.EqCatID=EqCat.EqCatID and MobID=" + FldVal;
					RS4.Open(CRecordset::dynaset,SQL);
					while(!RS4.IsEOF())
					{
						CString FldVal;
						RS4.GetFieldValue("EqName",FldVal);
						HTREEITEM root5=GetTreeCtrl().InsertItem("Equipment: "+FldVal,EQUIPMENT,EQUIPMENT,root4);
						RS5.m_pDatabase=&DB;
						RS4.GetFieldValue("EqID",FldVal);
						GetTreeCtrl().SetItem(root5,TVIF_PARAM,NULL,0,0,0,0,atol(FldVal));
						SQL="Select * from Frequency where EqID=" + FldVal;
						RS5.Open(CRecordset::dynaset,SQL);
						while(!RS5.IsEOF())
						{
							CString Freq, FldVal;
							RS5.GetFieldValue("Frequency",FldVal);
							Freq.Format("%f",atof(FldVal)/1000000.);
							Freq.TrimLeft(" ");
							Freq.TrimRight("0");
							Freq+=" MHz";
							HTREEITEM root6=GetTreeCtrl().InsertItem("Frequency: "+Freq,FREQUENCY,FREQUENCY,root5);
							RS5.GetFieldValue("FreqID",FldVal);
							GetTreeCtrl().SetItem(root6,TVIF_PARAM,NULL,0,0,0,0,atol(FldVal));

							SQL="Select * from Link where TXID=" + FldVal;
							RS6.m_pDatabase=&DB;
							RS6.Open(CRecordset::dynaset,SQL);
							while(!RS6.IsEOF())
							{
								CString FldVal;
								RS6.GetFieldValue("GeoType",FldVal);
								HTREEITEM Node=GetTreeCtrl().InsertItem("Receiver: "+FldVal,RECEIVER,RECEIVER,root6);
								RS6.GetFieldValue("ReceiverID",FldVal);
								GetTreeCtrl().SetItem(Node,TVIF_PARAM,NULL,0,0,0,0,atol(FldVal));
								RS6.MoveNext();
							}
							RS6.Close();
///// Fee
				//			HTREEITEM root6=GetTreeCtrl().InsertItem("Fee",FEE,FEE,Node);
				//			GetTreeCtrl().SetItem(root6,TVIF_PARAM,NULL,0,0,0,0,atol(FldVal));
/////
							RS5.MoveNext();
						}
						RS5.Close();
						SQL=_T("Select * from Antenna ,AntCat where Antenna.AntCatID=AntCat.AntCatID and EqID=") + FldVal;
						RS5.Open(CRecordset::dynaset,SQL);
						while(!RS5.IsEOF())
						{
							CString FldVal;
							RS5.GetFieldValue("AntName",FldVal);
							HTREEITEM Node=GetTreeCtrl().InsertItem("Antenna: "+FldVal,ANTENNA,ANTENNA,root5);
							RS5.GetFieldValue("AntID",FldVal);
							GetTreeCtrl().SetItem(Node,TVIF_PARAM,NULL,0,0,0,0,atol(FldVal));
							RS5.MoveNext();
						}
						RS5.Close();
						RS4.MoveNext();
					}
					RS4.Close();
					RS3.MoveNext();
				}
				RS3.Close();
				SQL=_T("Select * from Station where LicID=") + LicID + _T(" order by classstation,SiteName");
			}
			else if(SrvType==_T("Broadcasting"))
			{
				image=BC;
				SQL=_T("Select * from BCStation where LicID=") + LicID + _T(" order by classstation,SiteName");
			}
			else
			{
			//	CDatabase ES_DB;
			//	ES_DB.Open(_T("ES"),false,false,_T("ODBC;"),false);
				RS3.m_pDatabase=&DB;
				image=ESTATION;
				SQL=_T("Select * from e_stn WHERE licid=") +LicID+ _T(" order by Stn_Name");
				RS3.Open(CRecordset::dynaset,SQL);
				while(!RS3.IsEOF())
				{
					CString FldVal,ntc_id;
					RS3.GetFieldValue(_T("stn_name"),FldVal);
					RS3.GetFieldValue(_T("ntc_id"),ntc_id);
					FldVal+=_T("-")+ntc_id;
					HTREEITEM root4=GetTreeCtrl().InsertItem(_T("ES Station: ")+FldVal,image,image,root3);

					GetTreeCtrl().SetItem(root4,TVIF_PARAM,NULL,0,0,0,0,atol(ntc_id));
					RS4.m_pDatabase=&DB;
					SQL=_T("Select * from e_ant where ntc_id=") + ntc_id;
					RS4.Open(CRecordset::dynaset,SQL);
					while(!RS4.IsEOF())
					{
						CString FldVal,AntID,emi_rcp;
						RS4.GetFieldValue(_T("beam_name"),FldVal);
						RS4.GetFieldValue(_T("emi_rcp"),emi_rcp);
						HTREEITEM root5;
						if(emi_rcp==_T("R"))
							root5=GetTreeCtrl().InsertItem(_T("Beam: ")+FldVal,EANTDN,EANTDN,root4);
						else
							root5=GetTreeCtrl().InsertItem(_T("Beam: ")+FldVal,EANTUP,EANTUP,root4);
						RS4.GetFieldValue(_T("AntID"),AntID);
						GetTreeCtrl().SetItem(root5,TVIF_PARAM,NULL,0,0,0,0,atol(AntID));

						RS5.m_pDatabase=&DB;
						SQL=_T("Select * from grp where AntID=") + AntID;
						RS5.Open(CRecordset::dynaset,SQL);
						while(!RS5.IsEOF())
						{
							CString GroupID, FldVal;
							RS5.GetFieldValue(_T("grp_id"),GroupID);
							HTREEITEM root6=GetTreeCtrl().InsertItem(_T("Group: ")+GroupID,GROUP,GROUP,root5);
							GetTreeCtrl().SetItem(root6,TVIF_PARAM,NULL,0,0,0,0,atol(GroupID));
						RS5.MoveNext();
						}
						RS5.Close();
						RS4.MoveNext();
					}
					RS4.Close();

					RS3.MoveNext();
				}
				RS3.Close();
				goto ES;
			}
			RS3.Open(CRecordset::dynaset,SQL);
			while(!RS3.IsEOF())
			{
				CString FldVal,StClass;
				RS3.GetFieldValue(_T("SiteName"),FldVal);
				RS3.GetFieldValue(_T("ClassStation"),StClass);
				HTREEITEM root4=GetTreeCtrl().InsertItem(StClass.Left(2)+_T(" Station: ")+FldVal,image,image,root3);

				RS4.m_pDatabase=&DB;
				if(SrvType==_T("Fixed") || SrvType==_T("Land mobile"))
				{
					RS3.GetFieldValue("StID",FldVal);
					SQL="Select * from Equipment,EqCat where Equipment.EqCatID=EqCat.EqCatID and StID=" + FldVal;
				}
				if(SrvType=="Broadcasting")
				{
					RS3.GetFieldValue("StID",FldVal);
					SQL="Select * from Equipment,EqCat where Equipment.EqCatID=EqCat.EqCatID and BCID=" + FldVal;
				}
				GetTreeCtrl().SetItem(root4,TVIF_PARAM,NULL,0,0,0,0,atol(FldVal));
				RS4.Open(CRecordset::dynaset,SQL);
				while(!RS4.IsEOF())
				{
					CString FldVal;
					RS4.GetFieldValue("EqName",FldVal);
					HTREEITEM root5=GetTreeCtrl().InsertItem("Equipment: "+FldVal,EQUIPMENT,EQUIPMENT,root4);

					RS5.m_pDatabase=&DB;
					RS4.GetFieldValue("EqID",FldVal);
					GetTreeCtrl().SetItem(root5,TVIF_PARAM,NULL,0,0,0,0,atol(FldVal));
					SQL="Select * from Frequency where EqID=" + FldVal;
					RS5.Open(CRecordset::dynaset,SQL);
					while(!RS5.IsEOF())
					{
						CString Freq, FldVal;
						RS5.GetFieldValue("Frequency",FldVal);
						Freq.Format("%f",atof(FldVal)/1000000.);
						Freq.TrimLeft(" ");
						Freq.TrimRight("0");
						Freq+=" MHz";
						HTREEITEM root6=GetTreeCtrl().InsertItem("Frequency: "+Freq,FREQUENCY,FREQUENCY,root5);
						RS5.GetFieldValue("FreqID",FldVal);
						GetTreeCtrl().SetItem(root6,TVIF_PARAM,NULL,0,0,0,0,atol(FldVal));

						SQL="Select * from Link where TXID=" + FldVal;
						RS6.m_pDatabase=&DB;
						RS6.Open(CRecordset::dynaset,SQL);
						while(!RS6.IsEOF())
						{
							CString FldVal;
							RS6.GetFieldValue("GeoType",FldVal);
							HTREEITEM Node=GetTreeCtrl().InsertItem("Receiver: "+FldVal,RECEIVER,RECEIVER,root6);
							RS6.GetFieldValue("ReceiverID",FldVal);
							GetTreeCtrl().SetItem(Node,TVIF_PARAM,NULL,0,0,0,0,atol(FldVal));
							RS6.MoveNext();
						}
						RS6.Close();
///// Fee
			//			HTREEITEM root6=GetTreeCtrl().InsertItem("Fee",FEE,FEE,Node);
			//			GetTreeCtrl().SetItem(root6,TVIF_PARAM,NULL,0,0,0,0,atol(FldVal));
/////
						RS5.MoveNext();
					}
					RS5.Close();
					SQL=_T("Select * from Antenna ,AntCat where Antenna.AntCatID=AntCat.AntCatID and EqID=") + FldVal;
					RS5.Open(CRecordset::dynaset,SQL);
					while(!RS5.IsEOF())
					{
						CString FldVal;
						RS5.GetFieldValue(_T("AntName"),FldVal);
						HTREEITEM Node=GetTreeCtrl().InsertItem(_T("Antenna: ")+FldVal,ANTENNA,ANTENNA,root5);
						RS5.GetFieldValue(_T("AntID"),FldVal);
						GetTreeCtrl().SetItem(Node,TVIF_PARAM,NULL,0,0,0,0,atol(FldVal));
						RS5.MoveNext();
					}
					RS5.Close();
					
					RS4.MoveNext();
				}
				RS4.Close();
				RS3.MoveNext();
			}
			RS3.Close();
			{
				RS5.m_pDatabase=&DB;
				image=ALLOTMENT;
				SQL=_T("Select * from rrc_allotment WHERE licid=") +LicID+ _T(" order by allot_name");
				RS5.Open(CRecordset::dynaset,SQL);
				while(!RS5.IsEOF())
				{
					CString FldVal,TerraKey, AllotKey;
					RS5.GetFieldValue(_T("allot_name"),FldVal);
					RS5.GetFieldValue(_T("terrakey"),TerraKey);
					RS5.GetFieldValue(_T("allotkey"),AllotKey);
					FldVal+=_T("-")+AllotKey;
					HTREEITEM root4=GetTreeCtrl().InsertItem(_T("RRC06 Allotment: ")+FldVal,image,image,root3);

					GetTreeCtrl().SetItem(root4,TVIF_PARAM,NULL,0,0,0,0,atol(AllotKey));
					RS4.m_pDatabase=&DB;
					SQL=_T("Select * from rrc_sub_area,rrc_contour where rrc_sub_area.contourkey=rrc_contour.contourkey and allotkey=") + AllotKey;
					RS4.Open(CRecordset::dynaset,SQL);
					while(!RS4.IsEOF())
					{
						CString ContourID,ContourKey,emi_rcp;
						RS4.GetFieldValue(_T("contour_id"),ContourID);
						RS4.GetFieldValue(_T("contourkey"),ContourKey);
						HTREEITEM root5;
						root5=GetTreeCtrl().InsertItem(_T("Contour: ")+ContourKey,CONTOUR,CONTOUR,root4);
						//RS4.GetFieldValue(_T("AntID"),AntID);
						GetTreeCtrl().SetItem(root5,TVIF_PARAM,NULL,0,0,0,0,atol(ContourKey));

						RS4.MoveNext();
					}
					RS4.Close();

					RS5.MoveNext();
				}
				RS5.Close();
			}

ES:
			RS2.MoveNext();
		}
		RS2.Close();

		RS1.MoveNext();
	}
	RS1.Close();
	if(LicType==ACTIVE)
	{
		LicType=INACTIVE;
		goto again;
	}
	} // Security level
	DB.Close();
}
/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CTreeviewDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTreeviewDoc)));
	return (CTreeviewDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers



void CLeftView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	CString Mess;
	HTREEITEM node=GetTreeCtrl().GetSelectedItem();
	int Type;
	long RecID;
	GetTreeCtrl().GetItemImage(node,Type,Type);
	RecID=GetTreeCtrl().GetItemData(node);
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	switch(Type)
	{
		case ACTIVE: pView->m_Table="";CleanScreen(); break; //LoadData(_T("Active"),0,ACTIVE); break;
		case SMS4DC: pView->m_Table="";CleanScreen(); break;
		case OWNER:	LoadData(_T("Owner"), RecID, OWNER); break;
		case LICENSE: LoadData(_T("License"), RecID, LICENSE); break;
		case STATION: LoadData(_T("Station"), RecID, STATION); break;
		case BC: LoadData(_T("BCStation"), RecID, BC); break;
		case MOBILE: LoadData(_T("Mobiles"), RecID, MOBILE); break;
		case EQUIPMENT: LoadData(_T("Equipment"), RecID, EQUIPMENT); break;
		case FREQUENCY: LoadData(_T("Frequency"), RecID, FREQUENCY); break;
		case ANTENNA: LoadData(_T("Antenna"), RecID, ANTENNA); break;
		case INVOICE: LoadData(_T("Invoice"), RecID, INVOICE); break;
		case PAYMENT: LoadData(_T("Payment"), RecID, PAYMENT); break;
		case RECEIVER: LoadData(_T("Link"), RecID, RECEIVER); break;
		case ESTATION: LoadData(_T("Earth"), RecID, ESTATION); break;
		case EANTUP: LoadData(_T("Eant"), RecID, EANTUP); break;
		case EANTDN: LoadData(_T("Eant"), RecID, EANTDN); break;
		case GROUP: LoadData(_T("grp"), RecID, GROUP); break;
		case ALLOTMENT: LoadData(_T("Allotment"), RecID, ALLOTMENT); break;
		case CONTOUR: LoadData(_T("Contour"), RecID, CONTOUR); break;
//		case FEE: LoadData("Fee", RecID, FEE); break;
		default: pView->m_Table="";CleanScreen(); break;
	}
	*pResult = 0;
}

void CLeftView::LoadData(CString Table, long ID, int RecType)
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	pView->m_RecID=ID;
	pView->m_Table=Table;
	pView->m_Action=0;
	pView->m_Refresh=true;
	pView->m_RecordType=RecType;
//	pView->m_Service=
	pView->RedrawWindow();

}

void CLeftView::CleanScreen()
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	pView->m_RecID=-1;
	pView->m_Table="";
	pView->m_Action=0;
	pView->m_Refresh=true;
	pView->m_RecordType=SMS4DC;
	pView->RedrawWindow();
}

void CLeftView::OnSetfocus(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	(CMSMask *)(pView->GetDlgItem(IDC_EDITBOX))->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,
		SWP_NOSIZE|SWP_HIDEWINDOW);
	(CComboBox *)(pView->GetDlgItem(IDC_COMBO1))->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,
		SWP_NOSIZE|SWP_HIDEWINDOW);
	(CComboBox *)(pView->GetDlgItem(IDC_COMBO2))->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,
		SWP_NOSIZE|SWP_HIDEWINDOW);
	(CComboBox *)(pView->GetDlgItem(IDC_COMBO3))->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,
		SWP_NOSIZE|SWP_HIDEWINDOW);
	(CComboBox *)(pView->GetDlgItem(IDC_COMBO4))->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,
		SWP_NOSIZE|SWP_HIDEWINDOW);
	(CComboBox *)(pView->GetDlgItem(IDC_COMBO5))->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,
		SWP_NOSIZE|SWP_HIDEWINDOW);
	(CComboBox *)(pView->GetDlgItem(IDC_COMBO6))->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,
		SWP_NOSIZE|SWP_HIDEWINDOW);
	(CDateTimeCtrl *)(pView->GetDlgItem(IDC_DATEPICKER))->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,
		SWP_NOSIZE|SWP_HIDEWINDOW);
	(CDateTimeCtrl *)(pView->GetDlgItem(IDC_TIMEPICKER))->SetWindowPos(&CWnd::wndBottom, 0,0,0,0,
		SWP_NOSIZE|SWP_HIDEWINDOW);
	
	*pResult = 0;
}

void CLeftView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString DBSTR=/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR;
	int Level=/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel;
	AFX_MANAGE_STATE(AfxGetStaticModuleState()) ;
    CMenu   TreeMenu;
    // Store popup point, and convert to client coordinates
    // for the drawing functions.

	CPoint pt;
	GetCursorPos(&pt);
    ScreenToClient( &pt );

	UINT uFlags;
	HTREEITEM HitItem=GetTreeCtrl().HitTest(pt, &uFlags);

	if ((HitItem != NULL) && (TVHT_ONITEM & uFlags))
	{
		bool NoMenu=false;
		int NodeType;
		GetTreeCtrl().Select(HitItem, TVGN_CARET);
		GetTreeCtrl().GetItemImage(HitItem,NodeType,NodeType);
		switch(NodeType)
		{
			case SMS4DC:
				TreeMenu.LoadMenu(IDR_TREEVITYPE);
				if(Level==6)
					TreeMenu.EnableMenuItem(ID_ADDOWNER,FALSE);
				break;
			case OWNER:
				{
				HTREEITEM Parent=GetTreeCtrl().GetParentItem(HitItem);
				int Type;
				GetTreeCtrl().GetItemImage(Parent,Type,Type);
				if(Type!=INACTIVE)
					TreeMenu.LoadMenu(IDR_OWNER_MENU);
				else
					NoMenu=true;
				}
				break;
			case LICENSE:
				{
					HTREEITEM Parent=GetTreeCtrl().GetParentItem(GetTreeCtrl().GetParentItem(HitItem));
					int Type;
					GetTreeCtrl().GetItemImage(Parent,Type,Type);
					if(Type!=INACTIVE)
					{
						TreeMenu.LoadMenu(IDR_LICENSE_MENU);
						CRecordset RS;
						CString SQL,SrvID;
						CDatabase	DB;
 						RS.m_pDatabase=&DB;
						DB.Open(DBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
						long RecID=GetTreeCtrl().GetItemData(GetTreeCtrl().GetSelectedItem());
						SQL.Format(_T("Select SrvID from license where LicID=%ld"), RecID);
						RS.Open(CRecordset::snapshot, SQL);
						RS.GetFieldValue((short)0,SrvID);
						RS.Close();
						DB.Close();
						if(SrvID==_T("F"))
						{
							TreeMenu.RemoveMenu(ID_ADD_BC,MF_BYCOMMAND);
							TreeMenu.RemoveMenu(ID_ADD_LM,MF_BYCOMMAND);
							TreeMenu.RemoveMenu(ID_ADD_ML,MF_BYCOMMAND);
							TreeMenu.RemoveMenu(ID_ADD_ES,MF_BYCOMMAND);
							TreeMenu.RemoveMenu(ID_LICENSE_ADDALLOTMENT,MF_BYCOMMAND);
							TreeMenu.RemoveMenu(ID_LICENSE_MOVEALLOTMENT,MF_BYCOMMAND);
						}
						else if(SrvID==_T("B"))
						{
							TreeMenu.RemoveMenu(ID_ADD_FX,MF_BYCOMMAND);
							TreeMenu.RemoveMenu(ID_ADD_LM,MF_BYCOMMAND);
							TreeMenu.RemoveMenu(ID_ADD_ML,MF_BYCOMMAND);
							TreeMenu.RemoveMenu(ID_ADD_ES,MF_BYCOMMAND);
						}
						else if(SrvID==_T("MT"))
						{
							TreeMenu.RemoveMenu(ID_ADD_BC,MF_BYCOMMAND);
							TreeMenu.RemoveMenu(ID_ADD_FX,MF_BYCOMMAND);
							TreeMenu.RemoveMenu(ID_ADD_ES,MF_BYCOMMAND);
							TreeMenu.RemoveMenu(ID_LICENSE_ADDALLOTMENT,MF_BYCOMMAND);
							TreeMenu.RemoveMenu(ID_LICENSE_MOVEALLOTMENT,MF_BYCOMMAND);
						}
						else
						{
							TreeMenu.RemoveMenu(ID_ADD_BC,MF_BYCOMMAND);
							TreeMenu.RemoveMenu(ID_ADD_LM,MF_BYCOMMAND);
							TreeMenu.RemoveMenu(ID_ADD_ML,MF_BYCOMMAND);
							TreeMenu.RemoveMenu(ID_ADD_FX,MF_BYCOMMAND);
							TreeMenu.RemoveMenu(ID_LICENSE_ADDALLOTMENT,MF_BYCOMMAND);
							TreeMenu.RemoveMenu(ID_LICENSE_MOVEALLOTMENT,MF_BYCOMMAND);
						}
					}
					else
						NoMenu=true;
				}
				break;
			case STATION:
				{
					HTREEITEM Parent=GetTreeCtrl().GetParentItem(GetTreeCtrl().GetParentItem(GetTreeCtrl().GetParentItem(HitItem)));
					int Type;
					GetTreeCtrl().GetItemImage(Parent,Type,Type);
					if(Type!=INACTIVE)
						TreeMenu.LoadMenu(IDR_STATION_MENU);
					else
						NoMenu=true;
				}
				break;
			case BC:
				{
					HTREEITEM Parent=GetTreeCtrl().GetParentItem(GetTreeCtrl().GetParentItem(GetTreeCtrl().GetParentItem(HitItem)));
					int Type;
					GetTreeCtrl().GetItemImage(Parent,Type,Type);
					if(Type!=INACTIVE)
						TreeMenu.LoadMenu(IDR_STATION_MENU);
					else
						NoMenu=true;
				}
				break;
			case MOBILE:
				{
					HTREEITEM Parent=GetTreeCtrl().GetParentItem(GetTreeCtrl().GetParentItem(GetTreeCtrl().GetParentItem(HitItem)));
					int Type;
					GetTreeCtrl().GetItemImage(Parent,Type,Type);
					if(Type!=INACTIVE)
						TreeMenu.LoadMenu(IDR_STATION_MENU);
					else
						NoMenu=true;
				}
				break;
			case EQUIPMENT:
				{
					HTREEITEM Parent=GetTreeCtrl().GetParentItem(GetTreeCtrl().GetParentItem(GetTreeCtrl().GetParentItem(GetTreeCtrl().GetParentItem(HitItem))));
					int Type;
					GetTreeCtrl().GetItemImage(Parent,Type,Type);
					if(Type!=INACTIVE)
						TreeMenu.LoadMenu(IDR_EQUIPMENT_MENU);
					else
						NoMenu=true;
				}
				break;
			case ANTENNA:
				{
					HTREEITEM Parent=GetTreeCtrl().GetParentItem(
						GetTreeCtrl().GetParentItem(
							GetTreeCtrl().GetParentItem(
								GetTreeCtrl().GetParentItem(
									GetTreeCtrl().GetParentItem(HitItem)))));
					int Type;
					GetTreeCtrl().GetItemImage(Parent,Type,Type);
					if(Type!=INACTIVE)
						TreeMenu.LoadMenu(IDR_ANTENNA_MENU);
					else
					{
						TreeMenu.LoadMenu(IDR_ANTENNA_MENU);
						TreeMenu.RemoveMenu(ID_EDITANTENNA,MF_BYCOMMAND);
						TreeMenu.RemoveMenu(ID_DELETEANTENNA,MF_BYCOMMAND);
						//NoMenu=true;
					}
				}
				break;
			case FREQUENCY:
				{
					HTREEITEM Station=GetTreeCtrl().GetParentItem(
										GetTreeCtrl().GetParentItem(HitItem)),
								Parent=GetTreeCtrl().GetParentItem(Station);
					int Type,StType;
					GetTreeCtrl().GetItemImage(Parent,Type,Type);
					GetTreeCtrl().GetItemImage(Station,StType,StType);
						TreeMenu.LoadMenu(IDR_FREQUENCY_MENU);
						if(StType!=BC)
						{
							TreeMenu.RemoveMenu(ID_FREQUENCY_SERVICEAREA,MF_BYCOMMAND);
						}
					if(Type!=INACTIVE)
					{
/*						CRecordset RS;
						CString SQL,StCls,SrvID;
						CDatabase	DB;
 						RS.m_pDatabase=&DB;
						DB.Open(DBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
						long RecID=GetTreeCtrl().GetItemData(GetTreeCtrl().GetSelectedItem());
						SQL.Format(_T("Select SrvID from license where LicID=%ld"), RecID);
						RS.Open(CRecordset::snapshot, SQL);
						RS.GetFieldValue((short)0,SrvID);
						RS.Close();
						SQL.Format(_T("Select ClassStation from BCStation, Equipment, Frequency where BCStation.StID=Equipment.BCID and Frequency.EqID=Equipment.EqID and FreqID=%ld"), RecID);
						RS.Open(CRecordset::snapshot, SQL);
						RS.GetFieldValue((short)0,StCls);
						RS.Close();
						DB.Close();
						if(StCls!=_T("BC") && StCls!=_T("BT"))*/
					}
					else
						NoMenu=true;
				}
				break;
			case RECEIVER:
				{
					HTREEITEM Parent=GetTreeCtrl().GetParentItem(
						GetTreeCtrl().GetParentItem(
						GetTreeCtrl().GetParentItem(
							GetTreeCtrl().GetParentItem(
								GetTreeCtrl().GetParentItem(
									GetTreeCtrl().GetParentItem(HitItem))))));
					int Type;
					GetTreeCtrl().GetItemImage(Parent,Type,Type);
					if(Type!=INACTIVE)
						TreeMenu.LoadMenu(IDR_RECEIVER_MENU);
					else
						NoMenu=true;
				}
				break;
			case PAYMENT:
				{
					HTREEITEM Parent=GetTreeCtrl().GetParentItem(
						GetTreeCtrl().GetParentItem(
						GetTreeCtrl().GetParentItem(HitItem)));
					int Type;
					GetTreeCtrl().GetItemImage(Parent,Type,Type);
					if(Type!=INACTIVE)
						TreeMenu.LoadMenu(IDR_BILLING_MENU);
					else
						NoMenu=true;
				}
				break;
			case ESTATION:
				{
					HTREEITEM Parent=GetTreeCtrl().GetParentItem(
						GetTreeCtrl().GetParentItem(
						GetTreeCtrl().GetParentItem(HitItem)));
					int Type;
					GetTreeCtrl().GetItemImage(Parent,Type,Type);
					if(Type!=INACTIVE)
						TreeMenu.LoadMenu(IDR_ES_MENU);
					else
						NoMenu=true;
				}
				break;
			case EANTUP:
			case EANTDN:
				{
					HTREEITEM Parent=GetTreeCtrl().GetParentItem(
						GetTreeCtrl().GetParentItem(
						GetTreeCtrl().GetParentItem(
						GetTreeCtrl().GetParentItem(HitItem))));
					int Type;
					GetTreeCtrl().GetItemImage(Parent,Type,Type);
					if(Type!=INACTIVE)
						TreeMenu.LoadMenu(IDR_ESANT_MENU);
					else
					{
						TreeMenu.LoadMenu(IDR_ESANT_MENU);
						TreeMenu.RemoveMenu(ID_ESANTENNA_DELETE,MF_BYCOMMAND);
						TreeMenu.RemoveMenu(ID_ADDGROUP,MF_BYCOMMAND);
//						NoMenu=true;
					}
				}
				break;
			case GROUP:
				{
					HTREEITEM Parent=GetTreeCtrl().GetParentItem(
						GetTreeCtrl().GetParentItem(
							GetTreeCtrl().GetParentItem(
								GetTreeCtrl().GetParentItem(
									GetTreeCtrl().GetParentItem(HitItem)))));
					int Type;
					GetTreeCtrl().GetItemImage(Parent,Type,Type);
					if(Type!=INACTIVE)
						TreeMenu.LoadMenu(IDR_GROUP_MENU);
					else
						NoMenu=true;
				}
				break;
			case ALLOTMENT:
				{
					HTREEITEM Parent=GetTreeCtrl().GetParentItem(
						GetTreeCtrl().GetParentItem(
							GetTreeCtrl().GetParentItem(
								GetTreeCtrl().GetParentItem(HitItem))));
					int Type;
					GetTreeCtrl().GetItemImage(Parent,Type,Type);
					if(Type!=INACTIVE)
						TreeMenu.LoadMenu(IDR_ALLOT_MENU);
					else
						NoMenu=true;
				}
				break;
			case CONTOUR:
				{
					HTREEITEM Parent=GetTreeCtrl().GetParentItem(
						GetTreeCtrl().GetParentItem(
							GetTreeCtrl().GetParentItem(
								GetTreeCtrl().GetParentItem(HitItem))));
					int Type;
					GetTreeCtrl().GetItemImage(Parent,Type,Type);
					if(Type!=INACTIVE)
						TreeMenu.LoadMenu(IDR_CONTOUR_MENU);
					else
						NoMenu=true;
				}
				break;
			default:
				return;
		}
		if(!NoMenu)
		{
			CMenu* pPopup = TreeMenu.GetSubMenu( 0 );
			ClientToScreen(&pt);
			pPopup->TrackPopupMenu( TPM_LEFTALIGN|TPM_RIGHTBUTTON,
                            pt.x,
                            pt.y,
                            this );
		}
	}
	
}

void CLeftView::OnLicensePrintlicense() 
{
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	CString NodeText;
	NodeText=GetTreeCtrl().GetItemText(Node);
	NodeText.Delete(0,9);
	CString ID,Srv;
	CDatabase	DB;
	CRecordset	RS1;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS1.m_pDatabase=&DB;
	RS1.Open(CRecordset::dynaset,_T("Select LicID, SrvID from License where LicNo='")+NodeText + "'");
	RS1.GetFieldValue((short)0, ID);
	RS1.GetFieldValue((short)1, Srv);
	if(Srv==_T("F"))
		FixedLicense(ID);
	else if(Srv==_T("MT"))
		LMLicense(ID);
	else if(Srv==_T("B"))
		BCLicense(ID);
	else
		ESLicense(ID);
	RS1.Close();
	DB.Close();
}

CString CLeftView::GetReportPath()
{
	CString Path;
	Path=GetCommandLine();
	int Place=Path.ReverseFind('\\')-1;
	Path.Delete(0);
	Path.Delete(Place,Path.GetLength()-Place);
	Place=Path.ReverseFind('\\')+1;
	Path.Delete(Place,Path.GetLength()-Place);
	Path+="texts\\";
	return Path;
}

bool CLeftView::IsFieldValid(CString FieldName, CRecordset &ODBCRecs)
{
	for (int FldNo=0;FldNo<ODBCRecs.GetODBCFieldCount();FldNo++)
	{
		CODBCFieldInfo FldInfo;
		ODBCRecs.GetODBCFieldInfo(FldNo,FldInfo);
		if(!FieldName.Compare(FldInfo.m_strName))
			return true;
	}
	return false;
}

void CLeftView::ProcessBuf(CRecordset &Stations, CString RowBuf, CString &ResStr)
{
	int index=0, place;
	CString FValue;
	ResStr="";
	while(index<RowBuf.GetLength())
	{
		place=RowBuf.Find("{",index);
		if(place==-1) break;
		ResStr+=RowBuf.Mid(index, place-index);
		index=place+1;
		place=RowBuf.Find("}",index);
		if(IsFieldValid(RowBuf.Mid(index,place-index),Stations))
		{
			Stations.GetFieldValue(RowBuf.Mid(index,place-index),FValue);
			if(RowBuf.Mid(index,place-index)=="Frequency")
			{
				double Freq=atof(FValue);
				FValue.Format("%f",Freq/1000000.);
			}
		}
		else
			FValue=RowBuf.Mid(index-1,place-index+2);
		index=place+1;
		ResStr+=FValue;
	}
}

void CLeftView::FixedLicense(CString ID) 
{
	CRecordset Stations;
	FILE *source, *dest;
	CString RepPath=GetReportPath(), 
		SFile=RepPath+_T("FixedLic.htm"), 
		SQL;
	CDatabase	DB;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	SQL="Antenna.AntCatID=AntCat.AntCatID and Station.LicID="+ ID;
	SQL="Equipment.EqCatID=EqCat.EqCatID and Equipment.EqID = Antenna.EqID and [Station].[StID]=[Equipment].[StID] and "+SQL;
	SQL="WHERE License.LicID = Station.LicID and Owner.ID = License.AdmID and Equipment.EqID = Frequency.EqID and "+SQL;
	SQL="SELECT * FROM Equipment, EqCat ,Antenna, AntCat, Frequency ,Owner , License, Station "+SQL;
 	Stations.m_pDatabase=&DB;
	Stations.Open(CRecordset::snapshot, SQL);
	
	if(Stations.GetRecordCount()==0)
	{
		AfxMessageBox("Data for this license is not complete!");
		return;
	}
	if(source=fopen(SFile,"rt"))
	{
		CString FName;
		FName.Format("%06ld",atol(ID));
		RepPath=GetCommandLine();
		int Place=RepPath.ReverseFind('\\')-1;
		RepPath.Delete(0);
		RepPath.Delete(Place,RepPath.GetLength()-Place);
		Place=RepPath.ReverseFind('\\')+1;
		RepPath.Delete(Place,RepPath.GetLength()-Place);
		RepPath+="reports\\";
		FName="Lic"+FName+".htm";
		FName=RepPath+FName;
		dest=fopen(FName,"wt");
		while(!feof(source))
		{
			int ch;
			ch=fgetc(source);
			if(feof(source)) break;
			if(ch=='{')
			{
				CString FieldName, FValue;
				CString RowBuf, ResStr;
				while(!feof(source))
				{
					ch=fgetc(source);
					if(ch=='}') break;
					FieldName+=ch;
				}//end while
				if(FieldName.IsEmpty())
					fputs(FValue,dest);
				else if(FieldName.GetAt(0)=='\\')
				{
					while(!feof(source))
					{
						ch=fgetc(source);
						if(ch=='<') 
						{
							ch=fgetc(source);
							FieldName=ch;
							ch=fgetc(source);
							FieldName+=ch;
							if(FieldName=="tr")
							{
								ch=fgetc(source);
								while(!feof(source))
								{
									ch=fgetc(source);
									if(ch=='<') 
									{
										ch=fgetc(source);
										FieldName=ch;
										ch=fgetc(source);
										FieldName+=ch;
										ch=fgetc(source);
										FieldName+=ch;
										if(FieldName=="/tr")
										{
											ch=fgetc(source);
											while(!Stations.IsEOF())
											{
												ProcessBuf(Stations, RowBuf, ResStr);
												ResStr="<tr>"+ResStr;
												ResStr+="</tr>";
												fputs(ResStr,dest);
												Stations.MoveNext();
											}
											break;
										}
										else
											RowBuf+="<"+FieldName;
									}
									else
										RowBuf+=ch;
								}
								break;
							}
							else
							{
								FieldName="<"+FieldName;
								fputs(FieldName,dest);
							}
						}
						else
						{
							FieldName=ch;
							fputs(FieldName,dest);
						}
					}//end while
				}
				else if(IsFieldValid(FieldName,Stations))
				{
					Stations.GetFieldValue(FieldName,FValue);
					if(FieldName=="Frequency")
					{
						double Freq=atof(FValue);
						FValue.Format("%f",Freq/1000000.);
					}
				}
				else
				{
					FValue=_T("{") + FieldName + _T("}");
				}
				fputs(FValue,dest);
			}//end if
			else
				fputc(ch,dest);
		}//end while
		Stations.Close();
		fclose(dest);
		fclose(source);
		
		AddTrail("Fixed licence generated",atol((LPCTSTR)ID),"---");
		ShellExecute(this->m_hWnd,"open",FName,NULL,NULL,SW_SHOWNORMAL);
	}
	else
	{
		AfxMessageBox("License template for fixed service not found!");
	}
}

void CLeftView::LMLicense(CString ID) 
{
	CRecordset Stations;
	FILE *source, *dest;
	CString RepPath=GetReportPath(), 
		SFile=RepPath+"LMLic.htm", 
		SQL;
	CDatabase	DB;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	SQL="Antenna.AntCatID=AntCat.AntCatID and Station.LicID="+ ID;
	SQL="Equipment.EqCatID=EqCat.EqCatID and Equipment.EqID = Antenna.EqID and [Station].[StID]=[Equipment].[StID] and "+SQL;
	SQL="WHERE License.LicID = Station.LicID and Owner.ID = License.AdmID and Equipment.EqID = Frequency.EqID and "+SQL;
	SQL="SELECT * FROM Equipment, EqCat ,Antenna, AntCat, Frequency ,Owner , License, Station "+SQL;
 	Stations.m_pDatabase=&DB;
	Stations.Open(CRecordset::snapshot, SQL);
	if(Stations.GetRecordCount()==0)
	{
		AfxMessageBox("Data for this license is not complete!");
		return;
	}
	if(source=fopen(SFile,"rt"))
	{
		CString FName;
		FName.Format("%06ld",atol(ID));
		RepPath=GetCommandLine();
		int Place=RepPath.ReverseFind('\\')-1;
		RepPath.Delete(0);
		RepPath.Delete(Place,RepPath.GetLength()-Place);
		Place=RepPath.ReverseFind('\\')+1;
		RepPath.Delete(Place,RepPath.GetLength()-Place);
		RepPath+="reports\\";
		FName="Lic"+FName+".htm";
		FName=RepPath+FName;
		dest=fopen(FName,"wt");
		while(!feof(source))
		{
			int ch;
			ch=fgetc(source);
			if(feof(source)) break;
			if(ch=='{')
			{
				CString FieldName, FValue;
				CString RowBuf, ResStr;
				while(!feof(source))
				{
					ch=fgetc(source);
					if(ch=='}') break;
					FieldName+=ch;
				}//end while
				if(FieldName.IsEmpty())
					fputs(FValue,dest);
				else if(FieldName=="\\Base")
				{
					while(!feof(source))
					{
						ch=fgetc(source);
						if(ch=='<') 
						{
							ch=fgetc(source);
							FieldName=ch;
							ch=fgetc(source);
							FieldName+=ch;
							if(FieldName=="tr")
							{
								ch=fgetc(source);
								while(!feof(source))
								{
									ch=fgetc(source);
									if(ch=='<') 
									{
										ch=fgetc(source);
										FieldName=ch;
										ch=fgetc(source);
										FieldName+=ch;
										ch=fgetc(source);
										FieldName+=ch;
										if(FieldName=="/tr")
										{
											ch=fgetc(source);
											while(!Stations.IsEOF())
											{
												ProcessBuf(Stations, RowBuf, ResStr);
												ResStr="<tr>"+ResStr;
												ResStr+="</tr>";
												fputs(ResStr,dest);
												Stations.MoveNext();
											}
											break;
										}
										else
											RowBuf+="<"+FieldName;
									}
									else
										RowBuf+=ch;
								}
								break;
							}
							else
							{
								FieldName="<"+FieldName;
								fputs(FieldName,dest);
							}
						}
						else
						{
							FieldName=ch;
							fputs(FieldName,dest);
						}
					}//end while
				}
				else if(FieldName=="\\Mobile")
				{
					CRecordset Mobiles;
					SQL="Antenna.AntCatID=AntCat.AntCatID and Mobiles.LicID="+ ID;
					SQL="Equipment.EqCatID=EqCat.EqCatID and Equipment.EqID = Antenna.EqID and [Mobiles].[MobID]=[Equipment].[MobID] and "+SQL;
					SQL="WHERE License.LicID = Mobiles.LicID and Owner.ID = License.AdmID and Equipment.EqID = Frequency.EqID and "+SQL;
					SQL="SELECT * FROM Equipment, EqCat ,Antenna, AntCat, Frequency ,Owner , License, Mobiles "+SQL;
				 	Mobiles.m_pDatabase=&DB;
					Mobiles.Open(CRecordset::snapshot, SQL);
					if(Stations.GetRecordCount()==0)
					{
						AfxMessageBox("Data for this license is not complete!");
						return;
					}
					while(!feof(source))
					{
						ch=fgetc(source);
						if(ch=='<') 
						{
							ch=fgetc(source);
							FieldName=ch;
							ch=fgetc(source);
							FieldName+=ch;
							if(FieldName=="tr")
							{
								ch=fgetc(source);
								while(!feof(source))
								{
									ch=fgetc(source);
									if(ch=='<') 
									{
										ch=fgetc(source);
										FieldName=ch;
										ch=fgetc(source);
										FieldName+=ch;
										ch=fgetc(source);
										FieldName+=ch;
										if(FieldName=="/tr")
										{
											ch=fgetc(source);
											while(!Mobiles.IsEOF())
											{
												ProcessBuf(Mobiles, RowBuf, ResStr);
												ResStr="<tr>"+ResStr;
												ResStr+="</tr>";
												fputs(ResStr,dest);
												Mobiles.MoveNext();
											}
											break;
										}
										else
											RowBuf+="<"+FieldName;
									}
									else
										RowBuf+=ch;
								}
								break;
							}
							else
							{
								FieldName="<"+FieldName;
								fputs(FieldName,dest);
							}
						}
						else
						{
							FieldName=ch;
							fputs(FieldName,dest);
						}
					}//end while
					Mobiles.Close();
				}
				else if(IsFieldValid(FieldName,Stations))
				{
					Stations.GetFieldValue(FieldName,FValue);
					if(FieldName=="Frequency")
					{
						double Freq=atof(FValue);
						FValue.Format("%f",Freq/1000000.);
					}
				}
				else
				{
					FValue=_T("{") + FieldName + _T("}");
				}
				fputs(FValue,dest);
			}//end if
			else
				fputc(ch,dest);
		}//end while
		Stations.Close();
		fclose(dest);
		fclose(source);
		
		AddTrail("Land mobile licence generated",atol((LPCTSTR)ID),"---");
		ShellExecute(this->m_hWnd,"open",FName,NULL,NULL,SW_SHOWNORMAL);
	}
	else
	{
		AfxMessageBox("License template for land mobile service not found!");
	}
	DB.Close();
}

void CLeftView::BCLicense(CString ID) 
{
	CRecordset Stations;
	FILE *source, *dest;
	CString RepPath=GetReportPath(), 
		SFile=RepPath+"BCLic.htm", 
		SQL;
	CDatabase	DB;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	SQL="Antenna.AntCatID=AntCat.AntCatID and BCStation.LicID="+ ID;
	SQL="Equipment.EqCatID=EqCat.EqCatID and Equipment.EqID = Antenna.EqID and [BCStation].[StID]=[Equipment].[BCID] and "+SQL;
	SQL="WHERE License.LicID = BCStation.LicID and Owner.ID = License.AdmID and Equipment.EqID = Frequency.EqID and "+SQL;
	SQL="SELECT * FROM Equipment, EqCat ,Antenna, AntCat, Frequency ,Owner , License, BCStation "+SQL;
 	Stations.m_pDatabase=&DB;
	Stations.Open(CRecordset::snapshot, SQL);
	
	if(Stations.GetRecordCount()==0)
	{
		AfxMessageBox("Data for this license is not complete!");
		return;
	}
	if(source=fopen(SFile,"rt"))
	{
		CString FName;
		FName.Format("%06ld",atol(ID));
		RepPath=GetCommandLine();
		int Place=RepPath.ReverseFind('\\')-1;
		RepPath.Delete(0);
		RepPath.Delete(Place,RepPath.GetLength()-Place);
		Place=RepPath.ReverseFind('\\')+1;
		RepPath.Delete(Place,RepPath.GetLength()-Place);
		RepPath+="reports\\";
		FName="Lic"+FName+".htm";
		FName=RepPath+FName;
		dest=fopen(FName,"wt");
		while(!feof(source))
		{
			int ch;
			ch=fgetc(source);
			if(feof(source)) break;
			if(ch=='{')
			{
				CString FieldName, FValue;
				CString RowBuf, ResStr;
				while(!feof(source))
				{
					ch=fgetc(source);
					if(ch=='}') break;
					FieldName+=ch;
				}//end while
				if(FieldName.IsEmpty())
					fputs(FValue,dest);
				else if(FieldName.GetAt(0)=='\\')
				{
					while(!feof(source))
					{
						ch=fgetc(source);
						if(ch=='<') 
						{
							ch=fgetc(source);
							FieldName=ch;
							ch=fgetc(source);
							FieldName+=ch;
							if(FieldName=="tr")
							{
								ch=fgetc(source);
								while(!feof(source))
								{
									ch=fgetc(source);
									if(ch=='<') 
									{
										ch=fgetc(source);
										FieldName=ch;
										ch=fgetc(source);
										FieldName+=ch;
										ch=fgetc(source);
										FieldName+=ch;
										if(FieldName=="/tr")
										{
											ch=fgetc(source);
											while(!Stations.IsEOF())
											{
												ProcessBuf(Stations, RowBuf, ResStr);
												ResStr="<tr>"+ResStr;
												ResStr+="</tr>";
												fputs(ResStr,dest);
												Stations.MoveNext();
											}
											break;
										}
										else
											RowBuf+="<"+FieldName;
									}
									else
										RowBuf+=ch;
								}
								break;
							}
							else
							{
								FieldName="<"+FieldName;
								fputs(FieldName,dest);
							}
						}
						else
						{
							FieldName=ch;
							fputs(FieldName,dest);
						}
					}//end while
				}
				else if(IsFieldValid(FieldName,Stations))
				{
					Stations.GetFieldValue(FieldName,FValue);
					if(FieldName=="Frequency")
					{
						double Freq=atof(FValue);
						FValue.Format("%f",Freq/1000000.);
					}
				}
				else
				{
					FValue=_T("{") + FieldName + _T("}");
				}
				fputs(FValue,dest);
			}//end if
			else
				fputc(ch,dest);
		}//end while
		Stations.Close();
		fclose(dest);
		fclose(source);
		AddTrail("Broadcasting licence generated",atol((LPCTSTR)ID),"---");
		
		ShellExecute(this->m_hWnd,"open",FName,NULL,NULL,SW_SHOWNORMAL);
	}
	else
	{
		AfxMessageBox(_T("License template for broadcasting service not found!"));
	}
	DB.Close();
}

void CLeftView::ESLicense(CString ID) 
{
	CRecordset Stations;
	FILE *source, *dest;
	CString RepPath=GetReportPath(), 
		SFile=RepPath+_T("ESLic.htm"), 
		SQL;
	CDatabase	DB;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	SQL=" grp.grp_id=emiss.grp_id and e_stn.LicID="+ ID;
	SQL="e_ant.AntID=grp.AntID and e_ant.pattern_id=ant_type.pattern_id and grp.grp_id=assgn.grp_id and "+SQL;
	SQL="WHERE License.LicID = e_stn.LicID and Owner.ID = License.AdmID and e_stn.ntc_id = e_ant.ntc_id and "+SQL;
	SQL="SELECT *,freq_mhz*1000000 as Frequency FROM e_stn,e_ant,emiss,ant_type,grp,assgn ,Owner , License "+SQL;
 	Stations.m_pDatabase=&DB;
	Stations.Open(CRecordset::snapshot, SQL);
	
	if(Stations.GetRecordCount()==0)
	{
		AfxMessageBox("Data for this license is not complete!");
		return;
	}
	if(source=fopen(SFile,"rt"))
	{
		CString FName;
		FName.Format("%06ld",atol(ID));
		RepPath=GetCommandLine();
		int Place=RepPath.ReverseFind('\\')-1;
		RepPath.Delete(0);
		RepPath.Delete(Place,RepPath.GetLength()-Place);
		Place=RepPath.ReverseFind('\\')+1;
		RepPath.Delete(Place,RepPath.GetLength()-Place);
		RepPath+="reports\\";
		FName="Lic"+FName+".htm";
		FName=RepPath+FName;
		dest=fopen(FName,"wt");
		while(!feof(source))
		{
			int ch;
			ch=fgetc(source);
			if(feof(source)) break;
			if(ch=='{')
			{
				CString FieldName, FValue;
				CString RowBuf, ResStr;
				while(!feof(source))
				{
					ch=fgetc(source);
					if(ch=='}') break;
					FieldName+=ch;
				}//end while
				if(FieldName.IsEmpty())
					fputs(FValue,dest);
				else if(FieldName.GetAt(0)=='\\')
				{
					while(!feof(source))
					{
						ch=fgetc(source);
						if(ch=='<') 
						{
							ch=fgetc(source);
							FieldName=ch;
							ch=fgetc(source);
							FieldName+=ch;
							if(FieldName=="tr")
							{
								ch=fgetc(source);
								while(!feof(source))
								{
									ch=fgetc(source);
									if(ch=='<') 
									{
										ch=fgetc(source);
										FieldName=ch;
										ch=fgetc(source);
										FieldName+=ch;
										ch=fgetc(source);
										FieldName+=ch;
										if(FieldName=="/tr")
										{
											ch=fgetc(source);
											while(!Stations.IsEOF())
											{
												ProcessBuf(Stations, RowBuf, ResStr);
												ResStr="<tr>"+ResStr;
												ResStr+="</tr>";
												fputs(ResStr,dest);
												Stations.MoveNext();
											}
											break;
										}
										else
											RowBuf+="<"+FieldName;
									}
									else
										RowBuf+=ch;
								}
								break;
							}
							else
							{
								FieldName="<"+FieldName;
								fputs(FieldName,dest);
							}
						}
						else
						{
							FieldName=ch;
							fputs(FieldName,dest);
						}
					}//end while
				}
				else if(IsFieldValid(FieldName,Stations))
				{
					Stations.GetFieldValue(FieldName,FValue);
					if(FieldName=="freq_mhz")
					{
						double Freq=atof(FValue);
						FValue.Format("%f",Freq/1000000.);
					}
				}
				else
				{
					FValue=_T("{") + FieldName + _T("}");
				}
				fputs(FValue,dest);
			}//end if
			else
				fputc(ch,dest);
		}//end while
		Stations.Close();
		fclose(dest);
		fclose(source);
		
		AddTrail(_T("Earth station licence generated"),atol((LPCTSTR)ID),"---");
		ShellExecute(this->m_hWnd,"open",FName,NULL,NULL,SW_SHOWNORMAL);
	}
	else
	{
		AfxMessageBox("License template for earth stations not found!");
	}
}

void CLeftView::OnAddpayment() 
{
	CString Temp=/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR,
		UserName=/*((CSMS4DCApp *)AfxGetApp())->*/m_UserName;
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	AFX_MANAGE_STATE(AfxGetStaticModuleState()) ;
	CPaymentDlg PayDlg;
	PayDlg.m_UserName=UserName;
	PayDlg.m_CDBSTR=Temp;
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	PayDlg.m_ID=GetTreeCtrl().GetItemData(Node);
	PayDlg.DoModal();
	pView->m_Refresh=true;
	pView->RedrawWindow();
}

void CLeftView::IssueInvoices()
{
	CString SQL;
	CDatabase DB;
	CRecordset RS;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;

	SQL=_T("select qry.invperiod,months,format(lastinv,'yyyy/mm/dd'),qry.licid, format(opdate,'yyyy/mm/dd'),SrvID from invoiceperiod, ");
	SQL+=_T("(SELECT license.InvPeriod, Max(invoice.InvDate) AS lastinv, license.LicID, OpDate, SrvID ");
	SQL+=_T("FROM license, invoice WHERE license.LicID=[invoice].[licid] and license.archive=0 and license.status='Granted' ");
	SQL+=_T("GROUP BY license.InvPeriod, license.LicID, OpDate, SrvID) as qry ");
	SQL+=_T("where qry.invperiod=invoiceperiod.invperiod and Date()-lastinv>Months*30 order by qry.licid");

	RS.Open(CRecordset::snapshot,SQL);
	while(!RS.IsEOF())
	{
		CRecordset RS2;
		CString SQL2, LID, TotVal, Per, InvID, TempDate, SrvID, InvDt;
		long InvCount,PayCount;
		CString Debit=_T("0"),Paid=_T("0"),Temp;
		RS.GetFieldValue(1,Per);
		RS.GetFieldValue(2,InvDt);
		RS.GetFieldValue(3,LID);
		RS.GetFieldValue(4,TempDate);
		RS.GetFieldValue(5,SrvID);
		RS2.m_pDatabase=&DB;

		SQL.Format(_T("select Debit from invoice where LicID=%s order by InvDate"),LID);
		RS2.Open(CRecordset::snapshot,SQL);
		InvCount=RS2.GetRecordCount();
		if(InvCount>0)
		{
			RS2.GetFieldValue((short)0,Debit);
			RS2.MoveLast();
			InvCount=RS2.GetRecordCount();
		}
		RS2.Close();
		SQL.Format(_T("select Sum(Amount),Count(PaymentID) from payment where LicID=%s"),LID);
		RS2.Open(CRecordset::snapshot,SQL);
		RS2.GetFieldValue(1,Temp);
		PayCount=atol(Temp);
		if(PayCount>0)
			RS2.GetFieldValue((short)0,Paid);
		else
			Paid=_T("0");
		RS2.Close();
/*		SQL.Format(_T("select Debit from invoice where LicID=%s"),LID);
		RS2.Open(CRecordset::snapshot,SQL);
		InvCount=RS2.GetRecordCount();
		RS2.GetFieldValue((short)0,Debit);
		RS2.Close();
		SQL.Format(_T("select Amount from payment where LicID=%s"),LID);
		RS2.Open(CRecordset::snapshot,SQL);
		PayCount=RS2.GetRecordCount();
		if(PayCount)
			RS2.GetFieldValue((short)0,Paid);
		else
			Paid=_T("0");
		RS2.Close();*/
		if((PayCount<1 || InvCount<1) || (PayCount>=1 && InvCount==1 && atol(Debit)>atol(Paid)))  break;
		CTime OpDate(atoi(TempDate.Left(4)),atoi(TempDate.Mid(5,2)),atoi(TempDate.Right(2)),0,0,0), 
			InvDate(atoi(InvDt.Left(4)),atoi(InvDt.Mid(5,2)),atoi(InvDt.Right(2)),0,0,0);
		CTime Today =CTime::GetCurrentTime();
		CTimeSpan diff=Today-OpDate, Period(atol(Per)*31,0,0,0);
		if(SrvID==_T("F"))
		{
			SQL2=_T("SELECT sum(freqfee) as totVal from frequency,equipment,station,eqcat ");
			SQL2+=_T("where frequency.eqid=equipment.eqid and equipment.stid=station.stid and equipment.eqcatid=eqcat.eqcatid and station.licid=")+LID;
		}
		else if(SrvID==_T("B"))
		{
			SQL2=_T("SELECT sum(freqfee) as totVal from frequency,equipment,BCstation,license ");
			SQL2+=_T("where frequency.eqid=equipment.eqid and equipment.BCid=BCstation.stid and BCstation.licid=")+LID;
		}
		else if(SrvID==_T("MT"))
			continue;
		else
		{
			SQL2=_T("SELECT sum(FreqFee) as totVal from assgn,grp,e_stn ");
			SQL2+=_T("where assgn.grp_id=grp.grp_id and grp.ntc_id=e_stn.ntc_id and e_stn.LicID=")+LID;
		}
		RS2.Open(CRecordset::snapshot,SQL2);
		if(RS2.IsEOF())
			TotVal=_T("0");
		else
			RS2.GetFieldValue((short)0,TotVal);
		RS2.Close();
		long Sum=GetBalance(LID);

		while(true)
		{
			int NewYear=InvDate.GetYear(),NewMonth=InvDate.GetMonth(),NewDay=InvDate.GetDay();
			NewMonth+=atoi(Per);
			if(NewDay>28)
				NewDay=28;
			if(NewMonth>12)
			{
				NewMonth-=12;
				NewYear++;
			}
			CTime NewInvDate(NewYear,NewMonth,NewDay,0,0,0);
			CTimeSpan Due(15,0,0,0);
			CTime DueDate=NewInvDate+Due;
			if(Sum<0)
			{
				SQL.Format(_T("UPDATE Invoice SET Replaced = Yes WHERE InvoiceID=(select max(invoiceID) from invoice where Licid=%s)"),LID);
				DB.ExecuteSQL(SQL);
			}
			RS2.Open(CRecordset::snapshot,_T("select max(invoiceid) from invoice"));
			RS2.GetFieldValue((short)0,InvID);
			RS2.Close();
			if(InvID.IsEmpty()) InvID=_T("1");
			CString InvNum;
			InvNum.Format(_T("%05d%05d"),atol(LID),atol(InvID)+1);
			SQL2.Format(_T("select %ld,%s,'%s','%s','%s','%s',%ld,%ld"), atol(InvID)+1,LID,InvNum,NewInvDate.Format("%Y/%m/%d"),
				DueDate.Format("%Y/%m/%d"),_T("Generated on ")+Today.Format("%Y/%m/%d"),atol(TotVal),Sum);
			SQL2=_T("insert into invoice (invoiceid, licid, invoiceno, invdate, duedate, description, debit, credit) ")+SQL2;
			DB.ExecuteSQL(SQL2);
			AddTrail("Create invoice automatically",atol(InvID)+1,"Invoice");
			Sum-=atol(TotVal);
			InvDate=NewInvDate;
			if(InvDate+Period>Today) break;
		}
		RS.MoveNext();
	}
	RS.Close();
	DB.Close();
}

long CLeftView::GetBalance(CString LID)
{
	CDatabase DB;
	CRecordset RS;
	CString SQL1,SQL2,Value;
	long Sum=0;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	RS.m_pDatabase=&DB;
	SQL1.Format(_T("Select InvoiceNo, format(InvDate,'yyyy/mm/dd') as dt, Debit, Credit from Invoice where LicID=%s and Replaced=0"), LID);
	SQL2.Format(_T("Select PaymentNo, format(PayDate,'yyyy/mm/dd') as dt, 0, Amount from Payment where LicID=%s"), LID);
	SQL1=SQL1 + " union all " + SQL2;
	SQL2="select * from (" + SQL1 + ") order by dt";
	RS.Open(CRecordset::dynaset,SQL2);
	for(int k=0;!RS.IsEOF();k++)
	{

		RS.GetFieldValue(2,Value);
		if(atol(Value)==0)
		{
			Sum-=atol(Value);
			RS.GetFieldValue(3,Value);
			Sum+=atol(Value);
		}
		else
		{
			Sum=atol(Value);
			RS.GetFieldValue(3,Value);
			Sum=atol(Value)-Sum;
		}
		RS.MoveNext();
	}
	RS.Close();
	DB.Close();
	return Sum;
}

void CLeftView::OnLicenseNotice() 
{
}

void CLeftView::OnStationNotice() 
{
//	CString AdmRefID;
//	m_AdmRefID.GetWindowText(AdmRefID);
//	if(AdmRefID=="")
//	{
//		CTime tm = CTime::GetCurrentTime();
//		AdmRefID.Format("IRN%02d%02d%02d%02d%02d%02d",tm.GetYear(),tm.GetMonth(),tm.GetDay(),
//			tm.GetHour(),tm.GetMinute(),tm.GetSecond());
//		m_pSet.Edit();
//		m_pSet.m_AdmRefID=AdmRefID;
//		m_pSet.Update();
//		LoadData();
//	}
	CString Temp=/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR;
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem(),
		Parent=GetTreeCtrl().GetParentItem(Node);
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	AFX_MANAGE_STATE(AfxGetStaticModuleState()) ;
	CNotice NoticeDlg;
	NoticeDlg.m_CDBSTR=Temp;
	int Type;
	NoticeDlg.m_StID=GetTreeCtrl().GetItemData(Node);
	NoticeDlg.m_LicID=-1;
	GetTreeCtrl().GetItemImage(Node,Type,Type);
	if(Type==BC)
		NoticeDlg.m_SrvType=pView->m_Service;
	if(Type==STATION)
	{
		NoticeDlg.m_SrvType=pView->m_Service;
		NoticeDlg.m_StTable=_T("Station");
	}
	if(Type==MOBILE)
	{
		NoticeDlg.m_SrvType=pView->m_Service;
		NoticeDlg.m_StTable=_T("Mobiles");
	}
	NoticeDlg.DoModal();		
}

void CLeftView::OnDeleteReceiver() 
{
	CString Temp;
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	long RecID=GetTreeCtrl().GetItemData(Node);
	CDatabase DB;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR, FALSE, FALSE, _T( "ODBC;"), FALSE);
	CString SQL;
	SQL.Format("delete * from link where ReceiverID=%ld",RecID);
	DB.ExecuteSQL(SQL);
	DB.Close();
	AddTrail("Delete receiving area",RecID,"Link");
	GetTreeCtrl().DeleteItem(Node);
}

void CLeftView::OnEditOwner() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	pView->ModifyData();

}

void CLeftView::OnEditantenna() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	pView->ModifyData();
}

void CLeftView::OnEditequipment() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	pView->ModifyData();
}

void CLeftView::OnEditfrequency() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	pView->ModifyData();	
}

void CLeftView::OnEditlicense() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	CDatabase DB;
	CRecordset RS;
	RS.m_pDatabase=&DB;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR,false,false,_T("ODBC;"),false);
	CString SQL,Value;
	SQL.Format(_T("select Status from license where licid=%ld"),pView->m_RecID);
	RS.Open(CRecordset::snapshot,SQL);
	RS.GetFieldValue((short)0,Value);
	RS.Close();
	DB.Close();
	if(Value==_T("Granted"))
		CopyToArchive(pView->m_RecID);
	else
		pView->ModifyData();
}

void CLeftView::OnEditstation() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	pView->ModifyData();	
}

void CLeftView::OnAddOwner() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	GetTreeCtrl().EnableWindow(false);
	pView->m_OldRecID=pView->m_RecID;
	pView->m_RecID=-1;
	pView->m_Table=_T("Owner");
	pView->m_Action=1;
	pView->m_ReadOnly=false;
	pView->m_Refresh=true;
	pView->m_RecordType=OWNER;
	pView->RedrawWindow();
}

void CLeftView::OnAddLicense() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	GetTreeCtrl().EnableWindow(false);
	pView->m_OldRecordType=OWNER;
	pView->m_OldTable=_T("Owner");
	pView->m_OldRecID=pView->m_RecID;
	pView->m_RecID=-1;
	pView->m_Table=_T("License");
	pView->m_Action=1;
	pView->m_ReadOnly=false;
	pView->m_Refresh=true;
	pView->m_RecordType=LICENSE;
	pView->RedrawWindow();
}

void CLeftView::OnAddAntenna() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	GetTreeCtrl().EnableWindow(false);
	pView->m_OldRecordType=EQUIPMENT;
	pView->m_OldTable="Equipment";
	pView->m_OldRecID=pView->m_RecID;
	pView->m_RecID=-1;
	pView->m_Table="Antenna";
	pView->m_Action=1;
	pView->m_ReadOnly=false;
	pView->m_Refresh=true;
	pView->m_RecordType=ANTENNA;
	pView->RedrawWindow();
}


void CLeftView::OnAddEquipment() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	GetTreeCtrl().EnableWindow(false);
	int Img;
	GetTreeCtrl().GetItemImage(GetTreeCtrl().GetSelectedItem(),Img,Img);
	pView->m_OldRecordType=Img;
	if(Img==STATION)
		pView->m_OldTable="Station";
	if(Img==BC)
		pView->m_OldTable="BCStation";
	if(Img==MOBILE)
		pView->m_OldTable="Mobiles";
	pView->m_OldRecID=pView->m_RecID;
	pView->m_RecID=-1;
	pView->m_Table="Equipment";
	pView->m_Action=1;
	pView->m_ReadOnly=false;
	pView->m_Refresh=true;
	pView->m_RecordType=EQUIPMENT;
	pView->RedrawWindow();
}

void CLeftView::OnAddFrequency() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	GetTreeCtrl().EnableWindow(false);
	pView->m_OldRecordType=EQUIPMENT;
	pView->m_OldTable="Equipment";
	pView->m_OldRecID=pView->m_RecID;
	pView->m_RecID=-1;
	pView->m_Table="Frequency";
	pView->m_Action=1;
	pView->m_ReadOnly=false;
	pView->m_Refresh=true;
	pView->m_RecordType=FREQUENCY;
	pView->RedrawWindow();
}

void CLeftView::OnDeleteFrequency() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	HTREEITEM Par=GetTreeCtrl().GetParentItem(Node);
	if(DelRecPermanent(FREQUENCY, GetTreeCtrl().GetItemData(Node),IDNO, GetTreeCtrl().GetItemData(Par)))
	{
		AddTrail("Delete frequency",GetTreeCtrl().GetItemData(Node),"Frequency");
		pView->m_OldRecordType=EQUIPMENT;
		pView->m_OldTable=_T("Equipment");
		pView->m_OldRecID=GetTreeCtrl().GetItemData(Par);
		pView->m_RecID=GetTreeCtrl().GetItemData(Par);
		pView->m_Table=_T("Equipment");
		pView->m_Action=1;
		pView->m_ReadOnly=true;
		pView->m_Refresh=true;
		pView->m_RecordType=EQUIPMENT;
		GetTreeCtrl().SelectItem(Par);
		GetTreeCtrl().DeleteItem(Node);
		pView->RedrawWindow();
	}
}

void CLeftView::OnDeleteAntenna() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	HTREEITEM Par=GetTreeCtrl().GetParentItem(Node);
	if(DelRecPermanent(ANTENNA, GetTreeCtrl().GetItemData(Node),IDNO, GetTreeCtrl().GetItemData(Par)))
	{
		AddTrail(_T("Delete antenna"),GetTreeCtrl().GetItemData(Node),_T("Antenna"));
		pView->m_OldRecordType=EQUIPMENT;
		pView->m_OldTable=_T("Equipment");
		pView->m_OldRecID=GetTreeCtrl().GetItemData(Par);
		pView->m_RecID=GetTreeCtrl().GetItemData(Par);
		pView->m_Table=_T("Equipment");
		pView->m_Action=1;
		pView->m_ReadOnly=true;
		pView->m_Refresh=true;
		pView->m_RecordType=EQUIPMENT;
		GetTreeCtrl().SelectItem(Par);
		GetTreeCtrl().DeleteItem(Node);
		pView->RedrawWindow();
	}
}

void CLeftView::OnDeleteEquipment() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	HTREEITEM Par=GetTreeCtrl().GetParentItem(Node);
	if(DelRecPermanent(EQUIPMENT, GetTreeCtrl().GetItemData(Node),IDNO, GetTreeCtrl().GetItemData(Par)))
	{
		AddTrail("Delete equipment",GetTreeCtrl().GetItemData(Node),"Equipment");
		pView->m_OldRecordType=STATION;
		pView->m_OldTable=_T("Station");
		pView->m_OldRecID=GetTreeCtrl().GetItemData(Par);
		pView->m_RecID=GetTreeCtrl().GetItemData(Par);
		pView->m_Table=_T("Station");
		pView->m_Action=1;
		pView->m_ReadOnly=true;
		pView->m_Refresh=true;
		pView->m_RecordType=STATION;
		GetTreeCtrl().SelectItem(Par);
		GetTreeCtrl().DeleteItem(Node);
		pView->RedrawWindow();
	}
}

void CLeftView::OnDeleteStation() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	HTREEITEM Par=GetTreeCtrl().GetParentItem(Node);
	int typ;
	GetTreeCtrl().GetItemImage(Node,typ,typ);
	if(DelRecPermanent(typ, GetTreeCtrl().GetItemData(Node),IDNO, GetTreeCtrl().GetItemData(Par)))
	{
		if(typ==STATION)
			AddTrail("Delete fixed/base station",GetTreeCtrl().GetItemData(Node),"Station");
		if(typ==BC)
			AddTrail("Delete broadcasting station",GetTreeCtrl().GetItemData(Node),"BCStation");
		if(typ==MOBILE)
			AddTrail("Delete mobile station",GetTreeCtrl().GetItemData(Node),"Mobiles");
		GetTreeCtrl().GetItemImage(Par,typ,typ);
		if(typ==LICENSE)
		{
			pView->m_OldRecordType=LICENSE;
			pView->m_OldTable=_T("License");
			pView->m_Table=_T("License");
			pView->m_RecordType=LICENSE;
		}
		else
		{
			pView->m_OldRecordType=SMS4DC;
			pView->m_OldTable=_T("");
			pView->m_Table=_T("");
			pView->m_RecordType=SMS4DC;
		}
		pView->m_OldRecID=GetTreeCtrl().GetItemData(Par);
		pView->m_RecID=GetTreeCtrl().GetItemData(Par);
		pView->m_Action=1;
		pView->m_ReadOnly=true;
		pView->m_Refresh=true;
		GetTreeCtrl().SelectItem(Par);
		GetTreeCtrl().DeleteItem(Node);
		//pView->RedrawWindow();
		CleanScreen();
	}
}

void CLeftView::OnDeleteLicense() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	HTREEITEM Par=GetTreeCtrl().GetParentItem(Node);
	if(DelRecPermanent(LICENSE, GetTreeCtrl().GetItemData(Node),IDNO, GetTreeCtrl().GetItemData(Par)))
	{
		AddTrail("Delete license",GetTreeCtrl().GetItemData(Node),"License");
		pView->m_OldRecordType=OWNER;
		pView->m_OldTable=_T("Owner");
		pView->m_Table=_T("Owner");
		pView->m_RecordType=OWNER;
		pView->m_OldRecID=GetTreeCtrl().GetItemData(Par);
		pView->m_RecID=GetTreeCtrl().GetItemData(Par);
		pView->m_Action=1;
		pView->m_ReadOnly=true;
		pView->m_Refresh=true;
		GetTreeCtrl().SelectItem(Par);
		GetTreeCtrl().DeleteItem(Node);
		//pView->RedrawWindow();
		CleanScreen();
	}
}

bool CLeftView::DelRecPermanent(int Typ, long RecID, int Ans, long ParentID)
{
	bool Res=false;
	CDatabase DB;
	CRecordset RS;
	CString SQL;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR,false,false,_T("ODBC;"),false);
	RS.m_pDatabase=&DB;
	switch(Typ)
	{
	case FREQUENCY:
		if(Ans!=IDYES)
			Ans=AfxMessageBox(_T("Are you sure about deleting this frequency and all links to and from this?"),MB_YESNO|MB_ICONWARNING);
		if(Ans==IDYES)
		{
			SQL.Format(_T("delete * from Link where TXID=%ld or RXID=%ld"),RecID,RecID);
			DB.ExecuteSQL(SQL);
			SQL.Format(_T("delete * from frequency where freqid=%ld"),RecID);
			DB.ExecuteSQL(SQL);
			SQL.Format(_T("delete * from Coord where freq_id=%ld"),RecID);
			DB.ExecuteSQL(SQL);
			Res=true;
		}
		break;
	case ANTENNA:
		if(Ans!=IDYES)
			Ans=AfxMessageBox(_T("Are you sure about deleting this antenna and all links using this?"),MB_YESNO|MB_ICONWARNING);
		if(Ans==IDYES)
		{
			SQL.Format(_T("delete * from Link where TXAntID=%ld or RXAntID=%ld"),RecID,RecID);
			DB.ExecuteSQL(SQL);
			SQL.Format(_T("select antcatid from antenna where antid=%ld"),RecID);
			RS.Open(CRecordset::snapshot, SQL);
				CString AntID;
				RS.GetFieldValue((short)0,AntID);
			RS.Close();
			SQL.Format(_T("delete * from antenna where antid=%ld"),RecID);
			DB.ExecuteSQL(SQL);
			SQL.Format(_T("delete * from antcat where antcatid=%s"),AntID);
			DB.ExecuteSQL(SQL);
			SQL.Format(_T("delete * from antdiag where antid=%s"),AntID);
			DB.ExecuteSQL(SQL);
			SQL.Format(_T("delete * from anthgt where antid=%ld"),RecID);
			DB.ExecuteSQL(SQL);
			Res=true;
		}
		break;
	case EQUIPMENT:
		if(Ans!=IDYES)
			Ans=AfxMessageBox(_T("Are you sure about deleting this equipment and all of its frequencies, antennas and links?"),MB_YESNO|MB_ICONWARNING);
		if(Ans==IDYES)
		{
			SQL.Format(_T("select freqid from frequency,equipment where frequency.eqid=equipment.eqid and Equipment.EqID=%ld"),RecID);
			RS.Open(CRecordset::snapshot, SQL);
			while(true)
			{
				if(RS.IsEOF()) break;
				CString FreqID;
				RS.GetFieldValue((short)0,FreqID);
				DelRecPermanent(FREQUENCY, atol(FreqID),IDYES,RecID);
				RS.MoveNext();
			}
			RS.Close();
			SQL.Format(_T("select antid from antenna,equipment where antenna.eqid=equipment.eqid and Equipment.EqID=%ld"),RecID);
			RS.Open(CRecordset::snapshot, SQL);
			while(true)
			{
				if(RS.IsEOF()) break;
				CString AntID;
				RS.GetFieldValue((short)0,AntID);
				DelRecPermanent(ANTENNA, atol(AntID),IDYES,RecID);
				RS.MoveNext();
			}
			RS.Close();
			SQL.Format(_T("delete * from equipment where eqid=%ld"),RecID);
			DB.ExecuteSQL(SQL);
			Res=true;
		}
		break;
	case STATION:
		if(Ans!=IDYES)
			Ans=AfxMessageBox(_T("Are you sure about deleting this station and all of its equipments, frequencies, antennas and links?"),MB_YESNO|MB_ICONWARNING);
		if(Ans==IDYES)
		{
			SQL.Format(_T("select equipment.EqID from Station,equipment where Station.StID=equipment.stid and Station.StID=%ld"),RecID);
			RS.Open(CRecordset::snapshot, SQL);
			while(true)
			{
				if(RS.IsEOF()) break;
				CString EqID;
				RS.GetFieldValue((short)0,EqID);
				DelRecPermanent(EQUIPMENT, atol(EqID), IDYES,RecID);
				RS.MoveNext();
			}
			RS.Close();
			SQL.Format(_T("delete * from Station where Stid=%ld"),RecID);
			DB.ExecuteSQL(SQL);
			Res=true;
		}
		break;
	case BC:
		if(Ans!=IDYES)
			Ans=AfxMessageBox(_T("Are you sure about deleting this station and all of its equipments, frequencies, antennas and links?"),MB_YESNO|MB_ICONWARNING);
		if(Ans==IDYES)
		{
			SQL.Format(_T("select equipment.EqID from BCStation,equipment where BCStation.StID=equipment.BCid and BCStation.StID=%ld"),RecID);
			RS.Open(CRecordset::snapshot, SQL);
			while(true)
			{
				if(RS.IsEOF()) break;
				CString EqID;
				RS.GetFieldValue((short)0,EqID);
				DelRecPermanent(EQUIPMENT, atol(EqID), IDYES,RecID);
				RS.MoveNext();
			}
			RS.Close();
			SQL.Format(_T("delete * from BCStation where Stid=%ld"),RecID);
			DB.ExecuteSQL(SQL);
			Res=true;
		}
		break;
	case MOBILE:
		if(Ans!=IDYES)
			Ans=AfxMessageBox(_T("Are you sure about deleting this station and all of its equipments, frequencies, antennas and links?"),MB_YESNO|MB_ICONWARNING);
		if(Ans==IDYES)
		{
			SQL.Format(_T("select equipment.EqID from Mobiles,equipment where Mobiles.MobID=equipment.Mobid and Mobiles.MobID=%ld"),RecID);
			RS.Open(CRecordset::snapshot, SQL);
			while(true)
			{
				if(RS.IsEOF()) break;
				CString EqID;
				RS.GetFieldValue((short)0,EqID);
				DelRecPermanent(EQUIPMENT, atol(EqID), IDYES,RecID);
				RS.MoveNext();
			}
			RS.Close();
			SQL.Format(_T("delete * from Mobiles where Mobid=%ld"),RecID);
			DB.ExecuteSQL(SQL);
			Res=true;
		}
		break;
	case LICENSE:
		if(Ans!=IDYES)
			Ans=AfxMessageBox(_T("Are you sure about deleting this license and all of its stations, payments, invoices, equipments, frequencies, antennas and links?"),MB_YESNO|MB_ICONWARNING);
		if(Ans==IDYES)
		{
			CString Srv;
			SQL.Format(_T("select SrvID from License where LicID=%ld"),RecID);
			RS.Open(CRecordset::snapshot, SQL);
			RS.GetFieldValue((short)0,Srv);
			RS.Close();
			if(Srv==_T("F") || Srv==_T("MT"))
			{
				SQL.Format(_T("select stID from Station where licID=%ld"),RecID);
				RS.Open(CRecordset::snapshot, SQL);
				while(true)
				{
					if(RS.IsEOF()) break;
					CString StID;
					RS.GetFieldValue((short)0,StID);
					DelRecPermanent(STATION, atol(StID), IDYES,RecID);
					RS.MoveNext();
				}
				RS.Close();
			}
			else if(Srv==_T("B"))
			{
				SQL.Format(_T("select stID from BCStation where licID=%ld"),RecID);
				RS.Open(CRecordset::snapshot, SQL);
				while(true)
				{
					if(RS.IsEOF()) break;
					CString StID;
					RS.GetFieldValue((short)0,StID);
					DelRecPermanent(BC, atol(StID), IDYES,RecID);
					RS.MoveNext();
				}
				RS.Close();
			}
			else if(Srv==_T("MT"))
			{
				SQL.Format(_T("select MobID from Mobiles where licID=%ld"),RecID);
				RS.Open(CRecordset::snapshot, SQL);
				while(true)
				{
					if(RS.IsEOF()) break;
					CString StID;
					RS.GetFieldValue((short)0,StID);
					DelRecPermanent(MOBILE, atol(StID), IDYES,RecID);
					RS.MoveNext();
				}
				RS.Close();
			}
			else
			{
				SQL.Format(_T("select ntc_id from e_stn where LicID=%ld"),RecID);
				RS.Open(CRecordset::snapshot, SQL);
				while(true)
				{
					if(RS.IsEOF()) break;
					CString StID;
					RS.GetFieldValue((short)0,StID);
					DelRecPermanent(ESTATION, atol(StID), IDYES,RecID);
					RS.MoveNext();
				}
				RS.Close();
			}
			SQL.Format(_T("delete * from Invoice where Licid=%ld"),RecID);
			DB.ExecuteSQL(SQL);
			SQL.Format(_T("delete * from Payment where Licid=%ld"),RecID);
			DB.ExecuteSQL(SQL);
			SQL.Format(_T("delete * from License where Licid=%ld"),RecID);
			DB.ExecuteSQL(SQL);
			Res=true;
		}
		break;
	case OWNER:
		if(Ans!=IDYES)
			Ans=AfxMessageBox(_T("Are you sure about deleting this owner and all of its licenses, stations, payments, invoices, equipments, frequencies, antennas and links?"),MB_YESNO|MB_ICONWARNING);
		if(Ans==IDYES)
		{
			SQL.Format(_T("select LicID from License where AdmID=%ld"),RecID);
			RS.Open(CRecordset::snapshot, SQL);
			while(true)
			{
				if(RS.IsEOF()) break;
				CString LicID;
				RS.GetFieldValue((short)0,LicID);
				DelRecPermanent(LICENSE, atol(LicID), IDYES,RecID);
				RS.MoveNext();
			}
			RS.Close();
			SQL.Format(_T("delete * from Owner where ID=%ld"),RecID);
			DB.ExecuteSQL(SQL);
			Res=true;
		}
		break;
	case GROUP:
		if(Ans!=IDYES)
			Ans=AfxMessageBox(_T("Are you sure about deleting this group and all of its frequencies, emissions,\n coordinations, special sections, classes of station and filters?"),MB_YESNO|MB_ICONWARNING);
		if(Ans==IDYES)
		{
			SQL.Format(_T("delete * from emiss where grp_id=%ld"),RecID);
			DB.ExecuteSQL(SQL);
			SQL.Format(_T("delete * from assgn where grp_id=%ld"),RecID);
			DB.ExecuteSQL(SQL);
			SQL.Format(_T("delete * from gpub where grp_id=%ld"),RecID);
			DB.ExecuteSQL(SQL);
			SQL.Format(_T("delete * from provn where grp_id=%ld"),RecID);
			DB.ExecuteSQL(SQL);
			SQL.Format(_T("delete * from ESFilters where EqID=%ld"),RecID);
			DB.ExecuteSQL(SQL);
			SQL.Format(_T("delete * from srv_cls where grp_id=%ld"),RecID);
			DB.ExecuteSQL(SQL);

			SQL.Format(_T("delete * from grp where grp_id=%ld"),RecID);
			DB.ExecuteSQL(SQL);
			Res=true;
		}
		break;
	case EANTUP:
	case EANTDN:
		if(Ans!=IDYES)
			Ans=AfxMessageBox(_T("Are you sure about deleting this antenna and all of its group of information?"),MB_YESNO|MB_ICONWARNING);
		if(Ans==IDYES)
		{
			SQL.Format(_T("select grp_id from grp where AntID=%ld"),RecID);
			RS.Open(CRecordset::snapshot, SQL);
			CString grpID;
			while(!RS.IsEOF())
			{
				RS.GetFieldValue((short)0,grpID);
				DelRecPermanent(GROUP, atol(grpID),IDYES,RecID);
				RS.MoveNext();
			}
			RS.Close();

			SQL.Format(_T("delete * from ESAntPatt where AntID=%ld"),RecID);
			DB.ExecuteSQL(SQL);
			SQL.Format(_T("delete * from e_ant where AntID=%ld"),RecID);
			DB.ExecuteSQL(SQL);
			Res=true;
		}
		break;
	case ESTATION:
		if(Ans!=IDYES)
			Ans=AfxMessageBox(_T("Are you sure about deleting this station and all of its beams and groups?"),MB_YESNO|MB_ICONWARNING);
		if(Ans==IDYES)
		{
			SQL.Format(_T("select AntID from e_ant where ntc_id=%ld"),RecID);
			RS.Open(CRecordset::snapshot, SQL);
			while(true)
			{
				if(RS.IsEOF()) break;
				CString AntID;
				RS.GetFieldValue((short)0,AntID);
				DelRecPermanent(EANTUP, atol(AntID), IDYES,RecID);
				RS.MoveNext();
			}
			RS.Close();
			SQL.Format(_T("delete * from e_stn where ntc_id=%ld"),RecID);
			DB.ExecuteSQL(SQL);
			SQL.Format(_T("delete * from notice where ntc_id=%ld"),RecID);
			DB.ExecuteSQL(SQL);
			Res=true;
		}
		break;
	case ALLOTMENT:
		if(Ans!=IDYES)
			Ans=AfxMessageBox(_T("Are you sure about deleting this allotment and its contour(s)?"),MB_YESNO|MB_ICONWARNING);
		if(Ans==IDYES)
		{
			SQL.Format(_T("select contourkey from rrc_sub_area where allotkey=%ld"),RecID);
			RS.Open(CRecordset::snapshot, SQL);
			while(true)
			{
				if(RS.IsEOF()) break;
				CString ContourKey;
				RS.GetFieldValue((short)0,ContourKey);
				DelRecPermanent(CONTOUR, atol(ContourKey),IDYES,RecID);
				RS.MoveNext();
			}
			RS.Close();

			SQL.Format(_T("delete * from rrc_allotment where allotkey=%ld"),RecID);
			DB.ExecuteSQL(SQL);
			Res=true;
		}
		break;
	case CONTOUR:
		if(Ans!=IDYES)
			Ans=AfxMessageBox(_T("Are you sure about detatching this contour?"),MB_YESNO|MB_ICONWARNING);
		if(Ans==IDYES)
		{
			SQL.Format(_T("delete * from rrc_sub_area where allotkey=%ld and contourkey=%ld"),ParentID,RecID);
			DB.ExecuteSQL(SQL);
			SQL.Format(_T("update rrc_allotment set nb_sub_areas=nb_sub_areas-1 where allotkey=%ld"),ParentID);
			DB.ExecuteSQL(SQL);
			Res=true;
		}
		break;
	}
	DB.Close();
	return Res;
}

long CLeftView::AddSt(CString STname, double STlat_deg, double STlon_deg, long Sth_agl,
       double txfreq, double power_eirp, double Azimuth, double Elevation,
       double AntGain, double BWh, double BWv, CString Polarization, double InsertionLoss, 
       double RxSensitivity, CString STTP, CString Emission, double BandWidth, long HeightASL, 
	   CString AntPath)
{
	double Pwr2Ant = power_eirp*pow(10.0,-AntGain/10.0);

	////////////////// Country Code ////////////////////////////////////////
	double pi=4.0*atan(1.0);
	float RLON = (float)(STlon_deg*pi/180.0) ;
	float RLAT = (float)(STlat_deg*pi/180.0) ;

	CString Country("");
	GEOPLC(&RLON, &RLAT, (BYTE*)Country.GetBufferSetLength(3)) ;

	long  ITURegion= 0;
	GEORGN(&RLON, &RLAT,&ITURegion) ;


	CString LastStID, LastEqID, LastEqCatID, LastAntID, LastAntCatID, LastFreqID, SQL1, AntName;
	double FreqFrom, FreqTo;
	CDatabase DB1;
	CString  m_DB = ((CSMS4DCApp *)AfxGetApp())->m_CDBSTR;
	DB1.Open(_T(m_DB),false,false,_T("ODBC;"),false);

	CRecordset rs;
	rs.m_pDatabase=&DB1;
	STTP.MakeUpper();
	if(!STTP.Left(2).CompareNoCase(_T("FX")) || !STTP.Left(2).CompareNoCase(_T("FB")))
	{
// Fixed Station
		rs.Open(CRecordset::snapshot, _T("select max(StID)+1 from Station"));
		rs.GetFieldValue((short)0,LastStID);
		rs.Close();
		if(LastStID.IsEmpty())
			LastStID=_T("1");
		SQL1.Format(_T("SELECT %s, -1, '%s',%lf,%lf,%ld,'%s','%s',%ld "), LastStID, STname, STlat_deg, STlon_deg, HeightASL, STTP.Left(2),Country,ITURegion);
		SQL1=_T("INSERT INTO Station (StID, LicID, SiteName, GeoLat, GeoLon, HeightASL, ClassStation,Country,ITURegion) ")+SQL1;
		DB1.ExecuteSQL(SQL1);
	//EqCat
		rs.Open(CRecordset::snapshot, _T("select max(EqCatID)+1 from EqCat")); 
		rs.GetFieldValue((short)0,LastEqCatID);
		rs.Close();
		if(LastEqCatID.IsEmpty())
			LastEqCatID=_T("1");
		SQL1.Format(_T("SELECT %s,'I',%lf "), LastEqCatID, RxSensitivity);
		SQL1=_T("INSERT INTO EqCat (EqCatID, radpowertype, sensitivity) ")+SQL1; 
		DB1.ExecuteSQL(SQL1);
	//Equipment
		rs.Open(CRecordset::snapshot, _T("select max(EqID)+1 from Equipment"));
		rs.GetFieldValue((short)0,LastEqID);
		rs.Close();
		if(LastEqID.IsEmpty())
			LastEqID=_T("1");
		SQL1.Format(_T("SELECT %s, %s,%s, %lf,%lf"), LastEqID, LastEqCatID, LastStID, power_eirp,Pwr2Ant); 
		SQL1=_T("INSERT INTO Equipment (EqID, EqCatID, StID, radpwr,Pwr2Ant) ")+SQL1;
		DB1.ExecuteSQL(SQL1);
	}
	else if(!STTP.Left(2).CompareNoCase(_T("ML")))
	{
// Mobile Station
		rs.Open(CRecordset::snapshot, _T("select max(MobID)+1 from Mobiles"));
		rs.GetFieldValue((short)0,LastStID);
		rs.Close();
		if(LastStID.IsEmpty())
			LastStID=_T("1");
		SQL1.Format(_T("SELECT %s, -1, '%s',%lf,%lf,'%s','%s',%ld "), LastStID, STname, STlat_deg, STlon_deg, STTP.Left(2),Country,ITURegion);
		SQL1=_T("INSERT INTO Mobiles (MobID, LicID, MobName, GeoLat, GeoLon, ClassStation,Country,ITURegion) ")+SQL1;
		DB1.ExecuteSQL(SQL1);
	//EqCat
		rs.Open(CRecordset::snapshot, _T("select max(EqCatID)+1 from EqCat")); 
		rs.GetFieldValue((short)0,LastEqCatID);
		rs.Close();
		if(LastEqCatID.IsEmpty())
			LastEqCatID=_T("1");
		SQL1.Format(_T("SELECT %s,'I',%lf "), LastEqCatID, RxSensitivity);
		SQL1=_T("INSERT INTO EqCat (EqCatID, radpowertype, sensitivity) ")+SQL1; 
		DB1.ExecuteSQL(SQL1);
	//Equipment
		rs.Open(CRecordset::snapshot, _T("select max(EqID)+1 from Equipment"));
		rs.GetFieldValue((short)0,LastEqID);
		rs.Close();
		if(LastEqID.IsEmpty())
			LastEqID=_T("1");
		SQL1.Format(_T("SELECT %s, %s,%s, %lf,%lf"), LastEqID, LastEqCatID, LastStID, power_eirp,Pwr2Ant); 
		SQL1=_T("INSERT INTO Equipment (EqID, EqCatID, MobID, radpwr,Pwr2Ant) ")+SQL1;
		DB1.ExecuteSQL(SQL1);
	}
	else if(!STTP.Left(2).CompareNoCase(_T("BC")) || !STTP.Left (2).CompareNoCase(_T("BT")))
	{
// BC Station
		rs.Open(CRecordset::snapshot, _T("select max(StID)+1 from BCStation"));
		rs.GetFieldValue((short)0,LastStID);
		rs.Close();
		if(LastStID.IsEmpty())
			LastStID=_T("1");
		SQL1.Format(_T("SELECT %s, -1, '%s',%lf,%lf,%ld,'%s','%s',%ld "), LastStID, STname, STlat_deg, STlon_deg, HeightASL, 
			STTP.Left(2),Country,ITURegion);
		SQL1=_T("INSERT INTO BCStation (StID, LicID, SiteName, GeoLat, GeoLon, HeightASL, ClassStation,Country,ITURegion) ")+SQL1;
		DB1.ExecuteSQL(SQL1);
	//EqCat
		double erp_h=0.0, erp_v=0.0, erp;
		if(Polarization==_T("H"))
			erp=erp_h=10.0*log10(power_eirp);
		else if(Polarization==_T("V"))
			erp=erp_v=10.0*log10(power_eirp);
		else
		{
			erp_v=erp_h=10.0*log10(power_eirp);
			erp=10.0*log10(pow(10.0,erp_h/10.0)+pow(10.0,erp_v/10.0));
		}
		rs.Open(CRecordset::snapshot, _T("select max(EqCatID)+1 from EqCat")); 
		rs.GetFieldValue((short)0,LastEqCatID);
		rs.Close();
		if(LastEqCatID.IsEmpty())
			LastEqCatID=_T("1");
		SQL1.Format(_T("SELECT %s,'I',%lf, %lf, %lf, %lf "), LastEqCatID, RxSensitivity, erp, erp_h, erp_v);
		SQL1=_T("INSERT INTO EqCat (EqCatID, radpowertype, sensitivity, erp_dbw, erp_h_dbw, erp_v_dbw) ")+SQL1; 
		DB1.ExecuteSQL(SQL1);
	//Equipment
		rs.Open(CRecordset::snapshot, _T("select max(EqID)+1 from Equipment"));
		rs.GetFieldValue((short)0,LastEqID);
		rs.Close();
		if(LastEqID.IsEmpty())
			LastEqID=_T("1");
		SQL1.Format(_T("SELECT %s, %s,%s, %lf,%lf"), LastEqID, LastEqCatID, LastStID, power_eirp,Pwr2Ant); 
		SQL1=_T("INSERT INTO Equipment (EqID, EqCatID, BCID, radpwr,Pwr2Ant) ")+SQL1;
		DB1.ExecuteSQL(SQL1);
	}
	else return -1;
//AntCat    
	rs.Open(CRecordset::snapshot, _T("select max(AntCatID)+1 from AntCat"));
	rs.GetFieldValue ((short)0,LastAntCatID);
	rs.Close();
	if(LastAntCatID.IsEmpty())
		LastAntCatID=_T("1");
	AntName=AssignAntenna(&DB1,atol(LastAntCatID),AntPath,&FreqFrom,&FreqTo,Polarization,Azimuth);
	SQL1.Format(_T("SELECT %s, '%s', 'C','I','%s','%s',%lf,%lf,%lf,%lf,%lf,%lf,0 "), LastAntCatID, AntName, Polarization,
	(BWh==360?_T("N"):_T("D")), AntGain, BWh, BWv, InsertionLoss,FreqFrom,FreqTo); 
	SQL1=_T("INSERT INTO AntCat (AntCatID, AntName, ClassofAnt,GainType, Pol, AntDir, gain, beamwidthH, beamwidthV, insloss, FreqFrom, FreqTo,Lib) ")+SQL1;
	DB1.ExecuteSQL(SQL1);
//Antenna
	rs.Open(CRecordset::snapshot, _T("select max(AntID)+1 from Antenna")); 
	rs.GetFieldValue((short)0,LastAntID);
	rs.Close();
	if(LastAntID.IsEmpty())
		LastAntID=_T("1");
	SQL1.Format(_T("SELECT %s, %s,%s,%lf,%lf,%ld "), LastAntID, LastAntCatID, LastEqID, Azimuth, Elevation, Sth_agl);
	SQL1=_T("INSERT INTO Antenna (AntID, AntCatID, EqID,Azimuth,Elevation,AntHeightAGL) ")+SQL1;
	DB1.ExecuteSQL(SQL1);
//Frequency
	rs.Open(CRecordset::snapshot, _T("select max(FreqID)+1 from Frequency"));
	rs.GetFieldValue((short)0,LastFreqID);
	rs.Close();
	if(LastFreqID.IsEmpty())
		LastFreqID=_T("1");
	SQL1.Format(_T("SELECT %s, %s, %lf,'%s',%lf,'%s','CP', %lf"), LastFreqID, LastEqID, txfreq*1000000., Emission,	BandWidth,BWCode((double)BandWidth)+Emission, txfreq*1000000.); 
	SQL1=_T("INSERT INTO Frequency ( FreqID, EqID, Frequency, emissioncl, bandwidth, EmDes,NatServ,RespFreq ) ")+SQL1;
	DB1.ExecuteSQL(SQL1);
	DB1.Close();
	return atol(LastFreqID);
}

CString CLeftView::AssignAntenna(CDatabase *DB,long AntID, CString AntPath, double *FreqFrom, double *FreqTo, CString Pol, double Azimuth)
{
	CString AntName;
	FILE *fp=fopen(AntPath,"rt");
	if(fp!=NULL)
	{
		double AttnH[360],AttnV[360];
		char buf[150];
		int i,j;
		CString Sbuf;
		fgets(buf,100,fp);
		Sbuf=buf;
		Sbuf=Sbuf.Left(Sbuf.GetLength()-1);
		AntName=Sbuf.Mid(5);	AntName.TrimRight();
		fgets(buf,100,fp);
		fgets(buf,100,fp);
		fgets(buf,100,fp);
		fgets(buf,100,fp);
		Sbuf=buf;
		Sbuf=Sbuf.Left(Sbuf.GetLength()-2);
		*FreqFrom=atof(Sbuf.Mid(7));
		fgets(buf,100,fp);
		Sbuf=buf;
		Sbuf=Sbuf.Left(Sbuf.GetLength()-2);
		*FreqTo=atof(Sbuf.Mid(7));
		fgets(buf,100,fp);
//		Sbuf=buf;
//		double coef;
//		if(Sbuf.Mid(9,3)=="GHz") coef=1000000000.;
//		else if(Sbuf.Mid(9,3)=="MHz") coef=1000000.;
//		else if(Sbuf.Mid(9,3)=="KHz") coef=1000.;
//		else coef=1;
//		(*FreqFrom)*=coef;
//		(*FreqTo)*=coef;
		fgets(buf,100,fp);
		Sbuf=buf;
		fgets(buf,100,fp);
		j=0;
		double Patt[360]={0.0},Patt2[2][360]={0.0};
		for(i=0;i<360;i++)
		{
			fgets(buf,100,fp);
			Sbuf=buf;
			AttnH[i]=atof(Sbuf.Mid(3,15));
			AttnV[i]=atof(Sbuf.Mid(18,15));
			Patt[i]=i;
		}
		fclose(fp);
		Pol.TrimRight();
		CRecordset AntPatt;
		CString SQL;
		AntPatt.m_pDatabase=DB;
		SQL.Format(_T("select * from AntDiag where AntID=%ld"),AntID);
		AntPatt.Open(CRecordset::dynaset,SQL);
		if(AntPatt.GetRecordCount()>0)
		{
			SQL.Format(_T("Delete * from AntDiag where AntID=%ld"),AntID);
			DB->ExecuteSQL(SQL);
		}
		AntPatt.Close();
		if(Pol!=_T("V"))
		{
			if(Azimuth>=0)
			{
				i=359;
				while(Patt[i]>359-Azimuth && i>=0)
					i--;
				if(i==-1) i=359;
				for(int j=i;j>=0;j--)
					Patt[j]+=Azimuth;
				for(j=i+1;j<360;j++)
					Patt[j]-=360-Azimuth;
			}
			else
			{
				i=0;
				while(Patt[i]<-Azimuth && i<360)
					i++;
				if(i==360) i=0;
				for(int j=i;j<360;j++)
					Patt[j]+=Azimuth;
				for(j=0;j<i;j++)
					Patt[j]+=360+Azimuth;
			}
			for(j=0;j<360;j++)
			{
				Patt2[0][j]=(double)j;
				Patt2[1][(int)Patt[j]]=AttnH[j];
			}
			for(i=0;i<360;i++)
			{
				SQL.Format(_T("INSERT INTO AntDiag ( AntID, Azm, Polar, Attn ) SELECT %ld, %lf, '%s', %lf"),
					AntID, (double)i, "H", Patt2[1][i]);
				DB->ExecuteSQL(SQL);
			}
			for(i=0;i<360;i++)
			{
				SQL.Format(_T("INSERT INTO AntDiag ( AntID, Azm, Polar, Attn ) SELECT %ld, %lf, '%s', %lf"),
					AntID, (double)i, "V", AttnV[i]);
				DB->ExecuteSQL(SQL);
			}
		}
		if(Pol!=_T("H"))
		{
			if(Azimuth>=0)
			{
				i=359;
				while(Patt[i]>359-Azimuth && i>=0)
					i--;
				if(i==-1) i=359;
				for(int j=i;j>=0;j--)
					Patt[j]+=Azimuth;
				for(j=i+1;j<360;j++)
					Patt[j]-=360-Azimuth;
			}
			else
			{
				i=0;
				while(Patt[i]<-Azimuth && i<360)
					i++;
				if(i==360) i=0;
				for(int j=i;j<360;j++)
					Patt[j]+=Azimuth;
				for(j=0;j<i;j++)
					Patt[j]+=360+Azimuth;
			}
			for(j=0;j<360;j++)
			{
				Patt2[0][j]=(double)j;
				Patt2[1][(int)Patt[j]]=AttnV[j];
			}
			for(i=0;i<360;i++)
			{
				SQL.Format(_T("INSERT INTO AntDiag ( AntID, Azm, Polar, Attn ) SELECT %ld, %lf, '%s', %lf"),
					AntID, (double)i, "V", Patt2[1][i]);
				DB->ExecuteSQL(SQL);
			}
			for(i=0;i<360;i++)
			{
				SQL.Format(_T("INSERT INTO AntDiag ( AntID, Azm, Polar, Attn ) SELECT %ld, %lf, '%s', %lf"),
					AntID, (double)i, "H", AttnH[i]);
				DB->ExecuteSQL(SQL);
			}
		}
		return AntName;
	}
	return _T("");
}

void CLeftView::AddSt2(CString STname, double STlat_deg, double STlon_deg, long HeightASL, double Lon_nom, CString SatName, CString Ctry, double AzmFr, double AzmTo, double ElevMin, CString StType)
{
	CString LastNtcID, SQL1;
	CDatabase DB1;
	DB1.Open (m_CDBSTR,false,false,_T("ODBC;"),false);
	CRecordset rs;
	rs.m_pDatabase=&DB1;
	rs.Open(CRecordset::snapshot, _T("select max(ntc_id)+1 from e_stn"));
	rs.GetFieldValue((short)0,LastNtcID);
	rs.Close();
	if(LastNtcID.IsEmpty()) LastNtcID=_T("1");
	SQL1.Format(_T("SELECT %s, -1, '%s',%lf,%lf,%lf,%lf,%ld,%lf,%lf,'%s','%s'  "), LastNtcID, STname, STlon_deg, STlat_deg, ElevMin, Lon_nom, HeightASL, AzmFr, AzmTo, SatName, Ctry);
	SQL1=_T("INSERT INTO e_stn (ntc_id, LicID, stn_name, long_dec, lat_dec, elev_min,long_nom, ant_alt,azm_fr, azm_to, sat_name, ctry) ")+SQL1;
	DB1.ExecuteSQL(SQL1);
	SQL1.Format(_T("Insert into notice (ntc_id,ntc_type) Select %s,'%s' "), LastNtcID, StType);
	DB1.ExecuteSQL(SQL1);
	DB1.Close();
}

void CLeftView::OnLicensePrintSummary() 
{
	CDatabase DB;
	CRecordset RS,RS1,RS2,RS3,RS4;

	CString OutFile, NoticeDate;
	char buf[100];
	CString NoticeType,	SQL, LicID, StID, EqID, AntID, FreqID, SrvID;
	CDBVariant FVal;

	OutFile=GetCommandLine();
	int Place=OutFile.ReverseFind('\\')-1;
	OutFile.Delete(0);
	OutFile.Delete(Place,OutFile.GetLength()-Place);
	Place=OutFile.ReverseFind('\\')+1;
	OutFile.Delete(Place,OutFile.GetLength()-Place);
	OutFile+=_T("reports\\");
	CTime Today =CTime::GetCurrentTime();
	NoticeDate.Format(_T("%04d%02d%02d"),Today.GetYear(),Today.GetMonth(),Today.GetDay());
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	ltoa(GetTreeCtrl().GetItemData(Node),buf,10);
	LicID=buf;
	LicID.TrimRight(_T(" "));
	OutFile+=LicID;
	OutFile+=_T("Summary")+NoticeDate;
	OutFile+=_T(".txt");
	FILE *output=fopen(OutFile,_T("wt"));
	if(!output)
	{
		AfxMessageBox(_T("Cannot create output file!"));
		return;
	}
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR,false,false,_T("ODBC;"),false);
	RS.m_pDatabase=&DB;
	RS1.m_pDatabase=&DB;
	RS2.m_pDatabase=&DB;
	RS3.m_pDatabase=&DB;
	RS4.m_pDatabase=&DB;
	SQL.Format(_T("Select * from License where Archive=No and LicID=%s"), LicID);
	RS.Open(CRecordset::dynaset,SQL);
	fprintf(output,_T("License Information:\n\n"));
	for(int i=4;i<RS.GetODBCFieldCount();i++)
	{
		CString Value,Unit,FldName,Format,Srv,Mask;
		RS.GetFieldValue(i,Value);
		Value.TrimRight(_T(" "));
		CODBCFieldInfo FldInfo;
		RS.GetODBCFieldInfo(i,FldInfo);
		if(!FldInfo.m_strName.CompareNoCase(_T("SrvID")))
			SrvID=Value;
		FldName=GetFieldName(&DB, _T("License"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
		fprintf(output,_T("%s : %s \n"),FldName,Value);
	}
	RS.Close();
//  Stations
	int begin,end;
	CString Stype=_T("Fixed");
LM:
	begin=4;
	end=3;
	if(!SrvID.CompareNoCase(_T("F")))
	{
		SQL.Format(_T("Select * from Station where LicID=%s"), LicID);
	}
	else if(!SrvID.CompareNoCase(_T("B")))
	{
		SQL.Format(_T("Select * from BCStation where LicID=%s"), LicID);
		Stype=_T("Broadcasting");
	}
	else if(!SrvID.CompareNoCase(_T("MT")))
	{
		SQL.Format(_T("Select * from Mobiles where LicID=%s"), LicID);
		Stype=_T("Mobile");
		begin=2;
		end=1;
	}
	else
	{
		SQL.Format(_T("select * from e_stn where LicID=%s"),LicID);
		Stype=_T("Earth");
		begin=1;
		end=0;
	}
	RS.Open(CRecordset::dynaset,SQL);
	int StNo=1;
	while(true)
	{
		if(RS.IsEOF()) break;
		RS.GetFieldValue((short)0,StID);
		fprintf(output,_T("\n\t%s Station #%d Information:\n\n"),Stype,StNo);
		for(int i=begin;i<RS.GetODBCFieldCount()-end;i++)
		{
			CString Value,Unit,FldName,Format,Srv,Mask;
			RS.GetFieldValue(i,Value);
			Value.TrimRight(_T(" "));
			CODBCFieldInfo FldInfo;
			RS.GetODBCFieldInfo(i,FldInfo);
			if(!SrvID.CompareNoCase(_T("F")))
				FldName=GetFieldName(&DB, _T("Station"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
			else if(!SrvID.CompareNoCase(_T("B")))
				FldName=GetFieldName(&DB, _T("BCStation"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
			else if(!SrvID.CompareNoCase(_T("MT")))
				FldName=GetFieldName(&DB, _T("Mobiles"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
			else
				FldName=GetFieldName(&DB, _T("E-stn"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
			if(Srv!=_T("-")) fprintf(output,_T("\t%s : %s \n"),FldName,Value);
		}
		if(!SrvID.CompareNoCase(_T("F")) || !SrvID.CompareNoCase(_T("B")) || !SrvID.CompareNoCase(_T("MT")))
		{
	//  Equipments
			if(!SrvID.CompareNoCase(_T("F")))
				SQL.Format(_T("Select * from Equipment,EqCat where Equipment.eqcatid=eqcat.eqcatid and StID=%s"), StID);
			if(!SrvID.CompareNoCase(_T("B")))
				SQL.Format(_T("Select * from Equipment,EqCat where Equipment.eqcatid=eqcat.eqcatid and BCID=%s"), StID);
			if(!SrvID.CompareNoCase(_T("MT")))
				SQL.Format(_T("Select * from Equipment,EqCat where Equipment.eqcatid=eqcat.eqcatid and MobID=%s"), StID);
			RS1.Open(CRecordset::dynaset,SQL);
			int EqNo=1;
			while(true)
			{
				if(RS1.IsEOF()) break;
				RS1.GetFieldValue((short)0,EqID);
				fprintf(output,_T("\n\t\tEquipment #%d Information:\n\n"),EqNo);
				for(int i=7;i<RS1.GetODBCFieldCount()-2;i++)
				{
					CString Value,Unit,FldName,Format,Srv,Mask;
					RS1.GetFieldValue(i,Value);
					Value.TrimRight(_T(" "));
					CODBCFieldInfo FldInfo;
					RS1.GetODBCFieldInfo(i,FldInfo);
					FldName=GetFieldName(&DB, _T("EqCat"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
					if(Srv!=_T("-")) fprintf(output,_T("\t\t%s : %s %s\n"),FldName,Value,Unit);
				}
	//  Antenna
				SQL.Format(_T("Select * from Antenna,AntCat where Antenna.Antcatid=Antcat.Antcatid and eqID=%s"), EqID);
				RS2.Open(CRecordset::dynaset,SQL);
				int AntNo=1;
				while(true)
				{
					if(RS2.IsEOF()) break;
					fprintf(output,_T("\n\t\t\tAntenna #%d Information:\n\n"),AntNo);
					for(int i=3;i<RS2.GetODBCFieldCount()-2;i++)
					{
						if(i==7) continue;
						CString Value,Unit,FldName,Format,Srv,Mask;
						RS2.GetFieldValue(i,Value);
						Value.TrimRight(_T(" "));
						CODBCFieldInfo FldInfo;
						RS2.GetODBCFieldInfo(i,FldInfo);
						if(i>7)
							FldName=GetFieldName(&DB, _T("AntCat"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
						else
							FldName=GetFieldName(&DB, _T("Antenna"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
						if(Srv!=_T("-")) fprintf(output,_T("\t\t\t%s : %s %s\n"),FldName,Value,Unit);
					}
					RS2.MoveNext();
					AntNo++;
				}
				RS2.Close();
	//  Frequency
				SQL.Format(_T("Select * from Frequency where EqID=%s"), EqID);
				RS2.Open(CRecordset::dynaset,SQL);
				int FreqNo=1;
				while(true)
				{
					if(RS2.IsEOF()) break;
					RS2.GetFieldValue((short)0,FreqID);
					fprintf(output,_T("\n\t\t\tFrequency #%d Information:\n\n"),FreqNo);
					for(int i=2;i<RS2.GetODBCFieldCount()-3;i++)
					{
						CString Value,Unit,FldName,Format,Srv,Mask;
						RS2.GetFieldValue(i,Value);
						Value.TrimRight(_T(" "));
						CODBCFieldInfo FldInfo;
						RS2.GetODBCFieldInfo(i,FldInfo);
						FldName=GetFieldName(&DB, _T("Frequency"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
						if(Srv!=_T("-")) fprintf(output,_T("\t\t\t%s : %s %s\n"),FldName,Value,Unit);
					}

					SQL.Format(_T("Select * from link where TXID=%s"), FreqID);
					RS3.Open(CRecordset::dynaset,SQL);
					CString GeoType, RecID;
					if(!RS3.IsEOF())
					{
						RS3.GetFieldValue((short)0,RecID);
						RS3.GetFieldValue(3,GeoType);
						GeoType.TrimRight(_T(" "));
						if(GeoType==_T("POINT"))
						{
							fprintf(output,_T("\n\t\t\t\tReceiver information\n"));
							SQL.Format(_T(" from link,Frequency,eqcat, Equipment, Station where receiverID=%s"), RecID);
							SQL="Select sitename as Station_name, GeoType, geolat as latitude, geolon as longitude, station.country as Country, eqname as Equipment_name,frequency"+SQL;
							SQL=SQL+ " and link.rxid=frequency.freqid and frequency.eqid=equipment.eqid and equipment.stid=station.stid and eqcat.eqcatid=equipment.eqcatid";
							RS4.Open(CRecordset::dynaset,SQL);
							for(int i=0;i<RS4.GetODBCFieldCount() && !RS4.IsEOF();i++)
							{
								CString FldName,Value,Unit;
								RS4.GetFieldValue(i,Value);
								CODBCFieldInfo FldInfo;
								RS4.GetODBCFieldInfo(i,FldInfo);
		//						FldName=CTreeviewView::GetFieldName(&DB, _T("Link"), FldInfo.m_strName,_T("En"),&Unit);
								fprintf(output,_T("\t\t\t\t%s : %s %s\n"),FldInfo.m_strName,Value,Unit);
							}
							RS4.Close();
						}
						if(GeoType==_T("MULTIPOINT"))
						{
							fprintf(output,_T("\n\t\t\t\tReceiving area information\n"));
							SQL.Format(_T("Select * from link where receiverID=%s"), RecID);
							RS4.Open(CRecordset::dynaset,SQL);
							for(int i=1,j=13;i<7;i++)
							{
								CString Value;
								RS4.GetFieldValue(j++,Value);
								fprintf(output,_T("\t\t\t\tPoint %d latitude : %s\n"),i,Value);
								RS4.GetFieldValue(j++,Value);
								fprintf(output,_T("\t\t\t\tPoint %d longitude : %s\n"),i,Value);
							}
							RS4.Close();	
						}
						if(GeoType==_T("CIRCLE"))
						{
							fprintf(output,_T("\n\t\t\t\tReceiving area information\n"));
							SQL.Format(_T("Select * from link where receiverID=%s"), RecID);
							RS4.Open(CRecordset::dynaset,SQL);
							CString Value;
							RS4.GetFieldValue(9,Value);
							fprintf(output,_T("\t\t\t\tCenter latitude : %s\n"),Value);
							RS4.GetFieldValue(10,Value);
							fprintf(output,_T("\t\t\t\tCenter longitude : %s\n"),Value);
							RS4.GetFieldValue(11,Value);
							fprintf(output,_T("\t\t\t\tRadius : %s\n"),Value);
							RS4.GetFieldValue(12,Value);
							fprintf(output,_T("\t\t\t\tCountry : %s\n"),Value);
							RS4.Close();
						}
					}
					RS3.Close();
					RS2.MoveNext();
					FreqNo++;
				}
				RS2.Close();
				RS1.MoveNext();
				EqNo++;
			}
			RS1.Close();
			RS.MoveNext();
			StNo++;
		}
		else
		{
	// Beams
			SQL.Format(_T("select * from e_ant where ntc_id=%s"), StID);
			RS1.Open(CRecordset::dynaset,SQL);
			int BeamNo=1;
			CString GrpID,AntID;
			while(true)
			{
				if(RS1.IsEOF()) break;
				fprintf(output,_T("\n\t\tBeam #%d Information:\n\n"),BeamNo);
				for(int i=1;i<RS1.GetODBCFieldCount();i++)
				{
					CString Value,Unit,FldName,Format,Srv,Mask;
					RS1.GetFieldValue(i,Value);
					Value.TrimRight(_T(" "));
					CODBCFieldInfo FldInfo;
					RS1.GetODBCFieldInfo(i,FldInfo);
					if(FldInfo.m_strName==_T("AntID"))
						AntID=Value;
					FldName=GetFieldName(&DB, _T("e_ant"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
					if(Srv!=_T("-")) fprintf(output,_T("\t\t%s : %s %s\n"),FldName,Value,Unit);
				}
				SQL.Format(_T("select ant_type.* from e_ant,ant_type where e_ant.pattern_id=ant_type.pattern_id and ntc_id=%s"), StID);
				RS3.Open(CRecordset::dynaset,SQL);
				if(!RS3.IsEOF())
					for(int i=1;i<RS3.GetODBCFieldCount();i++)
					{
						CString Value,Unit,FldName,Format,Srv,Mask;
						RS3.GetFieldValue(i,Value);
						Value.TrimRight(_T(" "));
						CODBCFieldInfo FldInfo;
						RS3.GetODBCFieldInfo(i,FldInfo);
						FldName=GetFieldName(&DB, _T("ant_type"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
						if(Srv!=_T("-")) fprintf(output,_T("\t\t%s : %s %s\n"),FldName,Value,Unit);
					}
				RS3.Close();
		// Group
				SQL.Format(_T("Select * from grp where grp.AntID=%s"),AntID);
				RS2.Open(CRecordset::dynaset,SQL);
				int GrpNo=1;
				while(true)
				{
					if(RS2.IsEOF()) break;
					fprintf(output,_T("\n\t\t\tGroup #%d Information:\n\n"),GrpNo);
					for(int i=4;i<RS2.GetODBCFieldCount()-1;i++)
					{
						CString Value,Unit,FldName,Format,Srv,Mask;
						RS2.GetFieldValue(i,Value);
						Value.TrimRight(_T(" "));
						CODBCFieldInfo FldInfo;
						RS2.GetODBCFieldInfo(i,FldInfo);
						FldName=GetFieldName(&DB, _T("grp"), FldInfo.m_strName,_T("En"),&Unit,&Format,&Srv,&Mask);
						if(Srv!=_T("-")) fprintf(output,_T("\t\t\t%s : %s %s\n"),FldName,Value,Unit);
					}
					RS2.MoveNext();
					GrpNo++;
				}
				RS2.Close();
				RS1.MoveNext();
				BeamNo++;
			}
			RS1.Close();
			RS.MoveNext();
			StNo++;
		}
	}
	RS.Close();
	if(!SrvID.CompareNoCase(_T("MT")))
	{
		Stype=_T("Base");
		SrvID=_T("F");
		goto LM;
	}
	fclose(output);
	ShellExecute(this->m_hWnd,_T("open"),OutFile,NULL,NULL,SW_SHOWNORMAL);
	DB.Close();
}

void CLeftView::OnAntennaPattern() 
{
	CString Temp=/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR;
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	AFX_MANAGE_STATE(AfxGetStaticModuleState()) ;
	CAntPattern	 AntDlg;
	AntDlg.m_CDBSTR=Temp;
	AntDlg.m_AntID=GetTreeCtrl().GetItemData(Node);
	AntDlg.DoModal();
}

void CLeftView::OnAddFx() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	GetTreeCtrl().EnableWindow(false);
	pView->m_OldRecordType=LICENSE;
	pView->m_OldTable="License";
	pView->m_OldRecID=pView->m_RecID;
	pView->m_RecID=-1;
	pView->m_Table="Station";
	pView->m_Action=1;
	pView->m_ReadOnly=false;
	pView->m_Refresh=true;
	pView->m_RecordType=STATION;
	pView->RedrawWindow();
}

void CLeftView::OnAddLm() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	GetTreeCtrl().EnableWindow(false);
	pView->m_OldRecordType=LICENSE;
	pView->m_OldTable="License";
	pView->m_OldRecID=pView->m_RecID;
	pView->m_RecID=-1;
	pView->m_Table="Station";
	pView->m_Action=1;
	pView->m_ReadOnly=false;
	pView->m_Refresh=true;
	pView->m_RecordType=STATION;
	pView->RedrawWindow();
}

void CLeftView::OnAddBc() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	GetTreeCtrl().EnableWindow(false);
	pView->m_OldRecordType=LICENSE;
	pView->m_OldTable="License";
	pView->m_OldRecID=pView->m_RecID;
	pView->m_RecID=-1;
	pView->m_Table="BCStation";
	pView->m_Action=1;
	pView->m_ReadOnly=false;
	pView->m_Refresh=true;
	pView->m_RecordType=BC;
	pView->RedrawWindow();
}

void CLeftView::OnAddMl() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	GetTreeCtrl().EnableWindow(false);
	pView->m_OldRecordType=LICENSE;
	pView->m_OldTable=_T("License");
	pView->m_OldRecID=pView->m_RecID;
	pView->m_RecID=-1;
	pView->m_Table=_T("Mobiles");
	pView->m_Action=1;
	pView->m_ReadOnly=false;
	pView->m_Refresh=true;
	pView->m_RecordType=MOBILE;
	pView->RedrawWindow();
}

void CLeftView::OnImportTech() 
{
	CString Temp=/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR;
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	CDatabase DB;
	CRecordset RS;
	CString SQL,Srv;
	bool result;
	DB.Open(Temp,false,false,_T("ODBC;"),false);
	RS.m_pDatabase=&DB;
	SQL.Format(_T("select SrvID from license where licid=%ld"),GetTreeCtrl().GetItemData(Node));
	RS.Open(CRecordset::snapshot,SQL);
	RS.GetFieldValue((short)0,Srv);
	Srv.TrimRight();
	RS.Close();
	{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()) ;
	CMoveStation MoveDlg;
	MoveDlg.m_Service=Srv;
	MoveDlg.m_Lang=m_Lang;
	MoveDlg.m_CDBSTR=Temp;
	MoveDlg.DoModal();
	long ID=MoveDlg.m_StID;
	if(ID>-1)
	{
		if(Srv==_T("B"))
		{
			SQL.Format(_T("Update BCStation Set LicID=%ld where StID=%ld"), GetTreeCtrl().GetItemData(Node), ID);
			DB.ExecuteSQL(SQL);
			AddTrail(_T("Move broadcasting station from technical"),ID,_T("BCStation"));
		}
		else if(Srv==_T("F"))
		{
			SQL.Format(_T("Update Station Set LicID=%ld where StID=%ld"), GetTreeCtrl().GetItemData(Node), ID);
			DB.ExecuteSQL(SQL);
			AddTrail(_T("Move fixed/base station from technical"),ID,_T("Station"));
		}
		else if(Srv==_T("MT"))
		{
			SQL.Format(_T("Update Mobiles Set LicID=%ld where MobID=%ld"), GetTreeCtrl().GetItemData(Node), ID);
			DB.ExecuteSQL(SQL);
			AddTrail(_T("Move mobile station from technical"),ID,_T("Mobiles"));
		}
		else
		{
			SQL.Format(_T("Update e_stn Set LicID=%ld where ntc_id=%ld"), GetTreeCtrl().GetItemData(Node), ID);
			DB.ExecuteSQL(SQL);
			AddTrail(_T("Move earth station from technical"),ID,_T("e_stn"));
		}
		GetTreeCtrl().DeleteAllItems();
		DB.Close();
		BuildTree(2);
		result=true;
	}
	else
	{
		DB.Close();
		result=false;
	}
	}
	if(result) CleanScreen();
}

void CLeftView::OnFrequencyFilterTX() 
{
	CString Temp=/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR;
	AFX_MANAGE_STATE(AfxGetStaticModuleState()) ;
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	CTxRxFilterDLG	Dlg;
	Dlg.m_CDBSTR=Temp;
	Dlg.m_ID=GetTreeCtrl().GetItemData(Node);
	Dlg.m_TxRx=1;
	Dlg.DoModal();
}

void CLeftView::OnFrequencyFilterRX() 
{
	CString Temp=/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR;
	AFX_MANAGE_STATE(AfxGetStaticModuleState()) ;
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	CTxRxFilterDLG	Dlg;
	Dlg.m_CDBSTR=Temp;
	Dlg.m_ID=GetTreeCtrl().GetItemData(Node);
	Dlg.m_TxRx=2;
	Dlg.DoModal();
}

void CLeftView::OnAddInvoice() 
{
	CDatabase DB;
	CRecordset RS;
	CString ID;
	CTime Today =CTime::GetCurrentTime();
	CTimeSpan Due(15,0,0,0);
	CTime DueDate=Today+Due;

	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();

	CString m_InvoiceVal, m_InvoiceNo, Val,SQL;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR,false,false,_T("ODBC;"),false);
	RS.m_pDatabase=&DB;
	SQL.Format(_T("Select Count(InvoiceID) from Invoice where LicID=%ld"),GetTreeCtrl().GetItemData(Node));
	RS.Open(CRecordset::snapshot,SQL);
	RS.GetFieldValue((short)0,Val);
	RS.Close();
	if(atol(Val)==0)
	{
		RS.Open(CRecordset::snapshot,_T("Select max(InvoiceID) from Invoice"));
		RS.GetFieldValue((short)0,ID);
		RS.Close();
		if(ID.IsEmpty()) ID=_T("1");
		SQL.Format(_T("Select InitFee from License where LicID=%ld"),GetTreeCtrl().GetItemData(Node));
		RS.Open(CRecordset::snapshot,SQL);
		RS.GetFieldValue((short)0,m_InvoiceVal);
		RS.Close();	
		m_InvoiceNo.Format(_T("%05d%05d"),GetTreeCtrl().GetItemData(Node),atol(ID)+1);
		SQL.Format(_T("select %ld, %ld, '%s', '%s', '%s', '%s', %s, 0, 0 "), atol(ID)+1, GetTreeCtrl().GetItemData(Node), m_InvoiceNo, 
			Today.Format(_T("%m/%d/%Y")), DueDate.Format(_T("%m/%d/%Y")), _T("First"), m_InvoiceVal);
		SQL=_T("Insert into invoice (InvoiceID, LicID, InvoiceNo, InvDate, DueDate, Description, Debit, Credit, Replaced) ") +SQL;
		DB.ExecuteSQL(SQL);
		AddTrail("Add first invoice",atol(ID)+1,"Invoice");
		DB.Close();
		pView->LoadPayment(GetTreeCtrl().GetItemData(Node));
//		pView->m_Refresh=true;
//		pView->RedrawWindow();
	}
	else
	{
		AfxMessageBox(_T("The first invoice is already issued!"));
		DB.Close();
	}
}

void CLeftView::OnUpdateAddowner(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);	
}

void CLeftView::OnUpdateDeletestation(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnUpdateAddequipment(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnUpdateDeleteReceiver(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnUpdateDeleteowner(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);	
}

void CLeftView::OnUpdateEditowner(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);	
}

void CLeftView::OnUpdateAddlicense(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnUpdateEditstation(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnUpdateEditantenna(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnUpdateDeleteantenna(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnUpdateEditlicense(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnUpdateDeletelicense(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnUpdateCancellic(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnUpdateAddFx(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnUpdateAddBc(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnUpdateAddLm(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);	
}

void CLeftView::OnUpdateAddMl(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnUpdateImportTech(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnUpdateEditfrequency(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnUpdateDeletefrequency(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnUpdateFrequencyFiltertx(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnUpdateFrequencyFilterrx(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnUpdateAddfrequency(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnUpdateAddantenna(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnUpdateDeleteequipment(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnUpdateEditequipment(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnUpdateAddinvoice(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnUpdateAddpayment(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::CopyToArchive(long LicID)
{
	long FreqIDs[1000][2],AntIDs[1000][2],FreqInd=0,AntInd=0;
	CDatabase DB;
	CRecordset RS,RS2,RS3,RS4;
	CString SQL1,SQL2, SRV,STTP,OldLicID,NewLicID,OldStID,NewStID,OldEqID,NewEqID,OldAntID,NewAntID,OldFreqID,NewFreqID,NewLinkID,OldLinkID;
	RS.m_pDatabase=&DB;
	RS2.m_pDatabase=&DB;
	RS3.m_pDatabase=&DB;
	RS4.m_pDatabase=&DB;
	DB.Open(((CSMS4DCApp *)AfxGetApp())->m_CDBSTR,false,false,_T("ODBC;"),false);
	RS.Open(CRecordset::snapshot,_T("select max(LicID)+1 from license"));
	RS.GetFieldValue((short)0,NewLicID);
	RS.Close();
	SQL2=_T("INSERT INTO License ( AdmID, Archive, Grantable, LicNo, OpDate, ExpDate, Status, SrvID, PrdCode, InvPeriod, InitFee, LicID ) ");
	SQL1.Format(_T("SELECT AdmID, Archive, Grantable, LicNo, OpDate, ExpDate, Status, SrvID, PrdCode, InvPeriod, InitFee, %s AS Expr1 "),NewLicID);
	SQL2+=SQL1;
	SQL1.Format(_T("FROM (SELECT AdmID, Archive, Grantable, LicNo, OpDate, ExpDate, Status, SrvID, PrdCode, InvPeriod, InitFee FROM License where licid =%ld) AS qry"),LicID);
	SQL2+=SQL1;
	DB.ExecuteSQL(SQL2);
	SQL1.Format(_T("UPDATE License SET Archive = Yes WHERE LicID=%ld"),LicID);
	DB.ExecuteSQL(SQL1);
	SQL1.Format(_T("UPDATE License SET Status = 'Data entry' WHERE LicID=%s"),NewLicID);
	DB.ExecuteSQL(SQL1);
	SQL1.Format(_T("select SrvID from license where LicID=%ld"),LicID);
	RS.Open(CRecordset::snapshot,SQL1);
	RS.GetFieldValue((short)0,SRV);
	RS.Close();
	if(SRV==_T("F") || SRV==_T("MT"))
	{
		SQL1.Format(_T("select stID from station where LicID=%ld"),LicID);
		RS2.Open(CRecordset::snapshot,SQL1);
		while(true)
		{
			if(RS2.IsEOF()) break;
			RS2.GetFieldValue((short)0,OldStID);
			RS.Open(CRecordset::snapshot,_T("select max(StID)+1 from Station"));
			RS.GetFieldValue((short)0,NewStID);
			RS.Close();
			SQL2=_T("INSERT INTO Station ( LicID, TerraKey, Assgn_ID, AdmRefID, SiteID, SiteName, CallSign, ClassStation, StType, ITURegion, GeoLat, GeoLon, Country, Radius, HeightASL, Provision, AreaOfTrans, NetID, trgLat, trgLon, StID ) ");
			SQL1.Format(_T("SELECT %s as Expr2, TerraKey, Assgn_ID, AdmRefID, SiteID, SiteName, CallSign, ClassStation, StType, ITURegion, GeoLat, GeoLon, Country, Radius, HeightASL, Provision, AreaOfTrans, NetID, trgLat, trgLon, %s AS Expr1"),NewLicID,NewStID);
			SQL2+=SQL1;
			SQL2+=_T(" FROM (SELECT TerraKey, Assgn_ID, AdmRefID, SiteID, SiteName, CallSign, ClassStation, StType, ITURegion, GeoLat, GeoLon, Country, Radius, HeightASL, Provision, AreaOfTrans, NetID, trgLat, trgLon ");
			SQL1.Format(_T(" FROM Station where stid=%s) AS qry"),OldStID);
			SQL2+=SQL1;
			DB.ExecuteSQL(SQL2);
			SQL1.Format(_T("select eqID from equipment where stID=%s"),OldStID);
			RS3.Open(CRecordset::snapshot,SQL1);
			while(true)
			{
				if(RS3.IsEOF()) break;
				RS3.GetFieldValue((short)0,OldEqID);
				RS.Open(CRecordset::snapshot,_T("select max(EqID)+1 from Equipment"));
				RS.GetFieldValue((short)0,NewEqID);
				RS.Close();
				SQL2=_T("INSERT INTO Equipment ( EqCatID, StID, MobID, BCID, Pwr2Ant, RadPwr, EqID ) ");
				SQL1.Format(_T("SELECT EqCatID, %s as Expr2, MobID, BCID, Pwr2Ant, RadPwr, %s AS Expr1"),NewStID,NewEqID);
				SQL2+=SQL1;
				SQL2+=_T(" FROM (SELECT EqCatID, MobID, BCID, Pwr2Ant, RadPwr ");
				SQL1.Format(_T(" FROM Equipment where Eqid=%s) AS qry"),OldEqID);
				SQL2+=SQL1;
				DB.ExecuteSQL(SQL2);

				SQL1.Format(_T("select AntID from antenna where eqID=%s"),OldEqID);
				RS4.Open(CRecordset::snapshot,SQL1);
				while(true)
				{
					if(RS4.IsEOF()) break;
					RS4.GetFieldValue((short)0,OldAntID);
					RS.Open(CRecordset::snapshot,_T("select max(AntID)+1 from Antenna"));
					RS.GetFieldValue((short)0,NewAntID);
					RS.Close();
					AntIDs[AntInd][0]=atol(OldAntID);
					AntIDs[AntInd][1]=atol(NewAntID);
					AntInd++;
					SQL2=_T("INSERT INTO Antenna ( AntCatID, EqID, Azimuth, AzimTo, Elevation, AntHeightAGL, AntID ) ");
					SQL1.Format(_T("SELECT AntCatID, %s as Expr2, Azimuth, AzimTo, Elevation, AntHeightAGL, %s AS Expr1"),NewEqID,NewAntID);
					SQL2+=SQL1;
					SQL2+=_T(" FROM (SELECT AntCatID, Azimuth, AzimTo, Elevation, AntHeightAGL ");
					SQL1.Format(_T(" FROM Antenna where Antid=%s) AS qry"),OldAntID);
					SQL2+=SQL1;
					DB.ExecuteSQL(SQL2);
					RS4.MoveNext();
				}
				RS4.Close();

				SQL1.Format(_T("select FreqID from Frequency where eqID=%s"),OldEqID);
				RS4.Open(CRecordset::snapshot,SQL1);
				while(true)
				{
					if(RS4.IsEOF()) break;
					RS4.GetFieldValue((short)0,OldFreqID);
					RS.Open(CRecordset::snapshot,_T("select max(FreqID)+1 from Frequency"));
					RS.GetFieldValue((short)0,NewFreqID);
					RS.Close();
					FreqIDs[FreqInd][0]=atol(OldFreqID);
					FreqIDs[FreqInd][1]=atol(NewFreqID);
					FreqInd++;
					SQL2=_T("INSERT INTO Frequency ( EqID, Frequency, RespFreq, RefFreq, FreqDev, FreqRange, FreqVCarr, FreqSCarr, EmissionCl, BandWidth, ChannelSep, TVChan, ChannelNo, Traffic, PeakHour, Season, NatServ, HourFrom, HourTo, FreqFee, trgFrequency, EmDes, FreqID ) ");
					SQL1.Format(_T("SELECT %s as Expr2, Frequency, RespFreq, RefFreq, FreqDev, FreqRange, FreqVCarr, FreqSCarr, EmissionCl, BandWidth, ChannelSep, TVChan, ChannelNo, Traffic, PeakHour, Season, NatServ, HourFrom, HourTo, FreqFee, trgFrequency, EmDes, %s AS Expr1 "),NewEqID,NewFreqID);
					SQL2+=SQL1;
					SQL2+=_T(" FROM (SELECT Frequency, RespFreq, RefFreq, FreqDev, FreqRange, FreqVCarr, FreqSCarr, EmissionCl, BandWidth, ChannelSep, TVChan, ChannelNo, Traffic, PeakHour, Season, NatServ, HourFrom, HourTo, FreqFee, trgFrequency, EmDes ");
					SQL1.Format(_T(" FROM Frequency where Freqid=%s) AS qry"),OldFreqID);
					SQL2+=SQL1;
					DB.ExecuteSQL(SQL2);
					RS4.MoveNext();
				}
				RS4.Close();

				RS3.MoveNext();
			}
			RS3.Close();
			RS2.MoveNext();
		}
		RS2.Close();

		for(int i=0;i<FreqInd;i++)
		{
			long NewTXID,NewRXID,NewRXAntID,NewTXAntID;
			int j;
			CString Value;
			SQL1.Format(_T("select ReceiverID,RXID,TXAntID,RXAntID from Link where TXID=%ld"),FreqIDs[i][0]);
			RS4.Open(CRecordset::snapshot,SQL1);
			while(true)
			{
				if(RS4.IsEOF()) break;
				RS4.GetFieldValue((short)0,OldLinkID);
				for(j=0;j<FreqInd;j++)
					if(FreqIDs[j][0]==FreqIDs[i][0])
						break;
				NewTXID=FreqIDs[j][1];
				RS4.GetFieldValue(1,Value);
				for(j=0;j<FreqInd;j++)
					if(FreqIDs[j][0]==atol(Value))
						break;
				NewRXID=FreqIDs[j][1];
				RS4.GetFieldValue(2,Value);
				for(j=0;j<AntInd;j++)
					if(AntIDs[j][0]==atol(Value))
						break;
				NewTXAntID=AntIDs[j][1];
				RS4.GetFieldValue(3,Value);
				for(j=0;j<AntInd;j++)
					if(AntIDs[j][0]==atol(Value))
						break;
				NewRXAntID=AntIDs[j][1];
				RS.Open(CRecordset::snapshot,_T("select max(ReceiverID)+1 from Link"));
				RS.GetFieldValue((short)0,NewLinkID);
				RS.Close();
				SQL2=_T("INSERT INTO Link ( ReceiverID, HopID, LinkID, GeoType, TXID, RXID, TXAntID, RXAntID, CableLoss, RecLat, RecLon, Radius, Country, lat1, lon1, lat2, lon2, lat3, lon3, lat4, lon4, lat5, lon5, lat6, lon6, NoiseTemp ) ");
				SQL1.Format(_T("SELECT %s as e1, HopID, LinkID, GeoType, %ld as e2, %ld as e3, %ld as e4, %ld as e5, CableLoss, RecLat, RecLon, Radius, Country, lat1, lon1, lat2, lon2, lat3, lon3, lat4, lon4, lat5, lon5, lat6, lon6, NoiseTemp "),NewLinkID,NewTXID,NewRXID,NewTXAntID,NewRXAntID);
				SQL2+=SQL1;
				SQL2+=_T(" FROM (SELECT ReceiverID, HopID, LinkID, GeoType, TXID, RXID, TXAntID, RXAntID, CableLoss, RecLat, RecLon, Radius, Country, lat1, lon1, lat2, lon2, lat3, lon3, lat4, lon4, lat5, lon5, lat6, lon6, NoiseTemp ");
				SQL1.Format(_T(" FROM Link where ReceiverID=%s) AS qry"),OldLinkID);
				SQL2+=SQL1;
				DB.ExecuteSQL(SQL2);
				RS4.MoveNext();
			}
			RS4.Close();
		}
		AntInd=FreqInd=0;
	}
	else if(SRV==_T("B"))
	{
		SQL1.Format(_T("select stID from bcstation where LicID=%ld"),LicID);
		RS2.Open(CRecordset::snapshot,SQL1);
		while(true)
		{
			if(RS2.IsEOF()) break;
			RS2.GetFieldValue((short)0,OldStID);
			RS.Open(CRecordset::snapshot,_T("select max(StID)+1 from bcStation"));
			RS.GetFieldValue((short)0,NewStID);
			RS.Close();
			SQL2=_T("INSERT INTO bcStation ( LicID, TerraKey, Assgn_ID, AdmRefID, SiteID, SiteName, CallSign, ClassStation, StType, ITURegion, GeoLat, GeoLon, Country, Radius, HeightASL, Provision, Plan, trgLat, trgLon, StID ) ");
			SQL1.Format(_T("SELECT %s as Expr2, TerraKey, Assgn_ID, AdmRefID, SiteID, SiteName, CallSign, ClassStation, StType, ITURegion, GeoLat, GeoLon, Country, Radius, HeightASL, Provision, Plan, trgLat, trgLon, %s AS Expr1"),NewLicID,NewStID);
			SQL2+=SQL1;
			SQL2+=_T(" FROM (SELECT TerraKey, Assgn_ID, AdmRefID, SiteID, SiteName, CallSign, ClassStation, StType, ITURegion, GeoLat, GeoLon, Country, Radius, HeightASL, Provision, Plan, trgLat, trgLon ");
			SQL1.Format(_T(" FROM bcStation where stid=%s) AS qry"),OldStID);
			SQL2+=SQL1;
			DB.ExecuteSQL(SQL2);
			SQL1.Format(_T("select eqID from equipment where BCID=%s"),OldStID);
			RS3.Open(CRecordset::snapshot,SQL1);
			while(true)
			{
				if(RS3.IsEOF()) break;
				RS3.GetFieldValue((short)0,OldEqID);
				RS.Open(CRecordset::snapshot,_T("select max(EqID)+1 from Equipment"));
				RS.GetFieldValue((short)0,NewEqID);
				RS.Close();
				SQL2=_T("INSERT INTO Equipment ( EqCatID, StID, MobID, BCID, Pwr2Ant, RadPwr, EqID ) ");
				SQL1.Format(_T("SELECT EqCatID,StID, MobID, %s as Expr2, Pwr2Ant, RadPwr, %s AS Expr1"),NewStID,NewEqID);
				SQL2+=SQL1;
				SQL2+=_T(" FROM (SELECT EqCatID, StID, MobID, Pwr2Ant, RadPwr ");
				SQL1.Format(_T(" FROM Equipment where Eqid=%s) AS qry"),OldEqID);
				SQL2+=SQL1;
				DB.ExecuteSQL(SQL2);

				SQL1.Format(_T("select AntID from antenna where eqID=%s"),OldEqID);
				RS4.Open(CRecordset::snapshot,SQL1);
				while(true)
				{
					if(RS4.IsEOF()) break;
					RS4.GetFieldValue((short)0,OldAntID);
					RS.Open(CRecordset::snapshot,_T("select max(AntID)+1 from Antenna"));
					RS.GetFieldValue((short)0,NewAntID);
					RS.Close();
					SQL2=_T("INSERT INTO Antenna ( AntCatID, EqID, Azimuth, AzimTo, Elevation, AntHeightAGL, AntID ) ");
					SQL1.Format(_T("SELECT AntCatID, %s as Expr2, Azimuth, AzimTo, Elevation, AntHeightAGL, %s AS Expr1"),NewEqID,NewAntID);
					SQL2+=SQL1;
					SQL2+=_T(" FROM (SELECT AntCatID, Azimuth, AzimTo, Elevation, AntHeightAGL ");
					SQL1.Format(_T(" FROM Antenna where Antid=%s) AS qry"),OldAntID);
					SQL2+=SQL1;
					DB.ExecuteSQL(SQL2);
					RS4.MoveNext();
				}
				RS4.Close();

				SQL1.Format(_T("select FreqID from Frequency where eqID=%s"),OldEqID);
				RS4.Open(CRecordset::snapshot,SQL1);
				while(true)
				{
					if(RS4.IsEOF()) break;
					RS4.GetFieldValue((short)0,OldFreqID);
					RS.Open(CRecordset::snapshot,_T("select max(FreqID)+1 from Frequency"));
					RS.GetFieldValue((short)0,NewFreqID);
					RS.Close();
					SQL2=_T("INSERT INTO Frequency ( EqID, Frequency, RespFreq, RefFreq, FreqDev, FreqRange, FreqVCarr, FreqSCarr, EmissionCl, BandWidth, ChannelSep, TVChan, ChannelNo, Traffic, PeakHour, Season, NatServ, HourFrom, HourTo, FreqFee, trgFrequency, EmDes, FreqID ) ");
					SQL1.Format(_T("SELECT %s as Expr2, Frequency, RespFreq, RefFreq, FreqDev, FreqRange, FreqVCarr, FreqSCarr, EmissionCl, BandWidth, ChannelSep, TVChan, ChannelNo, Traffic, PeakHour, Season, NatServ, HourFrom, HourTo, FreqFee, trgFrequency, EmDes, %s AS Expr1 "),NewEqID,NewFreqID);
					SQL2+=SQL1;
					SQL2+=_T(" FROM (SELECT Frequency, RespFreq, RefFreq, FreqDev, FreqRange, FreqVCarr, FreqSCarr, EmissionCl, BandWidth, ChannelSep, TVChan, ChannelNo, Traffic, PeakHour, Season, NatServ, HourFrom, HourTo, FreqFee, trgFrequency, EmDes ");
					SQL1.Format(_T(" FROM Frequency where Freqid=%s) AS qry"),OldFreqID);
					SQL2+=SQL1;
					DB.ExecuteSQL(SQL2);
					RS4.MoveNext();
				}
				RS4.Close();

				RS3.MoveNext();
			}
			RS3.Close();
			RS2.MoveNext();
		}
		RS2.Close();
	}
	else if(SRV==_T("MT"))
	{
		SQL1.Format(_T("select MobID from Mobiles where LicID=%ld"),LicID);
		RS2.Open(CRecordset::snapshot,SQL1);
		while(true)
		{
			if(RS2.IsEOF()) break;
			RS2.GetFieldValue((short)0,OldStID);
			RS.Open(CRecordset::snapshot,_T("select max(MobID)+1 from Mobiles"));
			RS.GetFieldValue((short)0,NewStID);
			RS.Close();
			SQL2=_T("INSERT INTO Mobiles ( LicID, AdmRefID, MobileID, MobName, CallSign, ClassStation, StType, ITURegion, GeoLat, GeoLon, Country, Radius,  Provision,  NetID,  MobID ) ");
			SQL1.Format(_T("SELECT %s as Expr2, AdmRefID, MobileID, MobName, CallSign, ClassStation, StType, ITURegion, GeoLat, GeoLon, Country, Radius,  Provision,  NetID,   %s AS Expr1"),NewLicID,NewStID);
			SQL2+=SQL1;
			SQL2+=_T(" FROM (SELECT AdmRefID, MobileID, MobName, CallSign, ClassStation, StType, ITURegion, GeoLat, GeoLon, Country, Radius, Provision,  NetID ");
			SQL1.Format(_T(" FROM mobiles where mobid=%s) AS qry"),OldStID);
			SQL2+=SQL1;
			DB.ExecuteSQL(SQL2);
			SQL1.Format(_T("select eqID from equipment where MobID=%s"),OldStID);
			RS3.Open(CRecordset::snapshot,SQL1);
			while(true)
			{
				if(RS3.IsEOF()) break;
				RS3.GetFieldValue((short)0,OldEqID);
				RS.Open(CRecordset::snapshot,_T("select max(EqID)+1 from Equipment"));
				RS.GetFieldValue((short)0,NewEqID);
				RS.Close();
				SQL2=_T("INSERT INTO Equipment ( EqCatID, StID, MobID, BCID, Pwr2Ant, RadPwr, EqID ) ");
				SQL1.Format(_T("SELECT EqCatID,StID, %s as Expr2, BCID, Pwr2Ant, RadPwr, %s AS Expr1"),NewStID,NewEqID);
				SQL2+=SQL1;
				SQL2+=_T(" FROM (SELECT EqCatID, StID, BCID, Pwr2Ant, RadPwr ");
				SQL1.Format(_T(" FROM Equipment where Eqid=%s) AS qry"),OldEqID);
				SQL2+=SQL1;
				DB.ExecuteSQL(SQL2);

				SQL1.Format(_T("select AntID from antenna where eqID=%s"),OldEqID);
				RS4.Open(CRecordset::snapshot,SQL1);
				while(true)
				{
					if(RS4.IsEOF()) break;
					RS4.GetFieldValue((short)0,OldAntID);
					RS.Open(CRecordset::snapshot,_T("select max(AntID)+1 from Antenna"));
					RS.GetFieldValue((short)0,NewAntID);
					RS.Close();
					AntIDs[AntInd][0]=atol(OldAntID);
					AntIDs[AntInd][1]=atol(NewAntID);
					AntInd++;
					SQL2=_T("INSERT INTO Antenna ( AntCatID, EqID, Azimuth, AzimTo, Elevation, AntHeightAGL, AntID ) ");
					SQL1.Format(_T("SELECT AntCatID, %s as Expr2, Azimuth, AzimTo, Elevation, AntHeightAGL, %s AS Expr1"),NewEqID,NewAntID);
					SQL2+=SQL1;
					SQL2+=_T(" FROM (SELECT AntCatID, Azimuth, AzimTo, Elevation, AntHeightAGL ");
					SQL1.Format(_T(" FROM Antenna where Antid=%s) AS qry"),OldAntID);
					SQL2+=SQL1;
					DB.ExecuteSQL(SQL2);
					RS4.MoveNext();
				}
				RS4.Close();

				SQL1.Format(_T("select FreqID from Frequency where eqID=%s"),OldEqID);
				RS4.Open(CRecordset::snapshot,SQL1);
				while(true)
				{
					if(RS4.IsEOF()) break;
					RS4.GetFieldValue((short)0,OldFreqID);
					RS.Open(CRecordset::snapshot,_T("select max(FreqID)+1 from Frequency"));
					RS.GetFieldValue((short)0,NewFreqID);
					RS.Close();
					FreqIDs[FreqInd][0]=atol(OldFreqID);
					FreqIDs[FreqInd][1]=atol(NewFreqID);
					FreqInd++;
					SQL2=_T("INSERT INTO Frequency ( EqID, Frequency, RespFreq, RefFreq, FreqDev, FreqRange, FreqVCarr, FreqSCarr, EmissionCl, BandWidth, ChannelSep, TVChan, ChannelNo, Traffic, PeakHour, Season, NatServ, HourFrom, HourTo, FreqFee, trgFrequency, EmDes, FreqID ) ");
					SQL1.Format(_T("SELECT %s as Expr2, Frequency, RespFreq, RefFreq, FreqDev, FreqRange, FreqVCarr, FreqSCarr, EmissionCl, BandWidth, ChannelSep, TVChan, ChannelNo, Traffic, PeakHour, Season, NatServ, HourFrom, HourTo, FreqFee, trgFrequency, EmDes, %s AS Expr1 "),NewEqID,NewFreqID);
					SQL2+=SQL1;
					SQL2+=_T(" FROM (SELECT Frequency, RespFreq, RefFreq, FreqDev, FreqRange, FreqVCarr, FreqSCarr, EmissionCl, BandWidth, ChannelSep, TVChan, ChannelNo, Traffic, PeakHour, Season, NatServ, HourFrom, HourTo, FreqFee, trgFrequency, EmDes ");
					SQL1.Format(_T(" FROM Frequency where Freqid=%s) AS qry"),OldFreqID);
					SQL2+=SQL1;
					DB.ExecuteSQL(SQL2);
					RS4.MoveNext();
				}
				RS4.Close();

				RS3.MoveNext();
			}
			RS3.Close();
			RS2.MoveNext();
		}
		RS2.Close();
		for(int i=0;i<FreqInd;i++)
		{
			long NewTXID,NewRXID,NewRXAntID,NewTXAntID;
			int j;
			CString Value;
			SQL1.Format(_T("select ReceiverID,RXID,TXAntID,RXAntID from Link where TXID=%ld"),FreqIDs[i][0]);
			RS4.Open(CRecordset::snapshot,SQL1);
			while(true)
			{
				if(RS4.IsEOF()) break;
				RS4.GetFieldValue((short)0,OldLinkID);
				for(j=0;j<FreqInd;j++)
					if(FreqIDs[j][0]==FreqIDs[i][0])
						break;
				NewTXID=FreqIDs[j][1];
				RS4.GetFieldValue(1,Value);
				for(j=0;j<FreqInd;j++)
					if(FreqIDs[j][0]==atol(Value))
						break;
				NewRXID=FreqIDs[j][1];
				RS4.GetFieldValue(2,Value);
				for(j=0;j<AntInd;j++)
					if(AntIDs[j][0]==atol(Value))
						break;
				NewTXAntID=AntIDs[j][1];
				RS4.GetFieldValue(3,Value);
				for(j=0;j<AntInd;j++)
					if(AntIDs[j][0]==atol(Value))
						break;
				NewRXAntID=AntIDs[j][1];
				RS.Open(CRecordset::snapshot,_T("select max(ReceiverID)+1 from Link"));
				RS.GetFieldValue((short)0,NewLinkID);
				RS.Close();
				SQL2=_T("INSERT INTO Link ( ReceiverID, HopID, LinkID, GeoType, TXID, RXID, TXAntID, RXAntID, CableLoss, RecLat, RecLon, Radius, Country, lat1, lon1, lat2, lon2, lat3, lon3, lat4, lon4, lat5, lon5, lat6, lon6, NoiseTemp ) ");
				SQL1.Format(_T("SELECT %s as e1, HopID, LinkID, GeoType, %ld as e2, %ld as e3, %ld as e4, %ld as e5, CableLoss, RecLat, RecLon, Radius, Country, lat1, lon1, lat2, lon2, lat3, lon3, lat4, lon4, lat5, lon5, lat6, lon6, NoiseTemp "),NewLinkID,NewTXID,NewRXID,NewTXAntID,NewRXAntID);
				SQL2+=SQL1;
				SQL2+=_T(" FROM (SELECT ReceiverID, HopID, LinkID, GeoType, TXID, RXID, TXAntID, RXAntID, CableLoss, RecLat, RecLon, Radius, Country, lat1, lon1, lat2, lon2, lat3, lon3, lat4, lon4, lat5, lon5, lat6, lon6, NoiseTemp ");
				SQL1.Format(_T(" FROM Link where ReceiverID=%s) AS qry"),OldLinkID);
				SQL2+=SQL1;
				DB.ExecuteSQL(SQL2);
				RS4.MoveNext();
			}
			RS4.Close();
		}
	}
	if(false && SRV!=_T("F") && SRV!=_T("MT") && SRV!=_T("B") && SRV!=_T("MT"))
	{
		SQL1.Format(_T("select ntc_ID from e_stn where LicID=%ld"),LicID);
		RS2.Open(CRecordset::snapshot,SQL1);
		while(true)
		{
			if(RS2.IsEOF()) break;
			RS2.GetFieldValue((short)0,OldStID);
			RS.Open(CRecordset::snapshot,_T("select max(ntc_id)+1 from e_stn"));
			RS.GetFieldValue((short)0,NewStID);
			RS.Close();
			SQL2=_T("INSERT INTO e_stn ( LicID, stn_name, ctry, long_deg, long_ew, long_min, long_sec, lat_deg, lat_ns, lat_min, lat_sec, sat_name, long_nom, diag_hor, elev_min, elev_max, azm_fr, azm_to, ant_alt, f_active, long_dec, lat_dec, ntc_id ) ");
			SQL1.Format(_T("SELECT %s as Expr2, stn_name, ctry, long_deg, long_ew, long_min, long_sec, lat_deg, lat_ns, lat_min, lat_sec, sat_name, long_nom, diag_hor, elev_min, elev_max, azm_fr, azm_to, ant_alt, f_active, long_dec, lat_dec, %s AS Expr1"),NewLicID,NewStID);
			SQL2+=SQL1;
			SQL2+=_T(" FROM (SELECT stn_name, ctry, long_deg, long_ew, long_min, long_sec, lat_deg, lat_ns, lat_min, lat_sec, sat_name, long_nom, diag_hor, elev_min, elev_max, azm_fr, azm_to, ant_alt, f_active, long_dec, lat_dec ");
			SQL1.Format(_T(" FROM e_stn where ntc_id=%s) AS qry"),OldStID);
			SQL2+=SQL1;
			DB.ExecuteSQL(SQL2);
				SQL2=_T("INSERT INTO hor_elev ( ntc_id, azm, elev_ang, hor_dist ) ");
				SQL1.Format(_T("SELECT %s as Expr2,azm, elev_ang, hor_dist"),NewStID);
				SQL2+=SQL1;
				SQL2+=_T(" FROM (SELECT ntc_id, azm, elev_ang, hor_dist ");
				SQL1.Format(_T(" FROM hor_elev where ntc_id=%s) AS qry"),OldStID);
				SQL2+=SQL1;
				DB.ExecuteSQL(SQL2);
				SQL2=_T("INSERT INTO e_ant_elev ( ntc_id, azm, elev_ang ) ");
				SQL1.Format(_T("SELECT %s as Expr2,azm, elev_ang "),NewStID);
				SQL2+=SQL1;
				SQL2+=_T(" FROM (SELECT ntc_id, azm, elev_ang ");
				SQL1.Format(_T(" FROM e_ant_elev where ntc_id=%s) AS qry"),OldStID);
				SQL2+=SQL1;
				DB.ExecuteSQL(SQL2);
			SQL1.Format(_T("select AntID from e_ant where ntc_id=%s"),OldStID);
			RS3.Open(CRecordset::snapshot,SQL1);
			while(true)
			{
				if(RS3.IsEOF()) break;
				RS3.GetFieldValue((short)0,OldEqID);
				RS.Open(CRecordset::snapshot,_T("select max(AntID)+1 from e_ant"));
				RS.GetFieldValue((short)0,NewEqID);
				RS.Close();
				SQL2=_T("INSERT INTO e_ant ( ntc_id, emi_rcp, beam_name, bmwdth, gain, pattern_id,ant_diam,AntID ) ");
				SQL1.Format(_T("SELECT %s as Expr2, emi_rcp, beam_name, bmwdth, gain, pattern_id,ant_diam, %s AS Expr1"),NewStID,NewEqID);
				SQL2+=SQL1;
				SQL2+=_T(" FROM (SELECT ntc_id, emi_rcp, beam_name, bmwdth, gain, pattern_id,ant_diam,AntID ");
				SQL1.Format(_T(" FROM e_ant where AntID=%s) AS qry"),OldEqID);
				SQL2+=SQL1;
				DB.ExecuteSQL(SQL2);

				SQL2=_T("INSERT INTO ESAntPatt ( AntID, OffAng, AntGain ) ");
				SQL1.Format(_T("SELECT %s as Expr2, OffAng, AntGain"),NewEqID);
				SQL2+=SQL1;
				SQL2+=_T(" FROM (SELECT AntID, OffAng, AntGain ");
				SQL1.Format(_T(" FROM ESAntPatt where AntID=%s) AS qry"),OldEqID);
				SQL2+=SQL1;
				DB.ExecuteSQL(SQL2);
				
				SQL1.Format(_T("select grp_id from grp where AntID=%s"),OldEqID);
				RS4.Open(CRecordset::snapshot,SQL1);
				while(true)
				{
					if(RS4.IsEOF()) break;
					RS4.GetFieldValue((short)0,OldAntID);
					RS.Open(CRecordset::snapshot,_T("select max(grp_id)+1 from grp"));
					RS.GetFieldValue((short)0,NewAntID);
					RS.Close();
					SQL2=_T("INSERT INTO grp ( grp_id, ntc_id, emi_rcp, beam_name, adm_resp, bdwdth, d_inuse, noise_t, op_agcy, polar_type, polar_ang, remark, pwr_max, freq_min, freq_max, AntID ) ");
					SQL1.Format(_T("SELECT %s as Expr2, %s as Expr3, emi_rcp, beam_name, adm_resp, bdwdth, d_inuse, noise_t, op_agcy, polar_type, polar_ang, remark, pwr_max, freq_min, freq_max, %s AS Expr1"),NewAntID,NewStID,NewEqID);
					SQL2+=SQL1;
					SQL2+=_T(" FROM (SELECT emi_rcp, beam_name, adm_resp, bdwdth, d_inuse, noise_t, op_agcy, polar_type, polar_ang, remark, pwr_max, freq_min, freq_max ");
					SQL1.Format(_T(" FROM grp where Antid=%s) AS qry"),OldEqID);
					SQL2+=SQL1;
					DB.ExecuteSQL(SQL2);

						SQL2=_T("INSERT INTO emiss ( grp_id, seq_no, design_emi, pwr_tot_pk, pwr_ds_max, pwr_min_pk, pwr_ds_min, c_to_n ) ");
						SQL1.Format(_T("SELECT %s as Expr2,seq_no, design_emi, pwr_tot_pk, pwr_ds_max, pwr_min_pk, pwr_ds_min, c_to_n "),NewAntID);
						SQL2+=SQL1;
						SQL2+=_T(" FROM (SELECT grp_id, seq_no, design_emi, pwr_tot_pk, pwr_ds_max, pwr_min_pk, pwr_ds_min, c_to_n ");
						SQL1.Format(_T(" FROM emiss where grp_id=%s) AS qry"),OldAntID);
						SQL2+=SQL1;
						DB.ExecuteSQL(SQL2);
						SQL2=_T("INSERT INTO assgn ( grp_id, seq_no, freq_sym, freq_assgn, freq_mhz, freqfee ) ");
						SQL1.Format(_T("SELECT %s as Expr2,seq_no, freq_sym, freq_assgn, freq_mhz, freqfee "),NewAntID);
						SQL2+=SQL1;
						SQL2+=_T(" FROM (SELECT grp_id, seq_no, freq_sym, freq_assgn, freq_mhz, freqfee ");
						SQL1.Format(_T(" FROM assgn where grp_id=%s) AS qry"),OldAntID);
						SQL2+=SQL1;
						DB.ExecuteSQL(SQL2);
						SQL2=_T("INSERT INTO provn ( grp_id, seq_no, coord_prov, agree_st, adm ) ");
						SQL1.Format(_T("SELECT %s as Expr2,seq_no, coord_prov, agree_st, adm "),NewAntID);
						SQL2+=SQL1;
						SQL2+=_T(" FROM (SELECT grp_id, seq_no, coord_prov, agree_st, adm ");
						SQL1.Format(_T(" FROM provn where grp_id=%s) AS qry"),OldAntID);
						SQL2+=SQL1;
						DB.ExecuteSQL(SQL2);
						SQL2=_T("INSERT INTO gpub ( grp_id, seq_no, pub_ref, pub_no, ssn_type, ssn_rev, ssn_rev_no) ");
						SQL1.Format(_T("SELECT %s as Expr2,seq_no, pub_ref, pub_no, ssn_type, ssn_rev, ssn_rev_no "),NewAntID);
						SQL2+=SQL1;
						SQL2+=_T(" FROM (SELECT grp_id, seq_no, pub_ref, pub_no, ssn_type, ssn_rev, ssn_rev_no ");
						SQL1.Format(_T(" FROM gpub where grp_id=%s) AS qry"),OldAntID);
						SQL2+=SQL1;
						DB.ExecuteSQL(SQL2);
						SQL2=_T("INSERT INTO srv_cls ( grp_id, seq_no, stn_cls, nat_srv ) ");
						SQL1.Format(_T("SELECT %s as Expr2,seq_no, stn_cls, nat_srv "),NewAntID);
						SQL2+=SQL1;
						SQL2+=_T(" FROM (SELECT grp_id, seq_no, stn_cls, nat_srv ");
						SQL1.Format(_T(" FROM srv_cls where grp_id=%s) AS qry"),OldAntID);
						SQL2+=SQL1;
						DB.ExecuteSQL(SQL2);
						SQL2=_T("INSERT INTO ESFilters ( EqID, CS, Att ) ");
						SQL1.Format(_T("SELECT %s as Expr2, CS, Att "),NewAntID);
						SQL2+=SQL1;
						SQL2+=_T(" FROM (SELECT EqID, CS, Att ");
						SQL1.Format(_T(" FROM ESFilters where EqID=%s) AS qry"),OldAntID);
						SQL2+=SQL1;
						DB.ExecuteSQL(SQL2);

					RS4.MoveNext();
				}
				RS4.Close();
				
				RS3.MoveNext();			
			}
			RS3.Close();
			RS2.MoveNext();
		}
		RS2.Close();
	}
	DB.Close();
}

void CLeftView::AddTrail(CString Action, long RecordID, CString Table)
{
	//CRecordset m_rs;
	//CDBVariant TempVar;
	CDatabase DB;
//	CString UserName=((CSMS4DCApp *)AfxGetApp())->m_UserName;
	CTime Date=CTime::GetCurrentTime();
	DB.Open(m_CDBSTR,false,false,_T("ODBC;"),false);
	CString temp,
		m_Tbl="INSERT INTO Audit ( UserName, [DateTime], [Action], Record, [Table] ) SELECT \'";
	m_Tbl+= m_UserName +"\' as Expr1, \'";
	m_Tbl+= Date.Format("%c") + "\' AS Expr2, \'";
	m_Tbl+= Action + "\' AS Expr3, ";
	temp.Format("%ld",RecordID);
	m_Tbl+= temp + " AS Expr4, \'";
	m_Tbl+= Table + "\' AS Expr5";
	//m_rs.m_pDatabase=pDB;
	DB.ExecuteSQL(m_Tbl);
	DB.Close();
	//m_rs.Open( CRecordset::dynaset, m_Tbl);
}

void CLeftView::OnCancellic() 
{
	CDatabase DB;
	DB.Open(/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR,false,false,_T("ODBC;"),false);
	CRecordset RS;
	CString SQL,Value;
	RS.m_pDatabase=&DB;
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	SQL.Format(_T("select status from license where licid=%ld"),GetTreeCtrl().GetItemData(Node));
	RS.Open(CRecordset::snapshot,SQL);
	RS.GetFieldValue((short)0,Value);
	RS.Close();
	if(Value!=_T("Granted"))
		AfxMessageBox(_T("License is not granted yet!"));
	else
	{
		SQL.Format(_T("update license set archive=yes , status='Cancelled' where licid=%ld"),GetTreeCtrl().GetItemData(Node));
		DB.ExecuteSQL(SQL);
		GetTreeCtrl().DeleteAllItems();
		BuildTree(2);
		CleanScreen();
	}
	DB.Close();
}

void CLeftView::OnLicenseCopytoarchive() 
{
	CopyToArchive(GetTreeCtrl().GetItemData(GetTreeCtrl().GetSelectedItem()));
	GetTreeCtrl().DeleteAllItems();
	BuildTree(2);
	CleanScreen();
}

CString CLeftView::GetFieldName(CDatabase *DB, CString Table, CString OrigName, CString LangCode, CString *Unit, CString *Format, CString *Srv, CString *Mask)
{
	CRecordset	RS;
	RS.m_pDatabase=DB;
	CString FieldName,SQL;
	SQL.Format(_T("Select * from Fields where TableName='%s' and FieldName='%s'"), Table, OrigName);
	RS.Open(CRecordset::dynaset,SQL);
//	LangCode=/*((CSMS4DCApp *)AfxGetApp())->*/m_Lang;
	if(RS.GetRecordCount()>0)
	{
		if(m_Lang==_T("En"))
			RS.GetFieldValue(2,FieldName);
		if(m_Lang==_T("Fr"))
			RS.GetFieldValue(3,FieldName);
		if(m_Lang==_T("Es"))
			RS.GetFieldValue(4,FieldName);
		RS.GetFieldValue(5,*Unit);
		RS.GetFieldValue(6,*Srv);
		RS.GetFieldValue(7,*Mask);
		RS.GetFieldValue(8,*Format);
	}
	else
	{
		*Srv=_T("-");
	}
	RS.Close();
	return FieldName;
}

void CLeftView::OnTreeRefresh() 
{
	if(AfxMessageBox(_T("This process may take some time. Are you sure?"),MB_YESNO)==IDYES)
	{
		GetTreeCtrl().DeleteAllItems();
		BuildTree(2);
		CleanScreen();
	}
}

void CLeftView::OnGroupEmissions() 
{
	CString Temp=m_CDBSTR;
	AFX_MANAGE_STATE(AfxGetStaticModuleState()) ;
	CGrpDetails	GrpDlg;
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	int BeamType;
	GetTreeCtrl().GetItemImage(GetTreeCtrl().GetParentItem(Node),BeamType,BeamType);
	if(BeamType==EANTUP)
		GrpDlg.m_BeamType=1;
	else
		GrpDlg.m_BeamType=2;
	GrpDlg.m_CDBSTR=Temp;
	GrpDlg.m_Lang=m_Lang;
	GrpDlg.m_Grp_id=GetTreeCtrl().GetItemData(Node);
	GrpDlg.m_Type=1;
	GrpDlg.DoModal();
}

void CLeftView::OnGroupFrequency() 
{
	CString Temp=m_CDBSTR;
	long id;
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState()) ;
		CGrpDetails	GrpDlg;
		HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
		int BeamType;
		GetTreeCtrl().GetItemImage(GetTreeCtrl().GetParentItem(Node),BeamType,BeamType);
		if(BeamType==EANTUP)
			GrpDlg.m_BeamType=1;
		else
			GrpDlg.m_BeamType=2;
		GrpDlg.m_CDBSTR=Temp;
		GrpDlg.m_Lang=m_Lang;
		id=GrpDlg.m_Grp_id=GetTreeCtrl().GetItemData(Node);
		GrpDlg.m_Type=2;
		GrpDlg.DoModal();
	}
	LoadData(_T("grp"), id, GROUP);
}

void CLeftView::OnGroupCoordination() 
{
	CString Temp=m_CDBSTR;
	AFX_MANAGE_STATE(AfxGetStaticModuleState()) ;
	CGrpDetails	GrpDlg;
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	int BeamType;
	GetTreeCtrl().GetItemImage(GetTreeCtrl().GetParentItem(Node),BeamType,BeamType);
	if(BeamType==EANTUP)
		GrpDlg.m_BeamType=1;
	else
		GrpDlg.m_BeamType=2;
	GrpDlg.m_CDBSTR=Temp;
	GrpDlg.m_Lang=m_Lang;
	GrpDlg.m_Grp_id=GetTreeCtrl().GetItemData(Node);
	GrpDlg.m_Type=4;
	GrpDlg.DoModal();
}

void CLeftView::OnGroupFilter() 
{
	CString Temp=m_CDBSTR;
	AFX_MANAGE_STATE(AfxGetStaticModuleState()) ;
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	CTxRxFilterDLG	Dlg;
	Dlg.m_CDBSTR=Temp;
	Dlg.m_ID=GetTreeCtrl().GetItemData(Node);
	Dlg.m_TxRx=3;
	Dlg.DoModal();
}

void CLeftView::OnGroupClassofstation() 
{
	CString Temp=m_CDBSTR;
	AFX_MANAGE_STATE(AfxGetStaticModuleState()) ;
	CGrpDetails	GrpDlg;
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	int BeamType;
	GetTreeCtrl().GetItemImage(GetTreeCtrl().GetParentItem(Node),BeamType,BeamType);
	if(BeamType==EANTUP)
		GrpDlg.m_BeamType=1;
	else
		GrpDlg.m_BeamType=2;
	GrpDlg.m_CDBSTR=Temp;
	GrpDlg.m_Lang=m_Lang;
	GrpDlg.m_Grp_id=GetTreeCtrl().GetItemData(Node);
	GrpDlg.m_Type=5;
	GrpDlg.DoModal();
}

void CLeftView::OnEarthstationHorizontalelevation() 
{
	CString Temp=m_CDBSTR;
	AFX_MANAGE_STATE(AfxGetStaticModuleState()) ;
	CGrpDetails	GrpDlg;
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	int BeamType;
	GetTreeCtrl().GetItemImage(GetTreeCtrl().GetParentItem(Node),BeamType,BeamType);
	if(BeamType==EANTUP)
		GrpDlg.m_BeamType=1;
	else
		GrpDlg.m_BeamType=2;
	GrpDlg.m_CDBSTR=Temp;
	GrpDlg.m_Lang=m_Lang;
	GrpDlg.m_Grp_id=GetTreeCtrl().GetItemData(Node);
	GrpDlg.m_Type=6;
	GrpDlg.DoModal();
}

void CLeftView::OnEarthstationMinimumelevangles() 
{
	CString Temp=m_CDBSTR;
	AFX_MANAGE_STATE(AfxGetStaticModuleState()) ;
	CGrpDetails	GrpDlg;
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	int BeamType;
	GetTreeCtrl().GetItemImage(GetTreeCtrl().GetParentItem(Node),BeamType,BeamType);
	if(BeamType==EANTUP)
		GrpDlg.m_BeamType=1;
	else
		GrpDlg.m_BeamType=2;
	GrpDlg.m_CDBSTR=Temp;
	GrpDlg.m_Lang=m_Lang;
	GrpDlg.m_Grp_id=GetTreeCtrl().GetItemData(Node);
	GrpDlg.m_Type=7;
	GrpDlg.DoModal();
}

void CLeftView::OnAddEs() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	GetTreeCtrl().EnableWindow(false);
	pView->m_OldRecordType=LICENSE;
	pView->m_OldTable=_T("License");
	pView->m_OldRecID=pView->m_RecID;
	pView->m_RecID=-1;
	pView->m_Table=_T("Earth");
	pView->m_Action=1;
	pView->m_ReadOnly=false;
	pView->m_Refresh=true;
	pView->m_RecordType=ESTATION;
	pView->RedrawWindow();	
}

void CLeftView::OnAddbeamup() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	GetTreeCtrl().EnableWindow(false);
	pView->m_OldRecordType=ESTATION;
	pView->m_OldTable=_T("Earth");
	pView->m_OldRecID=pView->m_RecID;
	pView->m_RecID=-1;
	pView->m_Table=_T("Eant");
	pView->m_Action=1;
	pView->m_ReadOnly=false;
	pView->m_Refresh=true;
	pView->m_RecordType=EANTUP;
	pView->RedrawWindow();	
}

void CLeftView::OnAddbeamdown() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	GetTreeCtrl().EnableWindow(false);
	pView->m_OldRecordType=ESTATION;
	pView->m_OldTable=_T("Earth");
	pView->m_OldRecID=pView->m_RecID;
	pView->m_RecID=-1;
	pView->m_Table=_T("Eant");
	pView->m_Action=1;
	pView->m_ReadOnly=false;
	pView->m_Refresh=true;
	pView->m_RecordType=EANTDN;
	pView->RedrawWindow();		
}

void CLeftView::OnAddgroup() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	GetTreeCtrl().EnableWindow(false);
	int NType;
	GetTreeCtrl().GetItemImage(GetTreeCtrl().GetSelectedItem(),NType,NType);
	pView->m_OldRecordType=NType;
	pView->m_OldTable=_T("Eant");
	pView->m_OldRecID=pView->m_RecID;
	pView->m_RecID=-1;
	pView->m_Table=_T("grp");
	pView->m_Action=1;
	pView->m_ReadOnly=false;
	pView->m_Refresh=true;
	pView->m_RecordType=GROUP;
	pView->RedrawWindow();	
}

void CLeftView::OnGroupSpecialsection() 
{
	CString Temp=m_CDBSTR;
	AFX_MANAGE_STATE(AfxGetStaticModuleState()) ;
	CGrpDetails	GrpDlg;
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	int BeamType;
	GetTreeCtrl().GetItemImage(GetTreeCtrl().GetParentItem(Node),BeamType,BeamType);
	if(BeamType==EANTUP)
		GrpDlg.m_BeamType=1;
	else
		GrpDlg.m_BeamType=2;
	GrpDlg.m_CDBSTR=Temp;
	GrpDlg.m_Lang=m_Lang;
	GrpDlg.m_Grp_id=GetTreeCtrl().GetItemData(Node);
	GrpDlg.m_Type=3;
	GrpDlg.DoModal();
}

void CLeftView::OnGroupDelete() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	HTREEITEM Par=GetTreeCtrl().GetParentItem(Node);
	int type;
	GetTreeCtrl().GetItemImage(Par,type,type);
	if(DelRecPermanent(GROUP, GetTreeCtrl().GetItemData(Node),IDNO, GetTreeCtrl().GetItemData(Par)))
	{
		AddTrail(_T("Delete group"),GetTreeCtrl().GetItemData(Node),_T("grp"));
		pView->m_OldRecordType=type;
		pView->m_OldTable=_T("Eant");
		pView->m_OldRecID=GetTreeCtrl().GetItemData(Par);
		pView->m_RecID=GetTreeCtrl().GetItemData(Par);
		pView->m_Table=_T("Eant");
		pView->m_Action=1;
		pView->m_ReadOnly=true;
		pView->m_Refresh=true;
		pView->m_RecordType=type;
		GetTreeCtrl().SelectItem(Par);
		GetTreeCtrl().DeleteItem(Node);
		pView->RedrawWindow();
	}
}

void CLeftView::OnEsantennaDelete() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	HTREEITEM Par=GetTreeCtrl().GetParentItem(Node);
	int type;
	GetTreeCtrl().GetItemImage(Node,type,type);
	if(DelRecPermanent(type, GetTreeCtrl().GetItemData(Node),IDNO, GetTreeCtrl().GetItemData(Par)))
	{
		AddTrail(_T("Delete Earth Station Antenna"),GetTreeCtrl().GetItemData(Node),_T("Eant"));
		pView->m_OldRecordType=ESTATION;
		pView->m_OldTable=_T("Earth");
		pView->m_OldRecID=GetTreeCtrl().GetItemData(Par);
		pView->m_RecID=GetTreeCtrl().GetItemData(Par);
		pView->m_Table=_T("Earth");
		pView->m_Action=1;
		pView->m_ReadOnly=true;
		pView->m_Refresh=true;
		pView->m_RecordType=ESTATION;
		GetTreeCtrl().SelectItem(Par);
		GetTreeCtrl().DeleteItem(Node);
		pView->RedrawWindow();
	}
}

void CLeftView::OnEarthstationDelete() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	HTREEITEM Par=GetTreeCtrl().GetParentItem(Node);
	int type;
	GetTreeCtrl().GetItemImage(Node,type,type);
	if(DelRecPermanent(type, GetTreeCtrl().GetItemData(Node),IDNO, GetTreeCtrl().GetItemData(Par)))
	{
		AddTrail(_T("Delete Earth Station"),GetTreeCtrl().GetItemData(Node),_T("Earth"));
		GetTreeCtrl().GetItemImage(Par,type,type);
		if(type==LICENSE)
		{
			pView->m_OldRecordType=LICENSE;
			pView->m_OldTable=_T("License");
			pView->m_Table=_T("License");
			pView->m_RecordType=LICENSE;
		}
		else
		{
			pView->m_OldRecordType=SMS4DC;
			pView->m_OldTable=_T("");
			pView->m_Table=_T("");
			pView->m_RecordType=SMS4DC;
		}
		pView->m_OldRecID=GetTreeCtrl().GetItemData(Par);
		pView->m_RecID=GetTreeCtrl().GetItemData(Par);
		pView->m_Action=1;
		pView->m_ReadOnly=true;
		pView->m_Refresh=true;
		GetTreeCtrl().SelectItem(Par);
		GetTreeCtrl().DeleteItem(Node);
//		CleanScreen();
	}
}

void CLeftView::OnEarthstationNotice() 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()) ;
	CESNotice NoticeDlg;	
	NoticeDlg.m_CDBSTR=m_CDBSTR;
	NoticeDlg.m_Lang=m_Lang;
	NoticeDlg.m_ntc_id=GetTreeCtrl().GetItemData(GetTreeCtrl().GetSelectedItem());
	NoticeDlg.DoModal();
}

void CLeftView::OnFrequencyCoordination() 
{
	CString Temp=m_CDBSTR;
	AFX_MANAGE_STATE(AfxGetStaticModuleState()) ;
	CGrpDetails	GrpDlg;
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	GrpDlg.m_CDBSTR=Temp;
	GrpDlg.m_Lang=m_Lang;
	GrpDlg.m_Grp_id=GetTreeCtrl().GetItemData(Node);
	GrpDlg.m_Type=9;
	GrpDlg.DoModal();
}

extern "C" int WINAPI ESPATTERN(HWND hWndParent,CString DBSTR,long ntID,CString emi_rcp,CString beam, CString mLang);	//ESantDLL.lib
void CLeftView::OnEsantennaShowpattern() 
{
	long ntID;
	CString emi_rcp;
	CString beam = _T("CS");
	CString Txt;
	int strt;

	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem(),
		Par=GetTreeCtrl().GetParentItem(Node);
	int type;
	GetTreeCtrl().GetItemImage(Node,type,type);
	if(type==EANTUP)
		emi_rcp=_T("E");
	else
		emi_rcp=_T("R");
	ntID=GetTreeCtrl().GetItemData(Par);
	Txt=GetTreeCtrl().GetItemText(Node);
	strt=Txt.Find(_T(":"));
	beam=Txt.Right(Txt.GetLength()-strt-2);
	ESPATTERN(this->m_hWnd,m_CDBSTR,ntID,emi_rcp,beam, m_Lang);	
}


void CLeftView::OnDeleteOwner() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	HTREEITEM Par=GetTreeCtrl().GetParentItem(Node);
	if(DelRecPermanent(OWNER, GetTreeCtrl().GetItemData(Node),IDNO, GetTreeCtrl().GetItemData(Par)))
	{
		AddTrail("Delete Owner",GetTreeCtrl().GetItemData(Node),"Owner");
		pView->m_OldRecordType=SMS4DC;
		pView->m_OldTable=_T("");
		pView->m_Table=_T("");
		pView->m_RecordType=SMS4DC;
		pView->m_OldRecID=GetTreeCtrl().GetItemData(Par);
		pView->m_RecID=GetTreeCtrl().GetItemData(Par);
		pView->m_Action=1;
		pView->m_ReadOnly=true;
		pView->m_Refresh=true;
		GetTreeCtrl().SelectItem(Par);
		GetTreeCtrl().DeleteItem(Node);
		//pView->RedrawWindow();
		GetTreeCtrl().DeleteAllItems();
		BuildTree(2);
		CleanScreen();
	}
	
}

void CLeftView::OnContourPoints() 
{
	CString Temp=m_CDBSTR;
	AFX_MANAGE_STATE(AfxGetStaticModuleState()) ;
	CGrpDetails	GrpDlg;
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	GrpDlg.m_CDBSTR=Temp;
	GrpDlg.m_Lang=m_Lang;
	GrpDlg.m_Grp_id=GetTreeCtrl().GetItemData(Node);
	GrpDlg.m_Type=10;
	GrpDlg.DoModal();	
}

void CLeftView::OnUpdateAddAllotment(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnAddAllotment() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	GetTreeCtrl().EnableWindow(false);
	pView->m_OldRecID=pView->m_RecID;
	pView->m_RecID=-1;
	pView->m_Table=_T("Allotment");
	pView->m_Action=1;
	pView->m_ReadOnly=false;
	pView->m_Refresh=true;
	pView->m_RecordType=ALLOTMENT;
	pView->RedrawWindow();
}

void CLeftView::OnEditAllot() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	pView->ModifyData();	
}

void CLeftView::OnUpdateEditAllot(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);			
}

void CLeftView::OnUpdateDeleteAllot(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnDeleteAllot() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	HTREEITEM Par=GetTreeCtrl().GetParentItem(Node);
	if(DelRecPermanent(ALLOTMENT, GetTreeCtrl().GetItemData(Node),IDNO, GetTreeCtrl().GetItemData(Par)))
	{
		AddTrail("Delete allotment",GetTreeCtrl().GetItemData(Node),"rrc_allotment");
		pView->m_OldRecordType=SMS4DC;
		pView->m_OldTable=_T("");
		pView->m_OldRecID=GetTreeCtrl().GetItemData(Par);
		pView->m_RecID=GetTreeCtrl().GetItemData(Par);
		pView->m_Table=_T("");
		pView->m_Action=1;
		pView->m_ReadOnly=true;
		pView->m_Refresh=true;
		pView->m_RecordType=SMS4DC;
		GetTreeCtrl().SelectItem(Par);
		GetTreeCtrl().DeleteItem(Node);
		pView->RedrawWindow();
	}
}

void CLeftView::OnUpdateAddContour(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnAddContour() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	GetTreeCtrl().EnableWindow(false);
	pView->m_OldRecordType=ALLOTMENT;
	pView->m_OldTable=_T("Allotment");
	pView->m_OldRecID=pView->m_RecID;
	pView->m_RecID=-1;
	pView->m_Table=_T("Contour");
	pView->m_Action=1;
	pView->m_ReadOnly=false;
	pView->m_Refresh=true;
	pView->m_RecordType=CONTOUR;
	pView->RedrawWindow();
}

void CLeftView::OnUpdateDeleteContour(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnDeleteContour() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	HTREEITEM Par=GetTreeCtrl().GetParentItem(Node);
	if(DelRecPermanent(CONTOUR, GetTreeCtrl().GetItemData(Node),IDNO, GetTreeCtrl().GetItemData(Par)))
	{
		AddTrail(_T("Detatch contour"),GetTreeCtrl().GetItemData(Node),_T("rrc_sub_area"));
		pView->m_OldRecordType=ALLOTMENT;
		pView->m_OldTable=_T("rrc_allotment");
		pView->m_OldRecID=GetTreeCtrl().GetItemData(Par);
		pView->m_RecID=GetTreeCtrl().GetItemData(Par);
		pView->m_Table=_T("rrc_allotment");
		pView->m_Action=1;
		pView->m_ReadOnly=true;
		pView->m_Refresh=true;
		pView->m_RecordType=ALLOTMENT;
		GetTreeCtrl().SelectItem(Par);
		GetTreeCtrl().DeleteItem(Node);
		pView->RedrawWindow();
	}
}

void CLeftView::OnUpdateAddbeamdown(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnUpdateAddbeamup(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnUpdateAddEs(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnUpdateAddgroup(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnUpdateAttachContour(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnAttachContour() 
{
	CString Temp=/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR;
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	CDatabase DB;
	CRecordset RS;
	CString SQL,Srv;
	bool result=true;
	long CatID;
	{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()) ;
	CCatSelect CatDlg;
	CatDlg.m_CDBSTR=Temp;
	CatDlg.m_ID=GetTreeCtrl().GetItemData(Node);
	CatDlg.m_Table=_T("rrc_contour");
	CatDlg.m_EqGrid=NULL;
	//CatDlg.m_Srv=m_Service;
	CatDlg.DoModal();
	CatID=CatDlg.m_CatID;
	if(CatID>-1)
	{
		DB.Open(Temp,false,false,_T("ODBC;"),false);
		SQL.Format(_T("insert into rrc_sub_area (allotkey,contourkey) select %ld,%ld"), 
			GetTreeCtrl().GetItemData(Node), CatID);
		DB.ExecuteSQL(SQL);
		AddTrail(_T("Attach a contour"),CatID,_T("rrc_sub_area"));
		DB.Close();
		GetTreeCtrl().DeleteAllItems();
		BuildTree(2);
		result=true;
	}
	else
	{
		result=false;
	}
	}
	if(result) CleanScreen();
}

CString CLeftView::BWCode(double BW)
{
	int i;
	CString Temp;
	BW*=1000;
	char Code;
	if(BW<1000)
	{
		Code='H';
	}
	if(BW>=1000. && BW<1e+6)
	{
		BW/=1000.;
		Code='K';
	}
	if(BW>=1e+6 && BW<1e+9)
	{
		BW/=1e+6;
		Code='M';
	}
	if(BW>=1e+9 && BW<1e+12)
	{
		BW/=1e+9;
		Code='G';
	}
		int IPart=(int)BW;
		double FPart2=BW-IPart;
		char FP[10], tt[20];
		sprintf(FP,"%.3f",FPart2);
		strcpy(tt,FP+2);

		if(IPart)
		{
			if(FPart2)
				Temp.Format("%d%c%s",IPart,Code,tt);
			else
				Temp.Format("%d%c",IPart,Code);
		}
		else
			Temp.Format("%c%s",Code,tt);

	for(i=Temp.GetLength();i<4;i++)
		Temp+="0";
	Temp=Temp.Left(4);
	return Temp;
}

void CLeftView::OnAllotmentElectronicnotice() 
{
	CString Temp=/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR;
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem(),
		Parent=GetTreeCtrl().GetParentItem(Node);
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	AFX_MANAGE_STATE(AfxGetStaticModuleState()) ;
	CNotice NoticeDlg;
	NoticeDlg.m_CDBSTR=Temp;
	int Type;
	NoticeDlg.m_StID=GetTreeCtrl().GetItemData(Node);
	NoticeDlg.m_LicID=-1;
	GetTreeCtrl().GetItemImage(Node,Type,Type);
	NoticeDlg.m_SrvType=_T("Allotment");
	NoticeDlg.DoModal();			
}

void CLeftView::OnUpdateLicenseAddallotment(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnLicenseAddallotment() 
{
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	GetTreeCtrl().EnableWindow(false);
	pView->m_OldRecordType=LICENSE;
	pView->m_OldTable=_T("License");
	pView->m_OldRecID=pView->m_RecID;
	pView->m_RecID=-1;
	pView->m_Table=_T("Allotment");
	pView->m_Action=1;
	pView->m_ReadOnly=false;
	pView->m_Refresh=true;
	pView->m_RecordType=ALLOTMENT;
	pView->RedrawWindow();	
}

void CLeftView::OnLicenseMoveallotment() 
{
	CString Temp=/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR;
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	CDatabase DB;
	CString SQL,Srv;
	bool result;
	DB.Open(Temp,false,false,_T("ODBC;"),false);
	{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()) ;
	CMoveStation MoveDlg;
	MoveDlg.m_Service=_T("Allotment");
	MoveDlg.m_Lang=m_Lang;
	MoveDlg.m_CDBSTR=Temp;
	MoveDlg.DoModal();
	long ID=MoveDlg.m_StID;
	if(ID>-1)
	{
		SQL.Format(_T("Update rrc_allotment Set LicID=%ld where allotkey=%ld"), GetTreeCtrl().GetItemData(Node), ID);
		DB.ExecuteSQL(SQL);
		AddTrail(_T("Move broadcasting allotment from technical"),ID,_T("rrc_allotment"));
		GetTreeCtrl().DeleteAllItems();
		DB.Close();
		BuildTree(2);
		result=true;
	}
	else
	{
		DB.Close();
		result=false;
	}
	}
	if(result) CleanScreen();
}

void CLeftView::OnUpdateLicenseMoveallotment(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
}

void CLeftView::OnUpdateFrequencyServicearea(CCmdUI* pCmdUI) 
{
//	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
	
}

void CLeftView::OnFrequencyServicearea() 
{
	CString Temp=m_CDBSTR;
	AFX_MANAGE_STATE(AfxGetStaticModuleState()) ;
	CGrpDetails	GrpDlg;
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem(),
		ParentItem=GetTreeCtrl().GetParentItem(GetTreeCtrl().GetParentItem(Node));
	if(GetTreeCtrl().GetItemText(ParentItem).Left(1)==_T("B"))
	{
		GrpDlg.m_CDBSTR=Temp;
		GrpDlg.m_Lang=m_Lang;
		GrpDlg.m_Grp_id=GetTreeCtrl().GetItemData(Node);
		GrpDlg.m_Type=11;
		GrpDlg.DoModal();	
	}
}

void CLeftView::OnAllotCoordination() 
{
	CString Temp=m_CDBSTR;
	AFX_MANAGE_STATE(AfxGetStaticModuleState()) ;
	CGrpDetails	GrpDlg;
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem();
	GrpDlg.m_CDBSTR=Temp;
	GrpDlg.m_Lang=m_Lang;
	GrpDlg.m_Grp_id=GetTreeCtrl().GetItemData(Node);
	GrpDlg.m_Type=12;
	GrpDlg.DoModal();
	
}

void CLeftView::OnContourElectronicnotice() 
{
	CString Temp=/*((CSMS4DCApp *)AfxGetApp())->*/m_CDBSTR;
	HTREEITEM Node=GetTreeCtrl().GetSelectedItem(),
		Parent=GetTreeCtrl().GetParentItem(Node);
	CWnd* pWnd = ((CSplitterWnd *)GetParent())->GetPane(0, 1);
	CTreeviewView* pView = DYNAMIC_DOWNCAST(CTreeviewView, pWnd);
	AFX_MANAGE_STATE(AfxGetStaticModuleState()) ;
	CNotice NoticeDlg;
	NoticeDlg.m_CDBSTR=Temp;
	int Type;
	NoticeDlg.m_StID=GetTreeCtrl().GetItemData(Node);
	NoticeDlg.m_LicID=-1;
	GetTreeCtrl().GetItemImage(Node,Type,Type);
	NoticeDlg.m_SrvType=_T("Contour");
	NoticeDlg.DoModal();	
}

void CLeftView::OnUpdateDeleteselection(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(/*((CSMS4DCApp *)AfxGetApp())->*/m_UserLevel!=6);		
	
}

void CLeftView::OnDeleteselection() 
{
	HTREEITEM Root=GetTreeCtrl().GetRootItem(), 
		Par=GetTreeCtrl().GetChildItem(Root),
		Node=GetTreeCtrl().GetChildItem(GetTreeCtrl().GetChildItem(Root));
	int Ans;
	Ans=AfxMessageBox(_T("Are you sure to delete selected stations completely?"),MB_YESNO|MB_ICONWARNING);
	if(Ans==IDYES)
	{
		while(Node!=NULL)
		{
			if(GetTreeCtrl().GetCheck(Node))
			{
				int typ;
				GetTreeCtrl().GetItemImage(Node,typ,typ);
				DelRecPermanent(typ, GetTreeCtrl().GetItemData(Node),IDYES, GetTreeCtrl().GetItemData(Par));
			}
			Node=GetTreeCtrl().GetNextSiblingItem(Node);
		}
		GetTreeCtrl().DeleteAllItems();
		BuildTree(2);
		CleanScreen();
	}
}
