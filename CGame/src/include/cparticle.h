#ifndef __CPARTICLE_H_
#define __CPARTICLE_H_

#include "cimage.h"

//////////////////////////////////////////////////////////////////////////
// the struct of the particle
struct Particle{
	float x,y,z;		// the position of the particle
	unsigned int r,g,b;	// the color of the particle
	float vx,vy,vz;		// the velocity of the particle
	float ax,ay,az;		// the Acceleration of the particle
	float lifetime;		// the lifetime of  the particle
	float size;			// the size of particle
	float dec;			// the decrease velocity
};
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// the class of the particle
class CParticle{
public:
	CParticle();
	~CParticle();
	
	// create the array of the particle
	int Create( long num );

	// set the color and get it
	int SetColor( int r, int g, int b );
	int SetColor( int index, int r, int g, int b );
	int GetColor( int index, int &r, int &g, int &b );

	// set the velocity and get it 
	int SetVelocity(float vx,float vy,float vz);
	int SetVelocity(int index,float vx,float vy,float vz);
	int GetVelocity(int index,float &vx,float &vy,float &vz);

	// set the positon and get it 
	int SetPosition(float x,float y,float z);
	int SetPosition(int index,float x,float y,float z);
	int GetPosition(int index,float &x,float &y,float &z);

	//  set the acceleration and get it 
	int SetAcceleration(float ax,float ay,float az);
	int SetAcceleration(int index,float ax,float ay,float az);
	int GetAcceletation(int index,float &ax,float &ay,float &az);

	// set the size and get it 
	int SetSize(float size);
	int SetSize(int index,float size);
	int GetSize(int index,float &size);

	// set decrease velocity and get it 
	int SetDec(float dec);
	int SetDec(int index,float dec);
	int GetDec(int index,float &dec);

	// set the lifetime and get it 
	int SetLifeTime(float lifetime);
	int SetLifeTime(int index,float lifetime);
	int GetLifeTime(int index,float &lifetime);

	// load the texture and get it 
	bool LoadTextures();
	unsigned int GetTexture( int index );

	// get the address of the array of the particle
	Particle * GetParticle(){
		return m_data;
	}

	int GetNumOfParticle(){
		return m_numparticle;
	}
	
	// set all the property
	int SetAll(int index,int r,int g,int b,      
		float x,float y,float z,	
		float vx,float vy,float vz,	
		float ax,float ay,float az,	
		float size,						
		float lifetime,			
		float dec					
		);
	// get all the property
	int GetAll(int index,					// index
		int &r,int &g,int &b,				// the color 
		float &x,float &y,float &z,			// position
		float &vx,float &vy,float &vz,		// velocity
		float &ax,float &ay,float &az,		// acceleration
		float &size,						// size
		float &lifetime,					// lifetime
		float &dec							// decrease
		);

private:
	CImage		m_texture[2];	// load the bitmap 
	Particle*	m_data;		// the pointer of the particle
	int			m_numparticle;	// the number of particle
};

#endif	// __CPARTICLE_H_