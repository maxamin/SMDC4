#if !defined(AFX_HORIZONDISTANCEDLG_H__D9211EEA_9A6B_4BA0_9FA6_490B8CF34042__INCLUDED_)
#define AFX_HORIZONDISTANCEDLG_H__D9211EEA_9A6B_4BA0_9FA6_490B8CF34042__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HorizonDistanceDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHorizonDistanceDLG dialog

class CHorizonDistanceDLG : public CDialog
{
// Construction
public:
	CHorizonDistanceDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHorizonDistanceDLG)
	enum { IDD = IDD_HorizonDisttanceDLG };
	double	m_HA;
	double	m_HB;
	CString	m_K;
	double	m_R;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHorizonDistanceDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHorizonDistanceDLG)
	afx_msg void OnPaint();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	double atof_kfactor(CString k1) ;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HORIZONDISTANCEDLG_H__D9211EEA_9A6B_4BA0_9FA6_490B8CF34042__INCLUDED_)
