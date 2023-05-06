// BaseGLView.cpp : implementation file
//

#include "stdafx.h"
#include "BaseGLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define MAX_LISTS 20
#define INSTALLABLE_DRIVER_TYPE_MASK  (PFD_GENERIC_ACCELERATED|PFD_GENERIC_FORMAT)

/////////////////////////////////////////////////////////////////////////////
// CBaseGLView

IMPLEMENT_DYNCREATE(CBaseGLView, CView)

CBaseGLView::CBaseGLView()
{
	m_dAspectRatio = 1.0;
	m_bInsideDispList = FALSE; 
	m_bExternDispListCall = FALSE;
	m_bExternGLCall = FALSE;

	m_hMouseCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	for (int c=0;c<MAX_LISTS;c++) m_DispListVector[c] = 0;
}

CBaseGLView::~CBaseGLView()
{
}


BEGIN_MESSAGE_MAP(CBaseGLView, CView)
	//{{AFX_MSG_MAP(CBaseGLView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseGLView drawing

void CBaseGLView::OnDraw(CDC* pDC)
{
	static BOOL 	bBusy = FALSE;
	if(bBusy) return;
	bBusy = TRUE;

	wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	OnDrawGL();

	glFinish();
	SwapBuffers(m_pCDC->GetSafeHdc());
	bBusy = FALSE;
    wglMakeCurrent(NULL,NULL);
}

void CBaseGLView::OnDrawGL()
{
}
/////////////////////////////////////////////////////////////////////////////
// CBaseGLView diagnostics

#ifdef _DEBUG
void CBaseGLView::AssertValid() const
{
	CView::AssertValid();
}

void CBaseGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBaseGLView message handlers

BOOL CBaseGLView::bSetupPixelFormat()
{
//	static PIXELFORMATDESCRIPTOR pfd = 
	PIXELFORMATDESCRIPTOR pfd = 
	{
        sizeof(PIXELFORMATDESCRIPTOR),	// size of this pfd
        1,								// version number
        PFD_DRAW_TO_WINDOW |			// support window
        PFD_SUPPORT_OPENGL |			// support OpenGL
        PFD_DOUBLEBUFFER,				// double buffered
        PFD_TYPE_RGBA,                  // RGBA type
        24,                             // 24-bit color depth
        0, 0, 0, 0, 0, 0,               // color bits ignored
        0,                              // no alpha buffer
        0,                              // shift bit ignored
        0,                              // no accumulation buffer
        0, 0, 0, 0,                     // accum bits ignored
        32,                             // 32-bit z-buffer
        0,                              // no stencil buffer
        0,                              // no auxiliary buffer
        PFD_MAIN_PLANE,                 // main layer
        0,                              // reserved
        0, 0, 0                         // layer masks ignored
    };

    ASSERT(m_pCDC != NULL);
    int pixelformat;
	if ( (pixelformat = ChoosePixelFormat(m_pCDC->GetSafeHdc(), &pfd)) == 0 )
    {
        AfxMessageBox("ChoosePixelFormat failed");
        return FALSE;
    }

	if (SetPixelFormat(m_pCDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
    {
        pixelformat = 1;	
		if (DescribePixelFormat(m_pCDC->GetSafeHdc(), pixelformat, sizeof(PIXELFORMATDESCRIPTOR), &pfd)==0)
		{
			AfxMessageBox("SetPixelFormat failed (no OpenGL compatible video mode)");
			return FALSE;
		}
    }

    return TRUE;
}

int CBaseGLView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1) return -1;
	
	PIXELFORMATDESCRIPTOR pfd;

	m_pCDC= new CClientDC(this);

    if (!bSetupPixelFormat()) return 0;
	
    int n = ::GetPixelFormat(m_pCDC->GetSafeHdc());
    ::DescribePixelFormat(m_pCDC->GetSafeHdc(),n,sizeof(pfd),&pfd);

    m_hRC = wglCreateContext(m_pCDC->GetSafeHdc());

    wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);

	OnCreateGL();

    wglMakeCurrent(NULL,NULL);
	
	return 0;
}

void CBaseGLView::OnCreateGL()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.f,0.f,0.f,1.0f );
	glClearDepth(1.0f);
}

void CBaseGLView::OnDestroy() 
{
    wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);

	for (int c=0;c<MAX_LISTS;c++) if(m_DispListVector[c]) glDeleteLists(m_DispListVector[c],1);

	if (m_hRC!=NULL) ::wglDeleteContext(m_hRC);

	CPalette palDefault;
	palDefault.CreateStockObject(DEFAULT_PALETTE);
	m_pCDC->SelectPalette(&palDefault, FALSE);

	if(m_pCDC) delete m_pCDC;

	CView::OnDestroy();	
}

BOOL CBaseGLView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	cs.lpszClass = AfxRegisterWndClass(CS_OWNDC | CS_HREDRAW | CS_VREDRAW);
	
	return CView::PreCreateWindow(cs);
}

BOOL CBaseGLView::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

void CBaseGLView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

	if ( 0 < cx && 0 < cy )
	{
		m_dAspectRatio = cx<=cy ? double(cy)/cx : double(cx)/cy;

		wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);

		OnSizeGL(cx,cy);

		wglMakeCurrent(NULL,NULL);

		Invalidate(TRUE);
	};
}

void CBaseGLView::OnSizeGL(int cx, int cy)
{
	glViewport(0,0,cx,cy);

 	glPushMatrix();
		glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(50.0,m_dAspectRatio,0.1f, 10000.0f);
			glTranslatef(0.0f,0.0f,-4.f);
		glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void CBaseGLView::DrawStockDispLists()
{
	if(m_hRC==wglGetCurrentContext() && m_pCDC->GetSafeHdc()==wglGetCurrentDC() )
	{
		for (int c=0;c<MAX_LISTS;c++) if(m_DispListVector[c]) glCallList(m_DispListVector[c]);
	}
	else
	{
		wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);
		for (int c=0;c<MAX_LISTS;c++) if(m_DispListVector[c]) glCallList(m_DispListVector[c]);
		wglMakeCurrent(NULL,NULL);
	}
}

void CBaseGLView::StartStockDListDef()
{
	if(!m_bInsideDispList)
	{
		for (int c=0;m_DispListVector[c]!=0;c++);
		if(!( m_hRC==wglGetCurrentContext() && m_pCDC->GetSafeHdc()==wglGetCurrentDC() ))
		{
			wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);
			m_bExternDispListCall=TRUE;
		}
		m_DispListVector[c]=glGenLists(1);
		m_bInsideDispList=TRUE;
		glNewList(m_DispListVector[c],GL_COMPILE);
	}
}

void CBaseGLView::EndStockListDef()
{
	glEndList();
	m_bInsideDispList=FALSE;
	if(m_bExternDispListCall) wglMakeCurrent(NULL,NULL);
}


BOOL CBaseGLView::OnSetCursor(CWnd* /*pWnd*/, UINT /*nHitTest*/, UINT /*message*/) 
{
	ASSERT(m_hMouseCursor!=NULL);
	::SetCursor(m_hMouseCursor);
	return TRUE;
}

void CBaseGLView::BeginGLCommands()
{
	if(!( m_hRC==wglGetCurrentContext() && m_pCDC->GetSafeHdc()==wglGetCurrentDC() ))
	{
		wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);
		m_bExternGLCall = TRUE;
	}
}

void CBaseGLView::EndGLCommands()
{
	if(m_bExternGLCall) wglMakeCurrent(NULL,NULL);
}