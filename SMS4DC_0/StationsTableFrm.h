#if !defined(AFX_STATIONSTABLEFRM_H__7C808C77_BCBD_48F0_8D00_4E2FC9E033B4__INCLUDED_)
#define AFX_STATIONSTABLEFRM_H__7C808C77_BCBD_48F0_8D00_4E2FC9E033B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StationsTableFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStationsTableFrm frame

class CStationsTableFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CStationsTableFrm)
protected:
	CStationsTableFrm();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStationsTableFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CStationsTableFrm();

	// Generated message map functions
	//{{AFX_MSG(CStationsTableFrm)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATIONSTABLEFRM_H__7C808C77_BCBD_48F0_8D00_4E2FC9E033B4__INCLUDED_)
