#if !defined(AFX_CONTOURDLG_H__48551800_1861_48B4_8AF7_D71830B20E45__INCLUDED_)
#define AFX_CONTOURDLG_H__48551800_1861_48B4_8AF7_D71830B20E45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ContourDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CContourDLG dialog

class CContourDLG : public CDialog
{
// Construction
public:
	CContourDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CContourDLG)
	enum { IDD = IDD_ContourDLG };
	double	m_max;
	double	m_min;
	int		m_nL;
	double	m_step;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CContourDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CContourDLG)
	afx_msg void OnChangeEDITstep();
	afx_msg void OnChangeEDITnL();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTOURDLG_H__48551800_1861_48B4_8AF7_D71830B20E45__INCLUDED_)
