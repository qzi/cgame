#ifndef CVECTOR_H
#define CVECTOR_H

#define _scalar float

class CVector3{
public:

	union{
		struct{
			float x;
			float y;
			float z;	// x,y,z coordinates
		};
		float v[3];
	};
	// constructor
	CVector3();
	CVector3(float sx,float sy,float sz);
	CVector3(const CVector3 & vec);

	// assigment
	const CVector3 &operator=(const CVector3 &vec){

		x = vec.x;
		y = vec.y;
		z = vec.z;

		return *this;
	}

	// unary operators
	const CVector3 &operator-(){
		x = -x;
		y = -y;
		z = -z;
		return *this;
	}

	// vector add
	const CVector3 operator+(const CVector3 &vec) const{

		return CVector3(x + vec.x,y + vec.y ,z + vec.z);
	}

	// vector subtraction
	const CVector3 operator-(const CVector3 &vec) const{

		return CVector3(x - vec.x, y - vec.y, z - vec.z);
	}

	// divition
	const CVector3 operator/(const _scalar &s){

		const float recip = 1/s;	// for speed , one diversion
		x *= recip;
		y *= recip;
		z *= recip;
	}
	// selfdivision
	const CVector3 operator/=(const _scalar &s){

		const float recip = 1/s;	// for speed , one diversion
		x *= recip;
		y *= recip;
		z *= recip;

		return (*this);
	}

	// crossproduct
	const CVector3 CrossProduct(const CVector3 &vec) const{

		return CVector3(y*vec.z - z*vec.y,z*vec.x - x*vec.z, x*vec.y - y*vec.x);
	}

	// dotproduct
	const _scalar DotProduct(const CVector3 &vec) const;

	// length of this vector
	const _scalar Length() const;

	// normalize the vector
	void Normalize();
};

#endif	// CVECTOR_H