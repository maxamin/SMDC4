// SMS4DC.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SMS4DC.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "ChildFrmArea.h"
#include "SMS4DCDoc.h"
#include "SMS4DCView.h"

#include "ProfileDoc.h"
#include "ProfileView.h"

#include "ProfilePolygonDoc.h"
#include "ProfilePolygonView.h"

#include "Pro_Free_LineDoc.h"
#include "Pro_Free_LineView.h"

#include "Pro_Free_PolygonDoc.h"
#include "Pro_Free_PolygonView.h"

#include "Pro_Free_AreaDoc.h"
#include "Pro_Free_AreaView.h"

#include "Pro_P370_AreaDoc.h"
#include "Pro_P370_AreaView.h"
#include "Pro_P370_AreaFrm.h"

#include "Pro_P1546_AreaDoc.h"
#include "Pro_P1546_AreaView.h"
#include "Pro_P1546_AreaFrm.h"

#include "Pro_LoS_AreaDoc.h"
#include "Pro_LoS_AreaView.h"
#include "Pro_LoS_AreaFrm.h"

#include "StationsTableDoc.h"
#include "StationsTableView.h"
#include "StationsTableFrm.h"

#include "EffectiveHeigthDoc.h"
#include "EffectiveHeigthView.h"
#include "EffectiveHeigthFrm.h"

#include "Pro_Free_NetFDoc.h"
#include "Pro_Free_NetFView.h"
#include "Pro_Free_NetFFrm.h"

#include "Pro_Free_NetBDoc.h"
#include "Pro_Free_NetBView.h"
#include "Pro_Free_NetBFrm.h"

#include "Pro_P370_NetFDoc.h"
#include "Pro_P370_NetFView.h"
#include "Pro_P370_NetFFrm.h"

#include "Pro_P370_NetBDoc.h"
#include "Pro_P370_NetBView.h"
#include "Pro_P370_NetBFrm.h"

#include "Pro_P1546_NetFDoc.h"
#include "Pro_P1546_NetFView.h"
#include "Pro_P1546_NetFFrm.h"

#include "Pro_P1546_NetBDoc.h"
#include "Pro_P1546_NetBView.h"
#include "Pro_P1546_NetBFrm.h"

#include "AntennaFormDoc.h"
#include "AntennaFormView.h"
#include "AntennaFormFrm.h"

#include "Pro_P370_LineDoc.h"
#include "Pro_P370_LineView.h"
#include "Pro_P370_LineFrm.h"

#include "Pro_P1546_LineDoc.h"
#include "Pro_P1546_LineView.h"
#include "Pro_P1546_LineFrm.h"

#include "Pro_LoS_LineDoc.h"
#include "Pro_LoS_LineView.h"
#include "Pro_LoS_LineFrm.h"

#include "Allocations_DrawDoc.h"
#include "Allocations_DrawView.h"
#include "Allocations_DrawFrm.h"

#include "Pro_P370_PolygonDoc.h"
#include "Pro_P370_PolygonView.h"
#include "Pro_P370_PolygonFrm.h"

#include "Pro_P1546_PolygonDoc.h"
#include "Pro_P1546_PolygonView.h"
#include "Pro_P1546_PolygonFrm.h"

#include "Pro_LoS_PolygonDoc.h"
#include "Pro_LoS_PolygonView.h"
#include "Pro_LoS_PolygonFrm.h"

#include "Ant3DDoc.h"
#include "Ant3DView.h"
#include "Ant3DFrm.h"

#include "Area3DDoc.h"
#include "Area3DView.h"
#include "Area3DFrm.h"

#include "Contour_DEMDoc.h"
#include "Contour_DEMView.h"
#include "Contour_DEMFrm.h"

#include "Pro_P370_LinkDoc.h"
#include "Pro_P370_LinkView.h"
#include "Pro_P370_LinkFrm.h"

#include "Pro_P1546_LinkDoc.h"
#include "Pro_P1546_LinkView.h"
#include "Pro_P1546_LinkFrm.h"

#include "MainMapDoc.h"
#include "MainMapView.h"
#include "MainMapFrm.h"

#include "Pro_HATA_AreaDoc.h"
#include "Pro_HATA_AreaView.h"
#include "Pro_HATA_AreaFrm.h"

#include "Pro_HATA_NetFDoc.h"
#include "Pro_HATA_NetFView.h"
#include "Pro_HATA_NetFFrm.h"

#include "Pro_HATA_NetBDoc.h"
#include "Pro_HATA_NetBView.h"
#include "Pro_HATA_NetBFrm.h"

#include "IDWMMapDoc.h"
#include "IDWMMapView.h"
#include "IDWMMapFrm.h"

#include "StartDLG.h"

#include "SRVtableDoc.h"
#include "SRVtableView.h"
#include "SRVtableFrm.h"

#include "RGNtableDoc.h"
#include "RGNtableView.h"
#include "RGNtableFrm.h"

#include "Pro_P452_LinkDoc.h"
#include "Pro_P452_LinkView.h"
#include "Pro_P452_LinkFrm.h"

#include "Pro_P526_LinkDoc.h"
#include "Pro_P526_LinkView.h"
#include "Pro_P526_LinkFrm.h"

#include "Pro_Smooth_LinkDoc.h"
#include "Pro_Smooth_LinkView.h"
#include "Pro_Smooth_LinkFrm.h"

#include "Pro_P530_LinkDoc.h"
#include "Pro_P530_LinkView.h"
#include "Pro_P530_LinkFrm.h"

#include "Int_BC2BC_FreeDoc.h"
#include "Int_BC2BC_FreeView.h"
#include "Int_BC2BC_FreeFrm.h"

#include "Int_BT2BT_FreeDoc.h"
#include "Int_BT2BT_FreeView.h"
#include "Int_BT2BT_FreeFrm.h"

#include "MyDocManager.h"
#include "MyMultiDocTemplate.h"
#include <io.h>

#include "CountrySelectionDLG.h"

#include "FileDLG_ChangedType.h"

//#include <Windows.h>
#include <Winspool.h>

#include "VectorHandlingDoc.h"
#include "VectorHandlingView.h"
#include "VectorHandlingFrm.h"

#include "Pro_P1812_AreaDoc.h"
#include "Pro_P1812_AreaView.h"
#include "Pro_P1812_AreaFrm.h"

#include "Pro_P1812_LineDoc.h"
#include "Pro_P1812_LineView.h"
#include "Pro_P1812_LineFrm.h"

#include "Pro_P1812_PolygonDoc.h"
#include "Pro_P1812_PolygonView.h"
#include "Pro_P1812_PolygonFrm.h"

#include "Pro_P1812_LinkDoc.h"
#include "Pro_P1812_LinkView.h"
#include "Pro_P1812_LinkFrm.h"

#include "Pro_P1812_NetFDoc.h"
#include "Pro_P1812_NetFView.h"
#include "Pro_P1812_NetFFrm.h"

#include "Pro_P1812_NetBDoc.h"
#include "Pro_P1812_NetBView.h"
#include "Pro_P1812_NetBFrm.h"

#include "Pro_P526V14_LinkDoc.h"
#include "Pro_P526V14_LinkView.h"
#include "Pro_P526V14_LinkFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSMS4DCApp

BEGIN_MESSAGE_MAP(CSMS4DCApp, CWinApp)
	//{{AFX_MSG_MAP(CSMS4DCApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSMS4DCApp construction

CSMS4DCApp::CSMS4DCApp()
{
}

CSMS4DCApp::~CSMS4DCApp()
{
	m_Sel = NULL;
	delete [] m_Sel;

	m_pView = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSMS4DCApp object

CSMS4DCApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSMS4DCApp initialization

BOOL CSMS4DCApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif


//	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	SetRegistryKey(_T("ITU SMS4DC"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	m_pDocManager = new CMyDocManager ;
	CMyMultiDocTemplate* pDocTemplate;

//	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE

		IDR_SMS4DCTYPE,
		RUNTIME_CLASS(CSMS4DCDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CSMS4DCView));
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE1,
		RUNTIME_CLASS(CProfileDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CProfileView));
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE2,
		RUNTIME_CLASS(CPro_Free_LineDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CPro_Free_LineView));
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE3,
		RUNTIME_CLASS(CPro_Free_AreaDoc),
		RUNTIME_CLASS(CChildFrmArea), // custom MDI child frame
		RUNTIME_CLASS(CPro_Free_AreaView));
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE4,
		RUNTIME_CLASS(CProfilePolygonDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CProfilePolygonView));
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE5,
		RUNTIME_CLASS(CStationsTableDoc),
		RUNTIME_CLASS(CStationsTableFrm), // ???????????
		RUNTIME_CLASS(CStationsTableView));
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE6,
		RUNTIME_CLASS(CEffectiveHeigthDoc),
		RUNTIME_CLASS(CEffectiveHeigthFrm), // custom MDI child frame
		RUNTIME_CLASS(CEffectiveHeigthView));
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE7,
		RUNTIME_CLASS(CPro_Free_PolygonDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CPro_Free_PolygonView));
	AddDocTemplate(pDocTemplate);
	
	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE8,
		RUNTIME_CLASS(CPro_P370_AreaDoc),
		RUNTIME_CLASS(CPro_P370_AreaFrm), // custom MDI child frame
		RUNTIME_CLASS(CPro_P370_AreaView));
	AddDocTemplate(pDocTemplate);
	
	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE9,
		RUNTIME_CLASS(CPro_P1546_AreaDoc),
		RUNTIME_CLASS(CPro_P1546_AreaFrm), // custom MDI child frame
		RUNTIME_CLASS(CPro_P1546_AreaView));
	AddDocTemplate(pDocTemplate);
	
	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE10,
		RUNTIME_CLASS(CPro_LoS_AreaDoc),
		RUNTIME_CLASS(CPro_LoS_AreaFrm), // custom MDI child frame
		RUNTIME_CLASS(CPro_LoS_AreaView));
	AddDocTemplate(pDocTemplate);
	
	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE11,
		RUNTIME_CLASS(CPro_Free_NetFDoc),
		RUNTIME_CLASS(CPro_Free_NetFFrm), // custom MDI child frame
		RUNTIME_CLASS(CPro_Free_NetFView));
	AddDocTemplate(pDocTemplate);
	
	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE12,
		RUNTIME_CLASS(CPro_Free_NetBDoc),
		RUNTIME_CLASS(CPro_Free_NetBFrm), // custom MDI child frame
		RUNTIME_CLASS(CPro_Free_NetBView));
	AddDocTemplate(pDocTemplate);
		
	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE13,
		RUNTIME_CLASS(CPro_P370_NetFDoc),
		RUNTIME_CLASS(CPro_P370_NetFFrm), // custom MDI child frame
		RUNTIME_CLASS(CPro_P370_NetFView));
	AddDocTemplate(pDocTemplate);
	
	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE14,
		RUNTIME_CLASS(CPro_P370_NetBDoc),
		RUNTIME_CLASS(CPro_P370_NetBFrm), // custom MDI child frame
		RUNTIME_CLASS(CPro_P370_NetBView));
	AddDocTemplate(pDocTemplate);
	
	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE15,
		RUNTIME_CLASS(CPro_P1546_NetFDoc),
		RUNTIME_CLASS(CPro_P1546_NetFFrm), // custom MDI child frame
		RUNTIME_CLASS(CPro_P1546_NetFView));
	AddDocTemplate(pDocTemplate);
	
	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE16,
		RUNTIME_CLASS(CPro_P1546_NetBDoc),
		RUNTIME_CLASS(CPro_P1546_NetBFrm), // custom MDI child frame
		RUNTIME_CLASS(CPro_P1546_NetBView));
	AddDocTemplate(pDocTemplate);
	
	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE17,
		RUNTIME_CLASS(CAntennaFormDoc),
		RUNTIME_CLASS(CAntennaFormFrm), // custom MDI child frame
		RUNTIME_CLASS(CAntennaFormView));
	AddDocTemplate(pDocTemplate);
	
	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE18,
		RUNTIME_CLASS(CPro_P370_LineDoc),
		RUNTIME_CLASS(CPro_P370_LineFrm), // custom MDI child frame
		RUNTIME_CLASS(CPro_P370_LineView));
	AddDocTemplate(pDocTemplate);
	
	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE19,
		RUNTIME_CLASS(CPro_P1546_LineDoc),
		RUNTIME_CLASS(CPro_P1546_LineFrm), // custom MDI child frame
		RUNTIME_CLASS(CPro_P1546_LineView));
	AddDocTemplate(pDocTemplate);
	
	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE20,
		RUNTIME_CLASS(CPro_LoS_LineDoc),
		RUNTIME_CLASS(CPro_LoS_LineFrm), // custom MDI child frame
		RUNTIME_CLASS(CPro_LoS_LineView));
	AddDocTemplate(pDocTemplate);
	
	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE21,
		RUNTIME_CLASS(CAllocations_DrawDoc),
		RUNTIME_CLASS(CAllocations_DrawFrm), // custom MDI child frame
		RUNTIME_CLASS(CAllocations_DrawView));
	AddDocTemplate(pDocTemplate);
	
	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE22,
		RUNTIME_CLASS(CPro_P370_PolygonDoc),
		RUNTIME_CLASS(CPro_P370_PolygonFrm), // custom MDI child frame
		RUNTIME_CLASS(CPro_P370_PolygonView));
	AddDocTemplate(pDocTemplate);
	
	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE23,
		RUNTIME_CLASS(CPro_P1546_PolygonDoc),
		RUNTIME_CLASS(CPro_P1546_PolygonFrm), // custom MDI child frame
		RUNTIME_CLASS(CPro_P1546_PolygonView));
	AddDocTemplate(pDocTemplate);
	
	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE24,
		RUNTIME_CLASS(CPro_LoS_PolygonDoc),
		RUNTIME_CLASS(CPro_LoS_PolygonFrm), // custom MDI child frame
		RUNTIME_CLASS(CPro_LoS_PolygonView));
	AddDocTemplate(pDocTemplate);
	
	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE25,
		RUNTIME_CLASS(CAnt3DDoc),
		RUNTIME_CLASS(CAnt3DFrm), // custom MDI child frame
		RUNTIME_CLASS(CAnt3DView));
	AddDocTemplate(pDocTemplate);
	
	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE26,
		RUNTIME_CLASS(CArea3DDoc),
		RUNTIME_CLASS(CArea3DFrm), // custom MDI child frame
		RUNTIME_CLASS(CArea3DView));
	AddDocTemplate(pDocTemplate);
	
	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE27,
		RUNTIME_CLASS(CContour_DEMDoc),
		RUNTIME_CLASS(CContour_DEMFrm), // custom MDI child frame
		RUNTIME_CLASS(CContour_DEMView));
	AddDocTemplate(pDocTemplate);
	
	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE28,
		RUNTIME_CLASS(CPro_P370_LinkDoc),
		RUNTIME_CLASS(CPro_P370_LinkFrm), // custom MDI child frame
		RUNTIME_CLASS(CPro_P370_LinkView));
	AddDocTemplate(pDocTemplate);
	
	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE29,
		RUNTIME_CLASS(CPro_P1546_LinkDoc),
		RUNTIME_CLASS(CPro_P1546_LinkFrm), // custom MDI child frame
		RUNTIME_CLASS(CPro_P1546_LinkView));
	AddDocTemplate(pDocTemplate);
	
	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE30,
		RUNTIME_CLASS(CMainMapDoc),
		RUNTIME_CLASS(CMainMapFrm), // ???????????????
		RUNTIME_CLASS(CMainMapView));
	AddDocTemplate(pDocTemplate);
	
	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE31,
		RUNTIME_CLASS(CPro_HATA_AreaDoc),
		RUNTIME_CLASS(CPro_HATA_AreaFrm), // custom MDI child frame
		RUNTIME_CLASS(CPro_HATA_AreaView));
	AddDocTemplate(pDocTemplate);
	
	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE32,
		RUNTIME_CLASS(CPro_HATA_NetFDoc),
		RUNTIME_CLASS(CPro_HATA_NetFFrm), // custom MDI child frame
		RUNTIME_CLASS(CPro_HATA_NetFView));
	AddDocTemplate(pDocTemplate);
	
	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE33,
		RUNTIME_CLASS(CPro_HATA_NetBDoc),
		RUNTIME_CLASS(CPro_HATA_NetBFrm), // custom MDI child frame
		RUNTIME_CLASS(CPro_HATA_NetBView));
	AddDocTemplate(pDocTemplate);
	
	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE34,
		RUNTIME_CLASS(CIDWMMapDoc),
		RUNTIME_CLASS(CIDWMMapFrm), // custom MDI child frame
		RUNTIME_CLASS(CIDWMMapView));
	AddDocTemplate(pDocTemplate);
	
	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE35,
		RUNTIME_CLASS(CSRVtableDoc),
		RUNTIME_CLASS(CSRVtableFrm), // custom MDI child frame
		RUNTIME_CLASS(CSRVtableView));
	AddDocTemplate(pDocTemplate);
	
	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE36,
		RUNTIME_CLASS(CRGNtableDoc),
		RUNTIME_CLASS(CRGNtableFrm), // custom MDI child frame
		RUNTIME_CLASS(CRGNtableView));
	AddDocTemplate(pDocTemplate);
	
	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE38,
		RUNTIME_CLASS(CPro_P452_LinkDoc),
		RUNTIME_CLASS(CPro_P452_LinkFrm), // custom MDI child frame
		RUNTIME_CLASS(CPro_P452_LinkView));
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE39,
		RUNTIME_CLASS(CPro_P526_LinkDoc),
		RUNTIME_CLASS(CPro_P526_LinkFrm), // custom MDI child frame
		RUNTIME_CLASS(CPro_P526_LinkView));
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE40,
		RUNTIME_CLASS(CPro_Smooth_LinkDoc),
		RUNTIME_CLASS(CPro_Smooth_LinkFrm), // custom MDI child frame
		RUNTIME_CLASS(CPro_Smooth_LinkView));
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE41,
		RUNTIME_CLASS(CPro_P530_LinkDoc),
		RUNTIME_CLASS(CPro_P530_LinkFrm), // custom MDI child frame
		RUNTIME_CLASS(CPro_P530_LinkView));
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE42,
		RUNTIME_CLASS(CInt_BC2BC_FreeDoc),
		RUNTIME_CLASS(CInt_BC2BC_FreeFrm), // custom MDI child frame
		RUNTIME_CLASS(CInt_BC2BC_FreeView));
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE43,
		RUNTIME_CLASS(CInt_BT2BT_FreeDoc),
		RUNTIME_CLASS(CInt_BT2BT_FreeFrm), // custom MDI child frame
		RUNTIME_CLASS(CInt_BT2BT_FreeView));
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE44,
		RUNTIME_CLASS(CVectorHandlingDoc),
		RUNTIME_CLASS(CVectorHandlingFrm), // custom MDI child frame
		RUNTIME_CLASS(CVectorHandlingView));
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE45,
		RUNTIME_CLASS(CPro_P1812_AreaDoc),
		RUNTIME_CLASS(CPro_P1812_AreaFrm), // custom MDI child frame CMDIChildWnd
		RUNTIME_CLASS(CPro_P1812_AreaView));
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE46,
		RUNTIME_CLASS(CPro_P1812_LineDoc),
		RUNTIME_CLASS(CPro_P1812_LineFrm), // custom MDI child frame  CMDIChildWnd
		RUNTIME_CLASS(CPro_P1812_LineView));
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE47,
		RUNTIME_CLASS(CPro_P1812_PolygonDoc),
		RUNTIME_CLASS(CPro_P1812_PolygonFrm), // custom MDI child frame CMDIChildWnd
		RUNTIME_CLASS(CPro_P1812_PolygonView));
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE48,
		RUNTIME_CLASS(CPro_P1812_LinkDoc),
		RUNTIME_CLASS(CPro_P1812_LinkFrm), // custom MDI child frame
		RUNTIME_CLASS(CPro_P1812_LinkView));
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE49,
		RUNTIME_CLASS(CPro_P1812_NetFDoc),
		RUNTIME_CLASS(CPro_P1812_NetFFrm), // custom MDI child frame
		RUNTIME_CLASS(CPro_P1812_NetFView));
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE50,
		RUNTIME_CLASS(CPro_P1812_NetBDoc),
		RUNTIME_CLASS(CPro_P1812_NetBFrm), // custom MDI child frame
		RUNTIME_CLASS(CPro_P1812_NetBView));
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMyMultiDocTemplate(
		theApp.m_hInstance, // the apps HINTANCE
		IDR_SMS4DCTYPE51,
		RUNTIME_CLASS(CPro_P526V14_LinkDoc),
		RUNTIME_CLASS(CPro_P526V14_LinkFrm), // custom MDI child frame
		RUNTIME_CLASS(CPro_P526V14_LinkView));
	AddDocTemplate(pDocTemplate);

	LoadDLLs() ;
	RegisterDocTemplates() ;
 
	//////////////////////DATA BASE PATH//////////////////////////////////////
//	m_CDataBaseSTR = _T("select * from STtable order by IDst;");
	m_CDataBaseSTR.Format(_T("select * from %s order by IDst;") , Query_STtable() );

	CString PWD = _T(";ekardletoh");	PWD.MakeReverse();
	m_CDBSTR = _T("ODBC;DSN=SMS_NEW;PWD=") + PWD;

	m_UserName = _T("SMS4DC");
//	m_Lang = _T("En");
//	m_Lang = _T("Fr");
	m_UserLevel = 3;
	
	m_pView = NULL;

	////////////////////////Path Application////////////////////////////////////
	m_AppPath = GetCommandLine();
	int zz = m_AppPath.ReverseFind('\\');
	m_AppPath.Delete(zz,m_AppPath.GetLength()-zz);
	zz = m_AppPath.ReverseFind('\\')+1;
	m_AppPath.Delete(zz,m_AppPath.GetLength()-zz);
	m_AppPath.Delete(0);
	///////////////////////////////////////////////////////////////////////////

	CStartDLG xx;
	if (xx.DoModal()==IDOK)
	{
		m_UserName = xx.m_UserName;

		TileX= 46;     TileY = 25;
		////////////////////////Path Application////////////////////////////////////
//		m_AppPath = GetCommandLine();
//		int zz = m_AppPath.ReverseFind('\\');
//		m_AppPath.Delete(zz,m_AppPath.GetLength()-zz);
//		zz = m_AppPath.ReverseFind('\\')+1;
//		m_AppPath.Delete(zz,m_AppPath.GetLength()-zz);
//		m_AppPath.Delete(0);
		///////////////////////////////////////////////////////////////////////////
		ctryQ();

		// create main MDI Frame window
		CMainFrame* pMainFrame = new CMainFrame;
		if (!pMainFrame->LoadFrame(IDR_MAINFRAME))		return FALSE;
		m_pMainWnd = pMainFrame;

		// Parse command line for standard shell commands, DDE, file open
		CCommandLineInfo cmdInfo;
		ParseCommandLine(cmdInfo);

		// Dispatch commands specified on the command line
		if (!ProcessShellCommand(cmdInfo))	return FALSE;

		// The main window has been initialized, so show and update it.
		pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
		//pMainFrame->ShowWindow(m_nCmdShow);
		pMainFrame->UpdateWindow();
	}

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));}; //950505
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	
//	SetDlgItemText(IDC_STATICb1,_Z("Version")+(" 5.1"));			//950505
//	SetDlgItemText(IDC_STATICb4,_Z("Copyright © ITU")+(" 2016"));	//950505

	SetDlgItemText(IDC_STATICb1,_Z("Version")+(" 5.2"));			//970710
//	SetDlgItemText(IDC_STATICb4,_Z("Copyright © ITU")+(" 2018"));	//970710
//	SetDlgItemText(IDC_STATICb4,_Z("Copyright © ITU")+(" 2019"));	//970722
//	SetDlgItemText(IDC_STATICb4,_Z("Copyright © ITU")+(" 2020"));	//990431
	SetDlgItemText(IDC_STATICb4,_Z("Copyright © ITU")+(" 2021"));	//990431

	return TRUE;
}

// App command to run the dialog
void CSMS4DCApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CSMS4DCApp message handlers

BOOL CSMS4DCApp::OpenNewDocument(const CString& strTarget)
{
	CString strDocName;
	CDocTemplate* pSelectedTemplate;
	POSITION pos = GetFirstDocTemplatePosition();
	while (pos != NULL)
	{
		pSelectedTemplate = (CDocTemplate*) GetNextDocTemplate(pos);
		ASSERT(pSelectedTemplate != NULL);
		ASSERT(pSelectedTemplate->IsKindOf(RUNTIME_CLASS(CDocTemplate)));
		pSelectedTemplate->GetDocString(strDocName, CDocTemplate::docName);
		if (strDocName == strTarget)
		{ 
			pSelectedTemplate->OpenDocumentFile(NULL);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CSMS4DCApp::OnFileNew()
{
	if((m_UserLevel==1)||(m_UserLevel==5))
		OpenNewDocument(_T("Administrative data"));
	else
	{
	//	OpenNewDocument(_T("Main Desktop"));
		OpenNewDocument(_T("IDWM Map"));
	}
	return TRUE;
}




void CSMS4DCApp::SetLandscape()
{
    // Get default printer settings.
    PRINTDLG   pd;

    pd.lStructSize = (DWORD) sizeof(PRINTDLG);
    if (GetPrinterDeviceDefaults(&pd))
	{
		// Lock memory handle.
		DEVMODE FAR* pDevMode =  (DEVMODE FAR*)::GlobalLock(m_hDevMode);
		LPDEVNAMES lpDevNames;
		LPTSTR lpszDriverName, lpszDeviceName, lpszPortName;
		HANDLE hPrinter;

		if (pDevMode)
		{
			// Change printer settings in here.
			pDevMode->dmOrientation = DMORIENT_LANDSCAPE;
			// Unlock memory handle.
			lpDevNames = (LPDEVNAMES)GlobalLock(pd.hDevNames);
			lpszDriverName = (LPTSTR )lpDevNames + lpDevNames->wDriverOffset;
			lpszDeviceName = (LPTSTR )lpDevNames + lpDevNames->wDeviceOffset;
			lpszPortName   = (LPTSTR )lpDevNames + lpDevNames->wOutputOffset;

			::OpenPrinter(lpszDeviceName, &hPrinter, NULL);
			::DocumentProperties(NULL,hPrinter,lpszDeviceName,pDevMode, pDevMode, DM_IN_BUFFER|DM_OUT_BUFFER);

			// Sync the pDevMode.
			// See SDK help for DocumentProperties for more info.
			::ClosePrinter(hPrinter);
			::GlobalUnlock(m_hDevNames);
			::GlobalUnlock(m_hDevMode);
		}
	}
} 


int CSMS4DCApp::ExitInstance() 
{
	// delete doc manager before unloading dll's
	delete (CMyDocManager*)m_pDocManager ;
	m_pDocManager = NULL ;
	// from this point you can unload your DLL's
	// doing so before here will cause problems 
	if (m_number_of_dlls > 0)
	{
		// free the DLL's
		delete []m_LoadedDLLs ;
		m_LoadedDLLs = NULL ;
		m_number_of_dlls = 0 ;
	}
	return CWinApp::ExitInstance();
}

// this function looks for any DLL's in the same directory as the EXE and trys to load them
// if they export the correct function, then they will be loaded, and DocumentTemplates added
int CSMS4DCApp::LoadDLLs() 
{
	CString    command_line ;
	command_line = GetCommandLine() ;   // so we know ehere to look for DLL's
	command_line = command_line.Left(command_line.Find("SMS4DC.exe")) ; // lose exe name
	command_line = command_line.Right(command_line.GetLength() - 1) ;   // lose leading " 
/*
	long    hFile   = 0L;
	struct _finddata_t c_file;
	DLLwrapper   tmpDLL;     // for checking of functions
	CString    SearchPath  = _T("");
	CString    valid_filenames[100] ; // assumes max 100 DLL's!!!!!! 
	int     num_dlls = 0 ;

	SearchPath = command_line + _T("*.DLL");
	hFile = _findfirst(SearchPath, &c_file);
	if (hFile != -1L)
	{
		do
		{
			if (tmpDLL.LoadDLL(command_line + c_file.name  ))
			{
				// it loaded
				if (tmpDLL.DLLDocumentTemplate != NULL)
				{
					// exports correct function(s) 
					valid_filenames[num_dlls] = tmpDLL.m_filename ;
					num_dlls++ ;    // count valid DLL
				}
				tmpDLL.FreeDLL() ;   // release it
			}
		} while (_findnext(hFile, &c_file) == 0);
		_findclose(hFile) ; 
	}
	// we should now have a list of valid DLL's. Load them
	if (num_dlls > 0)
	{
		m_number_of_dlls = num_dlls ;
		m_LoadedDLLs = new DLLwrapper[m_number_of_dlls];
		for (num_dlls = 0 ; num_dlls < m_number_of_dlls ; num_dlls++) 
		m_LoadedDLLs[num_dlls].LoadDLL(valid_filenames[num_dlls]  ) ;
	}
*/
	m_number_of_dlls = 4 ;
	m_LoadedDLLs = new DLLwrapper[m_number_of_dlls];
	m_LoadedDLLs[0].LoadDLL(command_line + _T("Administrative.dll") , _T("DLLNewDocTemplate"));
	m_LoadedDLLs[1].LoadDLL(command_line + _T("ArgusWFdll.dll")		, _T("DLLargusDocTemplate"));
	m_LoadedDLLs[2].LoadDLL(command_line + _T("ThalesDrawDLL.dll")	, _T("DLLthalesDocTemplate"));
	m_LoadedDLLs[3].LoadDLL(command_line + _T("OthersWFdll.dll")	, _T("DLLothersDocTemplate"));
	return m_number_of_dlls ;   // return number loaded
}

int CSMS4DCApp::RegisterDocTemplates()
{
	// register doc templates from loaded DLL's
	int      num_registered = 0 ;
	CMyMultiDocTemplate* pTemplate = NULL ;

	for (int i = 0 ; i < m_number_of_dlls ; i++)
	{
		pTemplate = m_LoadedDLLs[i].DLLDocumentTemplate(); // get template pointer
		if (pTemplate != NULL)
		{
			// may not have exported a doc/view
			AddDocTemplate(pTemplate) ;
			pTemplate = NULL ;
			num_registered++ ;
		}
	}
	return num_registered ;
}


void CSMS4DCApp::ctryQ()
{
#ifdef _SMS4DC_TimeLimited_
	timeQ();
#endif

	CFileFind x1;
	CString ctryFile = m_AppPath + _T("\\Texts\\ctry.txt");
	BOOL cx1 = x1.FindFile(ctryFile);
	if(!cx1)
	{
		CCountrySelectionDLG CTYdlg;
		CTYdlg.m_code = "";

		do
		{
			while(CTYdlg.DoModal()!=IDOK);
			m_ctryLocal = CTYdlg.m_code;
		}
		while (m_ctryLocal.IsEmpty());

		FILE *fid;
		fid = fopen(ctryFile,"wt");
		fprintf( fid, "%s", m_ctryLocal);
		fclose(fid);
		
	}//if !cx1
	else
	{
		char buftemp[10];
		FILE *fid;
		fid = fopen(ctryFile,"rt");
		fscanf( fid, "%s", buftemp);
		m_ctryLocal = buftemp;
		if     (m_ctryLocal.GetLength()==1)			m_ctryLocal = m_ctryLocal + _T("  ");
		else if(m_ctryLocal.GetLength()==2)			m_ctryLocal = m_ctryLocal + _T(" ");
		fclose(fid);
	}
	x1.Close();
}


void CSMS4DCApp::timeQ()
{
//	CTime t1(2006,4,23,0,0,0),t2(2006,9,23,0,0,0) ,t3;		//Lao PDR
//	CTime t1(2006,4,30,0,0,0),t2(2006,5,13,0,0,0) ,t3;		//Tanzania
//	CTime t1(2007,8,9,0,0,0),t2(2008,1,1,0,0,0) ,t3;		//IRAN	PAT
//	CTime t1(2006,6,24,0,0,0),t2(2006,6,29,0,0,0) ,t3;		//Sudan
//	CTime t1(2007,11,26,0,0,0),t2(2007,12,8,0,0,0) ,t3;		//Yemen	
//	CTime t1(2007,12,17,0,0,0),t2(2007,12,20,0,0,0) ,t3;	//Geneva  FAT2	
//	CTime t1(2008,04,18,0,0,0),t2(2008,04,30,0,0,0) ,t3;	//Bangladesh
//	CTime t1(2008,11,16,0,0,0),t2(2008,11,28,0,0,0) ,t3;	//Lebanon
//	CTime t1(2009,10,24,0,0,0),t2(2009,11,07,0,0,0) ,t3;	//Jordan	
//	CTime t1(2010,02,01,0,0,0),t2(2010,05,01,0,0,0) ,t3;	//THALES	
//	CTime t1(2010,04,01,0,0,0),t2(2011,04,01,0,0,0) ,t3;	//R&S	
//	CTime t1(2010,04,01,0,0,0),t2(2011,04,01,0,0,0) ,t3;	//THALES	new ver 890208 ersal	
//	CTime t1(2012,10,06,0,0,0),t2(2013,01,01,0,0,0) ,t3;	//Argentina	new ver 910715 ersal	
//	CTime t1(2013,04,01,0,0,0),t2(2013,06,15,0,0,0) ,t3;	//Nigeria	ver 4.1 920124 ersal	
//	CTime t1(2013,11,10,0,0,0),t2(2014,01,01,0,0,0) ,t3;	//Venezuela	ver 4.1 920821 ersal	
//	CTime t1(2014,5,14,0,0,0),t2(2014,8,31,0,0,0) ,t3;		//Vanuatu	ver 4.1 930224 ersal	
	CTime t1(2016,11,21,0,0,0),t2(2016,12,04,0,0,0) ,t3;	//Addis-Ababa ver 5.0 950901 ersal	

	t3 = CTime::GetCurrentTime();
	if((t3<t1)||(t3>t2))
		exit(1);
}

// IsWin2000
BOOL CSMS4DCApp::IsWin2000()
{
	OSVERSIONINFOEX osvi;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	BOOL bOsVersionInfoEx = GetVersionEx((OSVERSIONINFO *) &osvi);
	if (!bOsVersionInfoEx)
	{
		// If OSVERSIONINFOEX doesn't work, try OSVERSIONINFO.
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		if (!GetVersionEx((OSVERSIONINFO *) &osvi))
			return FALSE;
	}

	switch (osvi.dwPlatformId)
	{
		case VER_PLATFORM_WIN32_NT:
			if (osvi.dwMajorVersion >= 5)
				return TRUE;
			break;
	}
	return FALSE;
}

BOOL CSMS4DCApp::PeekAndPump()
{
	static MSG msg;
	while (::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE))
	{
		if (!AfxGetApp()->PumpMessage())
		{
			::PostQuitMessage(0);
			return FALSE;
		}	
	}
	return TRUE;
}
/////////941016///////////////////////////////////////
void CSMS4DCApp::CDCToBmp24(CDC *pDC, CString fileOUT)
{
	BYTE BitsPerPixel = 24;
	CRect rect;
	CWnd *pWnd = pDC->GetWindow();
	pWnd->GetClientRect(&rect);
	long nW = rect.Width(), nH = rect.Height();

//++++++++++++++++++++++++++++++++++++++++
	CBitmap bmp,*pOldBmp;
	CDC memdc;	memdc.CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC, nW, nH);
	pOldBmp = memdc.SelectObject(&bmp);
	memdc.BitBlt(0,0, nW, nH, pDC,0,0,SRCCOPY);
//++++++++++++++++++++++++++++++++++++++++

	BYTE BytesPerPixel =  BitsPerPixel/8;
	int widthDW = (((nW * BitsPerPixel) + 31) / 32 * 4);
	int sz = widthDW * nH;

	BITMAPFILEHEADER bfh;
	bfh.bfType = ('M'<<8)+'B'; 
	bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER); 
	bfh.bfSize = sz + bfh.bfOffBits; 
	bfh.bfReserved1 = 0; 
	bfh.bfReserved2 = 0; 

	BITMAPINFO Bmi;
	memset(&Bmi,0,sizeof(BITMAPINFO));
	Bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	Bmi.bmiHeader.biWidth = nW;
	Bmi.bmiHeader.biHeight = nH;
	Bmi.bmiHeader.biPlanes = 1;
	Bmi.bmiHeader.biBitCount = BitsPerPixel; 
	Bmi.bmiHeader.biCompression = BI_RGB;		// no compression
	Bmi.bmiHeader.biSizeImage = 0; 

	FILE* fp = fopen (fileOUT,"wb");
	if(fp != 0)
	{
		BYTE* outBuf = new BYTE[BytesPerPixel*nW*nH];
		fwrite(&bfh,sizeof(bfh),1,fp);
		fwrite(&Bmi.bmiHeader,sizeof(BITMAPINFOHEADER),1,fp);

		long offset, data1, row, rowOffset, row_size = nW * BytesPerPixel;
		for ( row=0; row<nH; row++)
		{
			rowOffset = row * row_size;						      
			for (long col=0; col<nW; col++)
			{
//++++++++++++++++++++++++++++++++++++++++
				data1 = memdc.GetPixel(col,row);
//++++++++++++++++++++++++++++++++++++++++
//				data1 = pDC->GetPixel(col,row);
				offset = col * BytesPerPixel;
				*(outBuf + rowOffset + offset + 0) = GetBValue(data1);
				*(outBuf + rowOffset + offset + 1) = GetGValue(data1);
				*(outBuf + rowOffset + offset + 2) = GetRValue(data1);
//				if(BitsPerPixel==32)	*(outBuf + rowOffset + offset + 3) = 200;
			}
		}
//++++++++++++++++++++++++++++++++++++++++
		memdc.SelectObject(pOldBmp);
//++++++++++++++++++++++++++++++++++++++++
		char dummy;
		for( row=(nH-1); row>=0; row--)
		{
			rowOffset = row*row_size;						      
			fwrite( (void *)(outBuf+rowOffset) , row_size , 1 , fp);
			for (int count=row_size; count<widthDW; count++)
			{
				dummy = 0;
				fwrite( &dummy , 1 , 1 , fp);							  
			}
		}
		delete [] outBuf;
	}
	fclose(fp);
}
/*
void CSMS4DCApp::CDCToBmp24(CDC *pDC, CString fileOUT)
{
	CRect rect;
	CWnd *pWnd = pDC->GetWindow();
	pWnd->GetClientRect(&rect);

	long iW = rect.Width();
	long jH = rect.Height();

	unsigned short BitsPixel = 24;
	int widthDW = (((iW * BitsPixel) + 31) / 32 * 4);
	int sz = widthDW * jH;

	BITMAPFILEHEADER bfh;
	bfh.bfType = ('M'<<8)+'B'; 
	bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER); 
	bfh.bfSize = sz + bfh.bfOffBits; 
	bfh.bfReserved1 = 0; 
	bfh.bfReserved2 = 0; 

	BITMAPINFO Bmi;
	memset(&Bmi,0,sizeof(BITMAPINFO));
	Bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	Bmi.bmiHeader.biWidth = iW;
	Bmi.bmiHeader.biHeight = jH;
	Bmi.bmiHeader.biPlanes = 1;
	Bmi.bmiHeader.biBitCount = BitsPixel; 
	Bmi.bmiHeader.biCompression = BI_RGB;		// no compression
	Bmi.bmiHeader.biSizeImage = 0; 

	FILE* fp = fopen (fileOUT,"wb");
	if(fp != 0)
	{
		BYTE* outBuf = new BYTE[3*iW*jH];
		fwrite(&bfh,sizeof(bfh),1,fp);
		fwrite(&Bmi.bmiHeader,sizeof(BITMAPINFOHEADER),1,fp);

		long offset, data1, row, rowOffset, row_size = iW * 3;
		for ( row=0; row<jH; row++)
		{
			rowOffset = row * row_size;						      
			for (long col=0; col<iW; col++)
			{
				data1 = pDC->GetPixel(col,row);
				offset = col * 3;
				*(outBuf + rowOffset + offset + 0) = GetBValue(data1);
				*(outBuf + rowOffset + offset + 1) = GetGValue(data1);
				*(outBuf + rowOffset + offset + 2) = GetRValue(data1);
			}
		}

		char dummy;
		for( row=(jH-1); row>=0; row--)
		{
			rowOffset = row*row_size;						      
			fwrite( (void  *)(outBuf+rowOffset) , row_size , 1 , fp);
			for (DWORD count=row_size; count<widthDW; count++)
			{
				dummy = 0;
				fwrite( &dummy , 1 , 1 , fp);							  
			}
		}
		delete [] outBuf;
	}
	fclose(fp);
}
*/

BOOL CSMS4DCApp::VectorFileName(CString *sFile,CString *sPath, BOOL flag, CString sDefault) 
{
/*
	CFileDlg FileDLG(true, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "*.txt|*.vec|*.ant", NULL );
	if (FileDLG.DoModal() == IDOK)
	{
		*sPath=FileDLG.m_Path;
		*sFile=FileDLG.m_FName;
		return true;
	}
	return false;
*/
//	char strFilter[] = {"SMS4DC Vectors (*.txt)|*.txt|All Files (*.*)|*.*||"};
	CString strFilter = _Z("SMS4DC Vectors") +" (*.txt)|*.txt|"+ _Z("All Files") +" (*.*)|*.*||";

	CFileDialog FileDLG(flag, ".txt", sDefault, OFN_HIDEREADONLY  , strFilter);
	if (IsWin2000())	FileDLG.m_ofn.lStructSize = 88;		//76
	if (FileDLG.DoModal() == IDOK)
	{
		*sPath = FileDLG.GetPathName();
		*sFile = FileDLG.GetFileName();
		return true;
	}
	return false;
}

BOOL CSMS4DCApp::KmlSave(CString *sFile,CString *sPath,BOOL *flagShow, CString sDefault) 
{
/*
	CFileDlg FileDLG(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "*.kml", NULL );
	if (FileDLG.DoModal() == IDOK)
	{
		*sPath = FileDLG.m_Path;		*sFile = FileDLG.m_FName;
		return true;
	}
	return false;
*/
//	char strFilter[] = {"Google Files(*.kml)|*.kml||"};
	CString strFilter = _Z("Google Files") +"(*.kml)|*.kml||";

	CFileDLG_ChangedType FileDLG(FALSE, ".kml", sDefault, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT , strFilter);
	if (IsWin2000())		FileDLG.m_ofn.lStructSize = 88;		//76
	if (FileDLG.DoModal() == IDOK)
	{
		*sPath = FileDLG.GetPathName();
		*sFile = FileDLG.GetFileName();
		*flagShow = FileDLG.m_ShowFlag;
		return true;
	}
	return false;
}


CString CSMS4DCApp::VectorFileNameSave(CString FileNameNL) 
{
	CString sPath = _T("");
	if(FileNameNL.GetLength()>0)
	{
		CString sFile;
		if( VectorFileName( &sFile, &sPath , FALSE, FileNameNL) )
		{
			if(FileNameNL.Compare(sPath))
			{
				TRY	{ CFile::Remove(sPath);}
				CATCH( CFileException, e ){}
				END_CATCH

				CFile::Rename( FileNameNL, sPath );
			}
		}
	}
	return sPath;
}

CString CSMS4DCApp::SaveDesktop(CDC *pDC, CString FileName) 
{
	CString fileOUTtmp = m_AppPath + _T("Temp\\") + FileName + _T(".tmp");
	CDCToBmp24(pDC, fileOUTtmp);
	
	CString fileOUTbmp = m_AppPath + _T("Reports\\") + FileName + _T(".bmp");
//	char strFilter[] = {"Bitmap File (*.bmp)|*.bmp||"};
	CString strFilter = _Z("Bitmap File") + " (*.bmp)|*.bmp||";

	CFileDialog FileDLG(FALSE, ".bmp", fileOUTbmp, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
	if (IsWin2000())		FileDLG.m_ofn.lStructSize = 88;		//76
	if (FileDLG.DoModal() == IDOK)
	{
		fileOUTbmp = FileDLG.GetPathName();

		TRY{CFile::Remove( fileOUTbmp );}
		CATCH( CFileException, e )	   {}
		END_CATCH
		CFile::Rename(fileOUTtmp, fileOUTbmp);
/*
		SHELLEXECUTEINFO ShExecInfo;
		ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
		ShExecInfo.fMask = NULL;
		ShExecInfo.hwnd = m_hWnd;
		ShExecInfo.lpVerb = NULL;
		ShExecInfo.lpFile = fileOUTbmp;
		ShExecInfo.lpParameters = NULL;
		ShExecInfo.lpDirectory = NULL;
		ShExecInfo.nShow = SW_SHOWNORMAL;
		ShExecInfo.hInstApp = NULL;
		ShellExecuteEx(&ShExecInfo);
*/
		return fileOUTbmp;
	}
	else
	{
		TRY{CFile::Remove( fileOUTtmp );}
		CATCH( CFileException, e )     {}
		END_CATCH

		return "";
	}	
	return "";
}

CString CSMS4DCApp::Query_STtable() 
{
	CString str1,str2,str3,str4,str5,str6,str41,str51,str61,str7,str8,str9,str10,str11,str12,str13;	//1400/04/12
	//Query STtable
	str1 = _T(" ( SELECT Frequency.freqid AS IDst, SiteName AS STname, Geolat AS STlat_deg, Geolon AS STlon_deg, AntHeightAGL AS Sth_agl, frequency/1000000 AS TXfreq, iif(left(radPowerType,1)='E',RadPwr*1.65,iif(left(radPowerType,1)='V',RadPwr*3,RadPwr)) AS Power_eirp, Azimuth, Elevation, Gain AS ANTgain, BeamWidthH AS BWh, BeamWidthV AS BWv, Pol AS Polarization, AntName AS Antenna, InsLoss AS InsertionLoss, Sensitivity AS RxSensitivity, 1 as Srv,ClassStation AS STTP, EmDes AS Emission, Antenna.AntID ,respfreq/1000000 as  RXfreq,radius,NoiseFactor,HeightASL  AS Sth_asl,station.country as ctry ");
	str2 = _T(" FROM station, equipment, eqcat, antenna, antcat, frequency ");
	str3 = _T(" WHERE station.stid=equipment.stid and equipment.eqcatid=eqcat.eqcatid and equipment.eqid=antenna.eqid and antenna.antcatid=antcat.antcatid and equipment.eqid=frequency.eqid and ClassOfAnt<>'R'  and classstation='FX'  ");
	
	str4 = _T(" union all SELECT Frequency.freqid AS IDst, SiteName AS STname, Geolat AS STlat_deg, Geolon AS STlon_deg, AntHeightAGL AS Sth_agl, frequency/1000000 AS TXfreq, iif(left(radPowerType,1)='E',RadPwr*1.65,iif(left(radPowerType,1)='V',RadPwr*3,RadPwr)) AS Power_eirp, Azimuth, Elevation, Gain AS ANTgain, BeamWidthH AS BWh, BeamWidthV AS BWv, Pol AS Polarization, AntName AS Antenna, InsLoss AS InsertionLoss, Sensitivity AS RxSensitivity, 2 as Srv,ClassStation AS STTP, EmDes AS Emission, Antenna.AntID ,respfreq/1000000 as  RXfreq,radius,NoiseFactor,HeightASL  AS Sth_asll,station.country as ctry ");
	str5 = _T(" FROM station, equipment, eqcat, antenna, antcat, frequency ");
	str6 = _T(" WHERE station.stid=equipment.stid and equipment.eqcatid=eqcat.eqcatid and equipment.eqid=antenna.eqid and antenna.antcatid=antcat.antcatid and equipment.eqid=frequency.eqid and ClassOfAnt<>'R' and classstation='FB' ");

//1400/04/12
str41 = _T(" union all SELECT Frequency.freqid AS IDst, SiteName AS STname, Geolat AS STlat_deg, Geolon AS STlon_deg, AntHeightAGL AS Sth_agl, frequency/1000000 AS TXfreq, iif(left(radPowerType,1)='E',RadPwr*1.65,iif(left(radPowerType,1)='V',RadPwr*3,RadPwr)) AS Power_eirp, Azimuth, Elevation, Gain AS ANTgain, BeamWidthH AS BWh, BeamWidthV AS BWv, Pol AS Polarization, AntName AS Antenna, InsLoss AS InsertionLoss, Sensitivity AS RxSensitivity, 2 as Srv,ClassStation AS STTP, EmDes AS Emission, Antenna.AntID ,respfreq/1000000 as  RXfreq,radius,NoiseFactor,HeightASL  AS Sth_asll,station.country as ctry ");
str51 = _T(" FROM station, equipment, eqcat, antenna, antcat, frequency ");
str61 = _T(" WHERE station.stid=equipment.stid and equipment.eqcatid=eqcat.eqcatid and equipment.eqid=antenna.eqid and antenna.antcatid=antcat.antcatid and equipment.eqid=frequency.eqid and ClassOfAnt<>'R' and classstation='__' ");
	
	str7 = _T(" union all SELECT Frequency.freqid AS IDst, SiteName AS STname, Geolat AS STlat_deg, Geolon AS STlon_deg, AntHeightAGL AS Sth_agl, frequency/1000000 AS TXfreq, iif(left(radPowerType,1)='E',RadPwr*1.65,iif(left(radPowerType,1)='V',RadPwr*3,RadPwr)) AS Power_eirp, Azimuth, Elevation, Gain AS ANTgain, BeamWidthH AS BWh, BeamWidthV AS BWv, Pol AS Polarization, AntName AS Antenna, InsLoss AS InsertionLoss, Sensitivity AS RxSensitivity, 3 as Srv,ClassStation AS STTP,  EmDes  AS Emission, Antenna.AntID ,respfreq/1000000 as  RXfreq,radius,NoiseFactor,HeightASL  AS Sth_asll,BCstation.country as ctry ");
	str8 = _T(" FROM bcstation, equipment, eqcat, antenna, antcat, frequency ");
	str9 = _T(" WHERE bcstation.stid=equipment.bcid and equipment.eqcatid=eqcat.eqcatid and equipment.eqid=antenna.eqid and antenna.antcatid=antcat.antcatid and equipment.eqid=frequency.eqid  ");
	
	str10 = _T(" UNION ALL SELECT Frequency.freqid AS IDst, MobName AS STname, Geolat AS STlat_deg, Geolon AS STlon_deg, AntHeightAGL AS Sth_agl, frequency/1000000 AS TXfreq, iif(left(radPowerType,1)='E',RadPwr*1.65,iif(left(radPowerType,1)='V',RadPwr*3,RadPwr)) AS Power_eirp, Azimuth, Elevation, Gain AS ANTgain, BeamWidthH AS BWh, BeamWidthV AS BWv, Pol AS Polarization, AntName AS Antenna, InsLoss AS InsertionLoss, Sensitivity AS RxSensitivity, 2  as Srv,ClassStation AS STTP,  EmDes  AS Emission, Antenna.AntID ,respfreq/1000000 as  RXfreq,radius,NoiseFactor,3 as Sth_asll,Mobiles.country as ctry ");
	str11 = _T(" FROM mobiles, equipment, eqcat, antenna, antcat, frequency ");
	str12 = _T(" WHERE mobiles.mobid=equipment.mobid and equipment.eqcatid=eqcat.eqcatid and equipment.eqid=antenna.eqid and antenna.antcatid=antcat.antcatid and equipment.eqid=frequency.eqid ");
	
	str13 = _T(" ) as STtable ");
	CString qSTtable = str1+str2+str3+str4+str5+str6+str41+str51+str61+str7+str8+str9+str10+str11+str12+str13; //1400/04/12
	return qSTtable;
}



/////////////////////////////Language////////////////////////////
#define APSTUDIO_INVOKED
#include "resource.h"
void CSMS4DCApp::TranslateDialog(CDialog *pDialog)
{
	CString strOriginal(_T(""));
	for (int iID = 0; iID < _APS_NEXT_CONTROL_VALUE; iID++)
	{
		pDialog->GetDlgItemText(iID, strOriginal);
		if (!strOriginal.IsEmpty())
		{
			if(((pDialog->GetDlgItem(iID))->IsKindOf(RUNTIME_CLASS(CComboBox)))!=1)
			{
				CString s = GetTranslatedString(strOriginal);
				if (!s.IsEmpty() && strOriginal != s)
					pDialog->SetDlgItemText(iID, s);
			}
		}
	}//for
	strOriginal = _T("");
	pDialog->GetWindowText(strOriginal);
	if (!strOriginal.IsEmpty())
	{
		CString s = GetTranslatedString(strOriginal);
		if (!s.IsEmpty() && strOriginal != s)
			pDialog->SetWindowText(s);
	}
}

void CSMS4DCApp::TranslateMenu(CMenu *pMenu)
{
    CString strOriginal(_T(""));
	CString strTranslated(_T(""));
	WORD wMenuState;

	if (pMenu == NULL || !::IsMenu(pMenu->m_hMenu))		return;

	int iSize = pMenu->GetMenuItemCount();
    // loop all the menu items in this level
	MENUITEMINFO menuItemInfo;
    for (int i=0; i<iSize; i++)
    {
		wMenuState = (WORD) pMenu->GetMenuState(i, MF_BYPOSITION);
		BOOL bIsPopup = wMenuState & MF_POPUP;

//970904
BOOL bIsGrayed = wMenuState & MF_GRAYED;

        // Get the menu string
        //pMenu->GetMenuString(i, strOriginal, MF_BYPOSITION);
		ZeroMemory(&menuItemInfo, sizeof(MENUITEMINFO));
		menuItemInfo.cbSize = sizeof(MENUITEMINFO);
		menuItemInfo.fMask = MIIM_TYPE;
		pMenu->GetMenuItemInfo(i, &menuItemInfo, TRUE);
		if (menuItemInfo.cch > 0)
		{
			menuItemInfo.cch++;
			menuItemInfo.dwTypeData = new char [menuItemInfo.cch];
			pMenu->GetMenuItemInfo(i, &menuItemInfo, TRUE);
			strOriginal = CString(menuItemInfo.dwTypeData);
			delete [] menuItemInfo.dwTypeData;
			menuItemInfo.dwTypeData = NULL;
		}
		else	strOriginal = _T("");

		if (!strOriginal.IsEmpty())
		{
			strTranslated = GetTranslatedString(strOriginal);
			if (!strTranslated.IsEmpty() && strTranslated != strOriginal)
			{
				UINT uiID = 0;
				UINT uiFlags = MF_STRING | MF_BYPOSITION;

//970904
if (bIsGrayed)	uiFlags = uiFlags | MF_GRAYED;

				uiID = pMenu->GetMenuItemID(i);
				if (bIsPopup)
				{
					uiFlags |= MF_POPUP;
					HMENU hPopupMenu = pMenu->GetSubMenu(i)->m_hMenu;
					pMenu->ModifyMenu(i, uiFlags, (UINT)hPopupMenu, strTranslated);
				}
				else	pMenu->ModifyMenu(i, uiFlags, uiID, strTranslated);
			}
		}
		if (bIsPopup)
		{
			CMenu *pSubMenu = pMenu->GetSubMenu(i);
			if (pSubMenu != NULL && ::IsMenu(pSubMenu->m_hMenu))	TranslateMenu(pSubMenu);
		}
    }//for
}


CString CSMS4DCApp::GetTranslatedString(CString strOriginal)
{
	if(m_Lang==_T("En"))	return strOriginal;
	int ID=-1;
	HMODULE	hMod = LoadLibrary("ResDLLen.dll");
	if(hMod)
	{
		LPCTSTR lpszName = MAKEINTRESOURCE(1);
		if (::FindResource(hMod,  lpszName, RT_STRING) != NULL)
		{
			TCHAR szTemp[1001];
			int n=0, nLen = ::LoadString(hMod, 0, szTemp, 1000);
			if(nLen!=0)		n = atoi(szTemp);

			for(int ids=1; ids<=n; ids++)
			{
				nLen = ::LoadString(hMod, ids, szTemp, 1000);
				if(strOriginal==szTemp)
				{
					ID = ids;
					break;
				}
			}
		}
		FreeLibrary(hMod);
	}//hMod

	CString str;
	if		(m_Lang==_T("Fr")) 	hMod = LoadLibrary("ResDLLfr.dll");
	else if	(m_Lang==_T("Es")) 	hMod = LoadLibrary("ResDLLes.dll");
	else if	(m_Lang==_T("Ch")) 	hMod = LoadLibrary("ResDLLch.dll");
	else if	(m_Lang==_T("Ar")) 	hMod = LoadLibrary("ResDLLar.dll");
	else if	(m_Lang==_T("Ru")) 	hMod = LoadLibrary("ResDLLru.dll");

	if(hMod)
	{
		LPCTSTR lpszName = MAKEINTRESOURCE(1);
		if (::FindResource(hMod,  lpszName, RT_STRING) != NULL)
		{
			TCHAR szTemp[1001];
			::LoadString(hMod, ID, szTemp, 1000);
			str = szTemp;
		}
		FreeLibrary(hMod);
	}//hMod

	if(ID==-1) str = strOriginal;
	return str;
}


double CSMS4DCApp::ChangeLon(double lon,int Tx) 
{
	if((Tx >= m_Nxmax)&&(lon< 0.0))		lon = lon + 360.0;
	if((Tx <= 1    )&&(lon> 0.0))		lon = lon - 360.0;
	return lon;
}

double CSMS4DCApp::ReverseLon(double lon) 
{
	if(lon> 180.0)	lon = lon - 360.0;
	if(lon<-180.0)	lon = lon + 360.0;
	return lon;
}

void CSMS4DCApp::FindHelpFile() 
{
//	CString PathFileName =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Help\\SMS4DC Manual.pdf");
//	ShellExecute(m_hWnd, "open", PathFileName, NULL, NULL, SW_SHOWNORMAL);

	CString PathFileName, PathFileName0 =  m_AppPath + _T("Help\\SMS4DC Manual.pdf");

	if     (m_Lang==_T("En"))	PathFileName  =  PathFileName0;
	else if(m_Lang==_T("Fr"))	PathFileName  =  m_AppPath + _T("Help\\SMS4DC Manual_Fr.pdf");
	else if(m_Lang==_T("Es"))	PathFileName  =  m_AppPath + _T("Help\\SMS4DC Manual_Es.pdf");
	else if(m_Lang==_T("Ch"))	PathFileName  =  m_AppPath + _T("Help\\SMS4DC Manual_Ch.pdf");
	else if(m_Lang==_T("Ar"))	PathFileName  =  m_AppPath + _T("Help\\SMS4DC Manual_Ar.pdf");
	else if(m_Lang==_T("Ru"))	PathFileName  =  m_AppPath + _T("Help\\SMS4DC Manual_Ru.pdf");

	CFileFind x1;
	BOOL cx1 = x1.FindFile(PathFileName);
	if(cx1)		ShellExecute(NULL, "open", PathFileName , NULL, NULL, SW_SHOWNORMAL);
	else		ShellExecute(NULL, "open", PathFileName0, NULL, NULL, SW_SHOWNORMAL);
	x1.Close();
}


CString CSMS4DCApp::FindIndexFile(CString FilesPath, CString FilesPrefix) 
{
	CString strOUT = FilesPath + FilesPrefix + "_%02d_%02d";

	CString str1;	str1.Format("%s%s_*",FilesPath,FilesPrefix);

	CFileFind x1;
	BOOL cx1 = x1.FindFile(str1);
	if(cx1)
	{
		x1.FindNextFile();
		CString FileEXT = x1.GetFileName();
		CString str = x1.GetFileTitle();
		FileEXT.Replace(str,"");
		
		int L,a1,a2,x,y;
		L = str.GetLength();
		a2 = str.ReverseFind('_');
		y = L-a2-1;
		str.Delete(a2,L-a2);
		a1 = str.ReverseFind('_');
		x = a2-a1-1;

		CString s1;		s1.Format("%d", x);
		CString s2;		s2.Format("%d", y);

		strOUT = FilesPath + FilesPrefix + "_%0"  + s1 +  "d_%0"  + s2 +  "d" + FileEXT;
	}
	x1.Close();
	return strOUT;
}


//970710
void CSMS4DCApp::ToolBar_Function(int n) 
{
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ShowControlBar(&(((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ToolBarIDWMMap),  (n==1), FALSE);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ShowControlBar(&(((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndToolBar),		 (n==2), FALSE);

	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ShowControlBar(&(((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ToolBarALLplan),  (n==3), FALSE);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ShowControlBar(&(((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ToolBarSRVtable), (n==4), FALSE);
	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ShowControlBar(&(((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ToolBarRGNtable), (n==5), FALSE);

	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ShowControlBar(&(((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_ToolBarDATABASE), (n==6), FALSE);
}
