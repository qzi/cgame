#include "CBullet.h"
#include <gl/glut.h>


CBullet::CBullet():m_x(0),m_y(0),m_z(0)
{

	m_vx = 0.f;
	m_vy = 0.f;
	m_vz = 0.f;
}

CBullet::CBullet( float x, float y, float z )
{
	m_x = x;
	m_y = y;
	m_z = z;
}

CBullet::~CBullet()
{

}

void CBullet::DrawBullet()
{
	// draw the bullet
	glPushMatrix();
		glTranslatef( m_x, m_y, m_z );
		glColor3f( 1.0f, 0.0f, 0.0f );
		glutSolidSphere( 0.1f, 5, 5 );
	glPopMatrix();

	// update the position;
	m_x += m_vx * 1;
	m_y += m_vy * 1;
	m_z += m_vz * 1;
}


void CBullet::SetPosition( float x, float y, float z )
{
	m_x = x;
	m_y = y;
	m_z = z;
}

void CBullet::SetVelocity( float vx, float vy, float vz )
{
	m_vx = vx;
	m_vy = vy;
	m_vz = vz;
}
