#if !defined(AFX_PROPSELECT_H__96F2AFA8_9787_4C02_915B_78E9B27361D4__INCLUDED_)
#define AFX_PROPSELECT_H__96F2AFA8_9787_4C02_915B_78E9B27361D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropSelect.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropSelect dialog

class CPropSelect : public CDialog
{
// Construction
public:
	CPropSelect(CWnd* pParent = NULL);   // standard constructor
	CString m_Result, m_Lang;
	void TranslateDialog(CDialog *pDialog);
	CString GetTranslatedString(CString strOriginal, CString Lang);
	CString _Z(CString s){ return GetTranslatedString(_T(s),m_Lang); };

// Dialog Data
	//{{AFX_DATA(CPropSelect)
	enum { IDD = IDD_PROPSELECT };
	CListBox	m_Props;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropSelect)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPropSelect)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPSELECT_H__96F2AFA8_9787_4C02_915B_78E9B27361D4__INCLUDED_)
