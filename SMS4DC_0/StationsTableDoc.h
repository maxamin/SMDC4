#if !defined(AFX_STATIONSTABLEDOC_H__78465AB8_2C04_4F9C_BEF4_196837C22584__INCLUDED_)
#define AFX_STATIONSTABLEDOC_H__78465AB8_2C04_4F9C_BEF4_196837C22584__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StationsTableDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStationsTableDoc document

class CStationsTableDoc : public CDocument
{
protected:
	CStationsTableDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CStationsTableDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStationsTableDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStationsTableDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CStationsTableDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATIONSTABLEDOC_H__78465AB8_2C04_4F9C_BEF4_196837C22584__INCLUDED_)
