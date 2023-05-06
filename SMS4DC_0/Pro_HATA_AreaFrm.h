#if !defined(AFX_PRO_HATA_AREAFRM_H__9835E32C_8DB3_4014_8732_3C04C17DCC24__INCLUDED_)
#define AFX_PRO_HATA_AREAFRM_H__9835E32C_8DB3_4014_8732_3C04C17DCC24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pro_HATA_AreaFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPro_HATA_AreaFrm frame

class CPro_HATA_AreaFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CPro_HATA_AreaFrm)
protected:
	CPro_HATA_AreaFrm();           // protected constructor used by dynamic creation

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPro_HATA_AreaFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPro_HATA_AreaFrm();

	// Generated message map functions
	//{{AFX_MSG(CPro_HATA_AreaFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRO_HATA_AREAFRM_H__9835E32C_8DB3_4014_8732_3C04C17DCC24__INCLUDED_)
