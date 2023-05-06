//{{AFX_INCLUDES()
//#include "msflexgrid.h"
#include "EditGrid.h"

//}}AFX_INCLUDES
#if !defined(AFX_TXRXFILTERDLG_H__177DB028_63A0_4083_98BC_86C278F4DFDB__INCLUDED_)
#define AFX_TXRXFILTERDLG_H__177DB028_63A0_4083_98BC_86C278F4DFDB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TxRxFilterDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTxRxFilterDLG dialog

class CTxRxFilterDLG : public CDialog
{
// Construction
public:
	CTxRxFilterDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTxRxFilterDLG)
	enum { IDD = IDD_TxRxFilterDLG };
	CComboBox	m_fu;
	double	m_Channelsep;
	CEditGrid	m_ListGrid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTxRxFilterDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTxRxFilterDLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnBUTTONDraw();
	afx_msg void OnPaint();
	afx_msg void OnSelchangeCOMBOfu();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	double interwt(double *ft,double *at,int n,double f0) ;
	CRect m_rcPrintRect;
	int m_AxesT,m_AxesH,m_AxesW,m_AxesL;
	double MinValue(double *xi,int N) ;
	double MaxValue(double *xi,int N) ;
	void Xtick(CPaintDC* pDC,double xiMIN,double xiMAX);
	void YtickL(CPaintDC* pDC,double yiMIN,double yiMAX);
	int Round(double x);

	void Plot(CPaintDC *pDC,double *xi, double *yi,int Np,
						double xiMIN,double xiMAX,double yiMIN,double yiMAX,
						int nWidth=1,COLORREF crColor=RGB(0,0,0), int nStyle=PS_SOLID,
						int nMode=0,COLORREF flColor=RGB(255,255,255));

	void TextDraw(CPaintDC* pDC,int x, int y,CString str,
							COLORREF FontColor=RGB(0,0,0),
							int Escapement=0,int nHeight=12,int nWidth=0,
							int FontWeight=FW_NORMAL,CString FontName="Arial");

	void LineDraw(CPaintDC* pDC,int x1, int y1,int x2, int y2,
						int nWidth=1,COLORREF crColor=RGB(0,0,0), int nStyle=PS_SOLID);

	void Delete_set(long ID) ;

public:
	double m_f[20], m_a[20];
	int m_fuFlag;
	int m_TxRx;
	CString m_title;
	long m_ID;
	int m_num;

	int DP_LP(CDC* pDC, int nH_DP);	//1400/04/20
	void initDP_LP(CDC * pDC);
	int m_fontH2, m_fontH6, m_fontH12, m_fontH14, m_fontH20, 
		m_fontH24, m_fontH28, m_fontH30, m_fontH40, m_fontH44, m_fontH100, m_fontH150, m_fontH46;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TXRXFILTERDLG_H__177DB028_63A0_4083_98BC_86C278F4DFDB__INCLUDED_)
