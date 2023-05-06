#if !defined(AFX_COUNTRYLIST_H__CE3D7D6F_E269_42EA_B356_28EFF99A48BC__INCLUDED_)
#define AFX_COUNTRYLIST_H__CE3D7D6F_E269_42EA_B356_28EFF99A48BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CountryList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCountryList dialog

class CCountryList : public CDialog
{
// Construction
public:
	CCountryList(CWnd* pParent = NULL);   // standard constructor
	CString m_SDBSTR, m_Result, m_Lang;
	void TranslateDialog(CDialog *pDialog);
	CString GetTranslatedString(CString strOriginal, CString Lang);
	CString _Z(CString s){ return GetTranslatedString(_T(s),m_Lang); };
// Dialog Data
	//{{AFX_DATA(CCountryList)
	enum { IDD = IDD_COUNTSELECT };
	CListBox	m_Countries;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCountryList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCountryList)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COUNTRYLIST_H__CE3D7D6F_E269_42EA_B356_28EFF99A48BC__INCLUDED_)
