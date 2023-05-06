#if !defined(AFX_PRO_HATA_NETFFRM_H__36FC737A_03FB_40A0_BE31_D214BB9BA481__INCLUDED_)
#define AFX_PRO_HATA_NETFFRM_H__36FC737A_03FB_40A0_BE31_D214BB9BA481__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_HATA_NetFFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_HATA_NetFFrm frame

class CPro_HATA_NetFFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CPro_HATA_NetFFrm)
protected:
	CPro_HATA_NetFFrm();           // protected constructor used by dynamic creation

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_HATA_NetFFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPro_HATA_NetFFrm();

	// Generated message map functions
	//{{AFX_MSG(CPro_HATA_NetFFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_HATA_NETFFRM_H__36FC737A_03FB_40A0_BE31_D214BB9BA481__INCLUDED_)
