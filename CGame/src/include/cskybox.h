#pragma once //������ֹͷ�ļ������include

#include "cimage.h"
#include "ccamera.h"

class CSkybox
{
public:
	CSkybox(void);
	~CSkybox(void);

	bool Init();//��ʼ��

	void  CreateSkyBox();

private:

	CImage  m_texture[1];   // ������� 
	CCamera m_CameraPos;    // ��ǰ�����λ�� *

	float       length;         // ���� 
	float       width;          // ��� 
	float       height;         // �߶� 
};
