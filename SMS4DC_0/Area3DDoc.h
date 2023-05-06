#if !defined(AFX_AREA3DDOC_H__D91F7F16_B3E6_4935_B498_8E781D0EFBD9__INCLUDED_)
#define AFX_AREA3DDOC_H__D91F7F16_B3E6_4935_B498_8E781D0EFBD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Area3DDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CArea3DDoc document

class CArea3DDoc : public CDocument
{
protected:
	CArea3DDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CArea3DDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArea3DDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CArea3DDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CArea3DDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AREA3DDOC_H__D91F7F16_B3E6_4935_B498_8E781D0EFBD9__INCLUDED_)
