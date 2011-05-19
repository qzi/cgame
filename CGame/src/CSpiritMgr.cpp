#include "cmodel.h"
#include "CSpiritMgr.h"
#include <gl/glut.h>



//////////////////////////////////////////////////////////////////////////
// CSprite

CSpirit::CSpirit():m_x(0.0f),m_y(0.0f),m_z(0.0f),m_Velocity(1.0f)
{
	m_pModel = NULL;
	m_pBasePath = NULL;
	m_pFileName = NULL;
}

CSpirit::CSpirit( char * pathname, char * filename )
{
	m_pBasePath = pathname;
	m_pFileName = filename;
	m_bInitialized = FALSE;
}

CSpirit::~CSpirit()
{
	if ( m_pModel != NULL )
	{
		delete m_pModel;
		m_pModel = NULL;
	}
	m_pBasePath = NULL;
	m_pFileName = NULL;
}

void CSpirit::SetSpirites( char * pathname, char * filename )
{
	m_pBasePath = pathname;
	m_pFileName = filename;
}


void CSpirit::InitSprit()
{
	if ( this->m_bInitialized == FALSE )
	{
		m_pModel = new CModel();
		m_pModel->InitialModel( m_pBasePath, m_pFileName );
		m_bInitialized = TRUE;
	}
}

void CSpirit::DrawSprite()
{
	if( this->m_bInitialized == TRUE )
	{	glPushMatrix();

				glTranslatef( m_x, m_y,m_z );

					glPushMatrix();
					
						glRotatef( m_degree, m_Rx, m_Ry, m_Rz );
						m_pModel->Render();

					glPopMatrix();

		glPopMatrix();
	}
	else
		this->InitSprit();
}

void CSpirit::SetPosition( float x, float y, float z )
{
	m_x = x;
	m_y = y;
	m_z = z;
}

// set the three scale of the three dimension
void CSpirit::SetScale( float scale )
{
	if ( this->m_bInitialized == TRUE )
	{
		m_pModel->m_Scale = scale;
	}else
		;//break;
}

void CSpirit::SetVelocity( float velocity )
{
	m_Velocity = velocity;
}

void CSpirit::SetRotate( float degree, float x, float y, float z )
{
	m_degree	=	degree;
	m_Rx			=	x;
	m_Ry			=	y;
	m_Rz			=	z;
}



//////////////////////////////////////////////////////////////////////////
// CSpriteMgr

CSpiriteMgr::CSpiriteMgr()
{
	for( pCSListIter iter = m_pSpirites.begin();
		iter != m_pSpirites.end(); iter++ ){
		
			(*iter) = NULL;
	}
}

CSpiriteMgr::~CSpiriteMgr()
{
	if ( m_pSpirites.empty() != FALSE )
	{
		CleanupSprites();
	}

}

void CSpiriteMgr::AddSpirit( CSpirit * sprite )
{	
	if ( sprite != NULL && sprite->m_bInitialized != TRUE )
	{
		m_pSpirites.push_back( sprite );		// add to list at the back
		if ( m_pSpirites.back()->m_bInitialized == FALSE )
		{
			m_pSpirites.back()->InitSprit();		// initial the spirit
		}
	}
	else{
			// dothing warning // lack
	}
}

void CSpiriteMgr::UpdateSprites()
{
	for ( pCSListIter iter= m_pSpirites.begin();
		iter != m_pSpirites.end(); iter++ )
	{
		if ( (*iter)->m_bInitialized == TRUE)
		{
			(*iter)->DrawSprite();
		}else
		{
			continue;
		}
	}
}

void CSpiriteMgr::CleanupSprites()
{
	for ( pCSCListIter citer = m_pSpirites.begin();
		citer != m_pSpirites.end(); citer++ )
	{
		if ( (*citer) != NULL )
		{
			delete (*citer);
		}
	}
	m_pSpirites.clear();
}

// without delete the memory of the sppirit when next circle ended;
void CSpiriteMgr::DeleteSpirit( CSpirit * sprite )
{
	for ( pCSListIter iter = m_pSpirites.begin(); 
		iter != m_pSpirites.end();  ++iter )
	{
		if ( (*iter) == sprite )
		{
			m_pSpirites.erase( iter++ );
			break;			// important for ++iter;
		}
	}
}


CSpirit * NewCSpirit( CSpirit * spirte, char * basepath, char * filename ){

	CSpirit * p = spirte;
	if( p == NULL )
		p = new CSpirit( basepath, filename );
	return p;
}