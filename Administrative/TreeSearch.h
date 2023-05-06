#if !defined(AFX_TREESEARCH_H__579BCDC9_8BE3_4003_B142_EAB107970B79__INCLUDED_)
#define AFX_TREESEARCH_H__579BCDC9_8BE3_4003_B142_EAB107970B79__INCLUDED_

#include "resource.h"
#include "LeftView.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TreeSearch.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTreeSearch dialog

class CTreeSearch : public CDialog
{
// Construction
public:
	CString m_Lang;
	CLeftView* m_TreeView;
	CTreeSearch(CWnd* pParent = NULL);   // standard constructor
	void TranslateDialog(CDialog *pDialog);
	CString GetTranslatedString(CString strOriginal, CString Lang);
	CString _Z(CString s){ return GetTranslatedString(_T(s),m_Lang); };
	int DoModal();
//	HTREEITEM CTreeSearch::FindItem( HWND hwndTV, CString itemText );
//	HTREEITEM CTreeSearch::FindItemDepthFirstImpl( HWND hwndTV, HTREEITEM htStart, CString itemText );
	HTREEITEM CTreeSearch::FindItem(const CString& name, CTreeCtrl& tree, HTREEITEM hRoot);
	void CTreeSearch::AddFoundItem(HTREEITEM FoundItem);

// Dialog Data
	//{{AFX_DATA(CTreeSearch)
	enum { IDD = IDD_TREE_SEARCH };
	CTreeCtrl	m_SearchResult;
	CString	m_SearchText;
	CButton	m_BeginsWith;
	CButton	m_EndsWith;
	CButton	m_Anywhere;
	CButton	m_ExactMatch;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeSearch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTreeSearch)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDoSearch();
	afx_msg void OnDblclkSearchResult(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREESEARCH_H__579BCDC9_8BE3_4003_B142_EAB107970B79__INCLUDED_)
