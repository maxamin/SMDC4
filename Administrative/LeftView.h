// LeftView.h : interface of the CLeftView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEFTVIEW_H__6EA7D72A_4037_419E_99EF_6CD151FDF1E6__INCLUDED_)
#define AFX_LEFTVIEW_H__6EA7D72A_4037_419E_99EF_6CD151FDF1E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Administrative.h"

enum NodeTypes
{
	SMS4DC,	OWNER, LICENSE, STATION, BC, MOBILE, EQUIPMENT, FREQUENCY, ANTENNA, INVOICE,
	PAYMENT, RECEIVER, UNLICENSED, ACTIVE, INACTIVE, ESTATION, EANTUP, EANTDN, GROUP,
	ALLOTMENT, CONTOUR, MONITORING
};


class CTreeviewDoc;

class CLeftView : public CTreeView
{
protected: // create from serialization only
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// Attributes
public:
	CTreeviewDoc* GetDocument();
	CImageList	*m_ImageList;
	CPoint	m_MousePos;

	CString m_CDBSTR;
	CString m_UserName;
	int m_UserLevel;
	CString m_Lang;

	// Copy/Move data
	HTREEITEM m_CopyNode;
	CString m_StType;
	CString m_StName;
	long m_CopyID;
	bool m_Move; // TRUE:Move, FALSE:Copy

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL
	void BuildTree(int times);
	void LoadData(CString Table, long ID, int RecType);
	void CleanScreen();
	CString GetReportPath();
	bool IsFieldValid(CString FieldName, CRecordset &ODBCRecs);
	void ProcessBuf(CRecordset &Stations, CString RowBuf, CString &ResStr);
	void FixedLicense(CString ID);
	void LMLicense(CString ID);
	void BCLicense(CString ID);
	void ESLicense(CString ID);
	void IssueInvoices();
	long GetBalance(CString LID);
	long AddSt(CString STname, double STlat_deg, double STlon_deg, long Sth_agl,
       double txfreq, double power_eirp, double Azimuth, double Elevation,
       double AntGain, double BWh, double BWv, CString Polarization, double InsertionLoss, 
       double RxSensitivity, CString STTP, CString Emission, double BandWidth, long HeightASL, 
	   CString AntPath);
	void AddSt2(CString STname, double STlat_deg, double STlon_deg, long HeightASL, double Lon_nom, 
		CString Satname, CString Ctry, double AzmFr, double AzmTo, double ElevMin, CString StType);
	CString AssignAntenna(CDatabase *DB,long AntID, CString AntPath, double *FreqFrom, double *FreqTo, CString Pol, double Azimuth);
	bool DelRecPermanent(int Typ, long RecID, int Ans, long ParentID);
	bool DuplicateRec(int Typ, long RecID, int Ans, long ParentID, long NewID);
	void CopyToArchive(long LicID);
	void AddTrail(CString Action, long RecordID, CString Table);
	 CString GetFieldName(CDatabase *DB, CString Table, CString OrigName, CString LangCode, 
		CString *Unit, CString *Format, CString *Srv, CString *Mask);
	CString BWCode(double BW);
	void TranslateMenu(CMenu *pMenu);
	CString GetTranslatedString(CString strOriginal, CString Lang);
	void ChangeMenuLang(); 
	CString _Z(CString s){ return (((CAdministrativeApp *)AfxGetApp())->GetTranslatedString(_T(s), m_Lang)); };
	void OnCustomReport();
	void OnSearchTree();

// Implementation
public:
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLeftView)
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetfocus(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLicensePrintlicense();
	afx_msg void OnAddpayment();
	afx_msg void OnLicenseNotice();
	afx_msg void OnStationNotice();
	afx_msg void OnDeleteReceiver();
	afx_msg void OnEditOwner();
	afx_msg void OnEditantenna();
	afx_msg void OnEditequipment();
	afx_msg void OnEditfrequency();
	afx_msg void OnEditlicense();
	afx_msg void OnEditstation();
	afx_msg void OnDuplicatestation();
	afx_msg void OnMovestation();
	afx_msg void OnDuplicateEstation();
	afx_msg void OnMoveEstation();
	afx_msg void OnPasteStation();
	afx_msg void OnAddOwner();
	afx_msg void OnAddLicense();
	afx_msg void OnAddAntenna();
	afx_msg void OnAddEquipment();
	afx_msg void OnAddFrequency();
	afx_msg void OnDeleteFrequency();
	afx_msg void OnDeleteAntenna();
	afx_msg void OnDeleteEquipment();
	afx_msg void OnDeleteStation();
	afx_msg void OnDeleteLicense();
	afx_msg void OnLicensePrintSummary();
	afx_msg void OnAntennaPattern();
	afx_msg void OnAddFx();
	afx_msg void OnAddLm();
	afx_msg void OnAddBc();
	afx_msg void OnAddMl();
	afx_msg void OnImportTech();
	afx_msg void OnFrequencyFilterTX();
	afx_msg void OnFrequencyFilterRX();
	afx_msg void OnAddInvoice();
	afx_msg void OnUpdateAddowner(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDeletestation(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddequipment(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDeleteReceiver(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDeleteowner(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditowner(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddlicense(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditstation(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditantenna(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDeleteantenna(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditlicense(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDeletelicense(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCancellic(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddFx(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddBc(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddLm(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddMl(CCmdUI* pCmdUI);
	afx_msg void OnUpdateImportTech(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditfrequency(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDeletefrequency(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFrequencyFiltertx(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFrequencyFilterrx(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddfrequency(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddantenna(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDeleteequipment(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditequipment(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddinvoice(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddpayment(CCmdUI* pCmdUI);
	afx_msg void OnCancellic();
	afx_msg void OnLicenseCopytoarchive();
	afx_msg void OnTreeRefresh();
	afx_msg void OnGroupEmissions();
	afx_msg void OnGroupFrequency();
	afx_msg void OnGroupCoordination();
	afx_msg void OnGroupFilter();
	afx_msg void OnGroupClassofstation();
	afx_msg void OnEarthstationHorizontalelevation();
	afx_msg void OnEarthstationMinimumelevangles();
	afx_msg void OnAddEs();
	afx_msg void OnAddbeamup();
	afx_msg void OnAddbeamdown();
	afx_msg void OnAddgroup();
	afx_msg void OnGroupSpecialsection();
	afx_msg void OnGroupDelete();
	afx_msg void OnEsantennaDelete();
	afx_msg void OnEarthstationDelete();
	afx_msg void OnEarthstationNotice();
	afx_msg void OnFrequencyCoordination();
	afx_msg void OnEsantennaShowpattern();
	afx_msg void OnDeleteOwner();
	afx_msg void OnContourPoints();
	afx_msg void OnUpdateAddAllotment(CCmdUI* pCmdUI);
	afx_msg void OnAddAllotment();
	afx_msg void OnEditAllot();
	afx_msg void OnUpdateEditAllot(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDeleteAllot(CCmdUI* pCmdUI);
	afx_msg void OnDeleteAllot();
	afx_msg void OnUpdateAddContour(CCmdUI* pCmdUI);
	afx_msg void OnAddContour();
	afx_msg void OnUpdateDeleteContour(CCmdUI* pCmdUI);
	afx_msg void OnDeleteContour();
	afx_msg void OnUpdateAddbeamdown(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddbeamup(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddEs(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddgroup(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAttachContour(CCmdUI* pCmdUI);
	afx_msg void OnAttachContour();
	afx_msg void OnAllotmentElectronicnotice();
	afx_msg void OnUpdateLicenseAddallotment(CCmdUI* pCmdUI);
	afx_msg void OnLicenseAddallotment();
	afx_msg void OnLicenseMoveallotment();
	afx_msg void OnUpdateLicenseMoveallotment(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFrequencyServicearea(CCmdUI* pCmdUI);
	afx_msg void OnFrequencyServicearea();
	afx_msg void OnAllotCoordination();
	afx_msg void OnContourElectronicnotice();
	afx_msg void OnUpdateDeleteselection(CCmdUI* pCmdUI);
	afx_msg void OnDeleteselection();
	afx_msg void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTotalstations();
	afx_msg void OnExpiredlicenses();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LeftView.cpp
inline CTreeviewDoc* CLeftView::GetDocument()
   { return (CTreeviewDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEFTVIEW_H__6EA7D72A_4037_419E_99EF_6CD151FDF1E6__INCLUDED_)
