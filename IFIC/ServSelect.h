#if !defined(AFX_SERVSELECT_H__8060F7CB_A560_4953_9E21_D454BFFB6B65__INCLUDED_)
#define AFX_SERVSELECT_H__8060F7CB_A560_4953_9E21_D454BFFB6B65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServSelect.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CServSelect dialog

class CServSelect : public CDialog
{
// Construction
public:
	CServSelect(CWnd* pParent = NULL);   // standard constructor
	CString m_Result, m_Lang;
	bool m_Fixed;
	void TranslateDialog(CDialog *pDialog);
	CString GetTranslatedString(CString strOriginal, CString Lang);
	CString _Z(CString s){ return GetTranslatedString(_T(s),m_Lang); };
// Dialog Data
	//{{AFX_DATA(CServSelect)
	enum { IDD = IDD_SERVSELECT };
	CListBox	m_ServList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServSelect)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CServSelect)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVSELECT_H__8060F7CB_A560_4953_9E21_D454BFFB6B65__INCLUDED_)
