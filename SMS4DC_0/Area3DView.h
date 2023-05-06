#if !defined(AFX_AREA3DVIEW_H__D93FA4EF_B6F1_47CE_98AF_C6EB3849A1E8__INCLUDED_)
#define AFX_AREA3DVIEW_H__D93FA4EF_B6F1_47CE_98AF_C6EB3849A1E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Area3DView.h : header file
//
#include "Tile.h"
//#include "Area3DDoc.h"

#include "BaseGLView.h"

/////////////////////////////////////////////////////////////////////////////
// CArea3DView view
class CArea3DPropDLG;

class CPoint3D1
{
public:
	float x, y, z;
	CPoint3D1 () { x=y=z=0; }
	CPoint3D1 (float c1, float c2, float c3)
	{
		x = c1;		z = c2;		y = c3;
	}
	CPoint3D1& operator=(const CPoint3D1& pt)
	{
		x = pt.x;	z = pt.z;	y = pt.y;
		return *this;
	}
	CPoint3D1 (const CPoint3D1& pt)
	{
		*this = pt;
	}
};

//class CArea3DView : public CView
class CArea3DView : public CBaseGLView
{
protected:
	CArea3DView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CArea3DView)

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
	vector < CPoint3D1 > m_cPoints;	// Graphics dimension (along X-axis)
	int	m_LightParam[11];	// Graphics dimension (along X-axis)
	CArea3DPropDLG *m_pDlg;		// Graphics dimension (along X-axis)

	//======== Public methods
//	CArea3DDoc* GetDocument() { return DYNAMIC_DOWNCAST(CArea3DDoc,m_pDocument); }
//	virtual ~COGView();

	//======== New methods
	void DrawScene();	// Prepare and store the image
	void DefaultGraphic();	// Create and save the default plot
	void SetLightParam (short lp, int nPos);	// Set lighting parameters
	void GetLightParams(int *pPos);			// Get lighting parameters
	void SetLight();				// Set the lighting
	void SetBkColor();				// Set background color
	void LimitAngles();				// Limit rotation angles

	vector < COLORREF > m_cColor1;
	COLORREF RGBt[256];
	void ColorMap_Type(CString colormaptype1);

	CString colormaptype;
	CTile m_tile;
	int Contour(double y,double MinV,double MaxV,int nL) ;
	int m_level;
	double m_fMinY,m_fMaxY;

// Attributes
public:
	void OnCreateGL();
	void OnDrawGL();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArea3DView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CArea3DView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CArea3DView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnTopo0();
	afx_msg void OnUpdateTopo0(CCmdUI* pCmdUI);
	afx_msg void OnTopo1();
	afx_msg void OnUpdateTopo1(CCmdUI* pCmdUI);
	afx_msg void OnJet();
	afx_msg void OnUpdateJet(CCmdUI* pCmdUI);
	afx_msg void OnGray();
	afx_msg void OnUpdateGray(CCmdUI* pCmdUI);
	afx_msg void OnPink();
	afx_msg void OnUpdatePink(CCmdUI* pCmdUI);
	afx_msg void OnCopper();
	afx_msg void OnUpdateCopper(CCmdUI* pCmdUI);
	afx_msg void OnGlobe();
	afx_msg void OnUpdateGlobe(CCmdUI* pCmdUI);
	afx_msg void OnOptionBackgroundcolor();
	afx_msg void OnOptionFilldiagram();
	afx_msg void OnUpdateOptionFilldiagram(CCmdUI* pCmdUI);
	afx_msg void OnOptionQuadmode();
	afx_msg void OnUpdateOptionQuadmode(CCmdUI* pCmdUI);
	afx_msg void OnOptionProperties();
	afx_msg void OnOptionContour();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};
		CString m_FileInfo;
		void MinMax (float d, float& Min, float& Max);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AREA3DVIEW_H__D93FA4EF_B6F1_47CE_98AF_C6EB3849A1E8__INCLUDED_)
