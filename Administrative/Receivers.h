//{{AFX_INCLUDES()
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#include "LeftView.h"
#if !defined(AFX_RECEIVERS_H__0D8F402F_B5F4_4915_B07A_9B4DAE7ACD44__INCLUDED_)
#define AFX_RECEIVERS_H__0D8F402F_B5F4_4915_B07A_9B4DAE7ACD44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Receivers.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReceivers dialog

class CReceivers : public CDialog
{
// Construction
public:
	CString m_Lang;
	CReceivers(CWnd* pParent = NULL);   // standard constructor
	CString _Z(CString s){ return (((CAdministrativeApp *)AfxGetApp())->GetTranslatedString(_T(s),m_Lang)); };

// Dialog Data
	//{{AFX_DATA(CReceivers)
	enum { IDD = IDD_ADD_RECEIVER };
	CComboBox	m_Points;
	CComboBox	m_Zone;
	double	m_CenLat;
	double	m_CenLon;
	long	m_RecRadius;
	CMSHFlexGrid	m_RecStations;
	long	m_HopID;
	long	m_LinkID;
	double	m_Lat1;
	double	m_Lat2;
	double	m_Lat3;
	double	m_Lat4;
	double	m_Lat5;
	double	m_Lat6;
	double	m_Lon1;
	double	m_Lon2;
	double	m_Lon3;
	double	m_Lon4;
	double	m_Lon5;
	double	m_Lon6;
	CMSHFlexGrid	m_TXAntenna;
	double	m_NoiseTemp;
	//}}AFX_DATA
	long m_ID;
	CLeftView *m_TreeView;
	CString m_CDBSTR;
	CString m_Srv;
	CString m_STTP;
	bool m_IsTypical;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReceivers)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReceivers)
	afx_msg void OnPoint();
	afx_msg void OnMultipoint();
	afx_msg void OnCircle();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnZone();
	afx_msg void OnSelchangePoints();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECEIVERS_H__0D8F402F_B5F4_4915_B07A_9B4DAE7ACD44__INCLUDED_)
