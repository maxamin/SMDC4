//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_FASSIGN2DLG_H__C0FF351F_8F08_4517_B7E1_E7BC32A70F93__INCLUDED_)
#define AFX_FASSIGN2DLG_H__C0FF351F_8F08_4517_B7E1_E7BC32A70F93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Fassign2DLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFassign2DLG dialog

class CFassign2DLG : public CDialog
{
// Construction
public:
	CFassign2DLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFassign2DLG)
	enum { IDD = IDD_Fassign2DLG };
	CMSFlexGrid	m_GRID1;
	CMSFlexGrid	m_GRID2;
	CString	m_STname;
	CString	m_STLatLon;
	double	m_Imax;
	CString	m_SRV;
	int		m_SRV0;
	CString	m_SChannel;
	double	m_STfrq;
	long	m_IntC;
	long	m_TotalC;
	CString	m_STemission;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFassign2DLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFassign2DLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblClickMsflexgrid1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	long FindStation(double Fn,double Df,long *ID) ;

//	long m_ID[320][100];
//	long m_numID[1000];

	long (*m_ID)[200];

	long *m_numID;



	void FillGRID2(long ID,CString * name,double *frq,CString *LatLon , double *Dist ,
								 double *PtGt,CString *Emission,int *Srv,double *Lat,double *Lon,
								 double *AZ ,double *EL ,double *Hasl ,double *Hagl,CString *ant) ;
	
	double Emission2NBW(CString Emission) ;

	double NFD_Fixed(long ID_Tx , long ID_Rx, double frq_Tx, double frq_Rx,CString name_Tx,CString name_Rx) ;
	double MinValue(double *xi,int N) ;
	double MaxValue(double *xi,int N) ;
	double interwt(double *ft,double *at,int n,double f0) ;
	double subsection(double a,double b,double fc) ;

	double AZ_EL(double latT , double lonT , double latR , double lonR, double HtASGL, double HrASGL, double re, double *AZrad) ;
	double Azimuth_Deg(double lat1,double lon1,double lat2,double lon2) ;
	double Distance_km(double lat1,double lon1,double lat2,double lon2) ;
	void ReadAntennaData(CString antfile,int *f0,double *rH,double *rV) ;
	double Interp2(int *D0,double *E0,double d,int num) ;
	CString str_rep(CString str,int num);
	BOOL PeekAndPump();

public:
	double m_Fmin , m_Fmax , m_Df , m_Rkm;
	long m_STID;
	double m_STLat , m_STLon, m_STptgt , m_STh_agl , m_STh_asl , m_STaz0 , m_STel0;
	CString m_STant;

	CString	m_SChannelR;

	void Del() ;

	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FASSIGN2DLG_H__C0FF351F_8F08_4517_B7E1_E7BC32A70F93__INCLUDED_)
