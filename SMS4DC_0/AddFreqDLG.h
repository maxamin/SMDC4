#if !defined(AFX_ADDFREQDLG_H__940A883F_AB59_49E1_9A08_EDC55A885BB1__INCLUDED_)
#define AFX_ADDFREQDLG_H__940A883F_AB59_49E1_9A08_EDC55A885BB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddFreqDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddFreqDLG dialog

class CAddFreqDLG : public CDialog
{
// Construction
public:
	CAddFreqDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddFreqDLG)
	enum { IDD = IDD_AddFreqDLG };
	double	m_BW;
	double	m_Freq;
	BOOL	m_Flag;
	CString	m_Flo;
	CString	m_Fhi;
	CString	m_title;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddFreqDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddFreqDLG)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDFREQDLG_H__940A883F_AB59_49E1_9A08_EDC55A885BB1__INCLUDED_)
