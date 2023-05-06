#if !defined(AFX_ADDESSTATIONDLG_H__7C4FA211_D1AE_4591_96BF_84EA5CBDC216__INCLUDED_)
#define AFX_ADDESSTATIONDLG_H__7C4FA211_D1AE_4591_96BF_84EA5CBDC216__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddESStationDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddESStationDLG dialog

class CAddESStationDLG : public CDialog
{
// Construction
public:
	CAddESStationDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddESStationDLG)
	enum { IDD = IDD_AddESStationDLG };
	CComboBox	m_EStype;
	CComboBox	m_lonU;
	CComboBox	m_latU;
	CString	m_STname;
	CString	m_latD;
	CString	m_latM;
	CString	m_latS;
	CString	m_lonD;
	CString	m_lonM;
	CString	m_lonS;
	double	m_STh_asl;
	double	m_STlat_deg;
	double	m_STlon_deg;
	CString	m_nameSat;
	double	m_AzFrom;
	double	m_AzTo;
	double	m_ElST;
	long	m_ntcID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddESStationDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddESStationDLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusEDITlatD();
	afx_msg void OnKillfocusEDITlatM();
	afx_msg void OnKillfocusEDITlatS();
	afx_msg void OnKillfocusEDITlonD();
	afx_msg void OnKillfocusEDITlonM();
	afx_msg void OnKillfocusEDITlonS();
	afx_msg void OnSelchangelatU();
	afx_msg void OnSelchangelonU();
	afx_msg void OnKillfocusEDITlatST();
	afx_msg void OnKillfocusEDITlonST();
	virtual void OnOK();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void left2right() ;
	void DEG2DMS(CString type,double x,int *xD,int *xM,double *xS,char *xU) ;
	long AddESSt(CString STname, int lonD, CString lonU, int lonM, int lonS, int latD, CString latU, int latM, int latS,CString SATname, double EL,double AZf,double AZt,double HstASL, double STlat_deg, double STlon_deg,CString type);
	
	CFont m_font;	//98/04/12
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDESSTATIONDLG_H__7C4FA211_D1AE_4591_96BF_84EA5CBDC216__INCLUDED_)
