#if !defined(AFX_P1812DLG_H__371AA729_08E3_4A9F_A6D3_D2C1A1CDAC92__INCLUDED_)
#define AFX_P1812DLG_H__371AA729_08E3_4A9F_A6D3_D2C1A1CDAC92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// P1812DLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CP1812DLG dialog

class CP1812DLG : public CDialog
{
// Construction
public:
	CP1812DLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CP1812DLG)
	enum { IDD = IDD_P1812DLG };
	CComboBox	m_COMBO_IODoor;
	CComboBox	m_COMBO_Service;
	CComboBox	m_COMBO_Clutter;
	double	m_time;
	double	m_Location;
	double	m_RxH;
	double	m_Cvalue;
	//}}AFX_DATA

	int m_Clutter, m_Service, m_IODoor, m_CvShow, m_RxShow;;

	BOOL m_Monitoring;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CP1812DLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CP1812DLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCOMBOClutter();
	afx_msg void OnSelchangeCOMBOService();
	afx_msg void OnSelchangeCOMBOIODoor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_P1812DLG_H__371AA729_08E3_4A9F_A6D3_D2C1A1CDAC92__INCLUDED_)
