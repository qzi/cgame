#ifndef __CIMAGE_H_
#define __CIMAGE_H_

#define BITMAP_ID 0x4D42	/**< 位图文件的标志 */

#pragma warning(disable:4996)

class CImage
{
	public:
		CImage();
		~CImage();
		bool isLoadBMPFile(const char *filename);
		void FreeImage();

	public:
		int m_nImageWidth;                  /**< 图像宽度 */
		int m_nImageHeight;                 /**< 图像高度 */
		unsigned char *m_uData;            /**< 指向图像数据的指针 */

		unsigned int ID;                 /**< 用于记录生成纹理的ID号 */

};

#endif //__CIMAGE_H_
