
#include "resource.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IFICImport.h : header file
//

class CSetExtensionDllState
{
public:
	CSetExtensionDllState()
	{
		HINSTANCE hResourceModule = ::GetModuleHandle( _T("Administrative.dll"));
		ASSERT( hResourceModule );	
		m_hOld = AfxGetResourceHandle();
		AfxSetResourceHandle( hResourceModule);
		return;
	}

	~CSetExtensionDllState()
	{
		AfxSetResourceHandle( m_hOld);
		return;
	}

private:
	HINSTANCE m_hOld;
};

/////////////////////////////////////////////////////////////////////////////
// CCustomReport dialog

class CCustomReport : public CDialog
{
// Construction
public:
	CCustomReport(CWnd* pParent = NULL);   // standard constructor
	void TranslateDialog(CDialog *pDialog);
	CString GetTranslatedString(CString strOriginal, CString Lang);
	CString _Z(CString s){ return GetTranslatedString(_T(s),m_Lang); };
	int DoModal();
	CString m_CDBSTR, m_Lang;
// Dialog Data
	//{{AFX_DATA(CCustomReport)
	enum { IDD = IDD_CUSTOM_REPORT };
	CButton	m_FreqRem;
	CButton	m_Licensed;
	CButton	m_Unlicensed;
	CButton	m_All;
	CComboBox	m_Owner;
	CComboBox	m_License;
	CButton	m_FS;
	CButton	m_LMS;
	CButton	m_BS;
	CListBox	m_FreqCondSel;
	CListBox	m_FreqCond;
	CButton	m_FreqAdd;
	CComboBox	m_F2U;
	CEdit	m_F2;
	CComboBox	m_F1U;
	CEdit	m_F1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomReport)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCustomReport)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeFreqCond();
	afx_msg void OnSelchangeOwner();
	afx_msg void OnFreqAdd();
	virtual void OnOK();
	afx_msg void OnFreqRem();
	afx_msg void OnLicensed();
	afx_msg void OnUnlicensed();
	afx_msg void OnAll();
	virtual void OnCancel();
	//}}AFX_MSG
	double GetFreqUnit(CString Unit);
	CString GetFreqCond();
	CString GetFragList();
	void CreateReport(CDatabase m_DB, CRecordset m_rs);
	void RemoveQuote(CString *Str);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

