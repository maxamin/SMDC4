//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_HORIZONELEVATIONDATADLG_H__725F10BA_9192_40E0_B43E_191A3C3BCDA1__INCLUDED_)
#define AFX_HORIZONELEVATIONDATADLG_H__725F10BA_9192_40E0_B43E_191A3C3BCDA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HorizonElevationDataDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHorizonElevationDataDLG dialog

class CHorizonElevationDataDLG : public CDialog
{
// Construction
public:
	CHorizonElevationDataDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHorizonElevationDataDLG)
	enum { IDD = IDD_HorizonElevationDataDLG };
	CBitmapButton	m_BUTTON_Save;
	CMSFlexGrid	m_Grid;
	//}}AFX_DATA

	int m_Azimuth[360]; 
	double m_Elevation[360]; 
	double m_Distance[360]; 
	int m_Rows;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHorizonElevationDataDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHorizonElevationDataDLG)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HORIZONELEVATIONDATADLG_H__725F10BA_9192_40E0_B43E_191A3C3BCDA1__INCLUDED_)
