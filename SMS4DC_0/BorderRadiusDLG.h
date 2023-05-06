#if !defined(AFX_BORDERRADIUSDLG_H__3D925906_4A18_4C58_8BB8_720FDCCCAF65__INCLUDED_)
#define AFX_BORDERRADIUSDLG_H__3D925906_4A18_4C58_8BB8_720FDCCCAF65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BorderRadiusDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBorderRadiusDLG dialog

class CBorderRadiusDLG : public CDialog
{
// Construction
public:
	CBorderRadiusDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBorderRadiusDLG)
	enum { IDD = IDD_BorderRadiusDLG };
	double	m_R;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBorderRadiusDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBorderRadiusDLG)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BORDERRADIUSDLG_H__3D925906_4A18_4C58_8BB8_720FDCCCAF65__INCLUDED_)
