#if !defined(AFX_STARTDLG_H__F70540CC_528F_42AB_8994_FC39F391DC46__INCLUDED_)
#define AFX_STARTDLG_H__F70540CC_528F_42AB_8994_FC39F391DC46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StartDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStartDLG dialog

class CStartDLG : public CDialog
{
// Construction
public:
	CStartDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStartDLG)
	enum { IDD = IDD_StartDLG };
	CComboBox	m_COMBO_Lang;
	CString	m_UserName;
	CString	m_UserPassword;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStartDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStartDLG)
	afx_msg void OnPaint();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCOMBOLang();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
			
		CString m_LanguageFile;
		void CreateLanguageFile(CString mLang);
		void ReadLanguageFile();
		void LanguageQ();
	//	CBrush m_brush;
	//	COLORREF m_c1;

		HBITMAP ReplaceColor (HBITMAP hBmp, COLORREF cNewColor, HDC hBmpDC=NULL);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STARTDLG_H__F70540CC_528F_42AB_8994_FC39F391DC46__INCLUDED_)
