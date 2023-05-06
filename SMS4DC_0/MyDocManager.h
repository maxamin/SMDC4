// MyDocManager.h: interface for the CMyDocManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYDOCMANAGER_H__B9F77800_F449_11D3_ABBD_00C04F89AE42__INCLUDED_)
#define AFX_MYDOCMANAGER_H__B9F77800_F449_11D3_ABBD_00C04F89AE42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyDocManager : public CDocManager
{
	DECLARE_DYNAMIC(CMyDocManager)
public:
	CMyDocManager();
	virtual ~CMyDocManager();
	BOOL	CreateNewDocument(int doc_index) ;
	int		GetMyDocumentCount() ;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

#endif // !defined(AFX_MYDOCMANAGER_H__B9F77800_F449_11D3_ABBD_00C04F89AE42__INCLUDED_)
