#ifndef MATHEX_H
#define MATHEX_H
#include <math.h>
#define EPSILON 1.0e-8
#define ZERO EPSILON
#define M_PI 3.1415926535// the macros define the math 
#define PI (3.14159265358979323846)
#define RAD_FROM_DEG(degree) ((degree)*(PI)/180)// Useful constants
#define M3D_PI (3.14159265358979323846)
#define M3D_2PI (2.0 * M3D_PI)
#define M3D_PI_DIV_180 (0.017453292519943296)
#define M3D_INV_PI_DIV_180 (57.2957795130823229)
template <class T> inline T limit(const T &x, const T &lower, const T &upper)
{
	if (x < lower)
		return lower;
	if (x > upper)
		return upper;
	return x;
}

template <class T> inline T sqr(const T &x)
{
	return x*x;
}

template <class T> inline T RadToDeg(const T &rad)
{
	return (rad * 180.0) / M_PI;
}
template <class T> inline T DegToRad(const T &deg)
{
	return (deg * M_PI) / 180.0;
}
#endif	//MATHEX_H
