#if !defined(AFX_GRPDETAILS_H__69E5DFF7_4318_4C44_ADA4_318486968502__INCLUDED_)
#define AFX_GRPDETAILS_H__69E5DFF7_4318_4C44_ADA4_318486968502__INCLUDED_

#include "resource.h"
#include "Administrative.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GrpDetails.h : header file
//
#include "EditGrid.h"

/////////////////////////////////////////////////////////////////////////////
// CGrpDetails dialog

class CGrpDetails : public CDialog
{
// Construction
public:
	CGrpDetails(CWnd* pParent = NULL);   // standard constructor
	~CGrpDetails(){if(m_RS.IsOpen()) m_RS.Close(); m_DB.Close();}

// Dialog Data
	//{{AFX_DATA(CGrpDetails)
	enum { IDD = IDD_GrpDetails };
	CBitmapButton	m_SaveGrid;
	CBitmapButton	m_DelRec;
	CBitmapButton	m_AddRec;
	CEditGrid m_Grid;
	//}}AFX_DATA
	
	int m_Type; //  1=Emissions, 2=Frequencies, 3=Special Section, 4=Coordination, 5=Class of station, 
				//	6=Elevation angle, 7=Minimum Elev. Angles, 8=Antenna pattern, 9=Terresterial coord.
				// 10=Contour, 11=Service Area, 12=Allot Coord.
	int m_BeamType; //1=Emitter, 2=Receiver
	long m_Grp_id;
	CString m_CDBSTR, m_Lang, m_StName;
	CDatabase m_DB;
	CRecordset m_RS;
	bool m_DataSaved;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrpDetails)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGrpDetails)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddrec();
	afx_msg void OnDelrec();
	afx_msg bool OnSave();
	afx_msg void OnClose();
	virtual void OnCancel();
	//}}AFX_MSG
	CString GetFieldName(CDatabase *DB, CString Table, CString OrigName, CString LangCode, CString *Unit, CString *Format, CString *Srv, CString *Mask);
	CString _Z(CString s){ return (((CAdministrativeApp *)AfxGetApp())->GetTranslatedString(_T(s),m_Lang)); };
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRPDETAILS_H__69E5DFF7_4318_4C44_ADA4_318486968502__INCLUDED_)
