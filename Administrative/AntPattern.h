#if !defined(AFX_ANTPATTERN_H__6D9C09FC_BC27_4E84_950E_A54721B20D62__INCLUDED_)
#define AFX_ANTPATTERN_H__6D9C09FC_BC27_4E84_950E_A54721B20D62__INCLUDED_

#include "resource.h"
#include "Administrative.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AntPattern.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAntPattern dialog

class CAntPattern : public CDialog
{
// Construction
public:
	CAntPattern(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAntPattern)
	enum { IDD = IDD_ANT_PATTERN };
	long m_AntID;
	CString m_CDBSTR;
	//}}AFX_DATA
	CString m_Lang;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAntPattern)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAntPattern)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int  m_Angle[361];
	double m_PatternH[361],m_PatternV[361];
	CString m_Pol;
	bool ReadData();
	void DrawPattern(BOOL HV=true,int x0=305,int y0=305,int radius=280,int offset = 25);
	void DrawEllipse(BOOL nMode,int x1,int y1,int x2,int y2,int nStyle=PS_SOLID,int nWidth=1,COLORREF pColor=RGB(0,0,0),int x3=0,int y3=0,int x4=0,int y4=0,COLORREF bColor=RGB(255,255,255)); 
	int m_ThickLines;
	BOOL m_fill;
	COLORREF m_fillcolor;
	int	m_5degreestick;
	BOOL m_1degreestick;
	BOOL m_1dbtick;
	void DrawLine(int x1,int y1,int x2,int y2,int nStyle=PS_SOLID,int nWidth=1,COLORREF pColor=RGB(0,0,0)); 
	void Draw3Angle(int x1,int y1,int x2,int y2,int x3,int y3,int nStyle=PS_SOLID,int nWidth=1,COLORREF pColor=RGB(255,0,0),COLORREF bColor=RGB(255,0,0));
	double Interp2(double *D0,double *E0,double d,int num) ;
	CString _Z(CString s){ return (((CAdministrativeApp *)AfxGetApp())->GetTranslatedString(_T(s),m_Lang)); };
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANTPATTERN_H__6D9C09FC_BC27_4E84_950E_A54721B20D62__INCLUDED_)
