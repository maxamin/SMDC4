//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_VECTORHANDLINGVIEW_H__42D472BB_3F89_4BE9_8AC9_9DAF7AC37614__INCLUDED_)
#define AFX_VECTORHANDLINGVIEW_H__42D472BB_3F89_4BE9_8AC9_9DAF7AC37614__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VectorHandlingView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVectorHandlingView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include <afxtempl.h>

#include "SMS4DCDoc.h"
#include "SMS4DCView.h"

class CVectorHandlingView : public CFormView
{
protected:
	CVectorHandlingView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CVectorHandlingView)

// Form Data
public:
	//{{AFX_DATA(CVectorHandlingView)
	enum { IDD = IDD_VectorHandling };
	CButton	m_BUTTON_Exportg;
	CBitmapButton	m_BUTTON_Export;
	CBitmapButton	m_BUTTON_Edit;
	CBitmapButton	m_BUTTON_Delete;
	CBitmapButton	m_BUTTON_Load;
	CMSFlexGrid	m_LIST1;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVectorHandlingView)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CVectorHandlingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CVectorHandlingView)
	afx_msg void OnBUTTONLoad();
	afx_msg void OnBUTTONExport();
	afx_msg void OnBUTTONDelete();
	afx_msg void OnBUTTONExportg();
	afx_msg void OnBUTTONEdit();
	afx_msg void OnDblClickMsflexgrid1();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		void FillList();
		CSMS4DCView * m_pView;
		int m_Rows;
		CToolTipCtrl* m_pToolTip;
		void ActiveButton();
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VECTORHANDLINGVIEW_H__42D472BB_3F89_4BE9_8AC9_9DAF7AC37614__INCLUDED_)
