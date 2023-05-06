#if !defined(AFX_BEPOLAR_H__F185C6CC_6813_46D5_A3D0_58C3DBDC6A70__INCLUDED_)
#define AFX_BEPOLAR_H__F185C6CC_6813_46D5_A3D0_58C3DBDC6A70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BEpolar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBEpolar dialog

class CBEpolar : public CDialog
{
// Construction
public:
	CBEpolar(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBEpolar)
	enum { IDD = IDD_DIALOG1 };
	CComboBox	m_COMBO_Time;
	CComboBox	m_COMBO_Fr;
	//}}AFX_DATA

	struct FieldValueD
	{
  		CArray<double, double> List;
   		CArray<long, long> Index;
		double max;
		double min;
		BOOL flag;
	};
	FieldValueD	m_L;	//Level
	FieldValueD	m_Q;	//Quality
	FieldValueD	m_D;	//Direction
	CStringArray m_ListDateTime;

	BOOL m_flagLQ;
	CString m_Lu;
	BOOL m_Meanflag;

	FieldValueD	m_F;	//Frequency
	FieldValueD	m_L1;	//Level
	FieldValueD	m_Q1;	//Quality
	FieldValueD	m_D1;	//Direction
	CStringArray m_ListDateTime1;

	CString m_Lang;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBEpolar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBEpolar)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnCheck1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSelchangeCOMBOFr();
	afx_msg void OnSelchangeCOMBOTime();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

	void DrawPattern(BOOL HV=true,int x0=305,int y0=305,int radius=280,int offset = 25);
	void DrawEllipse(BOOL nMode,int x1,int y1,int x2,int y2,int nStyle=PS_SOLID,int nWidth=1,COLORREF pColor=RGB(0,0,0),int x3=0,int y3=0,int x4=0,int y4=0,COLORREF bColor=RGB(255,255,255)); 
	int m_ThickLines;
	BOOL m_fill;
	COLORREF m_fillcolor;
	int	m_5degreestick;
	void DrawLine(int x1,int y1,int x2,int y2,int nStyle=PS_SOLID,int nWidth=1,COLORREF pColor=RGB(0,0,0)); 

	BOOL m_flag;
	int Contour(double y,double MinV,double MaxV,int nL);
	COLORREF RGBt[256];
	CString m_colormaptype;
	void ColorMap(CString type);
	BOOL m_single;
	long m_i;
	void Set_Static_R() ;


	void GetFrequency();
		
	CString _Z(CString s){return (((CArgusWFdllApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BEPOLAR_H__F185C6CC_6813_46D5_A3D0_58C3DBDC6A70__INCLUDED_)
