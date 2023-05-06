#if !defined(AFX_PRO_P370_LINEFRM_H__6A09783E_74C8_4585_A559_62A24B17E40B__INCLUDED_)
#define AFX_PRO_P370_LINEFRM_H__6A09783E_74C8_4585_A559_62A24B17E40B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_P370_LineFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_P370_LineFrm frame

class CPro_P370_LineFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CPro_P370_LineFrm)
protected:
	CPro_P370_LineFrm();           // protected constructor used by dynamic creation

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_P370_LineFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPro_P370_LineFrm();

	// Generated message map functions
	//{{AFX_MSG(CPro_P370_LineFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_P370_LINEFRM_H__6A09783E_74C8_4585_A559_62A24B17E40B__INCLUDED_)
