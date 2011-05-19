#include "cparticle.h"

#include <memory>
#include <gl/glut.h>

CParticle::CParticle()
{
	m_data = NULL;
	m_numparticle = 0;
}

CParticle::~CParticle()
{
	delete[] m_data;
	m_data = NULL;
}

//////////////////////////////////////////////////////////////////////////
// create a array contain num of particle
int CParticle::Create( long num )
{
	// clear the array first
	if( m_data )
		delete[] m_data;

	// create the array
	if ( m_data = new Particle[num])
	{
		memset( m_data, 0, sizeof(Particle) * m_numparticle);
		m_numparticle = num;
		
		return m_numparticle;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
// load the texture
bool CParticle::LoadTextures()
{
	char * fileName[] = {"data/wall.bmp","data/snowball.bmp" };

	for( int i=0; i < 2; i++ )
	{
		if ( !m_texture[i].isLoadBMPFile( fileName[i] ))
		{
			//MessageBox( NULL, "载入纹理失败 ！", "错误", MB_OK );
			exit(0);
		}

		glGenTextures( 1,&m_texture[i].ID );

		// create texture object
		glBindTexture( GL_TEXTURE_2D, m_texture[i].ID );
		
		glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR );

		gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, m_texture[i].m_nImageWidth,
			m_texture[i].m_nImageHeight, GL_RGB, GL_UNSIGNED_BYTE,
			m_texture[i].m_uData );
	
	}
	return true;
}

// return the texture id 
unsigned int CParticle::GetTexture( int index )
{
	if ( index == 0 || index == 1 )
	{
		return m_texture[index].ID;
	}
}

// set the color and get it 
int CParticle::SetColor( int r, int g, int b )
{
	for ( int index = 0; index < m_numparticle; ++index )
	{
		m_data[index].r = r;
		m_data[index].g = g;
		m_data[index].b = b;
	}
	return true;
}

int CParticle::SetColor( int index, int r, int g, int b )
{
	if ( index >= 0 && index < m_numparticle )
	{
		m_data[index].r = r;
		m_data[index].g = g;
		m_data[index].b = b;
		return true;
	}
	return false;
}

int CParticle::GetColor( int index, int &r, int &g, int &b )
{
	if( index >= 0 && index < m_numparticle )
	{
		r=m_data[index].r;
		g=m_data[index].g;
		b=m_data[index].b;
		return true;
	}
	return false;
}

// set the velocity and get it 
int CParticle::SetVelocity( float vx,float vy,float vz )
{
	for ( int index=0; index < m_numparticle; ++index )
	{
		m_data[index].vx=vx;
		m_data[index].vy=vy;
		m_data[index].vz=vz;
	}
	return true;
}

int CParticle::SetVelocity( int index,float vx,float vy,float vz )
{
	if( index>=0 && index<m_numparticle )
	{
		m_data[index].vx=vx;
		m_data[index].vy=vy;
		m_data[index].vz=vz;
		return true;
	}
	return false;
}

int CParticle::GetVelocity( int index,float &vx,float &vy,float &vz )
{
	if( index >= 0 && index < m_numparticle )
	{
		vx=m_data[index].vx;
		vy=m_data[index].vy;
		vz=m_data[index].vz;
		return true;
	}
	return false;
}



// set the size
int CParticle::SetSize(float size)
{
	for ( int index = 0;index < m_numparticle; ++index )
	{
		m_data[index].size=size;
	}
	return true;
}

int CParticle::SetSize(int index,float size)
{
	if ( index >= 0 && index < m_numparticle )
	{
		m_data[index].size=size;
		return true;
	}
	return false;
}

int CParticle::GetSize(int index,float &size)
{
	if( index >= 0 && index < m_numparticle )
	{
		size=m_data[index].size;
		return true;
	}
	return false;
}

/** 消失速度Dec函数 */
int CParticle::SetDec(float dec)
{
	for ( int index = 0;index < m_numparticle; ++index )
	{
		m_data[index].dec=dec;
	}
	return true;
}
int CParticle::SetDec(int index,float dec)
{
	if( index >= 0 && index < m_numparticle )
	{
		m_data[index].dec=dec;
		return true;
	}
	return false;
}
int CParticle::GetDec(int index,float &dec)
{
	if( index >= 0 && index < m_numparticle )
	{
		dec=m_data[index].dec;
		return true;
	}
	return false;
}

// set the lifetime and get it 
int CParticle::SetLifeTime(float lifetime)
{
	for ( int index = 0; index < m_numparticle; ++index )
	{
		m_data[index].lifetime=lifetime;
	}
	return true;
}

int CParticle::SetLifeTime(int index,float lifetime)
{
	if( index >= 0 && index < m_numparticle )
	{
		m_data[index].lifetime=lifetime;
		return true;
	}
	return false;
}

int CParticle::GetLifeTime(int index,float &lifetime)
{
	if( index >= 0 && index < m_numparticle )
	{
		lifetime=m_data[index].lifetime;
		return true;
	}
	return false;
}

// get all the properties
int CParticle::GetAll(int index,int &r,int &g,int &b,       
					  float &x,float &y,float &z,		
					  float &vx,float &vy,float &vz,	
					  float &ax,float &ay,float &az,	
					  float &size,						   
					  float &lifetime,					 
					  float &dec					       
							)
{
	if ( index>=0 && index < m_numparticle )
	{
		r=m_data[index].r;
		g=m_data[index].g;
		b=m_data[index].b;
		x=m_data[index].x;
		y=m_data[index].y;
		z=m_data[index].z;
		vx=m_data[index].vx;
		vy=m_data[index].vy;
		vz=m_data[index].vz;
		ax=m_data[index].ax;
		ay=m_data[index].ay;
		az=m_data[index].az;
		lifetime=m_data[index].lifetime;
		size=m_data[index].size;
		dec=m_data[index].dec;
		return true;
	}
	return false;
}

// set all the properties
int CParticle::SetAll(int index,int r,int g,int b,      
					  float x,float y,float z,	
					  float vx,float vy,float vz,	
					  float ax,float ay,float az,	
					  float size,						
					  float lifetime,			
					  float dec					
							)
{
	if( index >= 0 && index < m_numparticle )
	{
		m_data[index].r=r;
		m_data[index].g=g;
		m_data[index].b=b;
		m_data[index].x=x;
		m_data[index].y=y;
		m_data[index].z=z;
		m_data[index].vx=vx;
		m_data[index].vy=vy;
		m_data[index].vz=vz;
		m_data[index].ax=ax;
		m_data[index].ay=ay;
		m_data[index].az=az;
		m_data[index].lifetime=lifetime;
		m_data[index].size=size;
		m_data[index].dec=dec;
		return true;
	}
	return false;

}