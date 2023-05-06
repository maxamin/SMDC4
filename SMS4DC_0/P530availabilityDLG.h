#if !defined(AFX_P530AVAILABILITYDLG_H__5B145DEA_2279_4DDE_9395_7D3A94D64DE5__INCLUDED_)
#define AFX_P530AVAILABILITYDLG_H__5B145DEA_2279_4DDE_9395_7D3A94D64DE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// P530availabilityDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CP530availabilityDLG dialog

class CP530availabilityDLG : public CDialog
{
// Construction
public:
	CP530availabilityDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CP530availabilityDLG)
	enum { IDD = IDD_P530AVAILABILITY };
	CString	m_MultiWMav;
	CString	m_MultiWMoutS;
	CString	m_MultiANav;
	CString	m_MultiANoutM;
	CString	m_MultiANoutS;
	CString	m_MultiWMoutM;
	CString	m_RainANav;
	CString	m_RainANoutM;
	CString	m_RainANoutS;
	CString	m_RainWMav;
	CString	m_RainWMoutM;
	CString	m_RainWMoutS;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CP530availabilityDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CP530availabilityDLG)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_P530AVAILABILITYDLG_H__5B145DEA_2279_4DDE_9395_7D3A94D64DE5__INCLUDED_)
