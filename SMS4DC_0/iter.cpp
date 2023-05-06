#include "stdafx.h"
#include "iter.h"

// Function fills a list of all document objects in the application
void DocUtil::GetAllDocuments(DocumentList_t &Docs)
{
	CWinApp *pApp = AfxGetApp();
	CDocManager *pDocMgr = pApp->m_pDocManager;  
	// For all document templates
	for(POSITION TmplPos = pDocMgr->GetFirstDocTemplatePosition();	TmplPos;)
	{
		CDocTemplate *pTmpl = pDocMgr->GetNextDocTemplate(TmplPos);
		ASSERT_VALID(pTmpl);    
		// For All open documents of this document template type.
		for(POSITION Pos = pTmpl->GetFirstDocPosition();Pos;) 
		{
			CDocument *pDoc = pTmpl->GetNextDoc(Pos);	  	  
			Docs.AddTail(pDoc);
		}
	}
}

CDocument * DocUtil::GetLastDocument(CString Type)
{
	DocumentList_t Docs;
	GetDocumentsByType(Docs,Type);  
//	CDocument *pDoc = Docs.GetTail();
//	return pDoc;

	return (Docs.GetTail());
}

bool DocUtil::GetDocumentsByType(DocumentList_t &Docs, CString Type)
{
	CWinApp *pApp = AfxGetApp();
	CDocManager *pDocMgr = pApp->m_pDocManager;  
	// For all document templates
	for(POSITION TmplPos = pDocMgr->GetFirstDocTemplatePosition();	TmplPos;)
	{
		CDocTemplate *pTmpl = pDocMgr->GetNextDocTemplate(TmplPos);
		CString DocString;
		ASSERT_VALID(pTmpl);    
		pTmpl->GetDocString(DocString,CDocTemplate::docName);
		if(!DocString.CompareNoCase(Type))
		{
			// For All open documents of this document template type.
			for(POSITION Pos = pTmpl->GetFirstDocPosition();Pos;) 
			{
				CDocument *pDoc = pTmpl->GetNextDoc(Pos);	  	  
				Docs.AddTail(pDoc);
			}
			return 1;
		}//end if
	}
	return 0;
}

BOOL DocUtil::IsOpenDocument(CDocument *pDocTest)
{
	DocumentList_t Docs;
	GetAllDocuments(Docs);  
	for(POSITION pos = Docs.GetHeadPosition();pos;)
	{			  
		if((Docs.GetNext(pos))==pDocTest) return TRUE;
	}
	return FALSE;
}

/*
// Function fills a list of all views in the application
void DocUtil::GetAllViews(ViewList_t &Views)
{
  CWinApp *pApp = AfxGetApp();
  CDocManager *pDocMgr = pApp->m_pDocManager;
  // For all document templates
  for(POSITION TmplPos = pDocMgr->GetFirstDocTemplatePosition();
	  TmplPos;)
  {
    CDocTemplate *pTmpl = pDocMgr->GetNextDocTemplate(TmplPos);
    ASSERT_VALID(pTmpl);
    // For All open documents of this document template type.
    for(POSITION Pos = pTmpl->GetFirstDocPosition();Pos;) 
	{
      CDocument *pDoc = pTmpl->GetNextDoc(Pos);	  	  
	  // For all views of this document
	  POSITION ViewPos = pDoc->GetFirstViewPosition();
	  while(ViewPos)
	  {
	    CView *pView =  pDoc->GetNextView(ViewPos); 		
		Views.AddTail(pView);
	  }
    }
  }
}

// Function fills a list of all Child frames in the application
// i.e. all CFrameWnd's except that returned by AfxGetMainWnd().
void DocUtil::GetAllFrameWnds(FrameList_t &Frames)
{
  CWinApp *pApp = AfxGetApp();
  CDocManager *pDocMgr = pApp->m_pDocManager;  
  // For all document templates
  for(POSITION TmplPos = pDocMgr->GetFirstDocTemplatePosition();
	  TmplPos;)
  {
    CDocTemplate *pTmpl = pDocMgr->GetNextDocTemplate(TmplPos);
    ASSERT_VALID(pTmpl);
    // For All open documents of this document template type.
    for(POSITION Pos = pTmpl->GetFirstDocPosition();Pos;) 
	{
      CDocument *pDoc = pTmpl->GetNextDoc(Pos);	  	  
	  // get me a view and from it the MDI child frame
      POSITION ViewPos = pDoc->GetFirstViewPosition();
      CView *pView =  pDoc->GetNextView(ViewPos); 	
      CFrameWnd *pFrame = pView->GetParentFrame();			
	  ASSERT_VALID(pFrame);
      Frames.AddTail(pFrame);    
    }
  }
}

// Function activates the MDI child for argument document object.
void DocUtil::BringToTop(CDocument *pDoc)
{
  // get me a view for this doc.
  POSITION ViewPos = pDoc->GetFirstViewPosition();
  if (ViewPos)
  {
    CView *pView =  pDoc->GetNextView(ViewPos); 
	CFrameWnd *pFrame = pView->GetParentFrame();
	if (pFrame)
	  pFrame->ActivateFrame(); // activate.
  }
}

// returns the active document (for both SDI and MDI).
CDocument *DocUtil::GetActiveDoc()
{
  CFrameWnd *pWnd = (CFrameWnd *) AfxGetMainWnd();  
  if (pWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd)))
  {
	pWnd = pWnd->GetActiveFrame();
	if (pWnd)
	  return pWnd->GetActiveDocument();
  }
  return 0;
}


// Function performs a "save all" command. Prompts to save all modified documents.
void DocUtil::CloseAllCommand()
{
  DocumentList_t Docs;
  GetAllDocuments(Docs);  
  for(POSITION pos = Docs.GetHeadPosition();pos;)
  {			  
    CDocument *pDoc = Docs.GetNext(pos);
    pDoc->OnCmdMsg(ID_FILE_CLOSE, 0, 0, 0);		
  }
}

void DocUtil::ListOpenDocuments()
{
  DocumentList_t Docs;
  GetAllDocuments(Docs);  
  for(POSITION pos = Docs.GetHeadPosition();pos;)
  {			  
    CDocument *pDoc = Docs.GetNext(pos);
	AfxMessageBox(pDoc->GetTitle());
  }
}

CDocument *DocUtil::FindLastDocument()
{
	DocumentList_t Docs;
	GetAllDocuments(Docs);  
	CDocument *pDoc = Docs.GetTail();
	//	AfxMessageBox(pDoc->GetTitle());
	return pDoc;

}

void DocUtil::ListOpenDocuments(CString Type)
{
  DocumentList_t Docs;
  GetDocumentsByType(Docs,Type);  
  for(POSITION pos = Docs.GetHeadPosition();pos;)
  {			  
    CDocument *pDoc = Docs.GetNext(pos);
	AfxMessageBox(pDoc->GetTitle());
  }
}
*/

// Function performs a "save all" command. Prompts to save all modified documents.
//void DocUtil::SaveAllCommand()
//{
/*  CDocument *pActiveDoc = GetActiveDoc();
  DocumentList_t Docs;
  GetAllDocuments(Docs);  
  for(POSITION pos = Docs.GetHeadPosition();pos;)
  {			  
    CDocument *pDoc = Docs.GetNext(pos);
    if (pDoc->IsModified())
	{
	  if (pDoc->GetPathName()=="") // if no path then promt is displayed
	    BringToTop(pDoc);  //   so bring window to top!.
	  pDoc->DoFileSave();	  
	}
  }
  if (pActiveDoc)
    BringToTop(pActiveDoc);
*/
//}
