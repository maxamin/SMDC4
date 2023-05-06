// ColorListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "thalesdrawdll.h"
#include "ColorListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorListCtrl

CColorListCtrl::CColorListCtrl()
{
	m_colRow1 = RGB(230,230,255);
	m_colRow2 = RGB(255,255,255);
}

CColorListCtrl::~CColorListCtrl()
{
}


BEGIN_MESSAGE_MAP(CColorListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CColorListCtrl)
	ON_WM_ERASEBKGND()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorListCtrl message handlers


BOOL CColorListCtrl::OnEraseBkgnd(CDC* pDC) 
{
	CRect rect;
	GetClientRect(rect);
	CBrush brush1(m_colRow1);
	CBrush brush2(m_colRow2);
	pDC->FillRect(&rect,&brush1);

	POINT point;  
	int n_height = max( GetItemCount() , GetCountPerPage() );
	for (int i=0; i<=n_height; i++)
	{
		GetItemPosition(i,  &point);	rect.top    = point.y ;
		GetItemPosition(i+1,&point);	rect.bottom = point.y;
		pDC->FillRect(&rect, i%2 ? &brush2 : &brush1);
	}
	brush1.DeleteObject();
	brush2.DeleteObject();
	return FALSE;
}

void CColorListCtrl::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
{
	*pResult = 0;
	LPNMLVCUSTOMDRAW  lplvcd = (LPNMLVCUSTOMDRAW)pNMHDR;
	int iRow = lplvcd->nmcd.dwItemSpec;

	switch(lplvcd->nmcd.dwDrawStage)
	{
		case CDDS_PREPAINT :
		{
			*pResult = CDRF_NOTIFYITEMDRAW;
			return;
		}
		// Modify item text and or background
		case CDDS_ITEMPREPAINT:
		{
			lplvcd->clrText = RGB(0,0,0);
			// If you want the sub items the same as the item, set *pResult to CDRF_NEWFONT
			*pResult = CDRF_NOTIFYSUBITEMDRAW;
			return;
		}
		// Modify sub item text and/or background
		case CDDS_SUBITEM | CDDS_PREPAINT | CDDS_ITEM:
		{
			if(iRow %2)		lplvcd->clrTextBk = m_colRow2;
			else			lplvcd->clrTextBk = m_colRow1;
			*pResult = CDRF_DODEFAULT;
			return;
		}
	}
}
