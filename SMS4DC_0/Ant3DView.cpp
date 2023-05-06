// Ant3DView.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Ant3DView.h"
#include <math.h>
#include "Ant3DPropDLG.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAnt3DView

IMPLEMENT_DYNCREATE(CAnt3DView, CBaseGLView)

CAnt3DView::CAnt3DView()
{
	m_antfile=((CSMS4DCApp *)AfxGetApp())->m_antfile;

	m_pDlg=NULL;
	//====== Rendering context does not exist yet
//	m_hRC = 0;

	//====== Initial image turn
	m_AngleX = 90.f;
	m_AngleY = 180.f;

	//====== Projection matrix view angle
	m_AngleView = 45.f;

	//====== Initial bkcolor
	m_BkClr = RGB(0, 0, 96);

	// Initial mode to fill the inner polygons (quads) points
	m_FillMode = GL_FILL;

	//====== Initial plot creation
	DefaultGraphic();

	//====== Initial image shift
	//====== One and a half object size (backward)
	m_zTrans = -1.5f*m_fRangeX;
//	m_zTrans = -0.5f*m_fRangeX;
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
//	m_LightParam[8] = 40;	// Specular material
	m_LightParam[8] = 80;	// Specular material
	m_LightParam[9] = 70;	// Shininess material
	m_LightParam[10] = 0;	// Emission material
}

CAnt3DView::~CAnt3DView()
{
}


BEGIN_MESSAGE_MAP(CAnt3DView, CBaseGLView)
	//{{AFX_MSG_MAP(CAnt3DView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_COMMAND(ID_OPTION_FILLDIAGRAM, OnOptionFilldiagram)
	ON_UPDATE_COMMAND_UI(ID_OPTION_FILLDIAGRAM, OnUpdateOptionFilldiagram)
	ON_COMMAND(ID_OPTION_QUADMODE, OnOptionQuadmode)
	ON_UPDATE_COMMAND_UI(ID_OPTION_QUADMODE, OnUpdateOptionQuadmode)
	ON_COMMAND(ID_OPTION_PROPERTIES, OnOptionProperties)
	ON_COMMAND(ID_OPTION_BACKGROUNDCOLOR, OnOptionBackgroundcolor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnt3DView drawing

/////////////////////////////////////////////////////////////////////////////
// CAnt3DView diagnostics

#ifdef _DEBUG
void CAnt3DView::AssertValid() const
{
	CView::AssertValid();
}

void CAnt3DView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAnt3DView message handlers


void CAnt3DView::SetBkColor()
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

void CAnt3DView::DefaultGraphic()
{
	//====== Coordinate grid dimensions
//	int n_step = 1;
	int n_step = 3;
	m_xSize = m_zSize = 1+ 360/n_step;
	m_cPoints.resize((m_xSize+1)*(m_zSize+1));

	ReadAntData();
	double R,maxR = -32768, minR = 32767;
	double Alim = -50;
	int i,j,i1,j1,n,cR,cG,cB;

	double	fMinY = 32767,	fMaxY = -32768;
	double c1,f,t,r = 68.0;
	double x,y, z, pi = 4.0*atan(1.0);

	for ( j=0;j<360;j++)
		for ( i=0;i<360;i++)
		{
			R = (  pow(10.0,-m_PatternH[i]/10.0)*pow(10.0,-m_PatternV[j]/10.0)  );
			maxR = max(maxR,R);
		}

	for ( j = 0; j < 360; j++)
		for ( i = 0; i < 360 ; i++) 
		{
			R=(  pow(10.0,-m_PatternH[i]/10.0)*pow(10.0,-m_PatternV[j]/10.0)  )/maxR;
			if (R<=pow(10.0,Alim/10.0))		R = pow(10.0,Alim/10.0);
			R = 10.0*log10(R);
			minR = min(minR,R);
		}

	for ( i=0,n=0;  i <= n_step*m_xSize;  i=i+n_step)
	{
		i1 = ( (i>=360) ? i-360 : i);
		f = i*pi/180.0;
		for ( j=0;  j <= n_step*m_zSize;  j=j+n_step,n++)
		{
			j1 = ( (j>=360) ? j-360 : j);
			t = j*pi/180.0;

////////////////////////////////////////////////////////////////////////////////////
/*
			if(f>=0 && f<pi)		h = f;
			else					h = -f;
			if(t>=3.0*pi/2.0 && t<=2.0*pi)		v = pi/2.0+2*pi-t;
			else								v = pi/2.0-t;

			tda = acos(cos(h)*cos(v));
			fda = tda;
			if(h<0)		fda = -(fda);
			if(v<0)		tda = -(tda);
 
			if(tda<0)		tda = tda+2*pi;
			if(fda<0)		fda = fda+2.0*pi;

			A1 = Interp2(m_Angle,m_PatternH,(180.0/pi)*fda,360);
			A2 = Interp2(m_Angle,m_PatternV,(180.0/pi)*tda,360);

			if(A1==A2)	A = A1;
			else		A = (A1*abs(h)+A2*abs(v))/(fabs(v)+fabs(h)+0.0000001);

			R = pow(10.0,-A/10.0)/maxR;
*/
////////////////////////////////////////////////////////////////////////////////////
/*
			A1 = pow(10.0,-m_PatternH[i1]/10.0);
			A2 = pow(10.0,-m_PatternV[j1]/10.0);
			if(A1==A2)	R = A1;
			else
			{
				double a0 = pow(acos(cos(f))/(acos(cos(f))+acos(cos(pi/2.0-t))),2);
				double b0 = 1.0 - a0;
				R = pow(A1,a0)*pow(A2,b0);
			}
			R = R/maxR;
*/			
			R = (  pow(10.0,-m_PatternH[i1]/10.0)*pow(10.0,-m_PatternV[j1]/10.0)  )/maxR;
////////////////////////////////////////////////////////////////////////////////////

			if (R<=pow(10.0,Alim/10.0))		R = pow(10.0,Alim/10.0);

			R = 10.0*log10(R);
			R = R - min(Alim,minR);
			R = r*R/(-Alim);

			x=R*sin(t)*cos(f);
			y=R*sin(t)*sin(f);
			z=R*cos(t);

			c1=(255*R/r);
			cR = int( (255*(c1-95)/(159-95))*(c1>95 && c1<159) + (255)*(c1>=159 && c1<=223) + ( 255+(127.5-255)*(c1-223)/(255-223) )*(c1>223) );
			cG = int( (255*(c1-31)/(95-31))*(c1>31 && c1<95) + (255)*(c1>=95 && c1<=159) + ( 255+(0-255)*(c1-159)/(223-159) )*(c1>159 && c1<223) );
			cB = int( (131.48+(255-131.48)*(c1-0)/(31-0) )*(c1>=0 && c1<31) + (255)*(c1>=31 && c1<=95) + ( 255+(0-255)*(c1-95)/(159-95) )*(c1>95 && c1<159) );
			m_cColor1[i/3][j/3] = RGB(cR,cG,cB);
//			m_cColor1[i][j] = RGB(cR,cG,cB);

			MinMax (y, fMinY, fMaxY);
			m_cPoints[n] = CPoint3D(x,z,y);
		}
	}

	float	right = (m_xSize-1)/2.f,
			rear  = (m_zSize-1)/2.f,
			range = (right + rear)/2.f;
	m_fRangeY = range;
	m_fRangeX = float(m_xSize);
	m_fRangeZ = float(m_zSize);
	m_zTrans = -1.5f * m_fRangeZ;

}


void CAnt3DView::DrawScene()
{
	//====== Create the new list of OpenGL commands
//	glNewList(1, GL_COMPILE);

	//====== Set the polygon filling mode
	glPolygonMode(GL_FRONT_AND_BACK, m_FillMode);

	//====== Image grid sizes
	UINT	nx = m_xSize-0,			nz = m_zSize-0;

	//====== Turn on the primitive connection mode (not connected)
	if (m_bQuad)		glBegin (GL_QUADS);

	for (UINT x=0, i=0;  x < nx;  x++, i++)
//	for (UINT z=0, i=0;  z < nz;  z++, i++)
	{
		//====== Turn on the primitive connection mode (connected)
		//====== The strip of connected quads begins here
		if (!m_bQuad)	glBegin(GL_QUAD_STRIP);

		for (UINT z=0;  z < nz;  z++, i++)
	//	for (UINT x=0;  x < nx;  x++, i++)
		{
			// i, j, k, n — 4 indices of a quad
			// Counter Clockwise direction

			int	j = i + m_xSize,	// Other vertices indices
				k = j+1,
				n = i+1;

			//=== Get coordinates of 4 vertices
			float
				xi = m_cPoints[i].x,
				yi = m_cPoints[i].y,
				zi = m_cPoints[i].z,

				xj = m_cPoints[j].x,
				yj = m_cPoints[j].y,
				zj = m_cPoints[j].z,

				xk = m_cPoints[k].x,
				yk = m_cPoints[k].y,
				zk = m_cPoints[k].z,

				xn = m_cPoints[n].x,
				yn = m_cPoints[n].y,
				zn = m_cPoints[n].z,

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
				glColor3f (GetRValue(m_cColor1[x][z])/255.f, GetGValue(m_cColor1[x][z])/255.f,GetBValue(m_cColor1[x][z])/255.f);
				//====== Vertices are given in counter clockwise direction order
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
			//	glColor3f (0.9f, 0.9f, 1.0f);
			//	glColor3f (1.0f, 0.9f, 0.9f);
			//	glVertex3f (xi, yi, zi);
			//	glColor3f (0.5f, 0.8f, 1.0f);
			//	glColor3f (1.0f, 0.7f, 0.7f);
			//	glVertex3f (xj, yj, zj);

				glColor3f (GetRValue(m_cColor1[x][z])/255.f, GetGValue(m_cColor1[x][z])/255.f,GetBValue(m_cColor1[x][z])/255.f);
				glVertex3f (xi, yi, zi);
				glVertex3f (xj, yj, zj);
			}
		}
		//====== Close block of GL_QUAD_STRIP commands
		if (!m_bQuad)	glEnd();
	}
		//====== Close block of GL_QUADS commands
	if (m_bQuad)	glEnd();

	//====== Close the list of OpenGL commands
//	glEndList();
}	


void CAnt3DView::ReadAntData() 
{
	FILE *fid;
	fid=fopen(m_antfile,"rt");

	char Name [20],
		 Gain_dBi [20],
		 BeamWidth_H [20],
		 BeamWidth_V [20],
		 Frq_Lo [20],
		 Frq_Hi [20],
		 Frq_unit [20],
		 Polarization [20],
		 dum[20];

	char Ang[20],PatH[20],PatV[20];

	fscanf( fid, "%s %s", dum,Name);
	fscanf( fid, "%s %s", dum,Gain_dBi);
	fscanf( fid, "%s %s", dum,BeamWidth_H);
	fscanf( fid, "%s %s", dum,BeamWidth_V);
	fscanf( fid, "%s %s", dum,Frq_Lo);
	fscanf( fid, "%s %s", dum,Frq_Hi);
	fscanf( fid, "%s %s", dum,Frq_unit);
	fscanf( fid, "%s %s", dum,Polarization);
	fscanf( fid, "%s", dum);
/*
	m_Name = Name;
	m_Gain_dBi = atof(Gain_dBi);
	m_BeamWidth_H = atof(BeamWidth_H);
	m_BeamWidth_V = atof(BeamWidth_V);
	m_Frq_Lo = atof(Frq_Lo);
	m_Frq_Hi = atof(Frq_Hi);
	m_Frq_unit = Frq_unit;
	m_Polarization = Polarization;
*/
	for (int i=0;i<360;i++)
	{
		fscanf( fid, "%s %s %s", Ang,PatH,PatV);
		m_Angle[i] = atoi(Ang);
		m_PatternH[i] = atof(PatH);
		m_PatternV[i] = atof(PatV);
	}
	fclose(fid);
}



void CAnt3DView::SetLight()
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

void CAnt3DView::LimitAngles()
{
	while (m_AngleX < -360.f)		m_AngleX += 360.f;
	while (m_AngleX > 360.f)		m_AngleX -= 360.f;
	while (m_AngleY < -360.f)		m_AngleY += 360.f;
	while (m_AngleY > 360.f)		m_AngleY -= 360.f;
}

void CAnt3DView::GetLightParams(int *pPos)
{
	for (int i=0; i<11; i++)
		pPos[i] = m_LightParam[i];
}


void CAnt3DView::SetLightParam (short lp, int nPos)
{
	m_LightParam[lp] = nPos;
	Invalidate(FALSE);
}

void CAnt3DView::OnLButtonDown(UINT nFlags, CPoint point) 
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

void CAnt3DView::OnLButtonUp(UINT nFlags, CPoint point) 
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

void CAnt3DView::OnMouseMove(UINT nFlags, CPoint point) 
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

void CAnt3DView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	//====== Remember the fact
	m_bRightButton = true;

	//====== and reproduce the left button response
	OnLButtonDown(nFlags, point);
}

void CAnt3DView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	m_bRightButton = m_bCaptured = false;
	ReleaseCapture();
}

void CAnt3DView::OnTimer(UINT nIDEvent) 
{
	LimitAngles();
	//====== Increase the angles
	m_AngleX += m_dy;
	m_AngleY += m_dx;
	Invalidate(FALSE);	
}

void CAnt3DView::OnOptionFilldiagram() 
{
	m_FillMode = m_FillMode==GL_FILL ? GL_LINE : GL_FILL;

	BeginGLCommands();
//	DrawScene();
	OnCreateGL();
	EndGLCommands();
	
	Invalidate(FALSE);
	UpdateWindow();		
}

void CAnt3DView::OnUpdateOptionFilldiagram(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_FillMode==GL_FILL);	
	
}

void CAnt3DView::OnOptionQuadmode() 
{
	m_bQuad = ! m_bQuad;

	BeginGLCommands();
//	DrawScene();
	OnCreateGL();
	EndGLCommands();
	
	Invalidate(FALSE);
	UpdateWindow();
}

void CAnt3DView::OnUpdateOptionQuadmode(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bQuad);	
}

void CAnt3DView::OnOptionProperties() 
{
	if (!m_pDlg)
	{
		m_pDlg = new CAnt3DPropDLG(this);
		m_pDlg->Create(IDD_Ant3DPropDLG);
	}
	else
		m_pDlg->SetActiveWindow();
	
}

void CAnt3DView::OnOptionBackgroundcolor() 
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

double CAnt3DView::Interp2(int *D0,double *E0,double d,int num) 
{
	double d1,d2,E1,E2,Eb;
	if (d<D0[0])
	{
		d1=D0[0];d2=D0[1];
		E1=E0[0];E2=E0[1];
	}
	else if (d>D0[num-1])
	{
		d1=D0[num-2];d2=D0[num-1];
		E1=E0[num-2];E2=E0[num-1];
	}
	else
	{
		/////////////////////////////////////////////
		int n1=0;
		while(d>=D0[n1])
		{
			n1++;
			if (n1==num)
				break;
		}
		if (n1==0)
			n1=1;
		d1=D0[n1-1];E1=E0[n1-1];
		///////////////////////////////////////////////
		int n2=num-1;
		while(d<=D0[n2])
			n2--;
		d2=D0[n2+1];E2=E0[n2+1];
		////////////////////////////////////////////////
	}
	Eb=((d1==d2) ? E1 : E1+(E2-E1)*(d-d1)/(d2-d1));

	return Eb;

}

void CAnt3DView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

	CString Title_En  = "Antenna 3D View";
	CString Title_Num = GetDocument()->GetTitle();		Title_Num.Replace(Title_En,"");
	GetParent()->SetWindowText(_Z(Title_En) + Title_Num); 

	((CMainFrame*)(AfxGetApp()->m_pMainWnd))->ChangeMenuLang(IDR_SMS4DCTYPE25);
}

/*
void CAnt3DView::OnDraw(CDC* pDC)
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
//BOOL CAnt3DView::OnEraseBkgnd(CDC* pDC) {	return TRUE;}

/*
int CAnt3DView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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
void CAnt3DView::OnSize(UINT nType, int cx, int cy) 
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
void CAnt3DView::OnCreateGL()
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

void CAnt3DView::OnDrawGL()
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

void CAnt3DView::MinMax (double d, double& Min, double& Max)
{
	if (d > Max)		Max = d;
	else if (d < Min)		Min = d;
}
