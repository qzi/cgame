#include <stdio.h>
#include <Windows.h>

#include "cimage.h"

CImage::CImage():m_uData(NULL),m_nImageWidth(0),m_nImageHeight(0)
{
	/*MessageBox(NULL,"cimage start","start",MB_OK);*/
}

CImage::~CImage()
{
	FreeImage();//�ͷ�ͼ�������õ����ڴ�
}

bool CImage::isLoadBMPFile(const char *filename)
{
	FILE *pFile = NULL;

	/** ����λͼ�ļ���Ϣ��λͼ�ļ�ͷ�ṹ */
	BITMAPINFOHEADER bitmapInfoHeader;
	BITMAPFILEHEADER header;

	/** ���ļ�,�������� */
	pFile = fopen(filename, "rb");
	if(pFile == 0) return false;

	/** ����λͼ�ļ�ͷ��Ϣ */ 
	fread(&header, sizeof(BITMAPFILEHEADER), 1, pFile);

	/** �����ļ��Ƿ�Ϊλͼ�ļ� */
	if(header.bfType != BITMAP_ID)
	{
		fclose(pFile);             /**< ������λͼ�ļ�,��ر��ļ������� */
		return false;
	}

	/** ����λͼ�ļ���Ϣ */
	fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, pFile);

	/** ����ͼ��Ŀ�Ⱥ͸߶� */
	m_nImageWidth = bitmapInfoHeader.biWidth;
	m_nImageHeight = bitmapInfoHeader.biHeight;

	/** ȷ����ȡ���ݵĴ�С */
	if(bitmapInfoHeader.biSizeImage == 0)
		bitmapInfoHeader.biSizeImage = bitmapInfoHeader.biWidth * bitmapInfoHeader.biHeight * 3;

	/** ��ָ���Ƶ����ݿ�ʼλ�� */
	fseek(pFile, header.bfOffBits, SEEK_SET);

	/** �����ڴ� */
	m_uData = new unsigned char[bitmapInfoHeader.biSizeImage];

	/** ����ڴ�����Ƿ�ɹ� */
	if(!m_uData)                        /**< �������ڴ�ʧ���򷵻� */
	{
		delete[] m_uData;
		fclose(pFile);
		return false;
	}

	/** ��ȡͼ������ */
	fread(m_uData, 1, bitmapInfoHeader.biSizeImage, pFile);

	unsigned char textureColors = 0;/**< ���ڽ�ͼ����ɫ��BGR�任��RGB */

	/** ��ͼ����ɫ���ݸ�ʽ���н���,��BGRת��ΪRGB */
	for(int index = 0; index < (int)bitmapInfoHeader.biSizeImage; index+=3)
	{
		textureColors = m_uData[index];
		m_uData[index] = m_uData[index + 2];
		m_uData[index + 2] = textureColors;
	}

	fclose(pFile);       /**< �ر��ļ� */
	return true;         /**< �ɹ����� */
}

/** �ͷ��ڴ� */
void CImage::FreeImage()
{
	/** �ͷŷ�����ڴ� */
	if(m_uData)
	{
		delete[] m_uData;
		m_uData = NULL;
	}
}

