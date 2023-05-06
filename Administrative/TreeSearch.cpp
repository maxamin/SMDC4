// TreeSearch.cpp : implementation file
//
#include "stdafx.h"
#define APSTUDIO_INVOKED
#undef APSTUDIO_READONLY_SYMBOLS
#include "administrative.h"
#include "TreeSearch.h"
#include <math.h>
#include <direct.h>
#include "windows.h"
#include <winreg.h>
#include <stdio.h>
#include <process.h>
#include "CustomReport.h"
//#include <strsafe.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CTreeSearch dialog


CTreeSearch::CTreeSearch(CWnd* pParent /*=NULL*/)
	: CDialog(CTreeSearch::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTreeSearch)
	m_SearchText = _T("");
	//}}AFX_DATA_INIT

}

void CTreeSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTreeSearch)
	DDX_Control(pDX, IDC_SEARCH_RESULT, m_SearchResult);
	DDX_Text(pDX, IDC_SEARCH_TEXT, m_SearchText);
	DDX_Control(pDX, IDC_BEGINS_WITH, m_BeginsWith);
	DDX_Control(pDX, IDC_ENDS_WITH, m_EndsWith);
	DDX_Control(pDX, IDC_ANYWHERE, m_Anywhere);
	DDX_Control(pDX, IDC_EXACT_MATCH, m_ExactMatch);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTreeSearch, CDialog)
	//{{AFX_MSG_MAP(CTreeSearch)
	ON_BN_CLICKED(IDC_DO_SEARCH, OnDoSearch)
	ON_NOTIFY(NM_DBLCLK, IDC_SEARCH_RESULT, OnDblclkSearchResult)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeSearch message handlers

int CTreeSearch::DoModal()
{
	//By construction of class CSetExtensionDllState the order of resource access is switched
	//to DLL before EXE (default is EXE before DLL) 
	CSetExtensionDllState state;
	return CDialog::DoModal();
}

void CTreeSearch::TranslateDialog(CDialog *pDialog)
{
	CString strOriginal(_T(""));
	for (int iID = 0; iID < 64000 /*_APS_NEXT_CONTROL_VALUE*/; iID++)
	{
		pDialog->GetDlgItemText(iID, strOriginal);
		if (!strOriginal.IsEmpty())
		{
			if(((pDialog->GetDlgItem(iID))->IsKindOf(RUNTIME_CLASS(CComboBox)))!=1)
			{
				CString s = GetTranslatedString(strOriginal, m_Lang);
				if (!s.IsEmpty())// && strOriginal != s)
					pDialog->SetDlgItemText(iID, s);
			}
		}
	}//for
	strOriginal = _T("");
	pDialog->GetWindowText(strOriginal);
	if (!strOriginal.IsEmpty())
	{
		CString s = GetTranslatedString(strOriginal, m_Lang);
		if (!s.IsEmpty() && strOriginal != s)
			pDialog->SetWindowText(s);
	}
}

CString CTreeSearch::GetTranslatedString(CString strOriginal, CString Lang)
{
	static CString m_Lang;
//	m_Lang="CC";
	if(Lang!=m_Lang && !Lang.IsEmpty()) 
		m_Lang=Lang;
	if(m_Lang==_T("En"))	return strOriginal;
	int ID=-1;
	HMODULE	hMod = LoadLibrary("ResDLLen.dll");
	if(hMod)
	{
		LPCTSTR lpszName = MAKEINTRESOURCE(1);
		if (::FindResource(hMod,  lpszName, RT_STRING) != NULL)
		{
			TCHAR szTemp[1001];
			int n=0, nLen = ::LoadString(hMod, 0, szTemp, 1000);
			if(nLen!=0)		n = atoi(szTemp);

			for(int ids=1; ids<=n; ids++)
			{
				nLen = ::LoadString(hMod, ids, szTemp, 1000);
				if(strOriginal==szTemp)
				{
					ID = ids;
					break;
				}
			}
		}
		FreeLibrary(hMod);
	}//hMod

	CString str;
	if		(m_Lang==_T("Fr")) 	hMod = LoadLibrary("ResDLLfr.dll");
	else if	(m_Lang==_T("Es")) 	hMod = LoadLibrary("ResDLLes.dll");
	else if	(m_Lang==_T("Ch")) 	hMod = LoadLibrary("ResDLLch.dll");
	else if	(m_Lang==_T("Ar")) 	hMod = LoadLibrary("ResDLLar.dll");
	else if	(m_Lang==_T("Ru")) 	hMod = LoadLibrary("ResDLLru.dll");

	if(hMod)
	{
		LPCTSTR lpszName = MAKEINTRESOURCE(1);
		if (::FindResource(hMod,  lpszName, RT_STRING) != NULL)
		{
			TCHAR szTemp[1001];
			::LoadString(hMod, ID, szTemp, 1000);
			str = szTemp;
		}
		FreeLibrary(hMod);
	}//hMod

	return str;
}

BOOL CTreeSearch::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//AfxGetModuleState()->m_dwVersion = 0x0601;

	m_Lang=((CSMS4DCApp *)AfxGetApp())->m_Lang;
//	m_SearchResult.SetImageList(m_TreeView->GetTreeCtrl().GetImageList(0),TVSIL_NORMAL);
	
//	LONG style = ::GetWindowLong(m_TreeView->GetTreeCtrl().m_hWnd, GWL_STYLE);

//	::SetWindowLong(m_SearchResult.m_hWnd, GWL_STYLE, style | TVS_HASBUTTONS | TVS_HASLINES | TVS_SHOWSELALWAYS);

	m_BeginsWith.SetCheck(BST_CHECKED);
	
	TranslateDialog(this);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTreeSearch::OnOK() 
{
	CDialog::OnOK();
}

void CTreeSearch::AddFoundItem(HTREEITEM FoundItem)
{
/*	int Typ;
	CString FoundText=m_TreeView->GetTreeCtrl().GetItemText(FoundItem);
	m_TreeView->GetTreeCtrl().GetItemImage(FoundItem,Typ,Typ);
	m_SearchResult.InsertItem(FoundText, Typ, Typ, m_SearchResult.GetRootItem());*/
	
	m_TreeView->GetTreeCtrl().SelectItem(FoundItem);
	m_TreeView->GetTreeCtrl().SetItemState(FoundItem, TVIS_EXPANDED, TVIS_EXPANDED);
}

// name - the name of the item that is searched for
// tree - a reference to the tree control
// hRoot - the handle to the item where the search begins
HTREEITEM CTreeSearch::FindItem(const CString& name, CTreeCtrl& tree, HTREEITEM hRoot)
{
	int NodeType;
	bool Found=false;
	static bool Abort=false;
	tree.GetItemImage(hRoot,NodeType,NodeType);
	if(NodeType==STATION || NodeType==BC || NodeType==MOBILE || NodeType==ESTATION)
	{
	// check whether the current item is the searched one
	   CString text = tree.GetItemText(hRoot);
	   text=text.Right(text.GetLength()-12);
	   if(m_EndsWith.GetCheck()==BST_CHECKED)
			if (name.Compare(text.Right(name.GetLength())) == 0)
				Found=true; 
	   if(m_ExactMatch.GetCheck()==BST_CHECKED)
			if (name.Compare(text) == 0)
				Found=true; 
	   if(m_BeginsWith.GetCheck()==BST_CHECKED)
			if (name.Compare(text.Left(name.GetLength())) == 0)
				Found=true; 
	   if(m_Anywhere.GetCheck()==BST_CHECKED)
			if (text.Find(name) != -1)
				Found=true;
	    if(Found)
		{
			AddFoundItem(hRoot); 
			if(AfxMessageBox(_Z("Do you wish to continue the search?"),MB_YESNO)==IDNO)
			{
				Abort=true;
				return NULL;
			}
		}
	}

   // get a handle to the first child item
   HTREEITEM hSub = tree.GetChildItem(hRoot);
   // iterate as long a new item is found
   while (hSub && !Abort)
   {
      // check the children of the current item
      HTREEITEM hFound = FindItem(name, tree, hSub);
      if (hFound)
         AddFoundItem(hFound); 
 
      // get the next sibling of the current item
      hSub = tree.GetNextSiblingItem(hSub);
   } 
 
   // return NULL if nothing was found
   return NULL;
}

/*
HTREEITEM CTreeSearch::FindItem( HWND hwndTV, CString itemText )
{
    HTREEITEM htiRoot = m_TreeView->GetTreeCtrl().GetRootItem( hwndTV );
    return FindItemDepthFirstImpl( hwndTV, htiRoot, itemText );
}

HTREEITEM CTreeSearch::FindItemDepthFirstImpl( HWND hwndTV, HTREEITEM htStart, CString itemText )
{
    HTREEITEM htItemMatch = NULL;

    HTREEITEM htItemCurrent = htStart;
    // Iterate over items until there are no more items or we found a match
    while ( htItemCurrent != NULL && htItemMatch == NULL )
    {
        if ( GetItemText( hwndTV, htItemCurrent ) == itemText )
        {
            htItemMatch = htItemCurrent;
        }
        else
        {
            // Traverse into child items
            htItemMatch = FindItemDepthFirstImpl( hwndTV, TreeView_GetChild( hwndTV, htItemCurrent ), itemText );
        }
        htItemCurrent = TreeView_GetNextSibling( hwndTV, htItemCurrent );
    }

    return htItemMatch;
}*/

void CTreeSearch::OnDoSearch() 
{
	// TODO: Add your control notification handler code here
//	m_SearchResult.DeleteAllItems();
	HTREEITEM tns;
//	HTREEITEM root=m_SearchResult.InsertItem(_Z("Search result"),SMS4DC,SMS4DC);

	UpdateData(true);

	tns=FindItem(m_SearchText, m_TreeView->GetTreeCtrl(), m_TreeView->GetTreeCtrl().GetRootItem());

	if(!tns) OnOK();
}

void CTreeSearch::OnDblclkSearchResult(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	m_TreeView->GetTreeCtrl().Expand(m_TreeView->GetTreeCtrl().GetRootItem(),TVE_TOGGLE);
	*pResult = 0;
}
