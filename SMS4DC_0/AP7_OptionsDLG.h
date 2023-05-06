//{{AFX_INCLUDES()
//#include "msflexgrid.h"

//#include "EditGrid.h"

//}}AFX_INCLUDES
#if !defined(AFX_AP7_OPTIONSDLG_H__F0EC222C_BCE3_4E30_836B_B28A7B8E0802__INCLUDED_)
#define AFX_AP7_OPTIONSDLG_H__F0EC222C_BCE3_4E30_836B_B28A7B8E0802__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AP7_OptionsDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAP7_OptionsDLG dialog

class CAP7_OptionsDLG : public CDialog
{
// Construction
public:
	CAP7_OptionsDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAP7_OptionsDLG)
	enum { IDD = IDD_AP7_OptionsDLG };
	CString	m_BDIRPC;
	CString	m_GMIN;
	CString	m_INCLINATION;
	CString	m_RECVPC;
	CString	m_SATEAST;
	CString	m_SATWEST;
	CString	m_TRANPC;
	BOOL	m_Manned;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAP7_OptionsDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAP7_OptionsDLG)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AP7_OPTIONSDLG_H__F0EC222C_BCE3_4E30_836B_B28A7B8E0802__INCLUDED_)
