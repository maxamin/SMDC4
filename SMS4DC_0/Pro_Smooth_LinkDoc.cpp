// Pro_Smooth_LinkDoc.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Pro_Smooth_LinkDoc.h"

#include <math.h>
#include "UTM.h"
#include "P452_Functions.h"

#include "P527_526_Functions.h"

extern "C" {
#include "C:\\Br_soft\\IDWM\\include\\idwm32.h"
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPro_Smooth_LinkDoc

IMPLEMENT_DYNCREATE(CPro_Smooth_LinkDoc, CDocument)

CPro_Smooth_LinkDoc::CPro_Smooth_LinkDoc()
{
	m_ReadyDoc=0;
	m_DrawFresnel = false;

	long UNR = 72 ;
	WDBUNIT(&UNR) ;
}

BOOL CPro_Smooth_LinkDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CPro_Smooth_LinkDoc::~CPro_Smooth_LinkDoc()
{
	delete [] m_di;
	delete [] m_hi;
	delete [] m_hikm;
}


BEGIN_MESSAGE_MAP(CPro_Smooth_LinkDoc, CDocument)
	//{{AFX_MSG_MAP(CPro_Smooth_LinkDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPro_Smooth_LinkDoc diagnostics

#ifdef _DEBUG
void CPro_Smooth_LinkDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPro_Smooth_LinkDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPro_Smooth_LinkDoc serialization

void CPro_Smooth_LinkDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPro_Smooth_LinkDoc commands


void CPro_Smooth_LinkDoc::GetData() 
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));

	CP452_Functions CP452;
	CP527_526_Functions CP527;

	int o_path_type;
	Linkk = atof_kfactor(m_kfactor) ;

	double o_loss_d = CP452.pn452_Lbdiff (m_di,m_hikm,Np,
						LinkfMHz_ST/1000.0, Linkk,LinkHagl_ST/1000.0,LinkRxH/1000.0,&o_path_type);
	double pi=4.0*atan(1.0);
	m_Distance = Dmax-Dmin;
	m_FsLoss = 92.45 + (20.0 * log10 (m_Distance * LinkfMHz_ST/1000.0));

	int pol = (m_Pol=="H") ? 0 : 1;

	m_Loss1L = _Z("Diffraction Loss(dB) : ");
	double Lsmooth = CP527.Lsmoot(m_Type,LinkfMHz_ST,Linkk,pol,m_Distance,LinkHagl_ST,LinkRxH);
	m_Loss1.Format("%0.3f",-Lsmooth);

	m_Loss2L = _Z("Total Loss(dB) : ");
	m_Loss2.Format("%0.3f",-Lsmooth + m_FsLoss);

	int PN452_LOS_CLEAR   = 0,
		PN452_LOS_SUB_P   = 1,
		PN452_TRANS_HOZ   = 2;

	if (o_path_type==PN452_LOS_CLEAR)
		m_tit = _Z("Line of Sight with > 0.6 Fresnel Clearance");
	else if (o_path_type==PN452_LOS_SUB_P)
		m_tit = _Z("Line of Sight with Sub-Path Obstruction");
	else if (o_path_type==PN452_TRANS_HOZ)
		m_tit = _Z("Transhorizon Path");
}


double CPro_Smooth_LinkDoc::atof_kfactor(CString k1) 
{
	double k2 = 1.0;
	k1.Remove(' ');
	int n = k1.Find('/');
	if (n != -1)
	{
		int m = k1.GetLength();
		CString ss1 = k1.Left(n);
		CString ss2 = k1.Right(m-n-1);
		k2 = atof(ss1)/atof(ss2);
	}
	else
		k2 = atof(k1);

	return k2;
}
