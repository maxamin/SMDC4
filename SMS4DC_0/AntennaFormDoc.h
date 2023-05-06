#if !defined(AFX_ANTENNAFORMDOC_H__8E01CE59_8949_4A97_AB5B_B663541A46BE__INCLUDED_)
#define AFX_ANTENNAFORMDOC_H__8E01CE59_8949_4A97_AB5B_B663541A46BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AntennaFormDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAntennaFormDoc document

class CAntennaFormDoc : public CDocument
{
protected:
	CAntennaFormDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CAntennaFormDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAntennaFormDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAntennaFormDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CAntennaFormDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANTENNAFORMDOC_H__8E01CE59_8949_4A97_AB5B_B663541A46BE__INCLUDED_)
