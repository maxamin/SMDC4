#if !defined(AFX_ALLOCATIONS_DRAWVIEW_H__F7382B95_FC5E_4DC1_9E3E_F0135E3D395F__INCLUDED_)
#define AFX_ALLOCATIONS_DRAWVIEW_H__F7382B95_FC5E_4DC1_9E3E_F0135E3D395F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Allocations_DrawView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAllocations_DrawView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

//98/05/06
#include "afxdb.h"
#include <odbcinst.h>

class CAllocations_DrawView : public CFormView
{
protected:
	CAllocations_DrawView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CAllocations_DrawView)

// Form Data
public:
	//{{AFX_DATA(CAllocations_DrawView)
	enum { IDD = IDD_Allocations_Draw_FORM };
	CEdit	m_EDIT_Doc;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAllocations_DrawView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnDraw(CDC* pDC);
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CAllocations_DrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CAllocations_DrawView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnEditPlan();
	afx_msg void OnSelchangeCOMBOregions();
	afx_msg void OnSelchangeCOMBOunit();
	afx_msg void OnSelchangeCOMBOscale();
	afx_msg void OnApply();
	afx_msg void OnSelchangeCOMBOArt5();
	afx_msg void OnEditServicetable();
	afx_msg void OnUpdateEditPlan(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditServicetable(CCmdUI* pCmdUI);
	afx_msg void OnEditFootnote();
	afx_msg void OnUpdateEditFootnote(CCmdUI* pCmdUI);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnFileImportPlan();
	afx_msg void OnFileImportServicetable();
	afx_msg void OnFileImportFootnote();
	afx_msg void OnFileExportPlan();
	afx_msg void OnFileExportServicetable();
	afx_msg void OnFileExportFootnote();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void OnFilePrintPreview() ;

//public:
	double m_AxesW,m_AxesW1;
	double m_AxesH,m_AxesH1;
	double m_AxesT,m_AxesT1;
	double m_AxesL,m_AxesL1;
	CString m_SRVstr;
	CString m_SRVstrfot;
	CString m_SRVstrfotPS;
	CString m_Fustr;
	CString m_Bandstr;

	void TextDraw(CDC* pDC,int x, int y,CString str,
							COLORREF FontColor=RGB(0,0,0),
							int Escapement=0,int nHeight=12,int nWidth=0,
							int FontWeight=FW_NORMAL,CString FontName="Arial");
	void DrawRectangle(CDC* pDC,CRgn *rgn,int x1,int y1,int x2,int y2,COLORREF fColor,int SRV_p_s,int SRV_sat) ;

	long ArtS5_codeList(BOOL S5_N);

	long m_ListNUM;
	CString *m_ArtS5_codeList;
	CString Code2Doc(CString code_str , BOOL S5_N);

	CRect m_rcPrintRect;
	CRgn m_rgnSRV[500][12];
		
	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};

	CString CAllocations_DrawView::GetUnitFreq(CString strF);


	int DP_LP(CDC* pDC, int nH_DP);	//97/10/12
	void initDP_LP(CDC * pDC);
	int m_fontH2, m_fontH6, m_fontH12, m_fontH14, m_fontH20, 
		m_fontH24, m_fontH28, m_fontH30, m_fontH40, m_fontH44, m_fontH100,
		m_fontH42, m_fontH48;

	int	m_fontH25,	m_fontH70,	m_fontH75,	m_fontH125,	m_fontH175,	m_fontH245,	m_fontH250,
		m_fontH300,	m_fontH600,	m_fontH630,	m_fontH165,	m_fontH420;


	///////////////// 98/05/06////////////////
	int CAllocations_DrawView::Exist_Table(CString sFile, CString table, CString strPWD);
	void CAllocations_DrawView::Import_Table(CDatabase *sms4dc_DB0, CString mdbPathFile_Src, CString tbl_Src, CString strPWD, 
									 CString mdbPathFile_Plan, CString tbl_Plan);
	void CAllocations_DrawView::File_Import(CString sFilePath, int iTable);
	void CAllocations_DrawView::OnFileImport_(int iTable);

	void CAllocations_DrawView::Export_Table(CDatabase *sms4dc_DB, CString mdbPathFile_Src, CString strPWD, CString mdbPathFile_Plan, CString tbl_Src, CString tbl_Plan);
	void CAllocations_DrawView::File_Export(CString sFilePath, int iTable);
	void CAllocations_DrawView::OnFileExport_(int iTable);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALLOCATIONS_DRAWVIEW_H__F7382B95_FC5E_4DC1_9E3E_F0135E3D395F__INCLUDED_)
