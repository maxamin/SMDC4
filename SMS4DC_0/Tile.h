// Tile.h: interface for the CTile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TILE_H__171D1435_E740_4B93_950F_764F8DF9D713__INCLUDED_)
#define AFX_TILE_H__171D1435_E740_4B93_950F_764F8DF9D713__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTile  
{
public:
	CTile();
	virtual ~CTile();
	void ColorMap(CString type);
	void getTileInfo(LPCTSTR lpszFileName,int *TileX,int *TileY,int *Npx,int *Npy,
		int *Nod,char *FilesPath,char *FilesPrefix);
	void CTile::getTileBuf(int TileX,int TileY,
					   int Npx,int Npy,int Nod,
					   char *FilesPath,char *FilesPrefix,
					   _int16 (* buf)[1200],
					   _int16 *bufMin,_int16 *bufMax);
	COLORREF RGBt[256];
	double m_Lower_left_x;
	double m_Lower_left_y;
	double m_Resolution_x;
	double m_Resolution_y;
	double m_NoData;
	char m_MachineFormat[1];
	int m_Nxmax, m_Nymax;

	CString _Z(CString s){return (((CSMS4DCApp *)AfxGetApp())->GetTranslatedString(_T(s)));};

};	

#endif // !defined(AFX_TILE_H__171D1435_E740_4B93_950F_764F8DF9D713__INCLUDED_)
