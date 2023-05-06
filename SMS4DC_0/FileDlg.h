#if !defined(AFX_FILEDLG_H__DCD0183C_6263_4470_A67C_C7D1BCC825B2__INCLUDED_)
#define AFX_FILEDLG_H__DCD0183C_6263_4470_A67C_C7D1BCC825B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileDlg dialog

class CFileDlg : public CDialog
{
// Construction
public:
	CFileDlg(CWnd* pParent = NULL);   // standard constructor

	CFileDlg(BOOL bOpenFileDialog, LPCTSTR lpszDefExt , 
				   LPCTSTR lpszFileName , 
				   DWORD dwFlags , 
				   LPCTSTR lpszFilter , CWnd* pParentWnd );

	BOOL GetDirectories(CString Path);
	BOOL GetFiles(CString Path,CString Filter);
	void DelLastDir();


// Dialog Data
	//{{AFX_DATA(CFileDlg)
	enum { IDD = IDD_FileDLG };
	CListCtrl	m_DirListCtrl;
	CListBox	m_FilesList;
	CListBox	m_DirList;
	CEdit	m_FileName;
	CComboBox	m_FileType;
	CComboBox	m_Drive;
	//}}AFX_DATA
	bool m_DlgType;
	CString m_DefExt, m_FName, m_Filter, m_Path;
	CImageList m_ListIcons;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileDlg)
	afx_msg void OnSelchangeCOMBODrive();
	afx_msg void OnSelchangeCOMBOType();
	afx_msg void OnDblclkLISTDirectories();
	afx_msg void OnSelchangeLISTFiles();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkLISTDirectoties(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEDLG_H__DCD0183C_6263_4470_A67C_C7D1BCC825B2__INCLUDED_)
