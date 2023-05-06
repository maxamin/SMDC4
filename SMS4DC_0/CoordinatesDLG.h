#if !defined(AFX_COORDINATESDLG_H__5501852D_0A7F_4C8F_BA8C_1D235F38BECF__INCLUDED_)
#define AFX_COORDINATESDLG_H__5501852D_0A7F_4C8F_BA8C_1D235F38BECF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CoordinatesDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCoordinatesDLG dialog

class CCoordinatesDLG : public CDialog
{
// Construction
public:
	CCoordinatesDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCoordinatesDLG)
	enum { IDD = IDD_CoordinatesDLG };
	CComboBox	m_lon2EW;
	CComboBox	m_lat2NS;
	CComboBox	m_lon1EW;
	CComboBox	m_lat1NS;
	CString	m_lat1M;
	CString	m_lat1D;
	CString	m_lat2D;
	CString	m_lat2M;
	CString	m_lat1S;
	CString	m_lat2S;
	CString	m_lon1D;
	CString	m_lon1M;
	CString	m_lon1S;
	CString	m_lon2D;
	CString	m_lon2M;
	CString	m_lon2S;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCoordinatesDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCoordinatesDLG)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COORDINATESDLG_H__5501852D_0A7F_4C8F_BA8C_1D235F38BECF__INCLUDED_)
