#if !defined(AFX_CIRCLERADIUSDLG_H__3ACE4411_71F5_4076_A72D_FB30DAAC74F3__INCLUDED_)
#define AFX_CIRCLERADIUSDLG_H__3ACE4411_71F5_4076_A72D_FB30DAAC74F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CircleRadiusDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCircleRadiusDLG dialog

class CCircleRadiusDLG : public CDialog
{
// Construction
public:
	CCircleRadiusDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCircleRadiusDLG)
	enum { IDD = IDD_CircleRadiusDLG };
	double	m_CircleRadius;
	CString	m_title;
	CString	m_lable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCircleRadiusDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCircleRadiusDLG)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CIRCLERADIUSDLG_H__3ACE4411_71F5_4076_A72D_FB30DAAC74F3__INCLUDED_)
