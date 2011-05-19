#include <Windows.h>
#include<gl/gl.h> 
#include "cfont.h"

CFont::CFont()
{

}

CFont::~CFont()
{
	if(m_hFont)
		DeleteObject(m_hFont); /**< ɾ�������� */
}

bool CFont::InitFont()
{
	// create the font
	m_hFont = CreateFont(24,		// the height of the font
		0,							// the width of the font
		0,							// Angle Of Escapement */
		0,							//Orientation Angle */
		FW_BOLD,				/**< ��������� */
		FALSE,					/**< �Ƿ�ʹ��б�� */
		FALSE,					/**< �Ƿ�ʹ���»��� */
		FALSE,					/**< �Ƿ�ʹ��ɾ���� */
		GB2312_CHARSET,			/**< �����ַ��� */
		OUT_TT_PRECIS,			/**< ������� */
		CLIP_DEFAULT_PRECIS,	/**< �ü����� */
		ANTIALIASED_QUALITY,	/**< ������� */
		FF_DONTCARE|DEFAULT_PITCH,		/**< Family And Pitch */
		"����");					// name
	if(!m_hFont)
		return false;				// if fail 

	return true;
}


void CFont::PrintText(char *string, float x, float y)
{
	HBITMAP hBitmap,hOldBmp;// define two handle of font
	BITMAP bm;				// the struct of bitmap
	SIZE size;				// the size 

	/** ��ó����е�״̬ */
	GLboolean lp,tp;
	glGetBooleanv(GL_LIGHTING,&lp);
	glGetBooleanv(GL_TEXTURE_2D,&tp);
	HDC hDC = ::CreateCompatibleDC(0); /**< �ݴ��豸���� */

	/** ���������һЩ���� */
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(0,0,-10.0f);
	glDisable(GL_LIGHTING);  /**< �رչ��� */
	glDisable(GL_TEXTURE_2D);/**< �ر����� */
	glDisable(GL_DEPTH_TEST);/**< �ر���Ȳ��� */ 

	SelectObject(hDC, m_hFont); /**< ѡ������ */
	GetTextExtentPoint32(hDC, string, strlen(string), &size);/**< ��ȡ�ַ�λͼ��С */
	hBitmap = CreateBitmap(size.cx, size.cy,1, 1, NULL); /**< ������hDC��ص�ɫλͼ */
	hOldBmp = (HBITMAP)SelectObject(hDC,hBitmap); /**< ѡ��λͼ */
	
	SetBkColor(hDC, RGB(0, 0, 0));              /**< ����ɫΪ��ɫ */
	SetTextColor(hDC, RGB(255, 255, 255));      /**< ������ɫ��ɫ */
	SetBkMode(hDC, OPAQUE);                     /**< �õ�ǰ�ı�����ɫ��䱳�� */
	TextOut(hDC, 0, 0, string, strlen(string)); /**< ������ֵ��ݴ�hDC */
	
	/** ������λͼ���ݽṹ */
	GetObject(hBitmap, sizeof(bm), &bm);
	size.cx = (bm.bmWidth + 31) & (~31); /**< ��Ե���� */
	size.cy = bm.bmHeight;
	int bufsize = size.cx * size.cy/8;  /**< ͼ�����ݳ��� */

	/**�����嵥ɫλͼ�ṹ */  
	struct {
		BITMAPINFOHEADER bih;
		RGBQUAD col[2];
	}bic;

	/** ��ȡ��ɫλͼ�ṹ��Ϣ */
	BITMAPINFO *binf = (BITMAPINFO *)&bic;
	binf->bmiHeader.biSize = sizeof(binf->bmiHeader); /**< �޸Ľṹ��Ϣ */
	binf->bmiHeader.biWidth = bm.bmWidth;
	binf->bmiHeader.biHeight = bm.bmHeight;
	binf->bmiHeader.biPlanes = 1;
	binf->bmiHeader.biBitCount = 1;       /**< ��ɫ */
	binf->bmiHeader.biCompression = BI_RGB;  /**< ��ɫ��ʽ */
	binf->bmiHeader.biSizeImage = bufsize;
	binf->bmiHeader.biXPelsPerMeter = 1;
	binf->bmiHeader.biYPelsPerMeter = 1;
	binf->bmiHeader.biClrUsed = 0;
	binf->bmiHeader.biClrImportant = 0;

	/** ����ͼ�����ݿ� */ 
	UCHAR* pBmpBits = new UCHAR[bufsize];	
	memset(pBmpBits, 0, sizeof(UCHAR)*bufsize);
	/** ���豸�޹����ݱ�����pBmpBitsָ������ݿ��� */
	::GetDIBits(hDC, hBitmap, 0, bm.bmHeight, pBmpBits, binf,DIB_RGB_COLORS);

	/** ��ʾ�ַ��� */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); /**< ָ�����ش洢ģʽ */
	glRasterPos2f(x,y);                  /**< ��λ */
	glBitmap(size.cx, size.cy, 0.0, 0.0, 0.0, 0.0, pBmpBits); /**< λͼ��ʾ */
	delete pBmpBits;                       /**< ɾ��ָ�� */
	SelectObject(hDC, hOldBmp);           /**< �ָ�ԭ��λͼ��Ϣ */
	DeleteObject(hBitmap);
	::DeleteDC(hDC);
	/** �ָ�һЩ״̬ */
	if(lp)
		glEnable(GL_LIGHTING);     /**< �������� */     
	if(tp)
		glEnable(GL_TEXTURE_2D);   /**< �������� */
	glEnable(GL_DEPTH_TEST);       /**< ������Ȳ��� */
	glPopMatrix();
}
