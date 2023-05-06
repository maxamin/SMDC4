#if !defined(AFX_RGNTABLEVIEW_H__1544BA0E_2ED6_499D_B1C3_67B99156E4C2__INCLUDED_)
#define AFX_RGNTABLEVIEW_H__1544BA0E_2ED6_499D_B1C3_67B99156E4C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RGNtableView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRGNtableView record view

#include "RGNtableSet.h"

class CRGNtableView : public CRecordView
{
protected:
	CRGNtableView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRGNtableView)

// Form Data
public:
	//{{AFX_DATA(CRGNtableView)
	enum { IDD = IDD_RGNtableDLG };
	CComboBox	m_ListSS6;
	CComboBox	m_ListSS5;
	CComboBox	m_ListSS4;
	CComboBox	m_ListSS3;
	CComboBox	m_ListSS2;
	CComboBox	m_ListSS1;
	CComboBox	m_ListPS5;
	CComboBox	m_ListPS6;
	CComboBox	m_ListPS4;
	CComboBox	m_ListPS3;
	CComboBox	m_ListPS2;
	CComboBox	m_ListPS1;
	CRGNtableSet* m_pSet;
	CString	m_Regions2;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	CRGNtableSet* GetRecordset();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRGNtableView)
	public:
	virtual CRecordset* OnGetRecordset();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRGNtableView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CRGNtableView)
	afx_msg void OnSelchangeComboPs1();
	afx_msg void OnSelchangeComboPs2();
	afx_msg void OnSelchangeComboPs3();
	afx_msg void OnSelchangeComboPs4();
	afx_msg void OnSelchangeComboPs5();
	afx_msg void OnSelchangeComboPs6();
	afx_msg void OnSelchangeComboSs1();
	afx_msg void OnSelchangeComboSs2();
	afx_msg void OnSelchangeComboSs3();
	afx_msg void OnSelchangeComboSs4();
	afx_msg void OnSelchangeComboSs5();
	afx_msg void OnSelchangeComboSs6();
	afx_msg void OnRecordFirst();
	afx_msg void OnRecordPrev();
	afx_msg void OnRecordNext();
	afx_msg void OnRecordLast();
	afx_msg void OnUpdateRecordNext(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecordLast(CCmdUI* pCmdUI);
	afx_msg void OnRecordSave();
	afx_msg void OnRecordAdd();
	afx_msg void OnRecordSub();
	afx_msg void OnKillfocusEditFlo();
	afx_msg void OnKillfocusEditFhi();
	afx_msg void OnKillfocusEDITfot();
	afx_msg void OnKillfocusFotp1();
	afx_msg void OnKillfocusFotp2();
	afx_msg void OnKillfocusFotp3();
	afx_msg void OnKillfocusFotp4();
	afx_msg void OnKillfocusFotp5();
	afx_msg void OnKillfocusFotp6();
	afx_msg void OnKillfocusFots1();
	afx_msg void OnKillfocusFots2();
	afx_msg void OnKillfocusFots3();
	afx_msg void OnKillfocusFots4();
	afx_msg void OnKillfocusFots5();
	afx_msg void OnKillfocusFots6();
	afx_msg void OnBandSort();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	int m_num;
	int m_count;
	int Name2ID(CString name_str,int psFlag);
	void SetListsItem() ;
	void OnAppend() ;
	void OnDelete() ;
	void OnRecordSave1() ;
	CString ID2Name(int ID,int psFlag);
	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RGNTABLEVIEW_H__1544BA0E_2ED6_499D_B1C3_67B99156E4C2__INCLUDED_)
