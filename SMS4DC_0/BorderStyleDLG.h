#if !defined(AFX_BORDERSTYLEDLG_H__911286BC_C6A6_450B_87D9_CD8ED60A3019__INCLUDED_)
#define AFX_BORDERSTYLEDLG_H__911286BC_C6A6_450B_87D9_CD8ED60A3019__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BorderStyleDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBorderStyleDLG dialog

class CBorderStyleDLG : public CDialog
{
// Construction
public:
	CBorderStyleDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBorderStyleDLG)
	enum { IDD = IDD_BorderStyleDLG };
	CComboBox	m_LineStyle;
	int		m_LineWidth;
	BYTE	m_LineColorBlue;
	BYTE	m_LineColorGreen;
	BYTE	m_LineColorRed;
	int		m_LineStyle0;
	//}}AFX_DATA
	CString m_Title;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBorderStyleDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBorderStyleDLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnChangeBorderLineWidth();
	afx_msg void OnSelendokBorderLineStyle();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChangeLineColorRed();
	afx_msg void OnChangeLineColorGreen();
	afx_msg void OnChangeLineColorBlue();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		public:
		COLORREF m_color1;	
		void OnVectorLineColor1() ;
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BORDERSTYLEDLG_H__911286BC_C6A6_450B_87D9_CD8ED60A3019__INCLUDED_)
