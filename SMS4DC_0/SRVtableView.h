#if !defined(AFX_SRVTABLEVIEW_H__CD372C12_E661_47B7_8D30_2C8FDA00C059__INCLUDED_)
#define AFX_SRVTABLEVIEW_H__CD372C12_E661_47B7_8D30_2C8FDA00C059__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SRVtableView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSRVtableView record view

#include "SRVtableSet.h"

class CSRVtableView : public CRecordView
{
protected:
	CSRVtableView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSRVtableView)

// Form Data
public:
	//{{AFX_DATA(CSRVtableView)
	enum { IDD = IDD_SRVtableDLG };
	CSRVtableSet* m_pSet;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	CSRVtableSet* GetRecordset();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSRVtableView)
		// NOTE - the ClassWizard will add and remove member functions here.
	public:
	virtual CRecordset* OnGetRecordset();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSRVtableView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CSRVtableView)
	afx_msg void OnRecordFirst();
	afx_msg void OnRecordPrev();
	afx_msg void OnRecordNext();
	afx_msg void OnRecordLast();
	afx_msg void OnRecordAdd();
	afx_msg void OnRecordSub();
	afx_msg void OnUpdateRecordNext(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecordLast(CCmdUI* pCmdUI);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChangeEDITRed();
	afx_msg void OnChangeEDITBlue();
	afx_msg void OnChangeEDITGreen();
	afx_msg void OnRecordSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	int m_num;
	int m_count;
	void OnAppend() ;
	void OnDelete() ;
	COLORREF m_color1;
	void OnColor2() ;

	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRVTABLEVIEW_H__CD372C12_E661_47B7_8D30_2C8FDA00C059__INCLUDED_)
