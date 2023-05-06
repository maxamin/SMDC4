#if !defined(AFX_ANTENNAFORMFRM_H__76F6B193_98F2_450E_A869_C483EA00F406__INCLUDED_)
#define AFX_ANTENNAFORMFRM_H__76F6B193_98F2_450E_A869_C483EA00F406__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AntennaFormFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAntennaFormFrm frame

class CAntennaFormFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CAntennaFormFrm)
protected:
	CAntennaFormFrm();           // protected constructor used by dynamic creation

// Attributes
public:
    HMENU &SharedMenu(void){return m_hMenuShared;};		//98/05/06

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAntennaFormFrm)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CAntennaFormFrm();

	// Generated message map functions
	//{{AFX_MSG(CAntennaFormFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANTENNAFORMFRM_H__76F6B193_98F2_450E_A869_C483EA00F406__INCLUDED_)
