// treeviewView.h : interface of the CTreeviewView class
//
/////////////////////////////////////////////////////////////////////////////
#include "resource.h"
#include "MSHFlexGrid.h"
#include "MSMask.h"
#include "TreeviewDoc.h"

#if !defined(AFX_TREEVIEWVIEW_H__345A1683_B0CC_4CB7_920C_B52F58CCDF7D__INCLUDED_)
#define AFX_TREEVIEWVIEW_H__345A1683_B0CC_4CB7_920C_B52F58CCDF7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTreeviewView : public CFormView //CListView
{
protected: // create from serialization only
	CTreeviewView();
	DECLARE_DYNCREATE(CTreeviewView)

// Attributes
public:
	CTreeviewDoc* GetDocument();
  enum { IDD = IDD_GRID };
  CMSHFlexGrid *m_Grid;
  long m_RecID, m_OldRecID, m_CatID;
  CString m_Table, m_OldTable,m_Mask[2][60];
  int m_Action;  //0= No action (view),  1=add new,  2=Edit
  int m_RecordType, m_OldRecordType;  //enum NodeTypes

  CString m_Service;
  bool m_Refresh, m_loaded, m_ReadOnly, m_OnEdit;

  CMSMask *m_EditBox;
  CEdit *m_NormalEdit;
  CComboBox *m_Combo1;
  CDateTimeCtrl *m_Date;
  long m_lBorderWidth;
  long m_lBorderHeight;

  int m_nLogX;
  int m_nLogY;
	CString m_CDBSTR;
	CString m_UserName;
	int m_UserLevel;
	CString m_Lang;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeviewView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTreeviewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	void CleanScreen();
	void LoadOwner(long ID);
	void LoadLicense(long ID);
	void LoadStation(long ID);
	void LoadBC(long ID);
	void LoadMobile(long ID);
	void LoadEquipment(long ID);
	void LoadAntenna(long ID);
	void LoadFrequency(long ID);
	void LoadInvoice(long ID);
	void LoadPayment(long ID);
	void RowDelete(long row);
	void LoadReceiver(long ID);
	void LoadES(long ID);
	void LoadAllot(long ID);
	void LoadContour(long ID);
	void AddESStation();
	void AddESAnt(int UpDown);
	bool ESSave();
	bool ESAntSave();
	bool ESAntValidation(CString Values[]);
	void LoadESAnt(long ID);
	void LoadESGroup(long ID);
	void AddESGroup();
	bool ESGrpSave();
	 CString GetFieldName(CDatabase *DB, CString Table, CString OrigName, CString LangCode, 
		CString *Unit, CString *Format, CString *Srv, CString *Mask);
	bool OwnerSave();
	bool LicenseSave();
	bool StationSave();
	bool BCSave();
	bool MobileSave();
	bool FrequencySave();
	bool EquipmentSave();
	bool AntennaSave();
	bool AllotSave();
	bool ContourSave();
	double GetFreqUnit(CString Unit);
	void ModifyData();
	void AddOwner();
	void AddLicense();
	void AddAntenna();
	void AddEquipment();
	void AddFrequency();
	void AddStation();
	void AddBCStation();
	void AddMobile();
	void AddAllotment();
	void AddContour();
	CString BWCode(double BW);
	bool OwnerValidation(CString Values[]);
	bool LicenseValidation(CString Values[], CString Fields[]);
	bool StationValidation(CString Values[]);
	bool BCValidation(CString Values[], CString Fields[]);
	bool MobileValidation(CString Values[]);
	bool ESValidation(CString Values[]);
	bool EquipmentValidation(CString Values[], CString StClass);
	bool AntennaValidation(CString Values[], CString StClass);
	bool FrequencyValidation(CString Values[], CString StClass);
	bool AllotValidation(CString Values[]);
	void AntAssign();
	void PrintBill();
	void OnPrintInvoice(long LicID, CString InvNo);
	CString GetReportPath();
	bool IsFieldValid(CString FieldName, CRecordset &ODBCRecs);
	void ProcessBuf(CRecordset &Stations, CString RowBuf, CString &ResStr);
	void OnPrintReceipt(long LicID, CString PayNo);
	void LoadUnpaid();
	void AddTrail(CString Action, long RecordID, CString Table);
	long GetBalance(long LicID,bool *Payment);
	void OnClickGrid();

	void TranslateMenu(CMenu *pMenu);
	CString GetTranslatedString(CString strOriginal, CString Lang);
	void ChangeMenuLang(); 
			
	CString _Z(CString s){ return (GetTranslatedString(_T(s),m_Lang)); };

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTreeviewView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKillfocusCombo1();
	afx_msg void OnKillfocusCombo2();
	afx_msg void OnKillfocusCombo3();
	afx_msg void OnKillfocusCombo4();
	afx_msg void OnKillfocusCombo5();
	afx_msg void OnKillfocusCombo6();
	afx_msg void OnKillfocusDatepicker(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusTimepicker(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in treeviewView.cpp
inline CTreeviewDoc* CTreeviewView::GetDocument()
   { return (CTreeviewDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEVIEWVIEW_H__345A1683_B0CC_4CB7_920C_B52F58CCDF7D__INCLUDED_)
