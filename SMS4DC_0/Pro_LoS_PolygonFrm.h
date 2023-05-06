#if !defined(AFX_PRO_LOS_POLYGONFRM_H__B6AFE294_B7A8_4E80_B667_ABB8FD507A6B__INCLUDED_)
#define AFX_PRO_LOS_POLYGONFRM_H__B6AFE294_B7A8_4E80_B667_ABB8FD507A6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_LoS_PolygonFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_LoS_PolygonFrm frame

class CPro_LoS_PolygonFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CPro_LoS_PolygonFrm)
protected:
	CPro_LoS_PolygonFrm();           // protected constructor used by dynamic creation

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_LoS_PolygonFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPro_LoS_PolygonFrm();

	// Generated message map functions
	//{{AFX_MSG(CPro_LoS_PolygonFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_LOS_POLYGONFRM_H__B6AFE294_B7A8_4E80_B667_ABB8FD507A6B__INCLUDED_)
