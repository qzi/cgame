#ifndef CBULLET_H
#define CBULLET_H

class CBullet{
public:
	CBullet();
	CBullet( float x, float y, float z );
	~CBullet();
	void SetPosition( float x, float y, float z );
	void SetVelocity( float vx, float vy, float vz );
	void DrawBullet();
	
	// position
	float m_x;
	float m_y;
	float m_z;
	
	// velocity
	float m_vx;
	float m_vy;
	float m_vz;
};




#endif	//CBULLET_H