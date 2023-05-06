#if !defined(AFX_COUNTRYSELECTIONDLG_H__90DDC596_9E5C_4B36_963B_92A9FA4CF956__INCLUDED_)
#define AFX_COUNTRYSELECTIONDLG_H__90DDC596_9E5C_4B36_963B_92A9FA4CF956__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CountrySelectionDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCountrySelectionDLG dialog

class CCountrySelectionDLG : public CDialog
{
// Construction
public:
	CCountrySelectionDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCountrySelectionDLG)
	enum { IDD = IDD_CountrySelectionDLG };
	CComboBox	m_List;
	CString	m_code;
	int		m_Edit1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCountrySelectionDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCountrySelectionDLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCOMBOCountry();
	afx_msg void OnDblclkCOMBOCountry();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CString countryCODEidwm[300];
	CString countryNAMEidwm[300];
	CString Name2Code_idwm(CString name);
	int Name2Indx_idwm(CString name);
	int Code2Indx_idwm(CString co);
	int m_num;

public:
	int Code2Indx_list(CString co);


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COUNTRYSELECTIONDLG_H__90DDC596_9E5C_4B36_963B_92A9FA4CF956__INCLUDED_)
