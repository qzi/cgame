#include <time.h>
#include <math.h>
#include <list>

#include "CPage.h"
#include "LSUtility.h"
#include "gl/glut.h"



CPageMgr::CPageMgr(){

	mInitialized = false;
	srand((unsigned)time(0));
}

void CPageMgr::CheckLoadPage(float x, float z)
{
	PageListIter findIter;
	bool bFinded = false;
	for(PageListIter iter = mPages.begin(); iter != mPages.end(); iter++ )
	{
		if(iter->pos.x == x && iter->pos.z == z)
		{
			findIter = iter;
			bFinded = true;
			break;
		}
	}


	if(bFinded) // move the page to begin of the list
		mPages.splice(mPages.begin(), mPages, findIter);
	else
	{
		// load new page if not find 
		LoadPage(x, z);
	}
}


void CPageMgr::LoadPage(float x, float z)
{
	
	Page page;
	page.pos.x = x;
	page.pos.z = z;
	page.pos.y = 0;
	page.color[0] = ((float)(rand() % 255)) / 255;
	page.color[1] = ((float)(rand() % 255)) / 255;
	page.color[2] = ((float)(rand() % 255)) / 255;

	// 加载高度图数据
	roamInit(page.landscape, gHeightMap);
	
    // 新加载的Page插入到队列的前面
	mPages.push_front(page);
}

void CPageMgr::Render()
{
	EnsurePages();
	DrawNinthGrid();
}

void DrawLandScaleTest( float x, float y, float z, float w, float h, const float color[] )
{
	glPushMatrix();

	glColor3f(color[0], color[1], color[2]);
	glTranslatef(x, y, z);
	glScalef(1.0f, 0.1f, h/w);
	glutSolidCube(w);

	glPopMatrix();
}

void CPageMgr::DrawNinthGrid( )
{
	for (  PageListIter iter = mPages.begin(); iter != mPages.end(); iter++ )
	{
		float centerX = iter->pos.x + WIDTH / 2;
		float centerZ = iter->pos.z + HEIGHT / 2;
		//DrawLandScaleTest(centerX, -20, centerZ, WIDTH, HEIGHT, iter->color);

		glPushMatrix();
		glTranslatef(iter->pos.x, 0, iter->pos.z);
		glScalef((float)WIDTH/MAP_SIZE, (float)WIDTH/MAP_SIZE, (float)HEIGHT/MAP_SIZE);
        

		iter->landscape.Reset();
		iter->landscape.Tessellate(m_ViewPos.x - iter->pos.x, m_ViewPos.z - iter->pos.z);
		iter->landscape.Render();
		glPopMatrix();
	}
}


void CPageMgr::EnsurePages()
{
	// 获取摄像机位置
	
	/* floor the row and col */
	int tempRow = (int)floorf( m_CameraPos.z / HEIGHT );
	int tempCol = (int)floorf( m_CameraPos.x / WIDTH );

	
	/* draw from the leftbottom */
	if ((mRow != tempRow) || (mCol != tempCol) || !mInitialized)
	{
		mRow = tempRow;
		mCol = tempCol;

		float leftX = (float)( mCol - 1 ) * WIDTH;
		float tempZ = (float)( mRow - 1 ) * HEIGHT;
		for(int i = 0; i<3; i++)
		{
            float tempX = leftX;		
 			for(int j= 0; j<3; j++)
			{
				CheckLoadPage(tempX, tempZ);
                tempX += WIDTH;
			}
			tempZ += HEIGHT;
		}

		// 释放不再使用的Page
		ClearDirtyPages();
		
		mInitialized = true;
	}
}

void CPageMgr::ClearDirtyPages()
{
	int i=0;
	PageListIter iter = mPages.begin();
	// 找到第10个Page的位置
	for(; iter!= mPages.end(); iter++ )
	{
       i++;	   
	   if(i > 9) break;	   
	}

	// 删除第10个Page之后的所有Page
	if (i > 9)
		while(iter != mPages.end())
			iter = mPages.erase(iter);
}

void CPageMgr::SetCameraPos( float x, float y, float z )
{
	m_CameraPos.x = x;
	m_CameraPos.y = y;
	m_CameraPos.z = z;
}

void CPageMgr::SetViewPos( float x, float y, float z )
{
	m_ViewPos.x = x;
	m_ViewPos.y = y;
	m_ViewPos.z = z;
}



