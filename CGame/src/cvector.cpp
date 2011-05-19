#include <math.h>
#include <memory>

#include "cvector.h"

CVector3::CVector3():x(0),y(0),z(0){

	v[0] = 0.f;
	v[1] = 0.f;
	v[2] = 0.f;

}

CVector3::CVector3( float sx,float sy,float sz ):x(sx),y(sy),z(sz){

}

CVector3::CVector3( const CVector3 & vec ):x(vec.x),y(vec.y),z(vec.z){

}

void CVector3::Normalize(){

	(*this) /= Length();
}

const _scalar CVector3::Length() const
{
	return (_scalar)sqrt((double)(x*x + y*y + z*z));
}

const _scalar CVector3::DotProduct( const CVector3 &vec ) const
{
	return (x*vec.x + y*vec.y + z*vec.z);
}
