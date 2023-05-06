#if !defined(AFX_LEGENDDLG_H__C4B8B09F_708A_40CE_9ACC_5BE3FA27FA3E__INCLUDED_)
#define AFX_LEGENDDLG_H__C4B8B09F_708A_40CE_9ACC_5BE3FA27FA3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LegendDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLegendDLG dialog

class CLegendDLG : public CDialog
{
// Construction
public:
	CLegendDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLegendDLG)
	enum { IDD = IDD_LegendDLG };
	double	m_MinValue;
	double	m_MaxValue;
	CString	m_title;
	CString	m_colormaptype;
	int		m_level;
	BOOL	m_bThreshold;
	double	m_Threshold;
	int		m_colorRate;
	//}}AFX_DATA
	BOOL m_ColorMapNegative;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLegendDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	public:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
//protected:
public:
	// Generated message map functions
	//{{AFX_MSG(CLegendDLG)
	afx_msg void OnPaint();
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEGENDDLG_H__C4B8B09F_708A_40CE_9ACC_5BE3FA27FA3E__INCLUDED_)
