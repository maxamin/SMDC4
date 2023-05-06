#if !defined(AFX_PRO_P1546_POLYGONFRM_H__CDFA1F7C_B55D_48BF_8398_D28C1FD86F59__INCLUDED_)
#define AFX_PRO_P1546_POLYGONFRM_H__CDFA1F7C_B55D_48BF_8398_D28C1FD86F59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_P1546_PolygonFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_P1546_PolygonFrm frame

class CPro_P1546_PolygonFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CPro_P1546_PolygonFrm)
protected:
	CPro_P1546_PolygonFrm();           // protected constructor used by dynamic creation

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_P1546_PolygonFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPro_P1546_PolygonFrm();

	// Generated message map functions
	//{{AFX_MSG(CPro_P1546_PolygonFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_P1546_POLYGONFRM_H__CDFA1F7C_B55D_48BF_8398_D28C1FD86F59__INCLUDED_)
