#ifndef CMATRIX_H
#define CMATRIX_H

#include "mathex.h"

class CVector3;

class CMatrix33
{
private:
	double _Mx[3][3];

public:

	// Constructors
	CMatrix33();

	CMatrix33(double Phi, double Theta, double Psi);

	CMatrix33(double mx00, double mx01, double mx02, double mx10, double mx11, double mx12, double mx20, double mx21, double mx22);


	// Selectors
	double operator()(int Row, int Column) const { return _Mx[Row][Column]; }

	double &operator()(int Row, int Column) { return _Mx[Row][Column]; }


	// Optimised artimetric methods
	static CMatrix33 &add(const CMatrix33 &m1, const CMatrix33 &m2, CMatrix33 &result);

	static CMatrix33 &subtract(const CMatrix33 &m1, const CMatrix33 &m2, CMatrix33 &result);

	static CMatrix33 &multiply(const CMatrix33 &m1, const CMatrix33 &m2, CMatrix33 &result);

	static CMatrix33 &multiply(const CMatrix33 &m1, const double &scale, CMatrix33 &result);

	static CVector3 &multiply(const CMatrix33 &m1, const CVector3 &v, CVector3 &result);


	// Matrix arithmetic

	CMatrix33 &operator+=(const CMatrix33 &m) { return add(*this, m, *this); }

	CMatrix33 &operator-=(const CMatrix33 &m) { return subtract(*this, m, *this); }

	CMatrix33 &operator*=(const CMatrix33 &m) { CMatrix33 tm(*this); return multiply(tm, m, *this); }

	CMatrix33 &operator*=(const double &scale) { return multiply(*this, scale, *this); }

	CMatrix33 operator+(const CMatrix33 &m) const { CMatrix33 tm; return add(*this, m, tm); }

	CMatrix33 operator-(const CMatrix33 &m) const { CMatrix33 tm; return subtract(*this, m, tm); }

	CMatrix33 operator*(const CMatrix33 &m) const { CMatrix33 tm; return multiply(*this, m, tm); }

	CMatrix33 operator*(const double &scale) const { CMatrix33 tm; return multiply(*this, scale, tm); }

	CVector3 operator*(const CVector3 &v) const;

	// Determinants
	double determinant() const;

	static double determinant(const CMatrix33 &m) { return m.determinant(); }

	// Transpose
	CMatrix33 &transpose();

	static CMatrix33 &transpose(const CMatrix33 &m, CMatrix33 &result) { result = m; return result.transpose(); }

	static CMatrix33 transpose(const CMatrix33 &m) { return CMatrix33(m).transpose(); }


	// Inverse
	static CMatrix33 &CMatrix33::inverse(const CMatrix33 &m1, CMatrix33 &result);

	static CMatrix33 CMatrix33::inverse(const CMatrix33 &m1) { CMatrix33 tm; return inverse(m1, tm); }

	CMatrix33 inverse() const { CMatrix33 tm; return inverse(*this, tm); }
};

#endif
