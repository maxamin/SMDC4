#if !defined(AFX_AREA3DPROPDLG_H__08772EED_3E64_4633_AA2C_46000F4373ED__INCLUDED_)
#define AFX_AREA3DPROPDLG_H__08772EED_3E64_4633_AA2C_46000F4373ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Area3DPropDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CArea3DPropDLG dialog
class CArea3DView;

class CArea3DPropDLG : public CDialog
{
// Construction
public:
//	CArea3DPropDLG(CWnd* pParent = NULL);   // standard constructor
	CArea3DPropDLG(CArea3DView* p);
	CArea3DView *m_pView;

	int m_Pos[11];
	int GetSliderNum(HWND hwnd, UINT& nID);

// Dialog Data
	//{{AFX_DATA(CArea3DPropDLG)
	enum { IDD = IDD_Area3DPropDLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArea3DPropDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CArea3DPropDLG)
	afx_msg void OnClose();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AREA3DPROPDLG_H__08772EED_3E64_4633_AA2C_46000F4373ED__INCLUDED_)
