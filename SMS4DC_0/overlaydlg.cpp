// OverlayDLG.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "OverlayDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COverlayDLG dialog


COverlayDLG::COverlayDLG(CWnd* pParent /*=NULL*/)
	: CDialog(COverlayDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(COverlayDLG)
	m_OverlayFactor = 50.0;
	//}}AFX_DATA_INIT
}


void COverlayDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COverlayDLG)
	DDX_Control(pDX, IDC_LIST_Overlay, m_overlay);
	DDX_Text(pDX, IDC_EDIT_OverlayFactor, m_OverlayFactor);
	DDV_MinMaxDouble(pDX, m_OverlayFactor, 0., 100.);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COverlayDLG, CDialog)
	//{{AFX_MSG_MAP(COverlayDLG)
	ON_LBN_DBLCLK(IDC_LIST_Overlay, OnDblclkLISTOverlay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COverlayDLG message handlers

BOOL COverlayDLG::OnInitDialog() 
{
/*
	CDialog::OnInitDialog();
	m_SelectedDoc=NULL;
	DocUtil::GetAllDocuments(Docs);  
	for(POSITION pos = Docs.GetHeadPosition();pos;)
	{			  
		CDocument *pDoc = Docs.GetNext(pos);
		m_overlay.AddString(pDoc->GetTitle());
	}	
	return TRUE;
*/
	CDialog::OnInitDialog();
	m_SelectedDoc = NULL;
	DocUtil::GetAllDocuments(Docs);  
	for(POSITION pos = Docs.GetHeadPosition();pos;)
	{			  
		CString strT = (Docs.GetNext(pos))->GetTitle();
		CString s = strT.Left(4);
//		if((s == _T("Area"))||(s == _T("Maxi"))||(s == _T("Best"))||(s == _T("Inte")) )		//98/12/17
		if((s == _T("Area"))||(s == _T("Maxi"))||(s == _T("Best"))||(s == _T("Inte"))  ||(s == _T("Moni"))||(s == _T("Cove"))||(s == _T("Loca")) )
			m_overlay.AddString(strT);
	}	
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;
}

void COverlayDLG::OnDblclkLISTOverlay() 
{
	OnOK();
}

void COverlayDLG::OnOK() 
{
/*
	int i=0;
//	DocUtil::GetAllDocuments(Docs);  
	for(POSITION pos = Docs.GetHeadPosition();pos;i++)
	{			  
		CDocument *pDoc = Docs.GetNext(pos);
		if(m_overlay.GetSel(i)>0)
		{
			//pDoc->SetTitle(pDoc->GetTitle()+" : Clicked");
			m_SelectedDoc=pDoc;
			break;
		}
	}		
*/
	int n = m_overlay.GetCurSel();
	if(n>-1)
	{
		CString strM;
		m_overlay.GetText(n,strM);

		for(POSITION pos = Docs.GetHeadPosition(); pos;)
		{			  
			CDocument *pDoc = Docs.GetNext(pos);
			CString strT = pDoc->GetTitle();
			if(strT.Compare(strM)==0)
			{
				m_SelectedDoc = pDoc;
				break;
			}
		}	
	}

	CDialog::OnOK();
}
