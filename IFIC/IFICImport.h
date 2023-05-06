#if !defined(AFX_IFICIMPORT_H__B3B1F0C5_5789_472B_B9F1_0CBC5952F565__INCLUDED_)
#define AFX_IFICIMPORT_H__B3B1F0C5_5789_472B_B9F1_0CBC5952F565__INCLUDED_

#include "resource.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IFICImport.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIFICImport dialog

class CIFICImport : public CDialog
{
// Construction
public:
	CIFICImport(CWnd* pParent = NULL);   // standard constructor
	void TranslateDialog(CDialog *pDialog);
	CString GetTranslatedString(CString strOriginal, CString Lang);
	CString _Z(CString s){ return GetTranslatedString(_T(s),m_Lang); };
	CString m_CDBSTR, m_Lang, m_BRIFIC;
// Dialog Data
	//{{AFX_DATA(CIFICImport)
	enum { IDD = IDD_QueryDLG };
	CButton	m_Browse;
	CButton	m_AccessMDB;
	CButton	m_SQLite;
	CButton	m_Digital;
	CListBox	m_IDSel;
	CButton	m_IDRemove;
	CButton	m_IDAdd;
	CEdit	m_TerraKey;
	CListBox	m_FragSel;
	CButton	m_FragRemove;
	CButton	m_FragClear;
	CButton	m_FragAdd;
	CListBox	m_ClassSel;
	CButton	m_ClassRemove;
	CButton	m_ClassClear;
	CButton	m_ClassAdd;
	CComboBox	m_Fragment;
	CComboBox	m_StationClass;
	CProgressCtrl	m_ImportProgress;
	CButton	m_LFMF;
	CButton	m_FXM;
	CButton	m_FreqRem;
	CListBox	m_FreqCondSel;
	CListBox	m_FreqCond;
	CButton	m_FreqAdd;
	CButton	m_FMTV;
	CComboBox	m_F2U;
	CEdit	m_F2;
	CComboBox	m_F1U;
	CEdit	m_F1;
	CListBox	m_AdmSel;
	CButton	m_AdmRemove;
	CListBox	m_AdmList;
	CButton	m_AdmClear;
	CButton	m_AdmAddAll;
	CButton	m_AdmAdd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFICImport)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CIFICImport)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdmAdd();
	afx_msg void OnAdmRemove();
	afx_msg void OnAdmClear();
	afx_msg void OnAdmAddAll();
	afx_msg void OnSelchangeFreqCond();
	afx_msg void OnFreqAdd();
	virtual void OnOK();
	afx_msg void OnFreqRem();
	afx_msg void OnFmtv();
	afx_msg void OnFxm();
	afx_msg void OnClassRemove();
	afx_msg void OnFragRemove();
	afx_msg void OnClassAdd();
	afx_msg void OnFragAdd();
	afx_msg void OnClassClear();
	afx_msg void OnFragClear();
	virtual void OnCancel();
	afx_msg void OnIDAdd();
	afx_msg void OnIDRemove();
	afx_msg void OnMdb();
	afx_msg void OnSqlite();
	afx_msg void OnBrowse();
	//}}AFX_MSG
	double GetFreqUnit(CString Unit);
	CString GetAdmList();
	CString GetFreqCond();
	CString GetFragList();
	CString GetIDList();
	CString GetClassList();
	void ImportData(CDatabase m_DB, CRecordset m_rs);
	CString GetODBCPath(CString Connection);
	void RemoveQuote(CString *Str);
	CString BandWidthCode(double BW);
	double Interp2(double *D0,double *E0,double d,int num) ;
	void AntennaSaveTxt(CString Name, double Gain, double BWH, double BWV, double FLow, double FHi, 
						 CString Pol, double PattV[], double PattH[],double Azm);

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFICIMPORT_H__B3B1F0C5_5789_472B_B9F1_0CBC5952F565__INCLUDED_)
