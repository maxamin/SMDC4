#if !defined(AFX_FILEDLG_CHANGEDTYPE_H__8AC5FB79_FA43_4C41_A9AB_9E4F6E1BAC89__INCLUDED_)
#define AFX_FILEDLG_CHANGEDTYPE_H__8AC5FB79_FA43_4C41_A9AB_9E4F6E1BAC89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileDLG_ChangedType.h : header file
//

#include "Resource.h"
/////////////////////////////////////////////////////////////////////////////
// CFileDLG_ChangedType dialog

class CFileDLG_ChangedType : public CFileDialog
{
	DECLARE_DYNAMIC(CFileDLG_ChangedType)

public:
	CFileDLG_ChangedType(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);
		BOOL m_ShowFlag;
	
		CString m_Lang;

protected:
	//{{AFX_MSG(CFileDLG_ChangedType)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCHECKShowGoogle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

		virtual void OnTypeChange();
		int Split(char *str,char *word[],int max,char c);
		char *newdup(const char *str);
		int				m_nComboLeftMargin;
		DWORD			m_dwFlags;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEDLG_CHANGEDTYPE_H__8AC5FB79_FA43_4C41_A9AB_9E4F6E1BAC89__INCLUDED_)
