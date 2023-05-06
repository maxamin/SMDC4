#if !defined(AFX_AP7_STYLEDLG_H__C9392490_3F13_44D1_9122_F20A0BDF39C3__INCLUDED_)
#define AFX_AP7_STYLEDLG_H__C9392490_3F13_44D1_9122_F20A0BDF39C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Ap7_StyleDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAp7_StyleDLG dialog

class CAp7_StyleDLG : public CDialog
{
// Construction
public:
	CAp7_StyleDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAp7_StyleDLG)
	enum { IDD = IDD_Ap7_StyleDLG };
	CComboBox	m_LineStyle8;
	CComboBox	m_LineStyle7;
	CComboBox	m_LineStyle6;
	CComboBox	m_LineStyle5;
	CComboBox	m_LineStyle4;
	CComboBox	m_LineStyle3;
	CComboBox	m_LineStyle2;
	CComboBox	m_LineStyle1;
	int		m_LineWidth1;
	BYTE	m_LineColorBlue1;
	BYTE	m_LineColorGreen1;
	BYTE	m_LineColorRed1;
	int		m_LineStyle01;
	int		m_LineWidth2;
	BYTE	m_LineColorBlue2;
	BYTE	m_LineColorGreen2;
	BYTE	m_LineColorRed2;
	int		m_LineStyle02;
	int		m_LineWidth3;
	int		m_LineWidth4;
	int		m_LineWidth5;
	int		m_LineWidth6;
	int		m_LineWidth7;
	int		m_LineWidth8;
	BYTE	m_LineColorBlue3;
	BYTE	m_LineColorBlue4;
	BYTE	m_LineColorBlue5;
	BYTE	m_LineColorBlue6;
	BYTE	m_LineColorBlue7;
	BYTE	m_LineColorBlue8;
	BYTE	m_LineColorGreen3;
	BYTE	m_LineColorGreen4;
	BYTE	m_LineColorGreen5;
	BYTE	m_LineColorGreen6;
	BYTE	m_LineColorGreen7;
	BYTE	m_LineColorGreen8;
	BYTE	m_LineColorRed3;
	BYTE	m_LineColorRed4;
	BYTE	m_LineColorRed5;
	BYTE	m_LineColorRed6;
	BYTE	m_LineColorRed7;
	BYTE	m_LineColorRed8;
	int		m_LineStyle03;
	int		m_LineStyle04;
	int		m_LineStyle05;
	int		m_LineStyle06;
	int		m_LineStyle07;
	int		m_LineStyle08;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAp7_StyleDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAp7_StyleDLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnChangeBorderLineWidth1();
	afx_msg void OnSelendokBorderLineStyle1();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChangeBorderLineWidth2();
	afx_msg void OnChangeBorderLineWidth3();
	afx_msg void OnChangeBorderLineWidth4();
	afx_msg void OnChangeBorderLineWidth5();
	afx_msg void OnChangeBorderLineWidth6();
	afx_msg void OnChangeBorderLineWidth7();
	afx_msg void OnChangeBorderLineWidth8();
	afx_msg void OnSelendokBorderLineStyle2();
	afx_msg void OnSelendokBorderLineStyle3();
	afx_msg void OnSelendokBorderLineStyle4();
	afx_msg void OnSelendokBorderLineStyle5();
	afx_msg void OnSelendokBorderLineStyle6();
	afx_msg void OnSelendokBorderLineStyle7();
	afx_msg void OnSelendokBorderLineStyle8();
	afx_msg void OnChangeLineColorRed1();
	afx_msg void OnChangeLineColorRed2();
	afx_msg void OnChangeLineColorRed3();
	afx_msg void OnChangeLineColorRed4();
	afx_msg void OnChangeLineColorRed5();
	afx_msg void OnChangeLineColorRed6();
	afx_msg void OnChangeLineColorRed7();
	afx_msg void OnChangeLineColorRed8();
	afx_msg void OnChangeLineColorGreen1();
	afx_msg void OnChangeLineColorGreen2();
	afx_msg void OnChangeLineColorGreen3();
	afx_msg void OnChangeLineColorGreen4();
	afx_msg void OnChangeLineColorGreen5();
	afx_msg void OnChangeLineColorGreen6();
	afx_msg void OnChangeLineColorGreen7();
	afx_msg void OnChangeLineColorGreen8();
	afx_msg void OnChangeLineColorBlue1();
	afx_msg void OnChangeLineColorBlue2();
	afx_msg void OnChangeLineColorBlue3();
	afx_msg void OnChangeLineColorBlue4();
	afx_msg void OnChangeLineColorBlue5();
	afx_msg void OnChangeLineColorBlue6();
	afx_msg void OnChangeLineColorBlue7();
	afx_msg void OnChangeLineColorBlue8();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		public:
		COLORREF m_color1,m_color2,m_color3,m_color4,m_color5,m_color6,m_color7,m_color8;	
		void OnVectorLineColor1() ;
		void OnVectorLineColor2() ;
		void OnVectorLineColor3() ;
		void OnVectorLineColor4() ;
		void OnVectorLineColor5() ;
		void OnVectorLineColor6() ;
		void OnVectorLineColor7() ;
		void OnVectorLineColor8() ;


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AP7_STYLEDLG_H__C9392490_3F13_44D1_9122_F20A0BDF39C3__INCLUDED_)
