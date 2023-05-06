#if !defined(AFX_AP7EARTHSTATIONDLG_H__A13FFCF1_37E3_4DE0_8222_FEB1105FA791__INCLUDED_)
#define AFX_AP7EARTHSTATIONDLG_H__A13FFCF1_37E3_4DE0_8222_FEB1105FA791__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AP7EarthStationDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAP7EarthStationDLG dialog

class CAP7EarthStationDLG : public CDialog
{
// Construction
public:
	CAP7EarthStationDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAP7EarthStationDLG)
	enum { IDD = IDD_AP7_EarthStationDLG };
	CString	m_Beam;
	CString	m_Group;
	CString	m_Notice;
	CString	m_Ctry;
	CString	m_BDIRPC;
	CString	m_GMIN;
	CString	m_INCLINATION;
	CString	m_RECVPC;
	CString	m_SATEAST;
	CString	m_SATWEST;
	CString	m_TRANPC;
	CString	m_TxRx;
	BOOL	m_Manned;
	//}}AFX_DATA
	int m_DataBaseFlag;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAP7EarthStationDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAP7EarthStationDLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBUTTONOptions();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	long AP28_SRS_CTRY(CString *cty) ;
	long AP28_SRS_ntc_id(CString cty,long *ntcid) ;
	long AP28_SRS_beam(long ntc,CString *beam,CString *TxRx) ;
	long AP28_SRS_group(long ntc,CString beam,CString TxRx,long *grpid) ;
	void TreeFill() ;
	CString	m_qAPP7_List;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AP7EARTHSTATIONDLG_H__A13FFCF1_37E3_4DE0_8222_FEB1105FA791__INCLUDED_)
