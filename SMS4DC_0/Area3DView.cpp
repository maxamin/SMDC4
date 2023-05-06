// Area3DView.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Area3DView.h"
#include <math.h>
#include "Area3DPropDLG.h"
#include "ContourDLG.h"

#include "MainFrm.h"
#include "Area3DDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CArea3DView

IMPLEMENT_DYNCREATE(CArea3DView, CBaseGLView)

CArea3DView::CArea3DView()
{
	colormaptype="Topo_1";
	m_level=255;
	m_pDlg=NULL;
	//====== Rendering context does not exist yet
//	m_hRC = 0;

	//====== Initial image turn
	m_AngleX = 90.f;
	m_AngleY = 90.f;

	//====== Projection matrix view angle
	m_AngleView = 50.f;

	//====== Initial bkcolor
	m_BkClr = RGB(96, 0, 0);

	// Initial mode to fill the inner polygons (quads) points
	m_FillMode = GL_FILL;

	//====== Initial plot creation
	CString FileInfo1 =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Temp\\Area3D.tmp");

	CTime t1 = CTime::GetCurrentTime();
	m_FileInfo.Format("%s\\Temp\\Area3D%d%02d%02d%02d%02d%02d.tmp" , ((CSMS4DCApp *)AfxGetApp())->m_AppPath , t1.GetYear(),t1.GetMonth(),t1.GetDay(),t1.GetHour(),t1.GetMinute(),t1.GetSecond());

	CopyFile(  FileInfo1,  m_FileInfo,  FALSE);
	DeleteFile(FileInfo1);

	DefaultGraphic();

	//====== Initial image shift
	//====== One and a half object size (backward)
	m_zTrans = -1.5f*m_fRangeX;
	m_xTrans = m_yTrans = 0.f;

	//== Initial shift quantums (for rotation animation)
	m_dx = m_dy = 0.f;

	//====== Mouse is not captured
	m_bCaptured = false;
	//====== Right mouse button has not been pressed
	m_bRightButton = false;
	//====== We use quads to create the surface
	m_bQuad = false;

	//====== Initial lighting params
	m_LightParam[0] = 50;	// X position
	m_LightParam[1] = 80;	// Y position
	m_LightParam[2] = 100;	// Z position
	m_LightParam[3] = 15;	// Ambient light
	m_LightParam[4] = 70;	// Diffuse light
	m_LightParam[5] = 100;	// Specular light
	m_LightParam[6] = 100;	// Ambient material
	m_LightParam[7] = 100;	// Diffuse material
	m_LightParam[8] = 40;	// Specular material
	m_LightParam[9] = 70;	// Shininess material
	m_LightParam[10] = 0;	// Emission material
}

CArea3DView::~CArea3DView()
{
}


BEGIN_MESSAGE_MAP(CArea3DView, CBaseGLView)
	//{{AFX_MSG_MAP(CArea3DView)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_COMMAND(ID_Topo_0, OnTopo0)
	ON_UPDATE_COMMAND_UI(ID_Topo_0, OnUpdateTopo0)
	ON_COMMAND(ID_Topo_1, OnTopo1)
	ON_UPDATE_COMMAND_UI(ID_Topo_1, OnUpdateTopo1)
	ON_COMMAND(ID_Jet, OnJet)
	ON_UPDATE_COMMAND_UI(ID_Jet, OnUpdateJet)
	ON_COMMAND(ID_Gray, OnGray)
	ON_UPDATE_COMMAND_UI(ID_Gray, OnUpdateGray)
	ON_COMMAND(ID_Pink, OnPink)
	ON_UPDATE_COMMAND_UI(ID_Pink, OnUpdatePink)
	ON_COMMAND(ID_Copper, OnCopper)
	ON_UPDATE_COMMAND_UI(ID_Copper, OnUpdateCopper)
	ON_COMMAND(ID_Globe, OnGlobe)
	ON_UPDATE_COMMAND_UI(ID_Globe, OnUpdateGlobe)
	ON_COMMAND(ID_OPTION_BACKGROUNDCOLOR, OnOptionBackgroundcolor)
	ON_COMMAND(ID_OPTION_FILLDIAGRAM, OnOptionFilldiagram)
	ON_UPDATE_COMMAND_UI(ID_OPTION_FILLDIAGRAM, OnUpdateOptionFilldiagram)
	ON_COMMAND(ID_OPTION_QUADMODE, OnOptionQuadmode)
	ON_UPDATE_COMMAND_UI(ID_OPTION_QUADMODE, OnUpdateOptionQuadmode)
	ON_COMMAND(ID_OPTION_PROPERTIES, OnOptionProperties)
	ON_COMMAND(ID_OPTION_CONTOUR, OnOptionContour)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArea3DView drawing


/////////////////////////////////////////////////////////////////////////////
// CArea3DView diagnostics

#ifdef _DEBUG
void CArea3DView::AssertValid() const
{
	CView::AssertValid();
}

void CArea3DView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CArea3DView message handlers

void CArea3DView::SetBkColor()
{
	//====== Split the color to 3 components
	GLclampf red	= GetRValue(m_BkClr)/255.f,
			 green	= GetGValue(m_BkClr)/255.f,
			 blue	= GetBValue(m_BkClr)/255.f;
	//====== Set the clear (background) color
	glClearColor (red, green, blue, 0.f);

	//====== Actual background erasure
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void CArea3DView::DrawScene()
{
	//====== Create the new list of OpenGL commands
//	glNewList(1, GL_COMPILE);

	//====== Set the polygon filling mode
	glPolygonMode(GL_FRONT_AND_BACK, m_FillMode);

	//====== Image grid sizes
	UINT	nx = m_xSize-1,		nz = m_zSize-1;

	float   shx = (-0.5)*(m_xSize),		shy = 0.f,		shz = (-0.5)*(m_zSize);

	//====== Turn on the primitive connection mode (not connected)
	if (m_bQuad)		glBegin (GL_QUADS);

	for (UINT z=0, i=0;  z < nz;  z++, i++)
	{
		//====== Turn on the primitive connection mode (connected)
		//====== The strip of connected quads begins here
		if (!m_bQuad)			glBegin(GL_QUAD_STRIP);

		for (UINT x=0;  x < nx;  x++, i++)
		{
			// i, j, k, n — 4 indices of a quad
			// Counter Clockwise direction

			int	j = i + m_xSize,	// Other vertices indices
				k = j+1,
				n = i+1;

			//=== Get coordinates of 4 vertices
			float
				xi = shx+m_cPoints[i].x,
				yi = shy+m_cPoints[i].y,
				zi = shz+m_cPoints[i].z,

				xj = shx+m_cPoints[j].x,
				yj = shy+m_cPoints[j].y,
				zj = shz+m_cPoints[j].z,

				xk = shx+m_cPoints[k].x,
				yk = shy+m_cPoints[k].y,
				zk = shz+m_cPoints[k].z,

				xn = shx+m_cPoints[n].x,
				yn = shy+m_cPoints[n].y,
				zn = shz+m_cPoints[n].z,

				//=== Quad side lines vectors coordinates
				ax = xi-xn,
				ay = yi-yn,

				by = yj-yi,
				bz = zj-zi,

				//====== Normal vector coordinates
				vx = ay*bz,
				vy = -bz*ax,
				vz = ax*by,

				//====== Normal vector length
				v  = float(sqrt(vx*vx + vy*vy + vz*vz));
			
			//====== Scale to unity
			vx /= v;
			vy /= v;
			vz /= v;

			//====== Set the normal vector
			glNormal3f (vx,vy,vz);

			//===== Not connected quads branch
			if (m_bQuad)
			{
				//====== Vertices are given in counter clockwise direction order
				glColor3f (GetRValue(m_cColor1[i])/255.f, GetGValue(m_cColor1[i])/255.f,GetBValue(m_cColor1[i])/255.f);

			//	glColor3f (0.2f, 0.8f, 1.f);
				glVertex3f (xi, yi, zi);
			//	glColor3f (0.6f, 0.7f, 1.f);
				glVertex3f (xj, yj, zj);
			//	glColor3f (0.7f, 0.9f, 1.f);
				glVertex3f (xk, yk, zk);
			//	glColor3f (0.7f, 0.8f, 1.f);
				glVertex3f (xn, yn, zn);
			}
			else
			//===== Connected quads branch
			{
				glColor3f (GetRValue(m_cColor1[i])/255.f, GetGValue(m_cColor1[i])/255.f,GetBValue(m_cColor1[i])/255.f);
				glVertex3f (xi, yi, zi);
				glVertex3f (xj, yj, zj);

			//	glColor3f (0.9f, 0.9f, 1.0f);
			//	glVertex3f (xi, yi, zi);
			//	glColor3f (0.5f, 0.8f, 1.0f);
			//	glVertex3f (xj, yj, zj);
			}
		}
		//====== Close block of GL_QUAD_STRIP commands
		if (!m_bQuad)			glEnd();
	}
		//====== Close block of GL_QUADS commands
	if (m_bQuad)		glEnd();

	//====== Close the list of OpenGL commands
//	glEndList();
}	

void CArea3DView::LimitAngles()
{
	while (m_AngleX < -360.f)		m_AngleX += 360.f;
	while (m_AngleX > 360.f)		m_AngleX -= 360.f;
	while (m_AngleY < -360.f)		m_AngleY += 360.f;
	while (m_AngleY > 360.f)		m_AngleY -= 360.f;
}

void CArea3DView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	//====== Stop rotation
	KillTimer(1);

	//====== Zero the quantums
	m_dx = 0.f;
	m_dy = 0.f;

	//====== Capture the mouse messages and direct them in our window
	SetCapture();
	//====== Remember the fact
	m_bCaptured = true;
	//====== and where it happened
	m_pt = point;
}

void CArea3DView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	//====== Remember the fact
	m_bRightButton = true;

	//====== and reproduce the left button response
	OnLButtonDown(nFlags, point);
}

void CArea3DView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_bCaptured)
	{
		// Desired rotation speed components
		m_dy = float(point.y - m_pt.y)/40.f;
		m_dx = float(point.x - m_pt.x)/40.f;

		//====== If Ctrl was pressed
		if (nFlags & MK_CONTROL)
		{
			//=== we shift (translate) the image
			m_xTrans += m_dx;
			m_yTrans -= m_dy;
		}
		else
		{
			//====== If the right mouse button is pressed
			if (m_bRightButton)
				//====== we shift along the z-axis
				m_zTrans += (m_dx + m_dy)/2.f;
			else
			{
				//====== otherwise we rotate the image
				LimitAngles();
				double a = fabs(m_AngleX);
				if (90. < a && a < 270.)
					m_dx = -m_dx;
				m_AngleX += m_dy;
				m_AngleY += m_dx;
			}
		}
		//=== In any case we should store the coordinates
		m_pt = point;
		Invalidate(FALSE);
	}
}

void CArea3DView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	//====== If we captured the mouse,
	if (m_bCaptured)
	{
		//=== query the desired quantum value
		//=== if it exeeds the sensativity threshold
		if (fabs(m_dx) > 0.5f || fabs(m_dy) > 0.5f)
			//=== Turn on the constant rotation
			SetTimer(1,33,0);
		else
			//=== Turn off the constant rotation
			KillTimer(1);

		//====== Clear the capture flag
		m_bCaptured = false;
		ReleaseCapture();
	}
}

void CArea3DView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	m_bRightButton = m_bCaptured = false;
	ReleaseCapture();
}

void CArea3DView::OnTimer(UINT nIDEvent) 
{
	LimitAngles();
	//====== Increase the angles
	m_AngleX += m_dy;
	m_AngleY += m_dx;
	Invalidate(FALSE);
}

void CArea3DView::DefaultGraphic()
{
/*
	//====== Coordinate grid dimensions
	CString FileInfo1 =  ((CSMS4DCApp *)AfxGetApp())->m_AppPath + _T("Temp\\Area3D.tmp");

	CTime t1 = CTime::GetCurrentTime();
	m_FileInfo.Format("%s\\Temp\\Area3D%d%02d%02d%02d%02d%02d.tmp" , ((CSMS4DCApp *)AfxGetApp())->m_AppPath , t1.GetYear(),t1.GetMonth(),t1.GetDay(),t1.GetHour(),t1.GetMinute(),t1.GetSecond());

	CopyFile(  FileInfo1,  m_FileInfo,  FALSE);
	DeleteFile(FileInfo1);
*/
	FILE *fid;
	fid  = fopen( m_FileInfo, "r+t" );
	char dum [20];
	fscanf( fid, "%s", dum);	int xN=atof(dum);
	fscanf( fid, "%s", dum);	int yN=atof(dum);

	m_zSize=xN;
	m_xSize=yN;
	m_cPoints.resize(m_xSize*m_zSize);

	m_cColor1.resize(m_xSize*m_zSize);

	float y,fMinY=32767, fMaxY=-32768;
	int i,j,n,c1;

	for ( i=0,n=0;  i < m_zSize;  i++)
	{
		for ( j=0;  j < m_xSize;  j++,n++)
		{

			fscanf( fid, "%s", dum);
			y=atof(dum);

			MinMax (y, fMinY, fMaxY);
			m_cPoints[n] = CPoint3D1(j,i,y);

		}
	}
	fclose( fid );

	float	right = (m_xSize-1)/2.f,
			rear  = (m_zSize-1)/2.f,
			range = (right + rear)/2.f;

	m_fRangeY = range;
//	m_fRangeX = float(m_xSize);
	m_fRangeX = float(m_xSize)/1.3f;
	m_fRangeZ = float(m_zSize);

	float zoom = fMaxY > fMinY ? range/(fMaxY-fMinY) : 1.f;

	ColorMap_Type(colormaptype);
	m_fMinY=fMinY,m_fMaxY=fMaxY;

	for (n=0;  n<m_xSize*m_zSize;  n++)
	{
		//c1=int(255*(m_cPoints[n].y-fMinY)/(fMaxY-fMinY));

		c1 = Contour( m_cPoints[n].y ,m_fMinY,m_fMaxY,m_level);

		m_cColor1[n] = RGBt[c1];

	//	m_cPoints[n].y = zoom * (m_cPoints[n].y/2.f - fMinY) - range/2.f;
		m_cPoints[n].y = (zoom * (m_cPoints[n].y - fMinY) - range/2.f)/2.f;
	}
}

void CArea3DView::SetLight()
{
	//====== Both surface sides are considered when calculating
	//====== each pixel color with the lighting formula

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,1);

	//====== Light source position depends on the object sizes scaled to (0,100)

	float fPos[] =
	{
		(m_LightParam[0]-50)*m_fRangeX/100,
		(m_LightParam[1]-50)*m_fRangeY/100,
		(m_LightParam[2]-50)*m_fRangeZ/100,
		1.f
	};
	glLightfv(GL_LIGHT0, GL_POSITION, fPos);

	//====== Ambient light intensity
	float f = m_LightParam[3]/100.f;
	float fAmbient[4] = { f, f, f, 0.f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, fAmbient);

	//====== Diffuse light intensity
	f = m_LightParam[4]/100.f;	
	float fDiffuse[4] = { f, f, f, 0.f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, fDiffuse);

	//====== Specular light intensity
	f = m_LightParam[5]/100.f;
	float fSpecular[4] = { f, f, f, 0.f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, fSpecular);

	//====== Surface material reflection properties for each light component
	f = m_LightParam[6]/100.f;
	float fAmbMat[4] = { f, f, f, 0.f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fAmbMat);

	f = m_LightParam[7]/100.f;
	float fDifMat[4] = { f, f, f, 1.f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, fDifMat);

	f = m_LightParam[8]/100.f;
	float fSpecMat[4] = { f, f, f, 0.f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, fSpecMat);

	//====== Material shininess
	float fShine = 128 * m_LightParam[9]/100.f;
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, fShine);

	//====== Material light emission property
	f = m_LightParam[10]/100.f;
	float fEmission[4] = { f, f, f, 0.f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, fEmission);
}

void CArea3DView::ColorMap_Type(CString colormaptype1)
{
	colormaptype = colormaptype1;
	m_tile.ColorMap(colormaptype);
	for (int i=0;i<256;i++)
		RGBt[i]=m_tile.RGBt[i];
}

void CArea3DView::OnTopo0() 
{
	if(colormaptype != "Topo_0")
	{
		colormaptype="Topo_0";

		BeginGLCommands();
		DefaultGraphic();
//		DrawScene();
		OnCreateGL();
		EndGLCommands();

		Invalidate(TRUE);
		UpdateWindow();
	}
}
void CArea3DView::OnUpdateTopo0(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(colormaptype=="Topo_0" ? 1 : 0);
}

void CArea3DView::OnTopo1() 
{
	if(colormaptype != "Topo_1")
	{
		colormaptype="Topo_1";
		BeginGLCommands();
		DefaultGraphic();
//		DrawScene();
		OnCreateGL();
		EndGLCommands();

		Invalidate(TRUE);
		UpdateWindow();
	}
}
void CArea3DView::OnUpdateTopo1(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(colormaptype=="Topo_1" ? 1 : 0);
}

void CArea3DView::OnJet() 
{
	if(colormaptype != "Jet")
	{
		colormaptype="Jet";
		BeginGLCommands();
		DefaultGraphic();
//		DrawScene();
		OnCreateGL();
		EndGLCommands();

		Invalidate(TRUE);
		UpdateWindow();
	}
}
void CArea3DView::OnUpdateJet(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(colormaptype=="Jet" ? 1 : 0);
}

void CArea3DView::OnGray() 
{
	if(colormaptype != "Gray")
	{
		colormaptype="Gray";
		BeginGLCommands();
		DefaultGraphic();
//		DrawScene();
		OnCreateGL();
		EndGLCommands();

		Invalidate(TRUE);
		UpdateWindow();
	}
}
void CArea3DView::OnUpdateGray(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(colormaptype=="Gray" ? 1 : 0);
}

void CArea3DView::OnPink() 
{
	if(colormaptype != "Pink")
	{
		colormaptype="Pink";
		BeginGLCommands();
		DefaultGraphic();
//		DrawScene();
		OnCreateGL();
		EndGLCommands();

		Invalidate(TRUE);
		UpdateWindow();
	}
}
void CArea3DView::OnUpdatePink(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(colormaptype=="Pink" ? 1 : 0);
}

void CArea3DView::OnCopper() 
{
	if(colormaptype != "Copper")
	{
		colormaptype="Copper";
		BeginGLCommands();
		DefaultGraphic();
//		DrawScene();
		OnCreateGL();
		EndGLCommands();

		Invalidate(TRUE);
		UpdateWindow();
	}
}
void CArea3DView::OnUpdateCopper(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(colormaptype=="Copper" ? 1 : 0);
}

void CArea3DView::OnGlobe() 
{
	if(colormaptype != "Globe")
	{
		colormaptype="Globe";
		BeginGLCommands();
		DefaultGraphic();
//		DrawScene();
		OnCreateGL();
		EndGLCommands();

		Invalidate(TRUE);
		UpdateWindow();
	}
}
void CArea3DView::OnUpdateGlobe(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(colormaptype=="Globe" ? 1 : 0);
}

void CArea3DView::OnOptionBackgroundcolor() 
{
	CColorDialog dlg(m_BkClr);
	dlg.m_cc.Flags |= CC_FULLOPEN;
	if (dlg.DoModal()==IDOK)
	{
		m_BkClr = dlg.m_cc.rgbResult;

		BeginGLCommands();
//		SetBkColor();
		OnCreateGL();
		EndGLCommands();

		Invalidate(FALSE);
	}	
}

void CArea3DView::OnOptionFilldiagram() 
{
	m_FillMode = m_FillMode==GL_FILL ? GL_LINE : GL_FILL;
	
	BeginGLCommands();
//	DrawScene();
	OnCreateGL();
	EndGLCommands();

	Invalidate(FALSE);
	UpdateWindow();
}

void CArea3DView::OnUpdateOptionFilldiagram(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_FillMode==GL_FILL);	
}

void CArea3DView::OnOptionQuadmode() 
{
	m_bQuad = ! m_bQuad;

	BeginGLCommands();
//	DrawScene();
	OnCreateGL();
	EndGLCommands();

	Invalidate(FALSE);
	UpdateWindow();
}

void CArea3DView::OnUpdateOptionQuadmode(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bQuad);	
}

void CArea3DView::GetLightParams(int *pPos)
{
	for (int i=0; i<11; i++)
		pPos[i] = m_LightParam[i];
}


void CArea3DView::SetLightParam (short lp, int nPos)
{
	m_LightParam[lp] = nPos;
	Invalidate(FALSE);
}

void CArea3DView::OnOptionProperties() 
{
	if (!m_pDlg)
	{
		m_pDlg = new CArea3DPropDLG(this);
		m_pDlg->Create(IDD_Area3DPropDLG);
	}
	else
		m_pDlg->SetActiveWindow();	
}

int CArea3DView::Contour(double y,double MinV,double MaxV,int nL) 
{
	if (nL>=255)
		return int(( y - MinV) * 255.0 / (MaxV- MinV));

	double StepV = ((MaxV-MinV)/nL);

	double a1,a2,b1,b2;
	int c=0;

	for (int i=0;i<nL;i++)
	{
		a1=MinV+i*StepV;
		a2=a1+StepV;
		if ( (y>=a1) && (y<a2))
		{
			b1=255.0*(a1-MinV)/(MaxV-MinV);
			b2=255.0*(a2-MinV)/(MaxV-MinV);
			c=int((b1+b2)/2.0);
		//	c=int(b1);
		}
	}
	return c;

}

void CArea3DView::OnOptionContour() 
{
	CContourDLG cdlg;
	cdlg.m_min = m_fMinY;
	cdlg.m_max = m_fMaxY;
	cdlg.m_step = double((int(1000.0*(m_fMaxY - m_fMinY)/m_level))/1000.0);
	cdlg.m_nL = m_level;
	if(cdlg.DoModal()==IDOK)
	{
		m_level = cdlg.m_nL;

		BeginGLCommands();
		DefaultGraphic();
//		DrawScene();
		OnCreateGL();
		EndGLCommands();

		Invalidate(FALSE);
		UpdateWindow();
	}	
}

void CArea3DView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

	CString Title_En  = "Area 3D View";
	CString Title_Num = GetDocument()->GetTitle();		Title_Num.Replace(Title_En,"");
	GetParent()->SetWindowText(_Z(Title_En) + Title_Num); 

	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ChangeMenuLang(IDR_SMS4DCTYPE26);
}

void CArea3DView::PostNcDestroy() 
{
	DeleteFile(m_FileInfo);
	
	CView::PostNcDestroy();
}


//BOOL CArea3DView::OnEraseBkgnd(CDC* pDC) { return TRUE; }

/*
int CArea3DView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	PIXELFORMATDESCRIPTOR pfd =	// Structure used to describe the format
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,			// Version
		PFD_DRAW_TO_WINDOW |	// Supports GDI
		PFD_SUPPORT_OPENGL |	// Supports OpenGL
		PFD_DOUBLEBUFFER,	// Use double buffering (more efficient drawing)
		PFD_TYPE_RGBA,		// No pallettes
		24, 			// Number of color planes
		 			// in each color buffer
		24,	0,		// for Red-component
		24,	0,		// for Green-component
		24,	0,		// for Blue-component
		24,	0,		// for Alpha-component
		0,			// Number of planes
					// of Accumulation buffer
		0,			// for Red-component
		0,			// for Green-component
		0,			// for Blue-component
		0,			// for Alpha-component
		32, 			// Depth of Z-buffer
		0,			// Depth of Stencil-buffer
		0,			// Depth of Auxiliary-buffer
		0,			// Now is ignored
		0,			// Number of planes
		0,			// Now is ignored
		0,			// Color of transparent mask
		0			// Now is ignored
	};

	//====== Get current Windows context
	m_hdc = ::GetDC(GetSafeHwnd());

	//====== Ask to find the nearest compatible pixel-format
	int iD = ChoosePixelFormat(m_hdc, &pfd);
	if ( !iD )
	{
		MessageBox("ChoosePixelFormat::Error");
		return -1;
	}

	//====== Try to set this format
	if ( !SetPixelFormat (m_hdc, iD, &pfd) )
	{
		MessageBox("SetPixelFormat::Error");
		return -1;
	}

	//====== Try to create the OpenGL rendering context
	if ( !(m_hRC = wglCreateContext (m_hdc)))
	{
		MessageBox("wglCreateContext::Error");
		return -1;
	}

	//====== Try to put it in action
	if ( !wglMakeCurrent (m_hdc, m_hRC))
	{
		MessageBox("wglMakeCurrent::Error");
		return -1;
	}

	//====== Now you can issue OpenGL commands (i.e. call gl*** functions)
	glEnable(GL_LIGHTING);		// Lighting will be used
	//====== Only one (first) source of light
	glEnable(GL_LIGHT0);
	//====== The depth of the Z-buffer will be taken into account
	glEnable(GL_DEPTH_TEST);
	//====== Material colors will be taken into account
	glEnable(GL_COLOR_MATERIAL);

	//====== Our function to set the background
	SetBkColor();

	//====== Create and store the image in a special list of OpenGL commands
	DrawScene();	
	return 0;
}
*/

/*
void CArea3DView::OnDraw(CDC* pDC)
{
	//========== Clear the background and Z-buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//========== Clean the modeling matrix (make it equal the unity matrix)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//======= At first set the light (otherwise it will rotate with the image)
	SetLight();

	//====== Change the modeling matrix coefficients in order
	glTranslatef(m_xTrans,m_yTrans,m_zTrans);	// to shift
	glRotatef (m_AngleX, 1.0f, 0.0f, 0.0f );	// and to rotate
	glRotatef (m_AngleY, 0.0f, 1.0f, 0.0f );

	//====== the following vertices coordinates (they are being multiplied by matrix)
	glCallList(1);

	//====== Switch back and front buffers (to show what happened)
	SwapBuffers(m_hdc);
}
*/
/*
void CArea3DView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	double dAspect = cx<=cy ? double(cy)/cx : double(cx)/cy;
	
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluPerspective (m_AngleView, dAspect, 0.1, 10000.);
	glViewport(0, 0, cx, cy);
	
}
*/

/////////////////////
void CArea3DView::OnCreateGL()
{
	glEnable(GL_DEPTH_TEST);

	StartStockDListDef();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	SetBkColor();
	DrawScene();	

	EndStockListDef();
}


void CArea3DView::OnDrawGL()
{
	glPushMatrix();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	SetLight();

	glTranslatef(m_xTrans,m_yTrans,m_zTrans);	// to shift
	glRotatef (m_AngleX, 1.0f, 0.0f, 0.0f );	// to rotate
	glRotatef (m_AngleY, 0.0f, 1.0f, 0.0f );

	DrawStockDispLists();

	glPopMatrix();
}

void CArea3DView::MinMax (float d, float& Min, float& Max)
{
	if      (d > Max)		Max = d;
	else if (d < Min)		Min = d;
}