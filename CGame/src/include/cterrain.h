#ifndef __CTERRAIN_H_
#define __CTERRAIN_H_

#include "cimage.h"

class CTerrain{
public:
	CTerrain();
	~CTerrain();
	
	// inital Terrain
	bool initTerrain();

	// set the size of the terrain
	void setSize(unsigned int width,unsigned int cell);
	
	// load the .raw file
	bool loadRawFile( const char * fileName );

	// load the texture
	bool loadTexture( const char * fileName );

	// get the height information of point(x,y)
	int getHeight( int x,int y );
	
	// set the coordinate of texutre
	void setTexCoord(float x,float z);

	// render the terrain
	void render();

private:
	unsigned int	m_nWidth;			// mesh numbers
	unsigned int	m_nCellWidth;		// the width of each mesh
	unsigned char *  m_pHeightMap;		// the height

public:
	CImage		m_texture;			// load the texture
	
};
#endif	//__CTERRAIN_H_