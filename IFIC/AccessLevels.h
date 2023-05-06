#if !defined(AFX_ACCESSLEVELS_H__2CEB7B45_946C_4482_9204_B74B5C135E41__INCLUDED_)
#define AFX_ACCESSLEVELS_H__2CEB7B45_946C_4482_9204_B74B5C135E41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AccessLevels.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAccessLevels dialog

class CAccessLevels : public CDialog
{
// Construction
public:
	CAccessLevels(CWnd* pParent = NULL);   // standard constructor
	void TranslateDialog(CDialog *pDialog);
	CString GetTranslatedString(CString strOriginal, CString Lang);
	CString _Z(CString s){ return GetTranslatedString(_T(s),m_Lang); };
	CString m_CDBSTR, m_Lang;
// Dialog Data
	//{{AFX_DATA(CAccessLevels)
	enum { IDD = IDD_ACCESSLEVEL };
	CComboBox	m_UserMod;
	CComboBox	m_AccessLevel;
	CString	m_PassAdd;
	CString	m_PassMod;
	CString	m_UserAdd;
	BOOL	m_Enabled;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAccessLevels)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void OnOK();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAccessLevels)
	virtual BOOL OnInitDialog();
	afx_msg void OnNew();
	afx_msg void OnModify();
	afx_msg void OnSave();
	afx_msg void OnDelete();
	afx_msg void OnSelchangeUsermod();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACCESSLEVELS_H__2CEB7B45_946C_4482_9204_B74B5C135E41__INCLUDED_)
