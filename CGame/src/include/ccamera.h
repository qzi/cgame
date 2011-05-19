#ifndef	__CCAMERA_H_
#define __CCAMERA_H_

#include "cvector.h"

// camera roving
class CCamera{
public:
	// constructor
	CCamera();
	~CCamera();

	CVector3 getPosition()  { return m_Position;	}
	CVector3 getView()		{ return m_View;		}
	CVector3 getUpVector()	{ return m_UpVector;	}
	float getSpeed()		{ return m_Speed;		}

	// set the position ,view and upvector of camera s
	void setCamera(	float posX,		float posY,		float posZ,
		float viewX,	float viewY,	float viewZ,
		float upVectorX,float upVectorY,float upVectorZ);

	//  yaw rotate
	void yawCamera( float degree );

	// pitch rotate
	void pitchCamera( float degree );

	// roll rotate
	void rollCamera( float degree );

	// move camera directly
	void moveCamera(float speed);

	// set the camera
	void setLook();

	// just for test
	//void LookAt(float eyex, float eyey, float eyez, float centerx,
	//	float centery, float centerz, float upx, float upy,
	//	float upz);

public:
	float matrixCamera[16];	// the GL_MODELVIEW_MATRIX 

private:

	CVector3 m_Position;	// camera position
	CVector3 m_View;		// camera view
	CVector3 m_UpVector;	// camera vector
	float	 m_Speed;       // camera speed
	
};

#endif	// __CCAMERA_H_
