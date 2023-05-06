// MyDocManager.cpp: implementation of the CMyDocManager class.
//
//////////////////////////////////////////////////////////////////////

#include <stdafx.h>
#include "MyDocManager.h"
#include "MyMultiDocTemplate.h"

#pragma warning(disable : 4100)	// disable warning "unreferenced formal parameter"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CMyDocManager, CDocManager)

CMyDocManager::CMyDocManager()
{

}

CMyDocManager::~CMyDocManager()
{

}

BOOL CMyDocManager::CreateNewDocument(int doc_index)
{
	// use the doc manager to add the polyfit document
	if (m_templateList.GetCount() >= doc_index)
		{
		POSITION	pos = m_templateList.GetHeadPosition() ;
		CDocTemplate *pTemplate = NULL ;
		// iterate through the list looking for the required document type
		if (doc_index == 0)
			pTemplate = (CDocTemplate*)m_templateList.GetNext(pos) ;
		while (pos != NULL && doc_index > 0)
			{
			pTemplate = (CDocTemplate*)m_templateList.GetNext(pos) ;
			ASSERT_KINDOF(CDocTemplate, pTemplate) ;

//			if (pTemplate->m_pDocClass == pRC)
//				{
//				// found the required document type, exit loop
//				break ;
//				}
			doc_index-- ;
			}
		// creaet the document!
		pTemplate->OpenDocumentFile(NULL);
		return TRUE ;
		}

	// create the required document
	return FALSE ;
}

#ifdef _DEBUG
void CMyDocManager::AssertValid() const
{
	CDocManager::AssertValid();
}

void CMyDocManager::Dump(CDumpContext& dc) const
{
	CDocManager::Dump(dc);
}
#endif

int	CMyDocManager::GetMyDocumentCount()
{
	return m_templateList.GetCount() ;
}


