#if !defined(AFX_INT_BC2BC_FREEFRM_H__BA0D2563_41BF_440F_B4D5_E4CFB56F49D5__INCLUDED_)
#define AFX_INT_BC2BC_FREEFRM_H__BA0D2563_41BF_440F_B4D5_E4CFB56F49D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Int_BC2BC_FreeFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInt_BC2BC_FreeFrm frame

class CInt_BC2BC_FreeFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CInt_BC2BC_FreeFrm)
protected:
	CInt_BC2BC_FreeFrm();           // protected constructor used by dynamic creation

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInt_BC2BC_FreeFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CInt_BC2BC_FreeFrm();

	// Generated message map functions
	//{{AFX_MSG(CInt_BC2BC_FreeFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INT_BC2BC_FREEFRM_H__BA0D2563_41BF_440F_B4D5_E4CFB56F49D5__INCLUDED_)
