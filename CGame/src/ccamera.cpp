#include <math.h>
#include <gl/glut.h>

#include "common.h"
#include "ccamera.h"
#include "cmatrix.h"
#include "math3d.h"


CCamera::CCamera(){
	
	// initial the vector
	CVector3 zero = CVector3(0.0, 0.0, 0.0);		
	CVector3 view = CVector3(0.0, 1.0, 0.5);		
	CVector3 up   = CVector3(0.0, 0.0, 1.0);		


	// initial the camera 
	m_Position	= zero;					
	m_View		= view;				
	m_UpVector	= up;	
	m_Speed     = 0.2f;

	matrixCamera[0] = 1.0f;			
	matrixCamera[1] = 0.0f;
	matrixCamera[2] = 0.0f;
	matrixCamera[3] = 0.0f;			// 4
	matrixCamera[4] = 0.0f;
	matrixCamera[5] = 1.0f;
	matrixCamera[6] = 0.0f;
	matrixCamera[7] = 0.0f;			// 8 
	matrixCamera[8] = 0.0f;
	matrixCamera[9] = 0.0f;
	matrixCamera[10] = 1.0f;
	matrixCamera[11] = 0.0f;		// 12
	matrixCamera[12] = 0.0f;
	matrixCamera[13] = 0.0f;
	matrixCamera[14] = 0.0f;
	matrixCamera[15] = 1.0f;		// 16
}

CCamera::~CCamera()
{

}

void CCamera::setCamera( float posX, float posY, float posZ, float viewX, float viewY, float viewZ, float upVectorX,float upVectorY,float upVectorZ )
{
	// construct vector
	CVector3 position	= CVector3( posX, posY, posZ );
	CVector3 view		= CVector3( viewX, viewY, viewZ );
	CVector3 upVector	= CVector3( upVectorX, upVectorY, upVectorZ );

	// set the camera
	m_Position	= position;
	m_View		= view;
	m_UpVector	= upVector;
}


void CCamera::yawCamera( float degree )
{
	CVector3 newView;
	CVector3 viewVector = m_View - m_Position;

	glPushMatrix();
	glLoadIdentity();
	glRotated( degree, m_UpVector.x, m_UpVector.y, m_UpVector.z );
	glGetFloatv( GL_MODELVIEW_MATRIX, matrixCamera );
	glPopMatrix();

	CMatrix33 rotateM(
		matrixCamera[0],matrixCamera[1],matrixCamera[2],
		matrixCamera[4],matrixCamera[5],matrixCamera[6],
		matrixCamera[8],matrixCamera[9],matrixCamera[10]
	);

	newView = rotateM * viewVector;
	// update the camera
	m_View = m_Position + newView;
	

	//glPushMatrix();
	//	glLoadIdentity();
	//	//glRotatef( degree,m_UpVector.x,m_UpVector.y,m_UpVector.z);
	//	glRotatef( degree, 0.0f, 1.0f, 0.0f );
	//	glMultMatrixf( matrixCamera );
	//	glGetFloatv( GL_MODELVIEW_MATRIX, matrixCamera );
	//glPopMatrix();

}

void CCamera::pitchCamera( float degree )
{
	CVector3 viewVector;
	CVector3 SideVector;		// the normal of  m_view and m_Upvector
	CVector3 resultViewVector;

	viewVector = m_View - m_Position;
	SideVector = viewVector.CrossProduct( m_UpVector );
	SideVector.Normalize();

	glPushMatrix();
		glLoadIdentity();
		glRotated( degree, SideVector.x, SideVector.y, SideVector.z );
		glGetFloatv( GL_MODELVIEW_MATRIX, matrixCamera );
	glPopMatrix();

	CMatrix33 rotateM(
		matrixCamera[0],matrixCamera[1],matrixCamera[2],
		matrixCamera[4],matrixCamera[5],matrixCamera[6],
		matrixCamera[8],matrixCamera[9],matrixCamera[10]
		);

	resultViewVector = rotateM * viewVector;
	m_UpVector = rotateM * m_UpVector;
	m_View = m_Position +  resultViewVector;

	
	//glPushMatrix();
	//	glLoadIdentity();
	//	glRotatef( degree, 1.f, 0.f, 0.f );
	//	glMultMatrixf( matrixCamera );
	//	glGetFloatv( GL_MODELVIEW_MATRIX, matrixCamera );
	//glPopMatrix();
}


void CCamera::rollCamera( float degree )
{

	CVector3 viewVector;
	viewVector = m_Position - m_View;

	glPushMatrix();
	glLoadIdentity();
	glRotated( degree, viewVector.x, viewVector.y, viewVector.z );
	glGetFloatv( GL_MODELVIEW_MATRIX, matrixCamera );
	glPopMatrix();

	CMatrix33 rotateM(
		matrixCamera[0],matrixCamera[1],matrixCamera[2],
		matrixCamera[4],matrixCamera[5],matrixCamera[6],
		matrixCamera[8],matrixCamera[9],matrixCamera[10]
	);

	m_UpVector = rotateM * m_UpVector;

		/*glPushMatrix();
		glLoadIdentity();
		glRotatef( degree, 0.0f, 0.0f, 1.0f );
		glMultMatrixf( matrixCamera );
		glGetFloatv( GL_MODELVIEW_MATRIX, matrixCamera );
		glPopMatrix();*/
 
}

void CCamera::moveCamera( float speed )
{
	// calculate the directional vector 
	CVector3 vector = m_View -m_Position;
	vector.Normalize();

	// update the camera
	m_Position.x += vector.x * speed;	// update the position according the speed
	m_Position.y += vector.y * speed;
	m_Position.z += vector.z * speed;	
	m_View.x += vector.x * speed;		// update the position according the direction
	m_View.y += vector.y * speed;
	m_View.z += vector.z * speed;	

	/*glPushMatrix();
	glLoadIdentity();
	glTranslatef( 0.0f,0.0f,speed);
	glMultMatrixf(matrixCamera);
	glGetFloatv(GL_MODELVIEW_MATRIX, matrixCamera);
	glPopMatrix();*/

}

void CCamera::setLook()
{
	gluLookAt(m_Position.x,m_Position.y,m_Position.z,
		m_View.x,m_View.y,m_View.z,
		m_UpVector.x,m_UpVector.y,m_UpVector.z);

	//LookAt( m_Position.x,m_Position.y,m_Position.z,
	//	m_View.x,m_View.y,m_View.z,
	//	m_UpVector.x,m_UpVector.y,m_UpVector.z );


}

//CVector3 CCamera::getView()
//{
//	float defaultViewVector[4] = { 0.f, 0.f, -1.f, 0.f};
//	float resultViewVector[4];
//
//	m3dTransformVector4( resultViewVector, defaultViewVector, matrixCamera );
//	
//	m_View.x = -resultViewVector[0];
//	m_View.y = -resultViewVector[1];
//	m_View.z = -resultViewVector[2];
//
//	return m_View;
//}
//
//CVector3 CCamera::getPosition()
//{
//	m_Position.x = -matrixCamera[12];
//	m_Position.y = -matrixCamera[13];
//	m_Position.z = -matrixCamera[14];
//
//	return m_Position;
//}

//////////////////////////////////////////////////////////////////////////
// glulookat
//static void normalize(float v[3])
//{
//	float r;
//
//	r = sqrt( v[0]*v[0] + v[1]*v[1] + v[2]*v[2] );
//	if (r == 0.0) return;
//
//	v[0] /= r;
//	v[1] /= r;
//	v[2] /= r;
//}
//
//static void cross(float v1[3], float v2[3], float result[3])
//{
//	result[0] = v1[1]*v2[2] - v1[2]*v2[1];
//	result[1] = v1[2]*v2[0] - v1[0]*v2[2];
//	result[2] = v1[0]*v2[1] - v1[1]*v2[0];
//}
//
//static void __gluMakeIdentityf(GLfloat m[16])
//{
//	m[0+4*0] = 1; m[0+4*1] = 0; m[0+4*2] = 0; m[0+4*3] = 0;
//	m[1+4*0] = 0; m[1+4*1] = 1; m[1+4*2] = 0; m[1+4*3] = 0;
//	m[2+4*0] = 0; m[2+4*1] = 0; m[2+4*2] = 1; m[2+4*3] = 0;
//	m[3+4*0] = 0; m[3+4*1] = 0; m[3+4*2] = 0; m[3+4*3] = 1;
//}
//
//void CCamera::LookAt( float eyex, float eyey, 
//				float eyez, float centerx, float centery, 
//				float centerz, float upx, float upy, float upz )
//{
//
//	float forward[3], side[3], up[3];
//	float m[4][4];
//
//	forward[0] = centerx - eyex;
//	forward[1] = centery - eyey;
//	forward[2] = centerz - eyez;
//
//	up[0] = upx;
//	up[1] = upy;
//	up[2] = upz;
//
//	normalize(forward);
//
//	/* Side = forward x up */
//	cross(forward, up, side);
//	normalize(side);
//
//	/* Recompute up as: up = side x forward */
//	cross(side, forward, up);
//
//	__gluMakeIdentityf(&m[0][0]);
//	m[0][0] = side[0];
//	m[1][0] = side[1];
//	m[2][0] = side[2];
//
//	m[0][1] = up[0];
//	m[1][1] = up[1];
//	m[2][1] = up[2];
//
//	m[0][2] = -forward[0];
//	m[1][2] = -forward[1];
//	m[2][2] = -forward[2];
//	
//	glGetFloatv(GL_MODELVIEW_MATRIX, matrixCamera); 
//	glMultMatrixf(&m[0][0]);
//	glGetFloatv(GL_MODELVIEW_MATRIX, matrixCamera); 
//	glTranslatef(-eyex, -eyey, -eyez);
//	glGetFloatv(GL_MODELVIEW_MATRIX, matrixCamera); 
//}
//
