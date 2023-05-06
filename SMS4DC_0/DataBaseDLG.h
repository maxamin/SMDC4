//{{AFX_INCLUDES()

#include "msflexgrid.h"

//}}AFX_INCLUDES
#if !defined(AFX_DATABASEDLG_H__F146C568_5C51_4B20_B5EA_207CD61D1DD5__INCLUDED_)
#define AFX_DATABASEDLG_H__F146C568_5C51_4B20_B5EA_207CD61D1DD5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataBaseDLG.h : header file
//


#include "DGrid.h"
/////////////////////////////////////////////////////////////////////////////
// CDataBaseDLG dialog

class CDataBaseDLG : public CDialog
{
// Construction
public:
	CDataBaseDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDataBaseDLG)
	enum { IDD = IDD_DataBase1 };
	CBitmapButton	m_BUTTON_Report;
	CBitmapButton	m_Sort_ZA;
	CBitmapButton	m_Sort_AZ;
	CDGrid	m_DataGrid;
	BOOL	m_Heff1;
	BOOL	m_Heff;
	BOOL	m_ReportFlag;
	//}}AFX_DATA
	CString m_Title;
	long m_O;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataBaseDLG)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolBar    m_wndToolBar;
	HICON m_hIcon;

	CToolTipCtrl* m_pToolTip;

	// Generated message map functions
	//{{AFX_MSG(CDataBaseDLG)
	afx_msg void OnSizing( UINT, LPRECT ); 
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSortAZ();
	virtual BOOL OnInitDialog();
	afx_msg void OnSortZA();
	afx_msg void OnMouseUpMsflexgrid1(short Button, short Shift, long x, long y);
	afx_msg void OnCHECKHeff();
	virtual void OnOK();
	afx_msg void OnBUTTONReport();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		BOOL m_GridLoaded;
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATABASEDLG_H__F146C568_5C51_4B20_B5EA_207CD61D1DD5__INCLUDED_)
