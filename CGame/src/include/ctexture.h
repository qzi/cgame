#ifndef __CTEXTURE_H_
#define __CTEXTURE_H_

#include	<list>
#include	<string>

// ==============================================
// CTexture - texture class object.
// ==============================================

class CTexture
{
public:
	// constructors/destructor
	CTexture( void ) { }
	CTexture( const char *texname ) { m_name = texname; }
	CTexture( unsigned int texid, const char *texname )	{ m_id = texid; m_name = texname; }
	~CTexture( void );
	unsigned int	GetTexId( void ) { return m_id; }
	const char		*GetName( void ) { return m_name.c_str(); }


public:
	// members variables
	unsigned int	m_id;			// texture id
	std::string		m_name;			// texture name

};



// ==============================================
// CTextureManager - OpenGL texture manager.
// ==============================================

class CTextureManager
{
protected:
	// constructor/destructor
	CTextureManager( void ) { Initialize(); }
	virtual ~CTextureManager( void ) { CleanAllTextures(); }

public:
	// singleton functions
	static CTextureManager	*GetInstance( void );
	static void				FreeInstance( void );


	// functions
	void			Initialize( void );
	unsigned int	LoadTexture( const char *filename );
	void			DeleteTexture( unsigned int id );
	void			CleanAllTextures( void );


private:
	// linked texture list
	typedef std::list<CTexture *>	TextureList;
	typedef TextureList::iterator	TListItor;

	TextureList						m_texlist;

	// singleton
	static CTextureManager			*m_singleton;

};



// global function using the texture manager
inline unsigned int LoadTexture( const char *filename )
{
	return CTextureManager::GetInstance()->LoadTexture( filename );
}

#endif	// __CTEXTURE_H_