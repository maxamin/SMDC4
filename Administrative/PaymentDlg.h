#if !defined(AFX_PAYMENTDLG_H__9FF9C3A7_F515_4D63_B2F7_6AAF70A83CD3__INCLUDED_)
#define AFX_PAYMENTDLG_H__9FF9C3A7_F515_4D63_B2F7_6AAF70A83CD3__INCLUDED_

#include "resource.h"
#include "Administrative.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PaymentDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPaymentDlg dialog

class CPaymentDlg : public CDialog
{
// Construction
public:
	CPaymentDlg(CWnd* pParent = NULL);   // standard constructor
	void AddTrail(CString Action, long RecordID, CString Table);
	long m_ID;
// Dialog Data
	//{{AFX_DATA(CPaymentDlg)
	enum { IDD = IDD_PAYMENT };
	CString	m_PaymentNo;
	long	m_PaymentVal;
	CString	m_PayDesc;
	CTime	m_PayDate;
	//}}AFX_DATA
	CString m_CDBSTR,m_UserName;
	CString m_Lang;

	CString _Z(CString s){ return (((CAdministrativeApp *)AfxGetApp())->GetTranslatedString(_T(s),m_Lang)); };

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaymentDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPaymentDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAYMENTDLG_H__9FF9C3A7_F515_4D63_B2F7_6AAF70A83CD3__INCLUDED_)
