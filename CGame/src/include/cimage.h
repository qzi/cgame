#ifndef __CIMAGE_H_
#define __CIMAGE_H_

#define BITMAP_ID 0x4D42	/**< λͼ�ļ��ı�־ */

#pragma warning(disable:4996)

class CImage
{
	public:
		CImage();
		~CImage();
		bool isLoadBMPFile(const char *filename);
		void FreeImage();

	public:
		int m_nImageWidth;                  /**< ͼ���� */
		int m_nImageHeight;                 /**< ͼ��߶� */
		unsigned char *m_uData;            /**< ָ��ͼ�����ݵ�ָ�� */

		unsigned int ID;                 /**< ���ڼ�¼���������ID�� */

};

#endif //__CIMAGE_H_
