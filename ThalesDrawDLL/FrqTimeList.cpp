// FrqTimeList.cpp : implementation file
//

#include "stdafx.h"
#include "thalesdrawdll.h"
#include "FrqTimeList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFrqTimeList dialog


CFrqTimeList::CFrqTimeList(CWnd* pParent /*=NULL*/)
	: CDialog(CFrqTimeList::IDD, pParent)
{
	m_flag_Frq_Time = TRUE;
	m_OccResFlag = 0;

	//{{AFX_DATA_INIT(CFrqTimeList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFrqTimeList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFrqTimeList)
	DDX_Control(pDX, IDC_LIST1, m_List1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFrqTimeList, CDialog)
	//{{AFX_MSG_MAP(CFrqTimeList)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFrqTimeList message handlers

BOOL CFrqTimeList::OnInitDialog() 
{
	CDialog::OnInitDialog();

	((CThalesDrawDLLApp *)AfxGetApp())->m_Lang = m_Lang;

	m_List1.SetExtendedStyle( LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );		

	if(m_OccResFlag==0)
	{
		if(m_flag_Frq_Time)
		{
			m_List1.InsertColumn (0, _T(""),			LVCFMT_CENTER, 0);
			m_List1.InsertColumn (1, _Z("Frequency"),	LVCFMT_CENTER, 100);
			m_List1.InsertColumn (2, _Z("Global rate"), LVCFMT_CENTER, 100);
			int r = m_Freq.GetSize();
			for(int i=0;i<r;i++)
			{
				CString str;
				str.Format(_T("%s"), m_Freq.GetAt(i));

//				m_List1.InsertItem( LVIF_TEXT|LVIF_STATE,i,str, LVIS_SELECTED , LVIS_SELECTED, 0, 0);
				m_List1.InsertItem( i,_T(""));
				m_List1.SetItemText(i, 1, str);

				str.Format(_T("%0.0f"), m_GlobalRate.GetAt(i));
				m_List1.SetItemText(i, 2, str);
			}
			SetWindowText(_Z("Select One Frequency"));
		}
		else
		{
			int n = m_TimeBracketList.GetSize();
			m_List1.InsertColumn (0, _T(""), LVCFMT_CENTER, 0);
			m_List1.InsertColumn (1, _Z("Start Date/Time"), LVCFMT_CENTER, 130);
			m_List1.InsertColumn (2, _Z("Stop Date/Time"),  LVCFMT_CENTER, 130);

			for(int i=7;i<n-1; i=i+2)
			{
				CString str1,str2;
				str1 =  m_TimeBracketList.GetAt(i);
				str2 =  m_TimeBracketList.GetAt(i+1);

//				m_List1.InsertItem( LVIF_TEXT|LVIF_STATE,(i-7)/2,str1, LVIS_SELECTED , LVIS_SELECTED, 0, 0);
				m_List1.InsertItem( (i-7)/2,_T(""));
				m_List1.SetItemText((i-7)/2, 1, str1);
				m_List1.SetItemText((i-7)/2, 2, str2);
			}
			SetWindowText(_Z("Select One Time Duration"));
		}
	}
	else if(m_OccResFlag==1)
	{
		if(m_flag_Frq_Time)
		{
			int r = m_Freq.GetSize();
			m_List1.InsertColumn (0, _T(""),				LVCFMT_CENTER, 0);
			m_List1.InsertColumn (1, _Z("Frequency(MHz)"),  LVCFMT_CENTER, 140);

			for(int i=0;i<r;i++)
			{
				CString str;
				str.Format(_T("%s"), m_Freq.GetAt(i));

		//		m_List1.InsertItem( LVIF_TEXT|LVIF_STATE,i,str, LVIS_SELECTED , LVIS_SELECTED, 0, 0);
				m_List1.InsertItem( i,_T(""));
				m_List1.SetItemText(i, 1, str);
			}
			SetWindowText(_Z("Select One Frequency"));
		}
		else
		{
			int r = m_TimeBracketList.GetSize();
			m_List1.InsertColumn (0, _T(""),						 LVCFMT_CENTER, 0);
			m_List1.InsertColumn (1, _Z("Date/Time of detection"),   LVCFMT_CENTER, 140);

			for(int i=0;i<r; i++)
			{
				CString str1;
				str1 =  m_TimeBracketList.GetAt(i);
			
		//		m_List1.InsertItem( LVIF_TEXT|LVIF_STATE,i,str1, LVIS_SELECTED , LVIS_SELECTED, 0, 0);
				m_List1.InsertItem( i,_T(""));
				m_List1.SetItemText(i, 1, str1);
			}
			SetWindowText(_Z("Select One Date/Time"));
		}
	}

	((CThalesDrawDLLApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}

void CFrqTimeList::OnOK() 
{
	POSITION pos = m_List1.GetFirstSelectedItemPosition();
	int r = m_List1.GetNextSelectedItem(pos);
	if(r==-1)	r = 0;

	if(m_OccResFlag==0)
	{
		if(m_flag_Frq_Time)		m_strOUT = m_List1.GetItemText(r, 1);
		else
		{
			m_strTimeStart	= m_List1.GetItemText(r, 1);
			m_strOUT		= m_List1.GetItemText(r, 2);
		}
	}
	else if(m_OccResFlag==1)
	{
		if(m_flag_Frq_Time)		m_strOUT		= m_List1.GetItemText(r, 1);
		else					m_strTimeStart	= m_List1.GetItemText(r, 1);
	}	
	CDialog::OnOK();
}

void CFrqTimeList::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnOK();
	*pResult = 0;
}
