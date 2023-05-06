// MyMultiDocTemplate.cpp: implementation of the CMyMultiDocTemplate class.
//
//////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "MyMultiDocTemplate.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CMyMultiDocTemplate, CMultiDocTemplate)

CMyMultiDocTemplate::CMyMultiDocTemplate(HINSTANCE hInst, UINT nIDResource, CRuntimeClass* pDocClass, CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass )
: CMultiDocTemplate(nIDResource, pDocClass, pFrameClass, pViewClass)
{
	m_hInst = hInst ;
	m_ResourceID = nIDResource ;
}

CMyMultiDocTemplate::~CMyMultiDocTemplate()
{

}

void CMyMultiDocTemplate::LoadTemplate()
{
	// call the base class member after switching the resource to the DLL, if this is a DLL document type
	HINSTANCE	hOld ;

	hOld = AfxGetResourceHandle() ;			// save
	AfxSetResourceHandle(m_hInst) ;			// set
	CMultiDocTemplate::LoadTemplate() ;		// now get from correct resources!
	AfxSetResourceHandle(hOld) ;			// restore
}

CDocument* CMyMultiDocTemplate::OpenDocumentFile(LPCTSTR lpszPathName, BOOL bMakeVisible)
{
	// switch to the correct resources and then resturn the document
	CDocument	*pDoc = NULL ;
	HINSTANCE	hOld ;

	hOld = AfxGetResourceHandle() ;			// save
	AfxSetResourceHandle(m_hInst) ;			// set
	pDoc = CMultiDocTemplate::OpenDocumentFile(lpszPathName, bMakeVisible) ;
	AfxSetResourceHandle(hOld) ;			// restore
	return pDoc ;
}

#ifdef _DEBUG
void CMyMultiDocTemplate::AssertValid() const
{
	CMultiDocTemplate::AssertValid();
}

void CMyMultiDocTemplate::Dump(CDumpContext& dc) const
{
	CMultiDocTemplate::Dump(dc);
}
#endif