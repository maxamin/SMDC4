#if !defined(AFX_HORIZONELEVATIONDLG_H__5BDE7CFC_F432_46A7_85EF_C4E4338CFA72__INCLUDED_)
#define AFX_HORIZONELEVATIONDLG_H__5BDE7CFC_F432_46A7_85EF_C4E4338CFA72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HorizonElevationDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHorizonElevationDLG dialog

class CHorizonElevationDLG : public CDialog
{
// Construction
public:
	CHorizonElevationDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHorizonElevationDLG)
	enum { IDD = IDD_HorizonElevationDLG };
	double	m_ES_Altitude;
	double	m_D_max;
	CString	m_k;
	double	m_Earth_radius_km;
	//}}AFX_DATA
	int m_Azimuth_Step_Deg;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHorizonElevationDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHorizonElevationDLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio1();
	afx_msg void OnRadio5();
	afx_msg void OnRadio10();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HORIZONELEVATIONDLG_H__5BDE7CFC_F432_46A7_85EF_C4E4338CFA72__INCLUDED_)
