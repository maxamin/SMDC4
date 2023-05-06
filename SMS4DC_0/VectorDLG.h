#if !defined(AFX_VECTORDLG_H__0951D07A_29C5_4D05_8410_F6495F0461B9__INCLUDED_)
#define AFX_VECTORDLG_H__0951D07A_29C5_4D05_8410_F6495F0461B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VectorDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVectorDLG dialog

class CVectorDLG : public CDialog
{
// Construction
public:
	CVectorDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVectorDLG)
	enum { IDD = IDD_VectorDLG };
	CSliderCtrl	m_SliderFillTransparancy;
	CComboBox	m_LineStyle;
	int		m_LineWidth;
	BOOL	m_FillMode;
	BYTE   		m_LineColorBlue;
	BYTE   		m_LineColorGreen;
	BYTE   		m_LineColorRed;
	BYTE   		m_FillColorBlue;
	BYTE   		m_FillColorGreen;
	BYTE   		m_FillColorRed;
	int		m_LineStyle0;
	int	m_FillTransparancy;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVectorDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVectorDLG)
	afx_msg void OnVectorFillMode();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelendokVectorLineStyle();
	afx_msg void OnChangeVectorLineWidth();
	afx_msg void OnPaint();
	afx_msg void OnChangeVectorFillTransparancy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnChangeLineColorRed();
	afx_msg void OnChangeLineColorGreen();
	afx_msg void OnChangeLineColorBlue();
	afx_msg void OnChangeFillColorRed();
	afx_msg void OnChangeFillColorGreen();
	afx_msg void OnChangeFillColorBlue();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CString m_TitleName;
	COLORREF m_color1;
	COLORREF m_color2;

	void OnVectorLineColor1(); 
	void OnVectorFillColor1();
	int m_Pos;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VECTORDLG_H__0951D07A_29C5_4D05_8410_F6495F0461B9__INCLUDED_)
