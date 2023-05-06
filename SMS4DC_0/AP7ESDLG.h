#if !defined(AFX_AP7ESDLG_H__8C8206F0_FC33_44E1_A768_89E23FF6B6A2__INCLUDED_)
#define AFX_AP7ESDLG_H__8C8206F0_FC33_44E1_A768_89E23FF6B6A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AP7ESDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAP7ESDLG dialog

class CAP7ESDLG : public CDialog
{
// Construction
public:
	CAP7ESDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAP7ESDLG)
	enum { IDD = IDD_AP7_ESDLG };
	CString	m_Ctry;
	CString	m_Notice;
	CString	m_Beam;
	CString	m_Group;
	CString	m_TxRx;
	CString	m_Frq;
	//}}AFX_DATA

	CString	m_TxRxQ, m_Title;
	int m_DataBaseFlag;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAP7ESDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAP7ESDLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void TreeFill() ;
	long AP28_SRS_CTRY(CString *cty) ;
	long AP28_SRS_ntc_id(CString cty,long *ntcid) ;
	long AP28_SRS_beam(long ntc,CString *beam,CString *TxRx) ;
	long AP28_SRS_group(long ntc,CString beam,CString TxRx,long *grpid) ;
	long AP28_SRS_frq(long grpid,double *frq) ;
	CString	m_qAPP7_List_Int;
	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AP7ESDLG_H__8C8206F0_FC33_44E1_A768_89E23FF6B6A2__INCLUDED_)
