#if !defined(AFX_ANTENNAFORMVIEW_H__5EFC9FC2_9E79_4012_AC03_A2E9C6C8688E__INCLUDED_)
#define AFX_ANTENNAFORMVIEW_H__5EFC9FC2_9E79_4012_AC03_A2E9C6C8688E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AntennaFormView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAntennaFormView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CAntennaFormView : public CFormView
{
protected:
	CAntennaFormView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CAntennaFormView)

// Form Data
public:
	//{{AFX_DATA(CAntennaFormView)
	enum { IDD = IDD_ANTENNA_FORM };
	CListBox	m_list;
	CString	m_Ang;
	CString	m_AttnH;
	CString	m_AttnV;
	double	m_Frq_Hi;
	double	m_Frq_Lo;
	CString	m_Frq_unit;
	double	m_Gain_dBi;
	CString	m_Name;
	CString	m_Polarization;
	double	m_BeamWidth_H;
	double	m_BeamWidth_V;
	double	m_AllValue;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAntennaFormView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CAntennaFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CAntennaFormView)
	afx_msg void OnOptionThicklines();
	afx_msg void OnUpdateOptionThicklines(CCmdUI* pCmdUI);
	afx_msg void OnOption5degreestick();
	afx_msg void OnUpdateOption5degreestick(CCmdUI* pCmdUI);
	afx_msg void OnOption1degreestick();
	afx_msg void OnUpdateOption1degreestick(CCmdUI* pCmdUI);
	afx_msg void OnOption1dbtick();
	afx_msg void OnUpdateOption1dbtick(CCmdUI* pCmdUI);
	afx_msg void OnLoad();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSelchangeLISTPattern();
	afx_msg void OnSave();
	afx_msg void OnChangeEDITAttnH();
	afx_msg void OnChangeEDITAttnV();
	afx_msg void OnOmni();
	afx_msg void OnClear();
	afx_msg void OnSetAll();
	afx_msg void OnOptionFilldiagram();
	afx_msg void OnUpdateOptionFilldiagram(CCmdUI* pCmdUI);
	afx_msg void OnOptionHorizontalpattern();
	afx_msg void OnUpdateOptionHorizontalpattern(CCmdUI* pCmdUI);
	afx_msg void OnOptionVerticalpattern();
	afx_msg void OnUpdateOptionVerticalpattern(CCmdUI* pCmdUI);
	afx_msg void OnOption3dgraph();
	afx_msg void OnHor();
	afx_msg void OnVer();
	afx_msg void On3d();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL m_HV;
	int  m_Angle[360];
	double m_PatternH[360],m_PatternV[360];
	CString m_antfile;

	int m_ThickLines;
	int	m_5degreestick;
	BOOL m_1degreestick;
	BOOL m_1dbtick;

	BOOL m_fill;
	COLORREF m_fillcolor;

	BOOL m_lbutton;

	int m_X, m_Y, m_radius, m_Xp, m_Yp;
	void ReadData(CString antfile);
	void DrawPattern(CDC* pDC,BOOL HV=1);
	void DrawEllipse(CDC* pDC,BOOL nMode,int x1,int y1,int x2,int y2,int nStyle=PS_SOLID,int nWidth=1,COLORREF pColor=RGB(0,0,0),int x3=0,int y3=0,int x4=0,int y4=0,COLORREF bColor=RGB(255,255,255)); 
	void DrawLine(CDC* pDC,int x1,int y1,int x2,int y2,int nStyle=PS_SOLID,int nWidth=1,COLORREF pColor=RGB(0,0,0)); 
	void Draw3Angle(CDC* pDC,int x1,int y1,int x2,int y2,int x3,int y3,int nStyle=PS_SOLID,int nWidth=1,COLORREF pColor=RGB(255,0,0),COLORREF bColor=RGB(255,0,0));
	int Round(double x); 
	int DrawLable(CDC* pDC,int x,int y,CString str,int nSize=12,COLORREF nColor=RGB(0,0,0),CString nFontname="Arial") ;
	int WriteToFile(CString FileName);
	void SetValue(double Val);

	CRect m_rcPrintRect;
	int m_AxesT,m_AxesH,m_AxesW,m_AxesL;
	int m_AxesT1,m_AxesH1,m_AxesW1,m_AxesL1;
	void OnFilePrintPreview() ;
	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANTENNAFORMVIEW_H__5EFC9FC2_9E79_4012_AC03_A2E9C6C8688E__INCLUDED_)
