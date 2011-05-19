#include <stdio.h>
#include <stdlib.h>
#include <gl/glut.h>
#include <Windows.h>
#include "common.h"
#include "cterrain.h"


CTerrain::CTerrain():m_pHeightMap(NULL)
{
	// set the size of the terrain
	setSize( MAP_WIDTH, CELL_WIDTH);

	// allocat the memory of the terrain
	m_pHeightMap = new unsigned char[ m_nWidth * m_nWidth ];

	memset(m_pHeightMap,0,sizeof(m_pHeightMap));
}

CTerrain::~CTerrain()
{
	// clear the memory
	if ( m_pHeightMap )
	{
		delete[] m_pHeightMap;
		m_pHeightMap = NULL;
	}

	// delete the texture and memory
	m_texture.FreeImage();
	glDeleteTextures( 1, &m_texture.ID );

}

bool CTerrain::loadRawFile( const char * fileName )
{
	FILE * pFile = NULL;

	// open the file
	pFile = fopen( fileName, "rb" );

	// check the error
	if ( pFile != NULL )
	{	
		// read the height file
		//fread( m_pHeightMap, 1, m_nWidth*m_nWidth, pFile );
		fread( m_pHeightMap, 1, m_nWidth*m_nWidth, pFile );

		// get the error code 
		int result = ferror( pFile );

		//　check the error code
		if ( result )
		{
			MessageBox(NULL ,"无法获取高度数据　！","错误",MB_OK);
			exit(0);

		}

		// close the file
		fclose(pFile);
		return true;

	}else{
		MessageBox( NULL , "打开高度图文件失败 !","错误！",MB_OK);
		exit(0);
	}

}

bool CTerrain::loadTexture( const char * fileName )
{
	if ( !m_texture.isLoadBMPFile(fileName))
	{
		MessageBox( NULL,"装载位图文件失败！","错误!",MB_OK);
		exit(0);
	}

	glGenTextures( 1, &m_texture.ID );	// gennerate the texture object id

	glBindTexture( GL_TEXTURE_2D ,m_texture.ID );
	// control the filter
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB,m_texture.m_nImageWidth,
		m_texture.m_nImageHeight,GL_RGB,GL_UNSIGNED_BYTE,
		m_texture.m_uData);

	return true;
}

bool CTerrain::initTerrain()
{
	// load the height file
	loadRawFile("data/terrain.raw");
	/*loadRawFile("data/terrain2.raw");*/

	// load the texture
	loadTexture("data/terrain.bmp");

	return true;
}

// get the height information of the terrain
int CTerrain::getHeight( int x,int y )
{
	if ( !m_pHeightMap )
		return 0;

	int X = x % m_nWidth;
	int Y = y % m_nWidth;

	if ( !m_pHeightMap)
		return 0;

	// return current height
	return m_pHeightMap[( X + Y * m_nWidth )];
}

void CTerrain::setSize( unsigned int width,unsigned int cell )
{
	m_nWidth = width;
	m_nCellWidth = cell;
}

// set the coordinate of texture
void CTerrain::setTexCoord( float x,float z )
{

	glTexCoord2f(   (float)x / (float)m_nWidth,	
		-(float)z / (float)m_nWidth	);
}

// render the terrain
void CTerrain::render()
{
	int X = 0,Y = 0;		// the coordinate of the height map(raw file)
	float x,y,z;
	bool bSwitchSides = true;

	glBindTexture( GL_TEXTURE_2D,m_texture.ID );
	glDisable( GL_LIGHTING );

	// draw the triangle strip
	glBegin( GL_TRIANGLE_STRIP );
	
	///** check the height map */
	if(!m_pHeightMap) 
	{
			MessageBox( NULL,"装载高度图文件失败！","错误!",MB_OK);
			return;
	}

	// set the vertex fo triangle 
	for ( X = 0; X <= m_nWidth; X += m_nCellWidth )
	{
		/// draw a clonium
		if ( !bSwitchSides)
		{
			for ( Y = 0; Y <= m_nWidth; Y += m_nCellWidth )
			{
				// vertex( X+m_nCellWidth, Y, Z )
				x = X + m_nCellWidth;
				y = getHeight( X + m_nCellWidth, Y );
				z = Y;

				// set the texture coordinate and vertex 
				setTexCoord( (float)x, (float)z );
				glVertex3f( x, y, z );

				// vertex( X ,Y ,Z)
				x = X;
				y = getHeight( X, Y );
				z = Y;

				// set the texture coordinate and vertex
				setTexCoord( (float)x, (float)z);
				glVertex3f( x, y, z );				
			}

		}else
		{
			for ( Y = m_nWidth; Y >= 0; Y -= m_nCellWidth )
			{
				// vertex( X ,Y ,Z);
				x = X;
				y = getHeight( X, Y );
				z = Y;

				//set the texture coordinate and vetex
				setTexCoord( (float)x, (float)z );
				glVertex3f( x, y, z );

				// vertex( X + m_nCellWidth, Y, Z )
				x = X + m_nCellWidth;
				y = getHeight( X + m_nCellWidth, Y );
				z = Y;

				// set the texture corrdinate and vertex
				setTexCoord( (float)x, (float)z );
				glVertex3f( x, y, z );
			}
		}
		bSwitchSides = !bSwitchSides;
	}
	glEnd();
}