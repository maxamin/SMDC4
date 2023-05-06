#if !defined(AFX_IDWMMAPFRM_H__62ACDE05_71DE_486E_9384_4DC04095CC4F__INCLUDED_)
#define AFX_IDWMMAPFRM_H__62ACDE05_71DE_486E_9384_4DC04095CC4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IDWMMapFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIDWMMapFrm frame

class CIDWMMapFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CIDWMMapFrm)
protected:
	CIDWMMapFrm();           // protected constructor used by dynamic creation

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIDWMMapFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CIDWMMapFrm();

	// Generated message map functions
	//{{AFX_MSG(CIDWMMapFrm)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IDWMMAPFRM_H__62ACDE05_71DE_486E_9384_4DC04095CC4F__INCLUDED_)
