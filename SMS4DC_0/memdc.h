#ifndef _MEMDC_H_
#define _MEMDC_H_

//////////////////////////////////////////////////
class CMemDC : public CDC 
{
	private:	
		CBitmap	m_Bitmap, *m_oBitmap;	
		CDC*	m_pDC;			
		CRect	m_rect;		
		BOOL	m_bMemDC;	
	public:
	
	CMemDC(CDC* pDC) : CDC()
	{
		ASSERT(pDC != NULL); 

		m_pDC     = pDC;
		m_oBitmap = NULL;
		m_bMemDC  = !pDC->IsPrinting();

		pDC->GetClipBox(&m_rect);

		if (m_bMemDC) 
		{
			CreateCompatibleDC(pDC);
			pDC->LPtoDP(&m_rect);

			m_Bitmap.CreateCompatibleBitmap(pDC, m_rect.Width(), m_rect.Height());
			m_oBitmap = SelectObject(&m_Bitmap);

			SetMapMode(pDC->GetMapMode());
			SetWindowExt(pDC->GetWindowExt());
			SetViewportExt(pDC->GetViewportExt());

			pDC->DPtoLP(&m_rect);
			SetWindowOrg(m_rect.left, m_rect.top);
		} 
		else 
		{
			m_bPrinting = pDC->m_bPrinting;
			m_hDC       = pDC->m_hDC;
			m_hAttribDC = pDC->m_hAttribDC;
		}
		FillSolidRect(m_rect, pDC->GetBkColor());
	}
	
	~CMemDC()	
	{		
		if (m_bMemDC) 
		{
			m_pDC->BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),	this, m_rect.left, m_rect.top, SRCCOPY);			
			SelectObject(m_oBitmap);		
		} 
		else 
		{
			m_hDC = m_hAttribDC = NULL;
		}	
	}
	
	CMemDC* operator->() 
	{
		return this;
	}	
	operator CMemDC*() 
	{
		return this;
	}
	
};

#endif