#if !defined(AFX_ADDSTATIONDLG_H__5B84121F_2E8B_4081_9B64_B461924DCE70__INCLUDED_)
#define AFX_ADDSTATIONDLG_H__5B84121F_2E8B_4081_9B64_B461924DCE70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddStationDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddStationDLG dialog

class CAddStationDLG : public CDialog
{
// Construction
public:
	CAddStationDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddStationDLG)
	enum { IDD = IDD_AddStationDLG };
	CComboBox	m_ListSTTP;
	CComboBox	m_ListSrv;
	CComboBox	m_lonU;
	CComboBox	m_latU;
	CString	m_STname;
	double	m_STlat_deg;
	double	m_STlon_deg;
	CString	m_Antenna;
	double	m_Azimuth;
	double	m_BWh;
	double	m_BWv;
	double	m_Elevation;
	double	m_TXfreq;
	double	m_ANTgain;
	double	m_STh_agl;
	long	m_IDst;
	CString	m_Polarization;
	double	m_Power_eirp;
	CString	m_latD;
	CString	m_latM;
	CString	m_latS;
	CString	m_lonD;
	CString	m_lonM;
	CString	m_lonS;
	double	m_InserLoss;
	double	m_RxSens;
	CString	m_STTP;
	int		m_Srv;
	CString	m_Emission;
	double	m_STh_asl;
	//}}AFX_DATA
	CString m_Lang;	//97/12/24
	int m_iLang;	//97/12/24


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddStationDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddStationDLG)
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
	afx_msg void OnAssignAntenna();
	afx_msg void OnShowPattern();
	afx_msg void OnSelchangeCOMBOSrv();
	afx_msg void OnSelchangeComboSttp();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	void left2right();
	void DEG2DMS(CString type,double x,int *xD,int *xM,double *xS,char *xU);
	void ReadAntData(CString antfile); 
	CString m_antfile;
	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};

	CFont m_font;	//98/04/12
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDSTATIONDLG_H__5B84121F_2E8B_4081_9B64_B461924DCE70__INCLUDED_)
