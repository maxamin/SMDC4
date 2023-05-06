//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_INT_ES2ESOUTDLG_H__3F23ACD0_191A_496A_9D89_9F8DC5694596__INCLUDED_)
#define AFX_INT_ES2ESOUTDLG_H__3F23ACD0_191A_496A_9D89_9F8DC5694596__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Int_ES2ESoutDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInt_ES2ESoutDLG dialog

class CInt_ES2ESoutDLG : public CDialog
{
// Construction
public:
	CInt_ES2ESoutDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInt_ES2ESoutDLG)
	enum { IDD = IDD_Int_ES2ESoutDLG };
	long	m_rowsY;
	CString	m_editX;
	CString	m_editY;
	CMSFlexGrid	m_LIST1;
	CMSFlexGrid	m_LIST2;
	//}}AFX_DATA

	long	m_rowsX;
	CString *m_strXt;
	CString *m_strYt;
	long	*m_rowsYx;

	CString m_Title1, m_Title2, m_Title3;
	int m_mode;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInt_ES2ESoutDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInt_ES2ESoutDLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickMsflexgrid1();
	virtual void OnOK();
	afx_msg void OnClose();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INT_ES2ESOUTDLG_H__3F23ACD0_191A_496A_9D89_9F8DC5694596__INCLUDED_)
