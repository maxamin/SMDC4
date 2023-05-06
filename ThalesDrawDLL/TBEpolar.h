#if !defined(AFX_TBEPOLAR_H__D830CD76_04D7_4692_A3EE_68FC5E8523D8__INCLUDED_)
#define AFX_TBEPOLAR_H__D830CD76_04D7_4692_A3EE_68FC5E8523D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TBEpolar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTBEpolar dialog

class CTBEpolar : public CDialog
{
// Construction
public:
	CTBEpolar(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTBEpolar)
	enum { IDD = IDD_DIALOG_TBE };
	CComboBox	m_COMBO_Time;
	CComboBox	m_COMBO_Fr;
	//}}AFX_DATA

	CStringArray	m_F;			//Frequency
	CArray<double,double>	m_L1;	//Level
	CArray<double,double>	m_Q1;	//Quality
	CArray<double,double>	m_D1;	//Direction
	CStringArray m_TimeListREStotal;	//Time

	CArray<double,double>	m_L;	//Level
	CArray<double,double>	m_Q;	//Quality
	CArray<double,double>	m_D;	//Direction
	CStringArray m_ListDateTime;	//Time

	double m_Qmin, m_Qmax;
	double m_Lmin, m_Lmax;

	CStringArray m_FreqUniq;
	COLORREF m_fillcolor;
	CString m_colormaptype;
	int m_ThickLines;

	BOOL m_flagLQ;
	CString m_Lu;

	CString	m_PathName, m_TxName, m_MOlon_degStr, m_MOlat_degStr;

	CString m_Lang;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTBEpolar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTBEpolar)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnCheck1();
	afx_msg void OnSelchangeCOMBOFr();
	afx_msg void OnSelchangeCOMBOTime();
	afx_msg void OnClose();
	afx_msg void OnBUTTONgoogleEarth();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

	void DrawPattern(BOOL HV=true,int x0=305,int y0=305,int radius=280,int offset = 25);
	void DrawEllipse(BOOL nMode,int x1,int y1,int x2,int y2,int nStyle=PS_SOLID,int nWidth=1,COLORREF pColor=RGB(0,0,0),int x3=0,int y3=0,int x4=0,int y4=0,COLORREF bColor=RGB(255,255,255)); 
	BOOL m_fill;
	int	m_5degreestick;
	void DrawLine(int x1,int y1,int x2,int y2,int nStyle=PS_SOLID,int nWidth=1,COLORREF pColor=RGB(0,0,0)); 

	BOOL m_flag;
	int Contour(double y,double MinV,double MaxV,int nL);
	COLORREF RGBt[256];
	void ColorMap(CString type);
	BOOL m_single;
	long m_i;
	void Set_Static_R() ;

	void GetFrequency();

	void reckon(double lat_deg,double lon_deg,double rng_km,double az_deg,double *latC_deg,double *lonC_deg) ;
	CString quality2color(int quality); 
	BOOL KmlSave(CString *sFile,CString *sPath,BOOL *flagShow, CString sDefault) ;
	BOOL IsWin2000();
	CString m_AppPath;

	CString _Z(CString s){return (((CThalesDrawDLLApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TBEPOLAR_H__D830CD76_04D7_4692_A3EE_68FC5E8523D8__INCLUDED_)
