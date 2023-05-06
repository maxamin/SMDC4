#if !defined(AFX_PRO_HATA_NETBFRM_H__BF19D43A_9215_4E90_BF11_EFD5A6479A95__INCLUDED_)
#define AFX_PRO_HATA_NETBFRM_H__BF19D43A_9215_4E90_BF11_EFD5A6479A95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_HATA_NetBFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_HATA_NetBFrm frame

class CPro_HATA_NetBFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CPro_HATA_NetBFrm)
protected:
	CPro_HATA_NetBFrm();           // protected constructor used by dynamic creation

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_HATA_NetBFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPro_HATA_NetBFrm();

	// Generated message map functions
	//{{AFX_MSG(CPro_HATA_NetBFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_HATA_NETBFRM_H__BF19D43A_9215_4E90_BF11_EFD5A6479A95__INCLUDED_)
