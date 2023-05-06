#if !defined(AFX_ANTPATTERNDLG_H__12A63E2B_A7FF_48A8_9986_DA8ED6E84688__INCLUDED_)
#define AFX_ANTPATTERNDLG_H__12A63E2B_A7FF_48A8_9986_DA8ED6E84688__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ANTpatternDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CANTpatternDLG dialog

class CANTpatternDLG : public CDialog
{
// Construction
public:
	CANTpatternDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CANTpatternDLG)
	enum { IDD = IDD_ANTpatternDLG };
	CString	m_antfile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CANTpatternDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CANTpatternDLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int  m_Angle[360];
	double m_PatternH[360],m_PatternV[360];
	bool ReadData(CString antfile);
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

	bool m_flag;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANTPATTERNDLG_H__12A63E2B_A7FF_48A8_9986_DA8ED6E84688__INCLUDED_)
