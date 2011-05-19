#pragma once //用来防止头文件被多次include

#include "cimage.h"
#include "ccamera.h"

class CSkybox
{
public:
	CSkybox(void);
	~CSkybox(void);

	bool Init();//初始化

	void  CreateSkyBox();

private:

	CImage  m_texture[1];   // 天空纹理 
	CCamera m_CameraPos;    // 当前摄像机位置 *

	float       length;         // 长度 
	float       width;          // 宽度 
	float       height;         // 高度 
};
