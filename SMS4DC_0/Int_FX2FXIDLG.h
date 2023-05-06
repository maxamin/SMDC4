//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_INT_FX2FXIDLG_H__75262204_BD47_4CDC_A1D7_B236AEB23D12__INCLUDED_)
#define AFX_INT_FX2FXIDLG_H__75262204_BD47_4CDC_A1D7_B236AEB23D12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Int_FX2FXIDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInt_FX2FXIDLG dialog

class CInt_FX2FXIDLG : public CDialog
{
// Construction
public:
	CInt_FX2FXIDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInt_FX2FXIDLG)
	enum { IDD = IDD_Int_FX2FXIDLG };
	long	m_rowsY;
	CString	m_editX;
	CString	m_editY;
	CMSFlexGrid	m_LIST1;
	CMSFlexGrid	m_LIST2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInt_FX2FXIDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInt_FX2FXIDLG)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		CString m_dataX, m_dataY;
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INT_FX2FXIDLG_H__75262204_BD47_4CDC_A1D7_B236AEB23D12__INCLUDED_)
