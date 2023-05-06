#if !defined(AFX_LOSDLG_H__3380DE47_A877_4B88_9671_A4B189B7BC6F__INCLUDED_)
#define AFX_LOSDLG_H__3380DE47_A877_4B88_9671_A4B189B7BC6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoSDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoSDLG dialog

class CLoSDLG : public CDialog
{
// Construction
public:
	CLoSDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLoSDLG)
	enum { IDD = IDD_LoSDLG };
	double	m_kfactor;
	double	m_RxH;
	CString	m_title;
	BOOL	m_Overlap;
	double	m_Fd;
	double	m_RPR;
	//}}AFX_DATA
	CString	m_title1;
	int	m_overlapDisp;
	int	m_FdDisp;

	int	m_stepDisp;
	int	m_step;

	int	m_bcbtDisp;
	CString	m_bcbt;
	int	m_AntDisc;

	BOOL m_nFter;

	BOOL m_Monitoring;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoSDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLoSDLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	afx_msg void OnRadio6();
	afx_msg void OnRadio7();
	afx_msg void OnCHECKAntDisc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		void RPR_FUNCTION(); 
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOSDLG_H__3380DE47_A877_4B88_9671_A4B189B7BC6F__INCLUDED_)
