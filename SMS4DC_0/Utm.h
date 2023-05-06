// Utm.h: interface for the CUtm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UTM_H__A66AD429_0D95_4522_A34E_CD034C91D4CB__INCLUDED_)
#define AFX_UTM_H__A66AD429_0D95_4522_A34E_CD034C91D4CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>

class CUtm  
{
public:
	CUtm();
	virtual ~CUtm();

	double x , y , phi , lambda;
	double pi , a , e , phi0 , l0 , phi1 , phi2;
	double FPhi(double pOld,double t);
	int sign(double t);
	void UTM2philambda();
	void philambda2UTM();

};

#endif // !defined(AFX_UTM_H__A66AD429_0D95_4522_A34E_CD034C91D4CB__INCLUDED_)
