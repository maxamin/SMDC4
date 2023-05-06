//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_INT_FX2FXDLG_H__43CF5D6A_BB19_4D2C_9E0C_BACE6345C879__INCLUDED_)
#define AFX_INT_FX2FXDLG_H__43CF5D6A_BB19_4D2C_9E0C_BACE6345C879__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Int_FX2FXDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInt_FX2FXDLG dialog

class CInt_FX2FXDLG : public CDialog
{
// Construction
public:
	CInt_FX2FXDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInt_FX2FXDLG)
	enum { IDD = IDD_Int_FX2FXDLG };
	CString	m_editX;
	CString	m_editY;
	long	m_rowsY;
	CMSFlexGrid	m_LIST1;
	CMSFlexGrid	m_LIST2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInt_FX2FXDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInt_FX2FXDLG)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		CString m_dataX, m_dataY;
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INT_FX2FXDLG_H__43CF5D6A_BB19_4D2C_9E0C_BACE6345C879__INCLUDED_)
