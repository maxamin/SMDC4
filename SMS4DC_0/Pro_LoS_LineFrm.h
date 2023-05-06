#if !defined(AFX_PRO_LOS_LINEFRM_H__F3F03249_3901_4792_AC1E_634A2401E591__INCLUDED_)
#define AFX_PRO_LOS_LINEFRM_H__F3F03249_3901_4792_AC1E_634A2401E591__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_LoS_LineFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_LoS_LineFrm frame

class CPro_LoS_LineFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CPro_LoS_LineFrm)
protected:
	CPro_LoS_LineFrm();           // protected constructor used by dynamic creation

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_LoS_LineFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPro_LoS_LineFrm();

	// Generated message map functions
	//{{AFX_MSG(CPro_LoS_LineFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_LOS_LINEFRM_H__F3F03249_3901_4792_AC1E_634A2401E591__INCLUDED_)
