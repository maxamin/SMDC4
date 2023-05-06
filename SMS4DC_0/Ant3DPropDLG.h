#if !defined(AFX_ANT3DPROPDLG_H__A6FE4A72_C940_450B_98D4_62810437F180__INCLUDED_)
#define AFX_ANT3DPROPDLG_H__A6FE4A72_C940_450B_98D4_62810437F180__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Ant3DPropDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAnt3DPropDLG dialog

class CAnt3DView;

class CAnt3DPropDLG : public CDialog
{
// Construction
public:
//	CAnt3DPropDLG(CWnd* pParent = NULL);   // standard constructor
	CAnt3DPropDLG(CAnt3DView* p);
	CAnt3DView *m_pView;

	int m_Pos[11];
	int GetSliderNum(HWND hwnd, UINT& nID);





// Dialog Data
	//{{AFX_DATA(CAnt3DPropDLG)
	enum { IDD = IDD_Ant3DPropDLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnt3DPropDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAnt3DPropDLG)
	afx_msg void OnClose();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANT3DPROPDLG_H__A6FE4A72_C940_450B_98D4_62810437F180__INCLUDED_)
