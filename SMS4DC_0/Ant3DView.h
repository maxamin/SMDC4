#if !defined(AFX_ANT3DVIEW_H__0779BA51_E2C4_4E7F_9F38_21E510D578C1__INCLUDED_)
#define AFX_ANT3DVIEW_H__0779BA51_E2C4_4E7F_9F38_21E510D578C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Ant3DView.h : header file
//
#include "Ant3DDoc.h"
#include "BaseGLView.h"

/////////////////////////////////////////////////////////////////////////////
// CAnt3DView view

class CAnt3DPropDLG;

class CPoint3D
{
public:
	float x, y, z;
	CPoint3D () { x=y=z=0; }
	CPoint3D (float c1, float c2, float c3)
	{
		x = c1;		z = c2;		y = c3;
	}
	CPoint3D& operator=(const CPoint3D& pt)
	{
		x = pt.x;	z = pt.z;	y = pt.y;
		return *this;
	}
	CPoint3D (const CPoint3D& pt)
	{
		*this = pt;
	}
};

//class CAnt3DView : public CView
class CAnt3DView : public CBaseGLView
{
protected:
	CAnt3DView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CAnt3DView)

public:
	//======== New data
	long	m_BkClr;	// Background color
//	HGLRC	m_hRC;		// Rendering context OpenGL
//	HDC	m_hdc;		// Windows device context
	GLfloat	m_AngleX;	// Rotation angle (around X-axis)
	GLfloat m_AngleY;	// Rotation angle (around Y-axis)
	GLfloat	m_AngleView;	// Perspective angle
	GLfloat	m_fRangeX;	// Graphics dimension (along X-axis)
	GLfloat m_fRangeY;	// Graphics dimension (along Y-axis)
	GLfloat m_fRangeZ;	// Graphics dimension (along Z-axis)
	GLfloat	m_dx;		// Displacement quantum (along X-axis)
	GLfloat m_dy;		// Displacement quantum (along Y-axis)
	GLfloat	m_xTrans;	// Displacement (along X-axis)
	GLfloat m_yTrans;	// Displacement (along Y-axis)
	GLfloat m_zTrans;	// Displacement (along Z-axis)
	GLenum	m_FillMode;	// Polygon filling mode
	bool	m_bCaptured;	// Mouse capture flag
	bool	m_bRightButton;	// Right mouse button flag
	bool	m_bQuad;	// Flag of using GL_QUAD (instead of GL_QUAD_STRIP)
	CPoint	m_pt;		// Current mouse position
	UINT	m_xSize;	// Current client window sixe (along X-axis)
	UINT	m_zSize;	// Current client window sixe (along -axis)
	vector < CPoint3D > m_cPoints;	// Graphics dimension (along X-axis)
	int	m_LightParam[11];	// Graphics dimension (along X-axis)
	CAnt3DPropDLG *m_pDlg;		// Graphics dimension (along X-axis)

	//======== Public methods
	CAnt3DDoc* GetDocument() { return DYNAMIC_DOWNCAST(CAnt3DDoc,m_pDocument); }
//	virtual ~COGView();

	//======== New methods
	void DrawScene();	// Prepare and store the image
	void DefaultGraphic();	// Create and save the default plot
	void SetLightParam (short lp, int nPos);	// Set lighting parameters
	void GetLightParams(int *pPos);			// Get lighting parameters
	void SetLight();				// Set the lighting
	void SetBkColor();				// Set background color
	void LimitAngles();				// Limit rotation angles


	void ReadAntData() ;
	CString  m_antfile;
	int  m_Angle[360];
	double m_PatternH[360],m_PatternV[360];
	COLORREF m_cColor1[122][122];
//	COLORREF m_cColor1[362][362];

	double Interp2(int *D0,double *E0,double d,int num) ;

// Attributes
public:
	void OnCreateGL();
	void OnDrawGL();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnt3DView)
	public:
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CAnt3DView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CAnt3DView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnOptionFilldiagram();
	afx_msg void OnUpdateOptionFilldiagram(CCmdUI* pCmdUI);
	afx_msg void OnOptionQuadmode();
	afx_msg void OnUpdateOptionQuadmode(CCmdUI* pCmdUI);
	afx_msg void OnOptionProperties();
	afx_msg void OnOptionBackgroundcolor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
		void MinMax (double d, double& Min, double& Max);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANT3DVIEW_H__0779BA51_E2C4_4E7F_9F38_21E510D578C1__INCLUDED_)
