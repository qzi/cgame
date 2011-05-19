#ifndef CSPIRITEMGR_H
#define CSPIRITEMGR_H

#include <list>

#define TRUE		1
#define FALSE		0
#define NULL		0


/* forword declaration */
class CModel;
class CSpirit;

// instead the new , just new once in the game circle
CSpirit * NewCSpirit( CSpirit * spirte, char * basepath, char * filename );

/* typdef */
typedef std::list<CSpirit *>::iterator pCSListIter;
typedef std::list<CSpirit *>::const_iterator pCSCListIter;

//////////////////////////////////////////////////////////////////////////
// the managerment of spirit
class CSpiriteMgr{
public:
	CSpiriteMgr();
	~CSpiriteMgr();

	void AddSpirit( CSpirit * sprite );

	void DeleteSpirit( CSpirit * sprite );

	void UpdateSprites();

	void CleanupSprites();

	std::list<CSpirit *> m_pSpirites;
};

//////////////////////////////////////////////////////////////////////////
// spirit
class CSpirit{
public:
	
	CSpirit();
	CSpirit( char * pathname, char * filename);
	~CSpirit();
	
	void		SetSpirites( char * pathname, char * filename );	// set the name fo the spirites
	void		SetPosition( float x, float y, float z );			// set the position lack
	void		SetScale( float scale );							// set the scale of the three demension
	void		SetRotate(float degree, float x, float y, float z );// set orientation
	void		SetVelocity( float velocity );						// set the velocity lack

	void		InitSprit();										// initial the engine
	void		DrawSprite();

	float		GetX()			{ return m_x; };
	float		GetY()			{ return m_y; };
	float		GetZ()			{ return m_z; };
	float		GetVelocity()	{ return m_Velocity; };

	float		m_x,m_y,m_z;								// the position
	float		m_Rx,m_Ry,m_Rz,m_degree;					// the orientation
	float		m_Velocity;									// the velocity of the object
	CModel *	m_pModel;									// the object
	bool		m_bInitialized;								// is there allcate the memory

private:
	char *		m_pBasePath;
	char *		m_pFileName;
};

#endif	//CSPIRITEMGR_H