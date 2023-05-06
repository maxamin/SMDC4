//{{AFX_INCLUDES()
#include "datagrid.h"
#include "adodc.h"
#include "mshflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_AGREEMENT_H__29AE85AB_C40E_44F9_9C29_6EB5DA398E10__INCLUDED_)
#define AFX_AGREEMENT_H__29AE85AB_C40E_44F9_9C29_6EB5DA398E10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Agreement.h : header file
//
#include "EditGrid.h"

/////////////////////////////////////////////////////////////////////////////
// CAgreement dialog

class CAgreement : public CDialog
{
// Construction
public:
	CAgreement(CWnd* pParent = NULL);   // standard constructor
	~CAgreement(){m_RS.Close(); m_DB.Close();}
	CString m_CDBSTR,m_SDBSTR,m_Lang;
	CDatabase m_DB;
	CRecordset m_RS;
	long m_AgCode,m_RecNo,m_RecTotal;
	int m_ViewAddEdit; // 0=View, 1=Add, 2=Edit

	void LoadAgreement(CRecordset &RS);
	void LoadModel(CString m_AgType);
	void OnOK();
	void TranslateDialog(CDialog *pDialog);
	CString GetTranslatedString(CString strOriginal, CString Lang);
	CString _Z(CString s){ return GetTranslatedString(_T(s),m_Lang); };

// Dialog Data
	//{{AFX_DATA(CAgreement)
	enum { IDD = IDD_AGREEMENTS };
	CBitmapButton	m_AgPlus;
	CBitmapButton	m_AgMinus;
	CButton	m_PrefCountries;
	CButton	m_ServList;
	CButton	m_ModelList;
	CButton	m_CountList;
	CComboBox	m_AgType;
	CBitmapButton	m_AgLast;
	CBitmapButton	m_AgFirst;
	CBitmapButton	m_AgDelete;
	CButton	m_AgCancel;
	CComboBox	m_AgModel;
	CBitmapButton	m_AgSave;
	CBitmapButton	m_AgPrev;
	CBitmapButton	m_AgNext;
	CBitmapButton	m_AgNew;
	CButton	m_AgMod;
	CString	m_AgName;
	CString	m_AgProp;
	CString	m_AgCountries;
	CString	m_AgServ;
	CString	m_RecordCount;
	CEditGrid m_AgList;
//	CMSHFlexGrid	m_AgList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAgreement)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAgreement)
	virtual BOOL OnInitDialog();
	afx_msg void OnAgprev();
	afx_msg void OnAgnext();
	afx_msg void OnAgnew();
	afx_msg void OnAgmod();
	afx_msg void OnAgsave();
	afx_msg void OnAgcancel();
	afx_msg void OnCountlist();
	afx_msg void OnAgfirst();
	afx_msg void OnAglast();
	afx_msg void OnModellist();
	afx_msg void OnServlist();
	afx_msg void OnPrefcountry();
	afx_msg void OnAgdelete();
	afx_msg void OnSelchangeAgtype();
	afx_msg void OnSelchangeAgmodel();
	afx_msg void OnKillfocusAgname();
	afx_msg void OnAgminus();
	afx_msg void OnAgplus();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AGREEMENT_H__29AE85AB_C40E_44F9_9C29_6EB5DA398E10__INCLUDED_)
