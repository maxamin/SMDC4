#if !defined(AFX_NOTICE_H__DDD16DE7_F9FE_4BF6_A5F9_ED0CF3AFDB7C__INCLUDED_)
#define AFX_NOTICE_H__DDD16DE7_F9FE_4BF6_A5F9_ED0CF3AFDB7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "resource.h"
#include "Administrative.h"
// Notice.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNotice dialog

class CNotice : public CDialog
{
// Construction
public:
	CNotice(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNotice)
	enum { IDD = IDD_NOTICE };
	CComboBox	m_PubReq;
	CComboBox	m_IsResub;
	CComboBox	m_Zone;
	CComboBox	m_GeoType;
	CDateTimeCtrl	m_NoticeDate;
	CComboBox	m_Action;
	BOOL	m_T14;
	CString	m_Admin;
	//}}AFX_DATA
	CString m_CDBSTR;
	long m_LicID;
	long m_StID;
	CString m_StTable;
	long m_AdmID;
	CString m_SrvType;
	CString	m_LicHrTo;
	CString	m_LicHrFrom;
	CString m_Lang;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNotice)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNotice)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	CString BandWidthCode(float BW);
	void Fixed();
	void LandMobile();
	void Broadcast();
	void Coord2DMS(int *d,int *m,int *s,double Val);
	double Interp2(double *D0,double *E0,double d,int num) ;
	void Allotment();
	void Contour();
	CString _Z(CString s){ return (((CAdministrativeApp *)AfxGetApp())->GetTranslatedString(_T(s),m_Lang)); };
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOTICE_H__DDD16DE7_F9FE_4BF6_A5F9_ED0CF3AFDB7C__INCLUDED_)
