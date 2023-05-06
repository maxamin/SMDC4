#if !defined(AFX_BESTSERVERDLG_H__3ADC4BE6_C2F5_4993_A0D4_7E75C9C335AA__INCLUDED_)
#define AFX_BESTSERVERDLG_H__3ADC4BE6_C2F5_4993_A0D4_7E75C9C335AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BestServerDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBestServerDLG dialog

class CBestServerDLG : public CDialog
{
// Construction
public:
	CBestServerDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBestServerDLG)
	enum { IDD = IDD_BestServerDLG };
	double	m_Tvalue;
	//}}AFX_DATA

CString m_title;	//98/12/27
CString m_label;	//99/04/28

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBestServerDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBestServerDLG)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BESTSERVERDLG_H__3ADC4BE6_C2F5_4993_A0D4_7E75C9C335AA__INCLUDED_)
