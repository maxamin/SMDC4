// ArgusDoc.h : interface of the CArgusDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARGUSDOC_H__32451509_4042_4208_9EDF_E53F5716D7C3__INCLUDED_)
#define AFX_ARGUSDOC_H__32451509_4042_4208_9EDF_E53F5716D7C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CArgusDoc : public CDocument
{
protected: // create from serialization only
	CArgusDoc();
	DECLARE_DYNCREATE(CArgusDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArgusDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CArgusDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CArgusDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARGUSDOC_H__32451509_4042_4208_9EDF_E53F5716D7C3__INCLUDED_)
