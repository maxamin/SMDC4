//{{AFX_INCLUDES()
#include "adodc.h"
#include "datagrid.h"
#include "StationsTableDoc.h"

//}}AFX_INCLUDES
#if !defined(AFX_STATIONSTABLEVIEW_H__F7929C16_E0B8_4129_ACDA_34970131AA03__INCLUDED_)
#define AFX_STATIONSTABLEVIEW_H__F7929C16_E0B8_4129_ACDA_34970131AA03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StationsTableView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStationsTableView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CStationsTableView : public CFormView
{
protected:
	CStationsTableView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CStationsTableView)

// Form Data
public:
	//{{AFX_DATA(CStationsTableView)
	enum { IDD = IDD_ADO1_FORM };
	CAdodc	m_ADO1;
	BOOL	m_AllowEdit;
	CDataGrid	m_GRID1;
	//}}AFX_DATA
	int m_MaxRowSel,
	m_MaxColSel,
	m_Selcount;
	BOOL m_Entrance;

	Status m_ColStat[1000], m_RowStat[100000];
	CString m_Sel[100];
//	CToolBar m_wndToolBar;

// Attributes
public:
	CStationsTableDoc* GetDocument();

// Operations
public:
	void GetSelection();
	int FindOrigRow(int j);
	CString GetRowText(int j);
	int GetRow(int X, int Y);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStationsTableView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CStationsTableView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CStationsTableView)
	afx_msg void OnCheck1();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseUpDatagrid1(short Button, short Shift, long X, long Y);
	afx_msg void OnExport();
	afx_msg void OnImport();
	afx_msg void OnDataBaseSortAZ();
	afx_msg void OnDataBaseSortZA();
	afx_msg void OnAsAntenna();
	afx_msg void OnShowPattern();
	afx_msg void OnBUTTONTx();
	afx_msg void OnBUTTONRx();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	void OnFilePrintPreview();
	void TxRxFilters(BOOL TxRx) ;

};

#ifndef _DEBUG  // debug version in ADO1View.cpp
inline CStationsTableDoc* CStationsTableView::GetDocument()
   { return (CStationsTableDoc*)m_pDocument; }
#endif
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATIONSTABLEVIEW_H__F7929C16_E0B8_4129_ACDA_34970131AA03__INCLUDED_)
