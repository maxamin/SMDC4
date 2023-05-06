#if !defined(AFX_SymbolDLG_H__521F31FF_9231_4964_8C72_58BB6B29CAD1__INCLUDED_)
#define AFX_SymbolDLG_H__521F31FF_9231_4964_8C72_58BB6B29CAD1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SymbolDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSymbolDLG dialog

class CSymbolDLG : public CDialog
{
// Construction
public:
	CSymbolDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSymbolDLG)
	enum { IDD = IDD_SymbolDLG };
	int		m_symbolcolorB;
	int		m_symbolcolorG;
	int		m_symbolcolorR;
	int		m_symbolsize;
	int		m_symbolTcolorB;
	int		m_symbolTcolorG;
	int		m_symbolTcolorR;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSymbolDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSymbolDLG)
	afx_msg void OnPaint();
	afx_msg void OnChangeSymbolSize();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnUpdateSymbolColorRed();
	afx_msg void OnUpdateSymbolTextColorRed();
	afx_msg void OnUpdateSymbolColorGreen();
	afx_msg void OnUpdateSymbolColorBlue();
	afx_msg void OnUpdateSymbolTextColorGreen();
	afx_msg void OnUpdateSymbolTextColorBlue();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int len1;
	CRect m_rectT,  m_rectS;
	void OnSymbolColor();
	void OnSymbolTextColor(); 
	int m_bLDown;
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SymbolDLG_H__521F31FF_9231_4964_8C72_58BB6B29CAD1__INCLUDED_)
