// Pro_P526_LinkDoc.cpp : implementation file
//

#include "stdafx.h"
#include "SMS4DC.h"
#include "Pro_P526_LinkDoc.h"
#include <math.h>
#include "UTM.h"
#include "P452_Functions.h"


extern "C" {
#include "C:\\Br_soft\\IDWM\\include\\idwm32.h"
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPro_P526_LinkDoc

IMPLEMENT_DYNCREATE(CPro_P526_LinkDoc, CDocument)

CPro_P526_LinkDoc::CPro_P526_LinkDoc()
{
	m_ReadyDoc=0;
	m_DrawFresnel = false;

	long UNR = 72 ;
	WDBUNIT(&UNR) ;
}

BOOL CPro_P526_LinkDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CPro_P526_LinkDoc::~CPro_P526_LinkDoc()
{
	delete [] m_di;
	delete [] m_hi;
	delete [] m_hikm;
}


BEGIN_MESSAGE_MAP(CPro_P526_LinkDoc, CDocument)
	//{{AFX_MSG_MAP(CPro_P526_LinkDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPro_P526_LinkDoc diagnostics

#ifdef _DEBUG
void CPro_P526_LinkDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPro_P526_LinkDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPro_P526_LinkDoc serialization

void CPro_P526_LinkDoc::Serialize(CArchive& ar)
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
// CPro_P526_LinkDoc commands


void CPro_P526_LinkDoc::GetData() 
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));

	CP452_Functions CP452;

	int o_path_type;
	double o_loss_d;

	double k50 = 4.0/3.0;
	o_loss_d = CP452.pn452_Lbdiff (m_di,m_hikm,Np,
						LinkfMHz_ST/1000.0, k50,LinkHagl_ST/1000.0,LinkRxH/1000.0,&o_path_type);


	double pi=4.0*atan(1.0);
	m_Distance = Dmax-Dmin;
//	m_FsLoss = 20.0*log10(4.0*pi*m_Distance*LinkfMHz_ST/0.3);
	m_FsLoss = 92.45 + (20.0 * log10 (m_Distance * LinkfMHz_ST/1000.0));

	m_Loss1L = _Z("Diffraction Loss(dB) : ");
	m_Loss1.Format("%0.3f",o_loss_d);



	m_Loss2L = _Z("Total Loss(dB) : ");
	m_Loss2.Format("%0.3f",o_loss_d + m_FsLoss);

	Linkk = atof_kfactor(m_kfactor) ;

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


double CPro_P526_LinkDoc::atof_kfactor(CString k1) 
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
