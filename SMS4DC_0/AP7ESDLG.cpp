// AP7ESDLG.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "AP7ESDLG.h"

#include <afxdb.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAP7ESDLG dialog


CAP7ESDLG::CAP7ESDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CAP7ESDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAP7ESDLG)
	m_Ctry = _T("");
	m_Notice = _T("");
	m_Beam = _T("");
	m_Group = _T("");
	m_TxRx = _T("");
	m_Frq = _T("");
	//}}AFX_DATA_INIT
	m_TxRxQ = _T("E");
	m_Title = _Z("Select Tx Earth Station");
	m_DataBaseFlag = 0;

}


void CAP7ESDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAP7ESDLG)
	DDX_Text(pDX, IDC_EDIT_Ctry, m_Ctry);
	DDX_Text(pDX, IDC_EDIT_Notice, m_Notice);
	DDX_Text(pDX, IDC_EDIT_Beam, m_Beam);
	DDX_Text(pDX, IDC_EDIT_Group, m_Group);
	DDX_Text(pDX, IDC_EDIT_TxRx, m_TxRx);
	DDX_Text(pDX, IDC_EDIT_Frq, m_Frq);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAP7ESDLG, CDialog)
	//{{AFX_MSG_MAP(CAP7ESDLG)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE1, OnDblclkTree1)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAP7ESDLG message handlers

void CAP7ESDLG::TreeFill() 
{
	CTreeCtrl* pCtrl = (CTreeCtrl*) GetDlgItem(IDC_TREE1);
	ASSERT(pCtrl != NULL);

	CImageList* m_ImageList = new CImageList();
	m_ImageList->Create(16, 16, ILC_COLOR8 | ILC_MASK,  6, 6);
	m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_ICON_N));
	m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_ICON_E));
	m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_ICON_R));
	m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_ICON_G));
	m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_ICON_C));
	m_ImageList->Add(AfxGetApp()->LoadIcon(IDI_ICON_F));

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

long CAP7ESDLG::AP28_SRS_CTRY(CString *cty) 
{
	CDatabase DB;
	CRecordset m_rs;
	CString m_Tbl;

	if(m_DataBaseFlag==0)
		DB.Open(_T("SRS_DB"),false,false,_T("ODBC;"),false);
	else
		DB.Open((((CSMS4DCApp *)AfxGetApp())->m_CDBSTR),false,false,_T("ODBC;"),false);

//	m_Tbl.Format("SELECT DISTINCT ctry FROM APP7_List_Int WHERE (((emi_rcp)=\'%s\')) ORDER BY ctry;",m_TxRxQ);
	m_Tbl.Format(_T("SELECT DISTINCT ctry FROM %s WHERE (((emi_rcp)=\'%s\')) ORDER BY ctry;"), m_qAPP7_List_Int , m_TxRxQ);

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

BOOL CAP7ESDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//Query APP7_List_Int
	CString str1 = _T(" ( SELECT e_stn.ctry, grp.ntc_id, grp.beam_name, grp.grp_id, grp.emi_rcp ");
	CString str2 = _T(" FROM (e_stn INNER JOIN grp ON e_stn.ntc_id = grp.ntc_id) INNER JOIN notice ON e_stn.ntc_id = notice.ntc_id ");
	CString str3 = _T(" WHERE (((e_stn.long_dec) Is Not Null) AND ((notice.ntc_type)=\'S\') AND ((e_stn.long_nom) Is Not Null)) ) as APP7_List_Int ");
	m_qAPP7_List_Int = str1+str2+str3;

	SetWindowText(m_Title);
	TreeFill(); 
	
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;
}

long CAP7ESDLG::AP28_SRS_group(long ntc,CString beam,CString TxRx,long *grpid) 
{
	CDatabase DB;
	CRecordset m_rs;
	CString m_Tbl;
	CDBVariant Fld;

	if(m_DataBaseFlag==0)
		DB.Open(_T("SRS_DB"),false,false,_T("ODBC;"),false);
	else
		DB.Open((((CSMS4DCApp *)AfxGetApp())->m_CDBSTR),false,false,_T("ODBC;"),false);

//	m_Tbl.Format("SELECT DISTINCT grp_id FROM APP7_List_Int WHERE (((ntc_id)=%ld) AND ((beam_name)=\'%s\') AND ((emi_rcp)=\'%s\'));",ntc,beam,TxRx);
	m_Tbl.Format(_T("SELECT DISTINCT grp_id FROM %s WHERE (((ntc_id)=%ld) AND ((beam_name)=\'%s\') AND ((emi_rcp)=\'%s\'));") , m_qAPP7_List_Int , ntc,beam,TxRx);

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



long CAP7ESDLG::AP28_SRS_beam(long ntc,CString *beam,CString *TxRx) 
{
	CDatabase DB;
	CRecordset m_rs;
	CString m_Tbl;

	if(m_DataBaseFlag==0)
		DB.Open(_T("SRS_DB"),false,false,_T("ODBC;"),false);
	else
		DB.Open((((CSMS4DCApp *)AfxGetApp())->m_CDBSTR),false,false,_T("ODBC;"),false);

//	m_Tbl.Format("SELECT DISTINCT beam_name, emi_rcp FROM APP7_List_Int WHERE (((emi_rcp)=\'%s\') AND ((ntc_id)=%ld));",m_TxRxQ,ntc);
	m_Tbl.Format(_T("SELECT DISTINCT beam_name, emi_rcp FROM %s WHERE (((emi_rcp)=\'%s\') AND ((ntc_id)=%ld));") , m_qAPP7_List_Int, m_TxRxQ,ntc);

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
			m_rs.GetFieldValue(1,TxRx[i]);
			i++;
			m_rs.MoveNext();
		}
	}
	m_rs.Close();
	DB.Close();

	return i;
}


long CAP7ESDLG::AP28_SRS_ntc_id(CString cty,long *ntcid) 
{
	CDatabase DB;
	CRecordset m_rs;
	CString m_Tbl;
	CDBVariant Fld;

	if(m_DataBaseFlag==0)
		DB.Open(_T("SRS_DB"),false,false,_T("ODBC;"),false);
	else
		DB.Open((((CSMS4DCApp *)AfxGetApp())->m_CDBSTR),false,false,_T("ODBC;"),false);

//	m_Tbl.Format("SELECT DISTINCT ntc_id FROM APP7_List_Int WHERE (((ctry)=\'%s\') AND ((emi_rcp)=\'%s\')) ORDER BY ntc_id;",cty,m_TxRxQ);
	m_Tbl.Format(_T("SELECT DISTINCT ntc_id FROM %s WHERE (((ctry)=\'%s\') AND ((emi_rcp)=\'%s\')) ORDER BY ntc_id;") , m_qAPP7_List_Int , cty,m_TxRxQ);

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

void CAP7ESDLG::OnDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult) 
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
		m_Frq.Empty();
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

	else if(strITEM.Left(6) ==_T("Notice"))
	{
		UpdateData();
		m_Notice = strITEM.Mid(12);
		m_Beam.Empty();
		m_TxRx.Empty();
		m_Group.Empty();
		m_Frq.Empty();

		HTREEITEM hCtry = pCtrl->GetParentItem(hRoot);
		m_Ctry = pCtrl->GetItemText(hCtry);
		UpdateData(false);

		CString  beam[10000], TxRx[10000];
		long beamNUM = AP28_SRS_beam(atol(m_Notice),beam,TxRx); 
		for(long i=0;i<beamNUM;i++)
		{
			if(TxRx[i]==_T("E"))
				pCtrl->InsertItem( "BeamE ID : "+beam[i], 1, 1, hRoot );
			else
				pCtrl->InsertItem( "BeamR ID : "+beam[i], 2, 2, hRoot );
		}
	}

	else if(strITEM.Left(5) ==_T("BeamE"))
	{
		UpdateData();
		m_Beam = strITEM.Mid(11);
		m_TxRx = _T("Tx");
		m_Group.Empty();
		m_Frq.Empty();

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

	else if(strITEM.Left(5) ==_T("BeamR"))
	{
		UpdateData();
		m_Beam = strITEM.Mid(11);
		m_TxRx = _T("Rx");
		m_Group.Empty();
		m_Frq.Empty();

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

	else if(strITEM.Left(5) ==_T("Group"))
	{
		UpdateData();
		m_Group = strITEM.Mid(11);
		m_Frq.Empty();

		HTREEITEM hBeam = pCtrl->GetParentItem(hRoot);
		CString str1;	str1.Format("%s", pCtrl->GetItemText(hBeam));

		m_Beam = str1.Mid(11);
		m_TxRx = (str1.Mid(4,1) ==_T("E")) ? _T("Tx") : _T("Rx");

		HTREEITEM hNotice = pCtrl->GetParentItem(hBeam);
		m_Notice = pCtrl->GetItemText(hNotice).Mid(12);

		HTREEITEM hCtry = pCtrl->GetParentItem(hNotice);
		m_Ctry = pCtrl->GetItemText(hCtry);
		UpdateData(false);

		double frq[1000];
		CString dum;
		long frqNUM = AP28_SRS_frq(atol(m_Group),frq) ;
		for(long i=0;i<frqNUM;i++)
		{
			dum.Format("Frq(MHz) : %0.4lf",frq[i]);
			pCtrl->InsertItem( dum, 5, 5, hRoot );
		}

	}
	else if(strITEM.Left(8) ==_T("Frq(MHz)"))
	{
		UpdateData();
		m_Frq = strITEM.Mid(11);

		HTREEITEM hGroup = pCtrl->GetParentItem(hRoot);
		m_Group = pCtrl->GetItemText(hGroup).Mid(11);

		HTREEITEM hBeam = pCtrl->GetParentItem(hGroup);
		CString str1;	str1.Format("%s", pCtrl->GetItemText(hBeam));

		m_Beam = str1.Mid(11);
		m_TxRx = (str1.Mid(4,1) ==_T("E")) ? _T("Tx") : _T("Rx");

		HTREEITEM hNotice = pCtrl->GetParentItem(hBeam);
		m_Notice = pCtrl->GetItemText(hNotice).Mid(12);

		HTREEITEM hCtry = pCtrl->GetParentItem(hNotice);
		m_Ctry = pCtrl->GetItemText(hCtry);
		UpdateData(false);
	}

	*pResult = 0;
}

HBRUSH CAP7ESDLG::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if (	pWnd->GetDlgCtrlID() == IDC_EDIT_Notice ||
			pWnd->GetDlgCtrlID() == IDC_EDIT_Beam	||
			pWnd->GetDlgCtrlID() == IDC_EDIT_Ctry	||
			pWnd->GetDlgCtrlID() == IDC_EDIT_TxRx	||
			pWnd->GetDlgCtrlID() == IDC_EDIT_Frq	||
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


long CAP7ESDLG::AP28_SRS_frq(long grpid,double *frq) 
{
	CDatabase DB;
	CRecordset m_rs;
	CString m_Tbl;
	CDBVariant Fld;

	if(m_DataBaseFlag==0)
		DB.Open(_T("SRS_DB"),false,false,_T("ODBC;"),false);
	else
		DB.Open((((CSMS4DCApp *)AfxGetApp())->m_CDBSTR),false,false,_T("ODBC;"),false);

	m_Tbl.Format("SELECT DISTINCT freq_mhz FROM assgn WHERE (((assgn.grp_id)=%ld));",grpid);

	m_rs.m_pDatabase = &DB;
	m_rs.Open( CRecordset::snapshot, m_Tbl);

	long i = 0;
	if(m_rs.GetRecordCount() == 1)
	{
		m_rs.MoveFirst();
		while(1)
		{
			if(m_rs.IsEOF()) break;
			m_rs.GetFieldValue((short)0,Fld);		frq[i] = Fld.m_dblVal;
			i++;
			m_rs.MoveNext();
		}
	}
	m_rs.Close();
	DB.Close();

	return i;
}
