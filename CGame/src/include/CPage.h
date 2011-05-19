#ifndef CPAGE_H
#define CPAGE_H

#define WIDTH			(1024)					// ÿһ��ҳ�Ŀ����������
#define HEIGHT			(1024)
#define WIDTH_NUM		(7)					// �������
#define HEIGHT_NUM		(7)					// �ߵ�����

/* ���Ͷ��� */
#include <list>
#include "cpoint.h"
#include "Landscape.h"


typedef struct node{
	CPoint pos;	// the position of the LeftTop corner
	int w, h;	// the width and height per page
	float color[3];
	unsigned char * data;	// ��ҳ��ָ���ͼ������		// Note that it's not NULL
	Landscape landscape;
}Page;

typedef std::list<Page> PageList;					// the list of page
typedef std::list<Page>::const_iterator PageListCIter;
typedef std::list<Page>::iterator PageListIter;

class CPageMgr
{
public:
	CPageMgr();
	//friend void GetCurrentPos( Point * point);	// ����ǰ�����λ��
	//friend void DrawLandScale( float x, float y, float z, float w, float h );
	//friend void DrawLandScaleTest( float x, float y, float z, float w, float h, const float color[] );
	void DrawNinthGrid();		// ������λ�õľŹ���
	void CheckLoadPage(float x, float y);			// whether or not we should load the page :return TRUE is yes; return FALSE is no;
	void LoadPage(float x, float y);		// Load the page according the position
	void EnsurePages();			// ��ʼ��
	void Render();					// ��ͼ
	void ClearDirtyPages();
	void SetCameraPos(float x, float y, float z);
    void SetViewPos(float x, float y, float z); 
private:
	int mRow;						// 
	int mCol;						// 
	PageList mPages;				// the list of all the pages
	bool mInitialized ;				// 


	CPoint m_CameraPos;
	CPoint m_ViewPos;

};

#endif	// CPAGE_H