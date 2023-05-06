#if !defined(AFX_POWERCALCULATORDLG_H__02D19352_69E1_4F85_8956_A6A23E8E4D74__INCLUDED_)
#define AFX_POWERCALCULATORDLG_H__02D19352_69E1_4F85_8956_A6A23E8E4D74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PowerCalculatorDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPowerCalculatorDLG dialog

class CPowerCalculatorDLG : public CDialog
{
// Construction
public:
	CPowerCalculatorDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPowerCalculatorDLG)
	enum { IDD = IDD_PowerCalculatorDLG };
	CComboBox	m_COMBO_DATAR;
	CComboBox	m_COMBO_DATAL;
	double	m_f_MHz;
	double	m_Gr;
	double	m_Lc;
	double	m_R;
	CString	m_DATAL;
	CString	m_DATAR;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPowerCalculatorDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPowerCalculatorDLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonl();
	afx_msg void OnSelchangeComboDatal();
	afx_msg void OnSelchangeComboDatar();
	afx_msg void OnButtonr();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_ErText;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POWERCALCULATORDLG_H__02D19352_69E1_4F85_8956_A6A23E8E4D74__INCLUDED_)
