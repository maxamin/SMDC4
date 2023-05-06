#if !defined(AFX_ALLOCATIONS_DRAWDOC_H__EDCBEDF5_F610_4998_B3BC_B73CBAFFAFA1__INCLUDED_)
#define AFX_ALLOCATIONS_DRAWDOC_H__EDCBEDF5_F610_4998_B3BC_B73CBAFFAFA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Allocations_DrawDoc.h : header file
//
#include "afxdb.h"

/////////////////////////////////////////////////////////////////////////////
// CAllocations_DrawDoc document

class CAllocations_DrawDoc : public CDocument
{
protected:
	CAllocations_DrawDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CAllocations_DrawDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAllocations_DrawDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAllocations_DrawDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CAllocations_DrawDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:


	struct PlanRecord{
		int SRVnum;
		COLORREF srvC[12];
		CString SRVname[12];
		int SRV_p_s[12];
		int SRV_sat[12];
		CString SRV_fot[12];
		CString SRV_fotT;
		int Region;
		CString Band;
		double FRQ_LO;
		double FRQ_HI;
/*
		CString PS1;
		CString FOTP1;
		CString PS2;
		CString FOTP2;
		CString PS3;
		CString FOTP3;
		CString PS4;
		CString FOTP4;
		CString PS5;
		CString FOTP5;
		CString PS6;
		CString FOTP6;
		CString SS1;
		CString FOTS1;
		CString SS2;
		CString FOTS2;
		CString SS3;
		CString FOTS3;
		CString SS4;
		CString FOTS4;
		CString SS5;
		CString FOTS5;
		CString SS6;
		CString FOTS6;
		CString FOT;
*/
	};

	PlanRecord *m_Recs;
	int m_RecsNUM;
	int m_ReadyDoc;
	double m_Flo,m_Fhi;
	int m_Lin_Log,m_REGION;

	int m_Fu;

	void GetData();
	int FindSat(CString PS); 
	CString Code2Name(CString code_str,int psFlag);

void ID2NameColor(CString id_str,int psFlag,CString *SRVname,COLORREF *srvRGB);


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALLOCATIONS_DRAWDOC_H__EDCBEDF5_F610_4998_B3BC_B73CBAFFAFA1__INCLUDED_)
