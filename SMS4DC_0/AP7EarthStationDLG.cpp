// AP7EarthStationDLG.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "AP7EarthStationDLG.h"

#include <afxdb.h>
#include "AP7_OptionsDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAP7EarthStationDLG dialog


CAP7EarthStationDLG::CAP7EarthStationDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CAP7EarthStationDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAP7EarthStationDLG)
	m_Beam = _T("");
	m_Group = _T("");
	m_Notice = _T("");
	m_Ctry = _T("");
	m_BDIRPC = _T("");
	m_GMIN = _T("-10");
	m_INCLINATION = _T("");
	m_RECVPC = _T("");
	m_SATEAST = _T("");
	m_SATWEST = _T("");
	m_TRANPC = _T("");
	m_TxRx = _T("");
	m_Manned = FALSE;
	//}}AFX_DATA_INIT
	m_DataBaseFlag = 0;
}


void CAP7EarthStationDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAP7EarthStationDLG)
	DDX_Text(pDX, IDC_EDIT_Beam, m_Beam);
	DDX_Text(pDX, IDC_EDIT_Group, m_Group);
	DDX_Text(pDX, IDC_EDIT_Notice, m_Notice);
	DDX_Text(pDX, IDC_EDIT_Ctry, m_Ctry);
	DDX_Text(pDX, IDC_EDIT_BDIRPC, m_BDIRPC);
	DDX_Text(pDX, IDC_EDIT_GMIN, m_GMIN);
	DDX_Text(pDX, IDC_EDIT_INCLINATION, m_INCLINATION);
	DDX_Text(pDX, IDC_EDIT_RECVPC, m_RECVPC);
	DDX_Text(pDX, IDC_EDIT_SATEAST, m_SATEAST);
	DDX_Text(pDX, IDC_EDIT_SATWEST, m_SATWEST);
	DDX_Text(pDX, IDC_EDIT_TRANPC, m_TRANPC);
	DDX_Text(pDX, IDC_EDIT_TxRx, m_TxRx);
	DDX_Text(pDX, IDC_EDIT_Manned, m_Manned);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAP7EarthStationDLG, CDialog)
	//{{AFX_MSG_MAP(CAP7EarthStationDLG)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE1, OnDblclkTree1)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_Options, OnBUTTONOptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAP7EarthStationDLG message handlers

BOOL CAP7EarthStationDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//Query APP7_List
	CString str1 = _T(" ( SELECT e_stn.ctry, grp.ntc_id, grp.beam_name, grp.grp_id, grp.emi_rcp ");
	CString str2 = _T(" FROM (e_stn INNER JOIN grp ON e_stn.ntc_id = grp.ntc_id) INNER JOIN notice ON e_stn.ntc_id = notice.ntc_id ");
	CString str3 = _T(" WHERE (((e_stn.long_dec) Is Not Null) AND ((notice.ntc_type)=\'S\')) ) as APP7_List ");
	m_qAPP7_List = str1+str2+str3;

	TreeFill(); 
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}

void CAP7EarthStationDLG::TreeFill() 
{
	CTreeCtrl* pCtrl = (CTreeCtrl*) GetDlgItem(IDC_TREE1);
	ASSERT(pCtrl != NULL);

	CImageList* m_ImageList = new CImageList();
	m_ImageList->Create(16, 16, ILC_COLOR8 | ILC_MASK,  5, 5);
	m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_ICON_N));
	m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_ICON_E));
	m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_ICON_R));
	m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_ICON_G));
	m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_ICON_C));

	pCtrl->SetImageList(m_ImageList,TVSIL_NORMAL);

	LONG style = ::GetWindowLong(pCtrl->m_hWnd, GWL_STYLE);
	::SetWindowLong(pCtrl->m_hWnd, GWL_STYLE, style | TVS_HASBUTTONS | TVS_HASLINES );

	CFont font ;
    if (!(HFONT)font)
	{
        LOGFONT lf;
		GetFont()->GetObject(sizeof(lf), &lf);
		lf.lfHeight = 16;
		lf.lfWeight = FW_BOLD;
		strcpy(lf.lfFaceName , "Times");
        font.CreateFontIndirect(&lf);
    }
	pCtrl->SetFont(&font);
	pCtrl->SetTextColor(RGB(127,0,0));
	font.DeleteObject();

	long ctyNUM;
	CString ctry[10000];
	ctyNUM = AP28_SRS_CTRY(ctry)  ;
	for(long i=0;i<ctyNUM;i++)
		pCtrl->InsertItem( ctry[i], 4, 4, TVI_ROOT );

}

long CAP7EarthStationDLG::AP28_SRS_group(long ntc,CString beam,CString TxRx,long *grpid) 
{
	CDatabase DB;
	CRecordset m_rs;
	CString m_Tbl;
	CDBVariant Fld;

	if(m_DataBaseFlag==0)
		DB.Open(_T("SRS_DB"),false,false,_T("ODBC;"),false);
	else
		DB.Open((((CSMS4DCApp *)AfxGetApp())->m_CDBSTR),false,false,_T("ODBC;"),false);

//	m_Tbl.Format("SELECT DISTINCT grp_id FROM APP7_List WHERE (((ntc_id)=%ld) AND ((beam_name)=\'%s\') AND ((emi_rcp)=\'%s\'));",ntc,beam,TxRx);
	m_Tbl.Format(_T("SELECT DISTINCT grp_id FROM %s WHERE (((ntc_id)=%ld) AND ((beam_name)=\'%s\') AND ((emi_rcp)=\'%s\'));") , m_qAPP7_List , ntc,beam,TxRx);

	m_rs.m_pDatabase = &DB;
	m_rs.Open( CRecordset::snapshot, m_Tbl);

	long i = 0;
	if(m_rs.GetRecordCount() == 1)
	{
		m_rs.MoveFirst();
		while(1)
		{
			if(m_rs.IsEOF()) break;
			m_rs.GetFieldValue((short)0,Fld);		grpid[i] = Fld.m_lVal;
			i++;
			m_rs.MoveNext();
		}
	}
	m_rs.Close();
	DB.Close();

	return i;
}



long CAP7EarthStationDLG::AP28_SRS_beam(long ntc,CString *beam,CString *TxRx) 
{
	CDatabase DB;
	CRecordset m_rs;
	CString m_Tbl;

	if(m_DataBaseFlag==0)
		DB.Open(_T("SRS_DB"),false,false,_T("ODBC;"),false);
	else
		DB.Open((((CSMS4DCApp *)AfxGetApp())->m_CDBSTR),false,false,_T("ODBC;"),false);

//	m_Tbl.Format("SELECT DISTINCT beam_name,emi_rcp FROM APP7_List WHERE (((ntc_id)=%ld));",ntc);
	m_Tbl.Format(_T("SELECT DISTINCT beam_name,emi_rcp FROM %s WHERE (((ntc_id)=%ld));") , m_qAPP7_List , ntc);

	m_rs.m_pDatabase = &DB;
	m_rs.Open( CRecordset::snapshot, m_Tbl);

	long i = 0;
	if(m_rs.GetRecordCount() == 1)
	{
		m_rs.MoveFirst();
		while(1)
		{
			if(m_rs.IsEOF()) break;
			m_rs.GetFieldValue((short)0,beam[i]);
			m_rs.GetFieldValue((short)1,TxRx[i]);
			i++;
			m_rs.MoveNext();
		}
	}
	m_rs.Close();
	DB.Close();

	return i;
}


long CAP7EarthStationDLG::AP28_SRS_ntc_id(CString cty,long *ntcid) 
{
	CDatabase DB;
	CRecordset m_rs;
	CString m_Tbl;
	CDBVariant Fld;

	if(m_DataBaseFlag==0)
		DB.Open(_T("SRS_DB"),false,false,_T("ODBC;"),false);
	else
		DB.Open((((CSMS4DCApp *)AfxGetApp())->m_CDBSTR),false,false,_T("ODBC;"),false);

//	m_Tbl.Format("SELECT DISTINCT ntc_id FROM APP7_List WHERE (((ctry)=\'%s\')) ORDER BY ntc_id;",cty);
	m_Tbl.Format(_T("SELECT DISTINCT ntc_id FROM %s WHERE (((ctry)=\'%s\')) ORDER BY ntc_id;") ,m_qAPP7_List,cty);

	m_rs.m_pDatabase = &DB;
	m_rs.Open( CRecordset::snapshot, m_Tbl);

	long i = 0;
	if(m_rs.GetRecordCount() == 1)
	{
		m_rs.MoveFirst();
		while(1)
		{
			if(m_rs.IsEOF()) break;
			m_rs.GetFieldValue((short)0,Fld);		ntcid[i] = Fld.m_lVal;
			i++;
			m_rs.MoveNext();
		}
	}
	m_rs.Close();
	DB.Close();

	return i;
}

long CAP7EarthStationDLG::AP28_SRS_CTRY(CString *cty) 
{
	CDatabase DB;
	CRecordset m_rs;
	CString m_Tbl;

	if(m_DataBaseFlag==0)
		DB.Open(_T("SRS_DB"),false,false,_T("ODBC;"),false);
	else
		DB.Open((((CSMS4DCApp *)AfxGetApp())->m_CDBSTR),false,false,_T("ODBC;"),false);

//	m_Tbl = _T("SELECT DISTINCT ctry FROM APP7_List ORDER BY ctry;");
	m_Tbl.Format( _T("SELECT DISTINCT ctry FROM %s ORDER BY ctry;") , m_qAPP7_List );

	m_rs.m_pDatabase = &DB;
	m_rs.Open( CRecordset::snapshot, m_Tbl);

	long i = 0;
	if(m_rs.GetRecordCount() == 1)
	{
		m_rs.MoveFirst();
		while(1)
		{
			if(m_rs.IsEOF()) break;
			m_rs.GetFieldValue((short)0,cty[i]);
			i++;
			m_rs.MoveNext();
		}
	}
	m_rs.Close();
	DB.Close();

	return i;
}


void CAP7EarthStationDLG::OnDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CTreeCtrl* pCtrl = (CTreeCtrl*) GetDlgItem(IDC_TREE1);
	ASSERT(pCtrl != NULL);
	
	// find the currently selected item
	HTREEITEM hRoot = pCtrl->GetNextItem(TVI_ROOT, TVGN_CARET);
	CString strITEM;	strITEM.Format("%s", pCtrl->GetItemText(hRoot));

	BOOL bITEM = pCtrl->ItemHasChildren(hRoot);
	while(bITEM==1)
	{
		HTREEITEM hITEM = pCtrl->GetChildItem(hRoot);		pCtrl->DeleteItem(hITEM);
		bITEM = pCtrl->ItemHasChildren(hRoot);
	}

	if(strITEM.GetLength() <4)
	{
		UpdateData();
		m_Ctry = strITEM;
		m_Notice.Empty();
		m_Beam.Empty();
		m_TxRx.Empty();
		m_Group.Empty();
		UpdateData(false);

		long ntcid[10000];
		long ntcNUM = AP28_SRS_ntc_id(strITEM,ntcid);
		CString dum;

		for(long i=0;i<ntcNUM;i++)
		{
			dum.Format("Notice ID : %ld",ntcid[i]);
			pCtrl->InsertItem( dum, 0, 0, hRoot );
		}
	}

	else if(strITEM.Left(6) =="Notice")
	{
		UpdateData();
		m_Notice = strITEM.Mid(12);
		m_Beam.Empty();
		m_TxRx.Empty();
		m_Group.Empty();

		HTREEITEM hCtry = pCtrl->GetParentItem(hRoot);
		m_Ctry = pCtrl->GetItemText(hCtry);
		UpdateData(false);

		CString  beam[10000], TxRx[10000];
		long beamNUM = AP28_SRS_beam(atol(m_Notice),beam,TxRx); 
		for(long i=0;i<beamNUM;i++)
		{
			if(TxRx[i]=="E")
				pCtrl->InsertItem( "BeamE ID : "+beam[i], 1, 1, hRoot );
			else
				pCtrl->InsertItem( "BeamR ID : "+beam[i], 2, 2, hRoot );
		}
	}

	else if(strITEM.Left(5) =="BeamE")
	{
		UpdateData();
		m_Beam = strITEM.Mid(11);
		m_TxRx = "Tx";
		m_Group.Empty();

		HTREEITEM hNotice = pCtrl->GetParentItem(hRoot);
		m_Notice = pCtrl->GetItemText(hNotice).Mid(12);

		HTREEITEM hCtry = pCtrl->GetParentItem(hNotice);
		m_Ctry = pCtrl->GetItemText(hCtry);
		UpdateData(false);

		long grpid[10000];
		CString dum;
		long grpNUM = AP28_SRS_group(atol(m_Notice),m_Beam,"E",grpid) ;
		for(long i=0;i<grpNUM;i++)
		{
			dum.Format("Group ID : %ld",grpid[i]);
			pCtrl->InsertItem( dum, 3, 3, hRoot );
		}
	}

	else if(strITEM.Left(5) =="BeamR")
	{
		UpdateData();
		m_Beam = strITEM.Mid(11);
		m_TxRx = "Rx";
		m_Group.Empty();

		HTREEITEM hNotice = pCtrl->GetParentItem(hRoot);
		m_Notice = pCtrl->GetItemText(hNotice).Mid(12);

		HTREEITEM hCtry = pCtrl->GetParentItem(hNotice);
		m_Ctry = pCtrl->GetItemText(hCtry);
		UpdateData(false);

		long grpid[10000];
		CString dum;
		long grpNUM = AP28_SRS_group(atol(m_Notice),m_Beam,"R",grpid) ;
		for(long i=0;i<grpNUM;i++)
		{
			dum.Format("Group ID : %ld",grpid[i]);
			pCtrl->InsertItem( dum, 3, 3, hRoot );
		}
	}

	else if(strITEM.Left(5) =="Group")
	{
		UpdateData();
		m_Group = strITEM.Mid(11);

		HTREEITEM hBeam = pCtrl->GetParentItem(hRoot);
		CString str1;	str1.Format("%s", pCtrl->GetItemText(hBeam));

		m_Beam = str1.Mid(11);
		m_TxRx = (str1.Mid(4,1) =="E") ? "Tx" : "Rx";

		HTREEITEM hNotice = pCtrl->GetParentItem(hBeam);
		m_Notice = pCtrl->GetItemText(hNotice).Mid(12);

		HTREEITEM hCtry = pCtrl->GetParentItem(hNotice);
		m_Ctry = pCtrl->GetItemText(hCtry);
		UpdateData(false);
	}
	
	*pResult = 0;
}

HBRUSH CAP7EarthStationDLG::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if (	pWnd->GetDlgCtrlID() == IDC_EDIT_Notice ||
			pWnd->GetDlgCtrlID() == IDC_EDIT_Beam	||
			pWnd->GetDlgCtrlID() == IDC_EDIT_Ctry	||
			pWnd->GetDlgCtrlID() == IDC_EDIT_TxRx	||
			pWnd->GetDlgCtrlID() == IDC_EDIT_Group	)
	{
		CFont font ;
        if (!(HFONT)font)
		{
            LOGFONT lf;
			GetFont()->GetObject(sizeof(lf), &lf);
			lf.lfHeight = 16;
			lf.lfWeight = FW_BOLD;
			strcpy(lf.lfFaceName , "Times");
            font.CreateFontIndirect(&lf);
        }
        pDC->SelectObject(&font);
		pDC->SetTextColor(RGB(0,0,255));
		font.DeleteObject();
	}	

	if (pWnd->GetDlgCtrlID() == IDC_TREE1 )
	{
		CFont font ;
		if (!(HFONT)font)
		{
			LOGFONT lf;
			GetFont()->GetObject(sizeof(lf), &lf);
			lf.lfHeight = 16;
			lf.lfWeight = FW_BOLD;
			strcpy(lf.lfFaceName , "Times");
			font.CreateFontIndirect(&lf);
		}
        pDC->SelectObject(&font);
		pDC->SetTextColor(RGB(127,0,0));
		font.DeleteObject();
	}


	return hbr;
}

void CAP7EarthStationDLG::OnBUTTONOptions() 
{
	UpdateData();

	CAP7_OptionsDLG xx;
	if(xx.DoModal() == IDOK)
	{
		m_BDIRPC = xx.m_BDIRPC;
		m_TRANPC = xx.m_TRANPC;
		m_RECVPC = xx.m_RECVPC;
		m_SATEAST = xx.m_SATEAST;
		m_SATWEST = xx.m_SATWEST;
		m_INCLINATION = xx.m_INCLINATION;
		m_GMIN = xx.m_GMIN;

		m_Manned = xx.m_Manned;
	}

	UpdateData(false);	
}
