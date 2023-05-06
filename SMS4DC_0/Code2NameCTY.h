// Code2NameCTY.h: interface for the CCode2NameCTY class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CODE2NAMECTY_H__98599FCB_6801_4E28_865B_ABD7BDA088C9__INCLUDED_)
#define AFX_CODE2NAMECTY_H__98599FCB_6801_4E28_865B_ABD7BDA088C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCode2NameCTY  
{
public:
	CCode2NameCTY();
	virtual ~CCode2NameCTY();

	CString countryCODEidwm[300];
	CString countryNAMEidwm[300];
	CString Code2Name_idwm(CString co);
	int m_num;
};

#endif // !defined(AFX_CODE2NAMECTY_H__98599FCB_6801_4E28_865B_ABD7BDA088C9__INCLUDED_)
