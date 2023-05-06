#ifndef _DOCVIEW_ITER_H_
#define _DOCVIEW_ITER_H_

#include <afxtempl.h>

//typedef CTypedPtrList<CPtrList,CView*>     ViewList_t;
//typedef CTypedPtrList<CPtrList,CFrameWnd*> FrameList_t;
typedef CTypedPtrList<CPtrList,CDocument*> DocumentList_t;


class DocUtil
{
public:
//  static void       GetAllViews    (ViewList_t     &Views);
//  static void       GetAllFrameWnds(FrameList_t    &Frames);
//  static void       BringToTop     (CDocument     *pDoc);
//  static CDocument *GetActiveDoc   ();
//  static void       SaveAllCommand ();
//  static void       CloseAllCommand();
//  static void		ListOpenDocuments();

//  static CDocument *FindLastDocument();
//	static void		ListOpenDocuments(CString Type);

	static void				GetAllDocuments(DocumentList_t &Docs);
	static CDocument *		GetLastDocument(CString Type);
	static bool				GetDocumentsByType(DocumentList_t &Docs, CString Type);
	static BOOL				IsOpenDocument(CDocument *pDocTest);

};

#endif
