// mArray.h: interface for the CmArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MARRAY_H__D1FB66FD_91D6_4A18_A455_A4D345A4C776__INCLUDED_)
#define AFX_MARRAY_H__D1FB66FD_91D6_4A18_A455_A4D345A4C776__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CmArray  
{
public:
	CmArray();
	virtual ~CmArray();


	double *elem_;
	long r_;
	long c_;

	CmArray(double *, long, long);
	CmArray(long, long);

	double *colon(double,double,double);
	void    del();
	CmArray Trans();

	// operators
    CmArray &operator=(CmArray &);
	CmArray  operator ==(CmArray &);
	CmArray  operator ==(const double &);
	CmArray  operator >=(CmArray &);
	CmArray  operator >=(const double &);
	CmArray  operator > (CmArray &);
	CmArray  operator > (const double &);
	CmArray  operator <=(CmArray &);
	CmArray  operator <=(const double &);
	CmArray  operator < (const double &);
	CmArray  operator < (CmArray &);
	CmArray  operator &&(CmArray &);
	CmArray  operator ||(CmArray &);
	CmArray  operator ||(const bool &);
	CmArray  operator +(CmArray &);
	CmArray  operator +(double &);
	CmArray  operator +(long &);
	CmArray  operator +(int &);
	CmArray  operator +(const double &);
	CmArray  operator +();
	CmArray  operator -(CmArray &);
	CmArray  operator -();
	CmArray  operator -(double &);
	CmArray  operator -(long &);
	CmArray  operator -(int &);
	CmArray  operator -(const double &);
	CmArray  operator *(CmArray &);
	CmArray  operator *(double &);
	CmArray  operator *(long &);
	CmArray  operator *(int &);
	CmArray  operator *(const double &);
	CmArray  operator /(const double &);
	CmArray  operator ^(double);
	CmArray  operator ^(CmArray);
	CmArray  operator &(CmArray &);   // Matlab .* equivalent
	CmArray  operator |(CmArray &);	// Matlab ./ equivalent
    CmArray	operator()(double *, long, long);
	double operator()(long);
	double operator()(long,long);


	CmArray mpow(double, CmArray);
	CmArray mlog10(CmArray);
	CmArray mlog(CmArray);

	CmArray AppColumn(CmArray);
	CmArray AppColumn(double);
	CmArray Extract(long,long,long,long);
	void	build(double *, long, long);

};

#endif // !defined(AFX_MARRAY_H__D1FB66FD_91D6_4A18_A455_A4D345A4C776__INCLUDED_)
