#if !defined(AFX_INTERMODDLG_H__DE628579_FEAA_4E6E_B199_86BE1EB875CA__INCLUDED_)
#define AFX_INTERMODDLG_H__DE628579_FEAA_4E6E_B199_86BE1EB875CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InterModDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInterModDLG dialog

class CInterModDLG : public CDialog
{
// Construction
public:
	CInterModDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInterModDLG)
	enum { IDD = IDD_InterModDLG };
	CListBox	m_LIST_Tx;
	CListBox	m_LIST_Rx;
	CListBox	m_LIST_OUT;
	int		m_Horder;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInterModDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInterModDLG)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAddTx();
	afx_msg void OnAddRx();
	afx_msg void OnDeleteTx();
	afx_msg void OnDeleteRx();
	afx_msg void OnRadioS2();
	afx_msg void OnRadioS3();
	afx_msg void OnRadioO3();
	afx_msg void OnRadioO5();
	afx_msg void OnRadioO7();
	afx_msg void OnSave();
	afx_msg void OnAddTxDB();
	afx_msg void OnAddRxDB();
	afx_msg void OnAddTx2Rx();
	afx_msg void OnAddRx2Tx();
	afx_msg void OnDeleteTxAll();
	afx_msg void OnDeleteRxAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL m_Signal;
	int m_Order;
	CString GetFld(CString Src,int N);
	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERMODDLG_H__DE628579_FEAA_4E6E_B199_86BE1EB875CA__INCLUDED_)
