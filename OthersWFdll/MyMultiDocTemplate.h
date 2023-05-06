// MyMultiDocTemplate.h: interface for the CMyMultiDocTemplate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYMULTIDOCTEMPLATE_H__9545A663_F409_11D3_ABBD_00C04F89AE42__INCLUDED_)
#define AFX_MYMULTIDOCTEMPLATE_H__9545A663_F409_11D3_ABBD_00C04F89AE42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyMultiDocTemplate : public CMultiDocTemplate
{
	DECLARE_DYNAMIC(CMyMultiDocTemplate)
public:
	CMyMultiDocTemplate(HINSTANCE hInst, UINT nIDResource, CRuntimeClass* pDocClass, CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass );
	virtual ~CMyMultiDocTemplate();
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszPathName, BOOL bMakeVisible = TRUE ) ;

	virtual void	LoadTemplate() ;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
public:
	HINSTANCE	m_hInst ;
	UINT		m_ResourceID ;
};

#endif // !defined(AFX_MYMULTIDOCTEMPLATE_H__9545A663_F409_11D3_ABBD_00C04F89AE42__INCLUDED_)
