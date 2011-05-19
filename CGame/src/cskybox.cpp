#include "cSkybox.h"
#include <gl/glut.h>

CSkybox::CSkybox(void):length(2.5f),width(2.5f),height(2.5f)
{
}

CSkybox::~CSkybox(void)
{
	 //ɾ�����������ռ�õ��ڴ�
		for(int i =0 ;i< 5; i++)
		{
			m_texture[i].FreeImage();
			glDeleteTextures(1,&m_texture[i].ID);
		}
}

bool CSkybox::Init()
{
	char* fileName[] = {"data/back.bmp","data/front.bmp","data/top.bmp","data/left.bmp","data/right.bmp"};

	for(int i=0; i < 5; i++)
	{
		m_texture[i].isLoadBMPFile(fileName[i]);

		glGenTextures(1, &m_texture[i].ID);                            // ����һ������������� 
	
		glBindTexture(GL_TEXTURE_2D,m_texture[i].ID);
		/** �����˲� */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
		/** �������� */
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_texture[i].m_nImageWidth,
			m_texture[i].m_nImageHeight, GL_RGB, GL_UNSIGNED_BYTE,	m_texture[i].m_uData);
	}
	return true;
}

void  CSkybox::CreateSkyBox()
{
	/** ��ʼ���� */
	glPushMatrix();
// 	glTranslatef(m_CameraPos.x,m_CameraPos.y,m_CameraPos.z);


	/** ���Ʊ��� */
	glBindTexture(GL_TEXTURE_2D, m_texture[0].ID);
	glBegin(GL_QUADS);		

	/** ָ����������Ͷ������� */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(  width, -height, -length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(  width,  height, -length); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f( -width,  height, -length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( -width, -height, -length);

	glEnd();

	/** ����ǰ�� */
	glBindTexture(GL_TEXTURE_2D, m_texture[1].ID);
	glBegin(GL_QUADS);	

	/** ָ����������Ͷ������� */
	glTexCoord2f(1.0f, 0.0f); glVertex3f( -width, -height, length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( -width,  height, length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(  width,  height, length); 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(  width, -height, length);

	glEnd();

	/** ���ƶ��� */
	glBindTexture(GL_TEXTURE_2D,  m_texture[2].ID);
	glBegin(GL_QUADS);		

	/** ָ����������Ͷ������� */
	glTexCoord2f(0.0f, 1.0f); glVertex3f(  width, height, -length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(  width, height,  length); 
	glTexCoord2f(1.0f, 0.0f); glVertex3f( -width, height,  length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( -width, height, -length);

	glEnd();

	/** �������� */
	glBindTexture(GL_TEXTURE_2D, m_texture[3].ID);
	glBegin(GL_QUADS);		

	/** ָ����������Ͷ������� */
	glTexCoord2f(1.0f, 1.0f);  glVertex3f( -width,  height,	-length);		
	glTexCoord2f(0.0f, 1.0f);  glVertex3f( -width,  height,  length); 
	glTexCoord2f(0.0f, 0.0f);  glVertex3f( -width, -height,  length);
	glTexCoord2f(1.0f, 0.0f);  glVertex3f( -width, -height, -length);	

	glEnd();

	/** �������� */
	glBindTexture(GL_TEXTURE_2D, m_texture[4].ID);
	glBegin(GL_QUADS);		

	/** ָ����������Ͷ������� */
	glTexCoord2f(0.0f, 0.0f); glVertex3f( width, -height, -length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( width, -height,  length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( width,  height,  length); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f( width,  height, -length);
	glEnd();

	glPopMatrix();                 /** ���ƽ��� */
}
