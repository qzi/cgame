#ifndef __CPICK_H_
#define __CPICK_H_

#include "cvector.h"
#include <gl/glut.h>

CVector3 V0( 1.0,0.0,-1.0 );
CVector3 V1( 0.0,1.0,-1.0 );
CVector3 V2( 0.0,0.0,-2.0 );
GLfloat g_color =1.0f;


//--------------------------------------------------------------------------------------
// Given a ray origin (orig) and direction (dir), and three vertices of a triangle, this
// function returns TRUE and the interpolated texture coordinates if the ray intersects 
// the triangle
//--------------------------------------------------------------------------------------
bool IntersectTriangle( const CVector3& orig, const CVector3& dir,
					   CVector3& v0, CVector3& v1, CVector3& v2/*,*/ 
					   /* GLfloat* t, GLfloat* u, GLfloat* v*/ )
{
	// Find vectors for two edges sharing vert0
	CVector3 edge1 = v1 - v0;
	CVector3 edge2 = v2 - v0;

	// Begin calculating determinant - also used to calculate U parameter
	CVector3 pvec = dir.CrossProduct( edge2 );

	// If determinant is near zero, ray lies in plane of triangle
	_scalar det = pvec.DotProduct( edge1 );

	CVector3 tvec;
	if ( det > 0 )
	{
		tvec = orig - v0;
	}else
	{
		tvec = v0 - orig;
		det = -det;
	}

	if( det < 0.0001f )
		return false;

	// Calculate U parameter and test bounds
	GLfloat u ;
	u = tvec.DotProduct( pvec );
	if( u < 0.0f || u > det )
		return false;

	// Prepare to test V parameter
	GLfloat v;
	CVector3 qvec = tvec.CrossProduct( edge1 );
	v = dir.DotProduct(qvec);
	if( v < 0.0f || u + v > det )
		return false;

	// Calculate t, scale parameters, ray intersects triangle
	GLfloat t;
	t = edge2.DotProduct( qvec );
	_scalar fInvDet = 1.0f/det;
	t *= fInvDet;
	u *= fInvDet;
	v *= fInvDet;

	return true;
}


void pick(GLfloat winx,GLfloat winy)
{
	//g_color = 0.0;
	//if(IntersectTriangle()) g_color=1.0;

	GLint viewport[4];
	GLdouble mvmatrix[16], projmatrix[16];
	GLint realY;  /*  OpenGL y coordinate position  */
	GLdouble nearX, nearY, nearZ;
	GLdouble farX, farY, farZ;

	glGetIntegerv( GL_VIEWPORT, viewport );
	glGetDoublev( GL_MODELVIEW_MATRIX, mvmatrix );
	glGetDoublev( GL_PROJECTION_MATRIX, projmatrix );

	/*  note viewport[3] is height of window in pixels  */
	realY = viewport[3] - (GLint) winy - 1;

	gluUnProject( (GLdouble)winx, (GLdouble)realY,0.0,		// the z depth is between (0.0,1.0)
		mvmatrix, projmatrix, viewport, &nearX, &nearY, &nearZ );
	gluUnProject( (GLdouble)winx, (GLdouble)realY,1.0,
		mvmatrix, projmatrix, viewport, &farX, &farY, &farZ );

	// calculate the ray direction
	CVector3 orig( nearX, nearY, nearZ );
	CVector3 dir( farX, farY, farZ );
	CVector3 dirVector = dir - orig;

	g_color = 0.0f;
	if (IntersectTriangle( orig, dir, V0, V1, V2 ))
	{
		g_color = 1.0f;
	}
}

#endif	__CPICK_H_