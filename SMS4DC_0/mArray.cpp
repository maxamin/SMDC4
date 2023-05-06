// mArray.cpp: implementation of the CmArray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SMS4DC.h"
#include "mArray.h"

#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CmArray::CmArray()
{
    elem_ = (double *)malloc(sizeof(double));
    elem_[0]=0;
	r_= 1;
	c_= 1;

}

CmArray::~CmArray()
{
//	delete elem_;
}


CmArray::CmArray(long row_, long col_)
{
	long sz;
	sz=row_*col_;
	elem_ = (double *)malloc(sizeof(double)*sz);
    for(long i=0;i<sz;i++) elem_[i]=0;
	r_= row_;
	c_= col_;
}

CmArray::CmArray(double *array, long row_, long col_=1)
{
	long sz;
	sz=row_*col_;
	elem_ = (double *)malloc(sizeof(double)*sz);
    for(long i=0;i<sz;i++) elem_[i]=array[i];
	r_= row_;
	c_= col_;
}

double *CmArray::colon(double st_,double end_,double dlt_=1)
{
	c_ = 1;
	r_ = (long)((end_-st_)/dlt_+1e-13);
	//dlt_ = (end_-st_)/r_;
	r_ = r_++;
	free(elem_);
	elem_ = (double *)malloc(sizeof(double)*r_);
	for(long i=0;i<r_;i++) elem_[i] = st_+i*dlt_;

	return elem_;
}
void CmArray::del()
{
	delete elem_;
}

CmArray CmArray::Trans()
{
	CmArray newarray(c_,r_);	
	
	for (long i=0; i<c_; i++)
		for (long j=0; j<r_; j++) newarray.elem_[j+i*r_] = elem_[i+j*c_];

	delete elem_;
	return newarray;
}



/////////////////////////////////////////////////////////
/////////////////////operatorS//////////////////////////////////
///////////////////////////////////////////////////////



CmArray &CmArray::operator=(CmArray &arr){
	
	elem_ = (double *)malloc(sizeof(double)*arr.c_*arr.r_);
	for(long i=0;i<arr.c_*arr.r_;i++)
			elem_[i] = arr.elem_[i];
    r_ = arr.r_;
	c_ = arr.c_;
	return *this;
}

CmArray CmArray::operator==(const double &r1){
	CmArray newarray(r_,c_);
	for (long i=0; i<c_*r_; i++) newarray.elem_[i]=(r1==elem_[i]);
	return newarray;
}

CmArray CmArray::operator==(CmArray &r1){
	if ((r1.r_!= r_) | (r1.c_!= c_))
	{
	//	cout<<"Erorr in == operation. Unequal Dimensions"<<endl;
		AfxMessageBox("Erorr in == operation. Unequal Dimensions");
	    exit(1);
	}
	else
	{
		CmArray newarray(r1.r_,r1.c_);
	    newarray.c_=r1.c_;
		newarray.r_=r1.r_;
		for (long i=0; i<r1.c_*r1.r_; i++) newarray.elem_[i]=(r1.elem_[i]==elem_[i]);
		return newarray;
	}
}

CmArray CmArray::operator>=(CmArray &r1){
	if ((r1.r_!= r_) | (r1.c_!= c_))
	{
	//	cout<<"Erorr in >= operation. Unequal Dimensions"<<endl;
		AfxMessageBox("Erorr in >= operation. Unequal Dimensions");
	    exit(1);
	}
	else
	{
		CmArray newarray(r1.r_,r1.c_);
	    newarray.c_=r1.c_;
		newarray.r_=r1.r_;
		for (long i=0; i<r1.c_*r1.r_; i++) newarray.elem_[i]=(elem_[i]>=r1.elem_[i]);
		return newarray;
	}
}

CmArray CmArray::operator>=(const double &r1){
	CmArray newarray(r_,c_);

	for (long i=0; i<c_*r_; i++) newarray.elem_[i]=(elem_[i]>=r1);

	return newarray;
}

CmArray CmArray::operator>(CmArray &r1){
	if ((r1.r_!= r_) | (r1.c_!= c_))
	{
	//	cout<<"Erorr in > operation. Unequal Dimensions"<<endl;
		AfxMessageBox("Erorr in > operation. Unequal Dimensions");

	    exit(1);
	}
	else
	{
		CmArray newarray(r1.r_,r1.c_);
	    newarray.c_=r1.c_;
		newarray.r_=r1.r_;
		for (long i=0; i<r1.c_*r1.r_; i++) newarray.elem_[i]=(elem_[i]>r1.elem_[i]);
		return newarray;
	}
}

CmArray CmArray::operator>(const double &r1){
	CmArray newarray(r_, c_);

	for (long i=0; i<c_*r_; i++) newarray.elem_[i]=(elem_[i]>r1);
	return newarray;
}

CmArray CmArray::operator<=(CmArray &r1){
	if ((r1.r_!= r_) | (r1.c_!= c_))
	{
	//	cout<<"Erorr in <= operation. Unequal Dimensions"<<endl;
		AfxMessageBox("Erorr in <= operation. Unequal Dimensions");

	    exit(1);
	}
	else
	{
		CmArray newarray(r1.r_,r1.c_);
	    newarray.c_=r1.c_;
		newarray.r_=r1.r_;
		for (long i=0; i<r1.c_*r1.r_; i++) newarray.elem_[i]=(elem_[i]<=r1.elem_[i]);
		return newarray;
	}
}

CmArray CmArray::operator< (CmArray &r1){
	if ((r1.r_!= r_) | (r1.c_!= c_))
	{
	//	cout<<"Erorr in <= operation. Unequal Dimensions"<<endl;
		AfxMessageBox("Erorr in <= operation. Unequal Dimensions");
	    exit(1);
	}
	else
	{
		CmArray newarray(r1.r_,r1.c_);
	    newarray.c_=r1.c_;
		newarray.r_=r1.r_;
		for (long i=0; i<r1.c_*r1.r_; i++) newarray.elem_[i]=(elem_[i]< r1.elem_[i]);
		return newarray;
	}
}

CmArray CmArray::operator<=(const double &r1){
	CmArray newarray(r_,c_);

	for (long i=0; i<c_*r_; i++) newarray.elem_[i]=(elem_[i]<=r1);
	return newarray;

}

CmArray CmArray::operator<(const double &r1){
	CmArray newarray(r_,c_);

	for (long i=0; i<c_*r_; i++) newarray.elem_[i]=(elem_[i]<r1);
	return newarray;

}

CmArray CmArray::operator &&(CmArray &r1){
	if ((r1.r_!= r_) | (r1.c_!= c_))
	{
	//	cout<<"Erorr in and operation. Unequal Dimensions"<<endl;
		AfxMessageBox("Erorr in and operation. Unequal Dimensions");
	    exit(1);
	}
	else
	{
		CmArray newarray(r1.r_,r1.c_);
	    newarray.c_=r1.c_;
		newarray.r_=r1.r_;
		for (long i=0; i<r1.c_*r1.r_; i++) newarray.elem_[i]=(r1.elem_[i]&&elem_[i]);
		return newarray;
	}
}

CmArray CmArray::operator ||(CmArray &r1){
	if ((r1.r_!= r_) | (r1.c_!= c_))
	{
	//	cout<<"Erorr in or operation. Unequal Dimensions"<<endl;
		AfxMessageBox("Erorr in or operation. Unequal Dimensions");
	    exit(1);
	}
	else
	{
		CmArray newarray(r1.r_,r1.c_);
	    newarray.c_=r1.c_;
		newarray.r_=r1.r_;
		for (long i=0; i<r1.c_*r1.r_; i++) newarray.elem_[i]=(r1.elem_[i]||elem_[i]);
		return newarray;
	}
}

CmArray CmArray::operator ||(const bool &r1){
	CmArray newarray(r_,c_);
    newarray.c_=c_;
	newarray.r_=r_;
	for (long i=0; i<c_*r_; i++) newarray.elem_[i]=(elem_[i]||r1);
	return newarray;
}

CmArray CmArray::operator()(double *elem, long r, long c)
{
	CmArray newarray(r, c);
	
	for (long i=0; i<r*c; i++) newarray.elem_[i]=elem[i];

	return newarray;
}

double CmArray::operator()(long i){
	if((r_>1 && c_>1))
	{
	//	cout<<"Treat as Two Dimensional Array"<<endl;
		AfxMessageBox("Treat as Two Dimensional Array");
		exit(1);
	}
	else{
		if((i>=r_ && c_==1)||(i>=c_ && r_==1))
		{
	//	    cout<<"Index Exceeds Vector Dimension"<<endl;
			AfxMessageBox("Index Exceeds Vector Dimension");
		    exit(1);
		}
	
	}
	return elem_[i];
}

double CmArray::operator()(long i,long j){
	if(i<0 || i>r_ || j<0 || j>c_)
	{
	//	cout<<"Index Exceed Matrix Dimension"<<endl;
		AfxMessageBox("Index Exceed Matrix Dimension");

		exit(1);
	}
	return elem_[(i-1)*c_+(j-1)];
}


CmArray CmArray::operator+(CmArray &r1){
	if ((r1.r_!= r_) | (r1.c_!= c_))
	{
	//	cout<<"Erorr in summation"<<endl;
		AfxMessageBox("Erorr in summation");
	    exit(1);
	}
	else
	{
		CmArray newarray(r1.r_,r1.c_);
		//free(newarray.elem_);
	    newarray.c_=r1.c_;
		newarray.r_=r1.r_;
		for (long i=0; i<r1.c_*r1.r_; i++) newarray.elem_[i]=r1.elem_[i]+elem_[i];
		return newarray;
	}
}

CmArray CmArray::operator+(double &D){
	CmArray newarray(r_,c_);

	newarray.c_=c_;
	newarray.r_=r_;
	for (long i=0; i<c_*r_; i++) newarray.elem_[i]=elem_[i]+D;

	return newarray;
}

CmArray CmArray::operator+(long &D){
	CmArray newarray(r_,c_);

	newarray.c_=c_;
	newarray.r_=r_;
	for (long i=0; i<c_*r_; i++) newarray.elem_[i]=elem_[i]+D;

	return newarray;
}

CmArray CmArray::operator+(int &D){
	CmArray newarray(r_,c_);

	newarray.c_=c_;
	newarray.r_=r_;
	for (long i=0; i<c_*r_; i++) newarray.elem_[i]=elem_[i]+D;

	return newarray;
}

CmArray CmArray::operator+(const double &D){
	CmArray newarray(r_,c_);

	newarray.c_=c_;
	newarray.r_=r_;
	for (long i=0; i<c_*r_; i++) newarray.elem_[i]=elem_[i]+D;

	return newarray;
}

CmArray CmArray::operator +()
{
	CmArray newarray(r_,c_);
	for(long i=0;i<c_*r_;i++) newarray.elem_[i]=elem_[i];
	return newarray;
}

CmArray CmArray::operator-(CmArray &r1){
	if ((r1.r_!= r_) | (r1.c_!= c_))
	{
	//	cout<<"Erorr in summation"<<endl;
		AfxMessageBox("Erorr in summation");
		exit(1);
	}
	else
	{
		CmArray newarray(r1.r_,r1.c_);
	    newarray.c_=r1.c_;
		newarray.r_=r1.r_;
		for (long i=0; i<r1.c_*r1.r_; i++) newarray.elem_[i]=elem_[i]-r1.elem_[i];
		return newarray;
	}
}

CmArray CmArray::operator -()
{
	CmArray newarray(r_,c_);
	for(long i=0;i<c_*r_;i++) newarray.elem_[i]=-elem_[i];
	return newarray;
}

CmArray CmArray::operator-(double &D){
	CmArray newarray(r_,c_);

	newarray.c_=c_;
	newarray.r_=r_;
	for (long i=0; i<c_*r_; i++) newarray.elem_[i]=elem_[i]-D;

	return newarray;
}

CmArray CmArray::operator-(long &D){
	CmArray newarray(r_,c_);

	newarray.c_=c_;
	newarray.r_=r_;
	for (long i=0; i<c_*r_; i++) newarray.elem_[i]=elem_[i]-D;

	return newarray;
}

CmArray CmArray::operator-(int &D){
	CmArray newarray(r_,c_);

	newarray.c_=c_;
	newarray.r_=r_;
	for (long i=0; i<c_*r_; i++) newarray.elem_[i]=elem_[i]-D;

	return newarray;
}

CmArray CmArray::operator -(const double &D){
	CmArray newarray(r_,c_);

	newarray.c_=c_;
	newarray.r_=r_;
	for (long i=0; i<c_*r_; i++) newarray.elem_[i]=elem_[i]-D;

	return newarray;
}

CmArray CmArray::operator *(CmArray &r1){

	if (r1.r_!= c_)
	{
	//	cout<<"Erorr in multiplication. Index mismatch"<<endl;
		AfxMessageBox("Erorr in multiplication. Index mismatch");
	    exit(1);
	}
	else
	{
		CmArray newarray(r_, r1.c_);
    	double sum=0;
	
		newarray.c_=r1.c_;
		newarray.r_=r_;
		for (long i=0; i<r_; i++)
			for (long j=0; j<r1.c_; j++)
			{
				sum =0;
				for (long k=0; k<c_; k++)
					sum = sum + r1.elem_[j+k*r1.c_]*elem_[k+i*c_];
				newarray.elem_[i*r1.c_+j] = sum;
			}
		return newarray;
	}
}


CmArray CmArray::operator *(double &D){
	CmArray newarray(r_, c_);
	newarray.c_ = c_;
	newarray.r_ = r_;
	for (long i=0; i<r_*c_; i++) newarray.elem_[i]=elem_[i]*D;

   return newarray;
}

CmArray CmArray::operator *(long &D){
	CmArray newarray(r_, c_);
	newarray.c_ = c_;
	newarray.r_ = r_;
	for (long i=0; i<r_*c_; i++) newarray.elem_[i]=elem_[i]*D;

   return newarray;
}

CmArray CmArray::operator *(int &D){
	CmArray newarray(r_, c_);
	newarray.c_ = c_;
	newarray.r_ = r_;
	for (long i=0; i<r_*c_; i++) newarray.elem_[i]=elem_[i]*D;

   return newarray;
}

CmArray CmArray::operator *(const double &D){
	CmArray newarray(r_, c_);
	newarray.c_ = c_;
	newarray.r_ = r_;
	for (long i=0; i<r_*c_; i++) newarray.elem_[i]=elem_[i]*D;

   return newarray;
}

CmArray CmArray::operator /(const double &D){
	CmArray newarray(r_, c_);
	newarray.c_ = c_;
	newarray.r_ = r_;
	for (long i=0; i<r_*c_; i++) newarray.elem_[i]=elem_[i]/D;

   return newarray;
}

CmArray CmArray::operator ^(double p_){
	CmArray newarray(r_, c_);
	for (long i=0; i<r_*c_; i++) newarray.elem_[i]= pow(elem_[i],p_);
	return newarray;
}

CmArray CmArray::operator ^(CmArray p_){
	if (p_.r_!=r_ || p_.c_!=c_)
	{
	//	cout<<"Error in elementwise power"<<endl;
		AfxMessageBox("Error in elementwise power");
	    exit(1);
	}
	CmArray newarray(p_.r_, p_.c_);
	for (long i=0; i<p_.r_*p_.c_; i++) newarray.elem_[i]= pow(elem_[i],p_.elem_[i]);
	return newarray;
}

CmArray CmArray::operator &(CmArray &r1){
	if ((r1.r_!= r_) | (r1.c_!= c_))
	{
	//	cout<<"Erorr in elementwise multiplication"<<endl;
		AfxMessageBox("Erorr in elementwise multiplication");
	    exit(1);
	}
	else
	{
		CmArray newarray(r1.r_,r1.c_);
	    newarray.c_=r1.c_;
		newarray.r_=r1.r_;
		for (long i=0; i<r1.c_*r1.r_; i++) newarray.elem_[i]=r1.elem_[i]*elem_[i];
		return newarray;
	}
}

CmArray CmArray::operator |(CmArray &r1){
	if ((r1.r_!= r_) | (r1.c_!= c_))
	{
	//	cout<<"Erorr in elementwise division"<<endl;
		AfxMessageBox("Erorr in elementwise division");
	    exit(1);
	}
	else
	{
		CmArray newarray(r1.r_,r1.c_);
	    newarray.c_=r1.c_;
		newarray.r_=r1.r_;
		for (long i=0; i<r1.c_*r1.r_; i++) newarray.elem_[i]=elem_[i]/r1.elem_[i];
		return newarray;
	}
}


CmArray CmArray::mpow(double base, CmArray arr)
{
	CmArray newarray(arr.r_, arr.c_);

	for (long i=0; i<arr.r_*arr.c_; i++) newarray.elem_[i] = pow(base, arr.elem_[i]);
	return newarray;
}

 CmArray CmArray::mlog10(CmArray arr)
{
	CmArray newarray(arr.r_, arr.c_);

	for (long i=0; i<arr.r_*arr.c_; i++) newarray.elem_[i] = log10(arr.elem_[i]);

	return newarray;
}

 CmArray CmArray::mlog(CmArray arr)
{
	CmArray newarray(arr.r_, arr.c_);

	for (long i=0; i<arr.r_*arr.c_; i++) newarray.elem_[i] = log(arr.elem_[i]);

	return newarray;
}


CmArray CmArray::AppColumn(CmArray arr){
	if (c_ != arr.c_)
	{
	//	cout<<"Erorr in Appending to Column. Unequal Columns"<<endl;
		AfxMessageBox("Erorr in Appending to Column. Unequal Columns");
	    exit(1);
	}
	else
	{
		CmArray newarray(r_+arr.r_,c_);

		for(long i=0; i<newarray.r_; i++)
			for (long j=0; j<c_; j++)
			{
				if(i<r_) newarray.elem_[i*c_+j] = elem_[j+i*c_];
				else
					newarray.elem_[i*c_+j] = arr.elem_[j+(i-r_)*c_];
			}
		return newarray;
	}
}

CmArray CmArray::AppColumn(double element){
	if (c_ != 1)
	{
	//	cout<<"Erorr in Appending one element to Column"<<endl;
		AfxMessageBox("Erorr in Appending one element to Column");
	    exit(1);
	}
	else
	{
		CmArray newarray(r_+1,c_);

		for(long i=0; i<newarray.r_; i++)
			{
				if(i<r_) newarray.elem_[i] = elem_[i];
				else
					newarray.elem_[i] = element;
			}
		return newarray;
	}
}

CmArray CmArray::Extract(long r1, long r2, long c1, long c2){
	CmArray newarray(abs(r2-r1)+1,abs(c2-c1)+1);
    
	for(long i=0;i<=(r2-r1);i++){
		for(long j=0;j<=abs(c2-c1);j++){

			if (c2>=c1)
				newarray.elem_[i*(c2-c1+1)+j] = elem_[(i+r1-1)*c_+j+c1-1];
			else
				newarray.elem_[i*(c1-c2+1)+j] = elem_[(i+r1-1)*c_-j+c1-1];
	}}
   
	return newarray;
}
void CmArray::build(double *array, long row_, long col_=1){
	long sz;
	sz=row_*col_;
	elem_ = (double *)realloc(elem_, sizeof(double)*sz);
    for(long i=0;i<sz;i++) elem_[i]=array[i];
	r_= row_;
	c_= col_;
}
