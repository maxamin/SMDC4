#if !defined(AFX_FOLDERDLG_H__E1B8B449_D4AA_4EE7_A506_94C248826A67__INCLUDED_)
#define AFX_FOLDERDLG_H__E1B8B449_D4AA_4EE7_A506_94C248826A67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FolderDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFolderDLG dialog

class CFolderDLG : public CDialog
{
// Construction
public:
	CFolderDLG(CWnd* pParent = NULL);   // standard constructor

	CFolderDLG(BOOL bOpenFileDialog, LPCTSTR lpszDefExt , 
				   LPCTSTR lpszFileName , 
				   DWORD dwFlags , 
				   LPCTSTR lpszFilter , CWnd* pParentWnd );

	BOOL GetDirectories(CString Path);
	void DelLastDir();




// Dialog Data
	//{{AFX_DATA(CFolderDLG)
	enum { IDD = IDD_FolderDLG };
	CEdit	m_FileName;
	CComboBox	m_Drive;
	CListCtrl	m_DirListCtrl;
	//}}AFX_DATA

	bool m_DlgType;
	CString m_DefExt, m_FName, m_Filter, m_Path;
	CImageList m_ListIcons;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFolderDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFolderDLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCOMBODrive();
	virtual void OnOK();
	afx_msg void OnDblclkLISTDirectoties(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOLDERDLG_H__E1B8B449_D4AA_4EE7_A506_94C248826A67__INCLUDED_)
