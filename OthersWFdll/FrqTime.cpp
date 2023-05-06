// FrqTime.cpp : implementation file
//

#include "stdafx.h"
#include "arguswfdll.h"
#include "FrqTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFrqTime dialog


CFrqTime::CFrqTime(CWnd* pParent /*=NULL*/)
	: CDialog(CFrqTime::IDD, pParent)
{
	m_flag_Frq_Time = TRUE;

	//{{AFX_DATA_INIT(CFrqTime)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFrqTime::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFrqTime)
	DDX_Control(pDX, IDC_LIST1, m_List1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFrqTime, CDialog)
	//{{AFX_MSG_MAP(CFrqTime)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFrqTime message handlers

BOOL CFrqTime::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	((CArgusWFdllApp *)AfxGetApp())->m_Lang = m_Lang;

	m_List1.SetExtendedStyle( LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );		

	if(m_flag_Frq_Time)
	{
		m_List1.InsertColumn (0, _T(""),			LVCFMT_CENTER, 0);
		m_List1.InsertColumn (1, _Z("Frequency"),	LVCFMT_CENTER, 120);
		int r = m_ListFrq.GetSize();
		for(int i=0;i<r;i++)
		{
			CString str;
			str.Format(_T("%f"), m_ListFrq.GetAt(i));

			m_List1.InsertItem( i,_T(""));
			m_List1.SetItemText(i, 1, str);
		}
		SetWindowText(_T("Select One Frequency"));
	}
	else
	{
		int r = m_ListDateTime.GetSize();
		m_List1.InsertColumn (0, _T(""), LVCFMT_CENTER, 0);
		m_List1.InsertColumn (1, _Z("Date/Time"), LVCFMT_CENTER, 170);

		for(int i=0;i<r;i++)
		{
			CString str;
			str.Format(_T("%s"), m_ListDateTime.GetAt(i));

			m_List1.InsertItem( i,_T(""));
			m_List1.SetItemText(i, 1, str);
		}
		SetWindowText(_T("Select One Time Duration"));
	}

	((CArgusWFdllApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}

void CFrqTime::OnOK() 
{
	POSITION pos = m_List1.GetFirstSelectedItemPosition();
	int r = m_List1.GetNextSelectedItem(pos);
	if(r==-1)	r = 0;

	m_strOUT = m_List1.GetItemText(r, 1);
	CDialog::OnOK();
}
void CFrqTime::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnOK();
	*pResult = 0;
}
