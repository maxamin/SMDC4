// ThalesDrawDoc.h : interface of the CThalesDrawDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_THALESDRAWDOC_H__993AC25D_D2B3_43ED_B189_36C770E7B2CD__INCLUDED_)
#define AFX_THALESDRAWDOC_H__993AC25D_D2B3_43ED_B189_36C770E7B2CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CThalesDrawDoc : public CDocument
{
protected: // create from serialization only
	CThalesDrawDoc();
	DECLARE_DYNCREATE(CThalesDrawDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThalesDrawDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CThalesDrawDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CThalesDrawDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THALESDRAWDOC_H__993AC25D_D2B3_43ED_B189_36C770E7B2CD__INCLUDED_)
