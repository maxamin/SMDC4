#if !defined(AFX_ANT3DDOC_H__715632D3_85B5_4ABF_9607_ADC9D879D9C0__INCLUDED_)
#define AFX_ANT3DDOC_H__715632D3_85B5_4ABF_9607_ADC9D879D9C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Ant3DDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAnt3DDoc document

class CAnt3DDoc : public CDocument
{
protected:
	CAnt3DDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CAnt3DDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnt3DDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAnt3DDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CAnt3DDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANT3DDOC_H__715632D3_85B5_4ABF_9607_ADC9D879D9C0__INCLUDED_)
