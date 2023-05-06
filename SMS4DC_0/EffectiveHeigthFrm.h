#if !defined(AFX_EFFECTIVEHEIGTHFRM_H__8C3CFAA5_8F47_4893_B62C_013AE82A1A5A__INCLUDED_)
#define AFX_EFFECTIVEHEIGTHFRM_H__8C3CFAA5_8F47_4893_B62C_013AE82A1A5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EffectiveHeigthFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEffectiveHeigthFrm frame

class CEffectiveHeigthFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CEffectiveHeigthFrm)
protected:
	CEffectiveHeigthFrm();           // protected constructor used by dynamic creation

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEffectiveHeigthFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CEffectiveHeigthFrm();

	// Generated message map functions
	//{{AFX_MSG(CEffectiveHeigthFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EFFECTIVEHEIGTHFRM_H__8C3CFAA5_8F47_4893_B62C_013AE82A1A5A__INCLUDED_)
