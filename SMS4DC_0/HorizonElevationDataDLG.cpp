// HorizonElevationDataDLG.cpp : implementation file
//

#include "stdafx.h"
#include "sms4dc.h"
#include "HorizonElevationDataDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHorizonElevationDataDLG dialog


CHorizonElevationDataDLG::CHorizonElevationDataDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CHorizonElevationDataDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHorizonElevationDataDLG)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CHorizonElevationDataDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHorizonElevationDataDLG)
	DDX_Control(pDX, IDOK, m_BUTTON_Save);
	DDX_Control(pDX, IDC_MSFLEXGRID1, m_Grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHorizonElevationDataDLG, CDialog)
	//{{AFX_MSG_MAP(CHorizonElevationDataDLG)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHorizonElevationDataDLG message handlers

BOOL CHorizonElevationDataDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_BUTTON_Save.LoadBitmaps(IDB_Save1,IDB_Save2,IDB_Save1,IDB_Save3);

	int nCOLS = 3;
	m_Grid.SetCols(nCOLS);
	
	m_Grid.SetRow(0);
	m_Grid.SetRowHeight(0,800);
	m_Grid.SetColWidth(0,800);

	m_Grid.SetCol(0);m_Grid.SetCellAlignment(4);		m_Grid.SetText(_Z("Azimuth (Deg.)"));
	m_Grid.SetCol(1);m_Grid.SetCellAlignment(4);		m_Grid.SetText(_Z("Elevation Angle (Deg.)"));
	m_Grid.SetCol(2);m_Grid.SetCellAlignment(4);		m_Grid.SetText(_Z("Distance (km)"));

	CString ResultSTR;
	m_Grid.SetRows(m_Rows);
	for(int j=0;j<m_Rows-1;j++)
	{
		m_Grid.SetRow(j+1);

		m_Grid.SetCol(0);	ResultSTR.Format(_T("%d"),    m_Azimuth[j]);	m_Grid.SetText(ResultSTR);
		m_Grid.SetCol(1);	ResultSTR.Format(_T("%0.3f"), m_Elevation[j]);	m_Grid.SetText(ResultSTR);
		m_Grid.SetCol(2);	ResultSTR.Format(_T("%0.3f"), m_Distance[j]);	m_Grid.SetText(ResultSTR);
	}
	((CSMS4DCApp *)AfxGetApp())->TranslateDialog(this);
	return TRUE;  
}
