#if !defined(AFX_MONITORINGTHDLG_H__7991A8EF_CEC4_47B5_8C02_16968351FD91__INCLUDED_)
#define AFX_MONITORINGTHDLG_H__7991A8EF_CEC4_47B5_8C02_16968351FD91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MonitoringThDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMonitoringThDLG dialog

class CMonitoringThDLG : public CDialog
{
// Construction
public:
	CMonitoringThDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMonitoringThDLG)
	enum { IDD = IDD_MonitoringThDLG };
	double	m_EDIT_mth1;
	double	m_EDIT_mth2;
	double	m_EDIT_mth3;
	//}}AFX_DATA

int m_flag;
CString m_title;	
CString m_label1,m_label2,m_label3;	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMonitoringThDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMonitoringThDLG)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONITORINGTHDLG_H__7991A8EF_CEC4_47B5_8C02_16968351FD91__INCLUDED_)
