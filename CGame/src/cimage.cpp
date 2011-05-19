#include <stdio.h>
#include <Windows.h>

#include "cimage.h"

CImage::CImage():m_uData(NULL),m_nImageWidth(0),m_nImageHeight(0)
{
	/*MessageBox(NULL,"cimage start","start",MB_OK);*/
}

CImage::~CImage()
{
	FreeImage();//释放图像数据用掉的内存
}

bool CImage::isLoadBMPFile(const char *filename)
{
	FILE *pFile = NULL;

	/** 创建位图文件信息和位图文件头结构 */
	BITMAPINFOHEADER bitmapInfoHeader;
	BITMAPFILEHEADER header;

	/** 打开文件,并检查错误 */
	pFile = fopen(filename, "rb");
	if(pFile == 0) return false;

	/** 读入位图文件头信息 */ 
	fread(&header, sizeof(BITMAPFILEHEADER), 1, pFile);

	/** 检查该文件是否为位图文件 */
	if(header.bfType != BITMAP_ID)
	{
		fclose(pFile);             /**< 若不是位图文件,则关闭文件并返回 */
		return false;
	}

	/** 读入位图文件信息 */
	fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, pFile);

	/** 保存图像的宽度和高度 */
	m_nImageWidth = bitmapInfoHeader.biWidth;
	m_nImageHeight = bitmapInfoHeader.biHeight;

	/** 确保读取数据的大小 */
	if(bitmapInfoHeader.biSizeImage == 0)
		bitmapInfoHeader.biSizeImage = bitmapInfoHeader.biWidth * bitmapInfoHeader.biHeight * 3;

	/** 将指针移到数据开始位置 */
	fseek(pFile, header.bfOffBits, SEEK_SET);

	/** 分配内存 */
	m_uData = new unsigned char[bitmapInfoHeader.biSizeImage];

	/** 检查内存分配是否成功 */
	if(!m_uData)                        /**< 若分配内存失败则返回 */
	{
		delete[] m_uData;
		fclose(pFile);
		return false;
	}

	/** 读取图像数据 */
	fread(m_uData, 1, bitmapInfoHeader.biSizeImage, pFile);

	unsigned char textureColors = 0;/**< 用于将图像颜色从BGR变换到RGB */

	/** 将图像颜色数据格式进行交换,由BGR转换为RGB */
	for(int index = 0; index < (int)bitmapInfoHeader.biSizeImage; index+=3)
	{
		textureColors = m_uData[index];
		m_uData[index] = m_uData[index + 2];
		m_uData[index + 2] = textureColors;
	}

	fclose(pFile);       /**< 关闭文件 */
	return true;         /**< 成功返回 */
}

/** 释放内存 */
void CImage::FreeImage()
{
	/** 释放分配的内存 */
	if(m_uData)
	{
		delete[] m_uData;
		m_uData = NULL;
	}
}

