#if !defined(AFX_CONTOUR_DEMFRM_H__BD4A8035_640D_4FEA_BEE4_5A7865FA3D1F__INCLUDED_)
#define AFX_CONTOUR_DEMFRM_H__BD4A8035_640D_4FEA_BEE4_5A7865FA3D1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Contour_DEMFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CContour_DEMFrm frame

class CContour_DEMFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CContour_DEMFrm)
protected:
	CContour_DEMFrm();           // protected constructor used by dynamic creation

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CContour_DEMFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CContour_DEMFrm();

	// Generated message map functions
	//{{AFX_MSG(CContour_DEMFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTOUR_DEMFRM_H__BD4A8035_640D_4FEA_BEE4_5A7865FA3D1F__INCLUDED_)
