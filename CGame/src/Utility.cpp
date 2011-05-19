#include "Utility.h"


/* definition */

GLfloat gCameraPos[3] = { 0.0f, -92.0f, 5.0f };
GLfloat gViewPos[3] = {0.0f, -92.5f, 0.0f };
GLfloat gUpPos[3] = { 0.0f, 1.0f, 0.0f };

/*CCamera gCamera;*/
CCamera gCamera;

/* roam below */
//GLfloat gFovX = 90.0f;
FILE * pFileLog = NULL;
float gSpeed = 10.2;
DirectMode gDirectMode;
CPageMgr gPageMgr;
/* roam above */

/* cspirites */
CSpirit * gSpirites[3];
CSpiriteMgr * gSpiritMgr = NULL;
CBullet gBullet;
bool flag = false;

/* font */
CFont gFont;

/* cgui */
CEGUI::CGUI gGUI;

void GLUTRenderScene( void ){

	// render the scene
	RenderScene();

	// swap the offscene buffers
	glutSwapBuffers();
}

void GLUTReshape(int w, int h)
{
	glViewport( 0, 0, (GLsizei) w , (GLsizei) h  );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective( 45.f , (GLfloat) w/ (GLfloat) h, NEAR_CLIP, FAR_CLIP );

	glMatrixMode(GL_MODELVIEW); 

}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor (1.0f, 1.0f, 1.0f, 0.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//////////////////////////////////////////////////////////////////////////
	// fps
	CTimer::GetInstance()->Update();
	
	//////////////////////////////////////////////////////////////////////////
	// camera
	gCamera.setLook();
	

	// Set the camera
	//glPushMatrix();	// the camera
	//glMultMatrixf(gCamera.matrixCamera);

	//////////////////////////////////////////////////////////////////////////
	// spirites manager
	glPushMatrix();
	CVector3 viewVector = gCamera.getView() -gCamera.getPosition();
	viewVector.Normalize();

	gSpirites[0] = NewCSpirit( gSpirites[0], "./data/models/", "gl-14.3ds" );
	gSpirites[0]->SetPosition( gCamera.getPosition().x + 5 * viewVector.x,
		gCamera.getPosition().y + 5 * viewVector.y,gCamera.getPosition().z + 5 * viewVector.z );
	gSpirites[0]->SetRotate( -90.f, 0.f, 1.f, 0.f );
	//gSpirites[0]->SetScale( 1.2f );
	/*gSpirites[1] = NewCSpirit( gSpirites[1], "./TEST/", "gl-14c.3ds");
	gSpirites[1]->SetPosition( 0.0f,-360.0f,-30.0f);
	gSpirites[2] = NewCSpirit( gSpirites[2], "./TEST/", "cannon1.3ds");
	gSpirites[2]->SetPosition( 2.0f,-350.0f,-30.0f );
	gSpirites[2]->SetScale( 0.2f );*/

	gSpiritMgr->AddSpirit( gSpirites[0] );
	//gSpiritMgr->AddSpirit( gSpirites[1] );
	//gSpiritMgr->AddSpirit( gSpirites[2] );

	//gSpiriteMgr->DeleteSpirit( gSpirit[1] );  // without clean the memory

	gSpiritMgr->UpdateSprites();

	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	// bullet
	glPushMatrix();
		
		if ( !flag )
		{
			gBullet.SetPosition( gCamera.getPosition().x + 5 * viewVector.x,
				gCamera.getPosition().y + 5 * viewVector.y,gCamera.getPosition().z + 5 * viewVector.z );
			flag = true;
		}
		gBullet.SetVelocity( 0.f, 0.f, -0.5f );
		//gBullet.SetVelocity( viewVector.x, viewVector.y, viewVector.z );
		gBullet.DrawBullet();

	glPopMatrix();




	////////////////////////////////////////////////////////////////////////
	// paging roam system
	glPushMatrix();
		glTranslatef( 0.0f, -200.0f, 0.0f );
		gPageMgr.SetCameraPos( gCamera.getPosition().x,
			gCamera.getPosition().y, gCamera.getPosition().z );
		gPageMgr.SetViewPos( gCamera.getView().x,
			gCamera.getView().y, gCamera.getView().z );
		gPageMgr.Render();
	glPopMatrix();
		
	//////////////////////////////////////////////////////////////////////////
	// font
#pragma warning(disable:4996)
	glPushAttrib( GL_CURRENT_BIT );
		glColor3f( 0.f ,0.f, 0.f );
		int SrcWidth = glutGet( GLUT_WINDOW_WIDTH );
		int SrcHeight = glutGet( GLUT_WINDOW_HEIGHT );
		char PosX[20];
		sprintf( PosX, "PosX : %5.2f\0",gCamera.getPosition().x );
		gFont.PrintText( PosX, -4.f, 3.f );
		char PosY[20];
		sprintf( PosY, "PoxY : %5.2f\0",gCamera.getPosition().y );
		gFont.PrintText( PosY, -4.f, 2.75f );
		char PosZ[20];
		sprintf( PosZ, "PoxZ : %5.2f\0",gCamera.getPosition().z );
		gFont.PrintText( PosZ, -4.f, 2.5f );
		char fps[20];
		sprintf( fps, "Fps : %5.2f\0",CTimer::GetInstance()->GetFps() );
		gFont.PrintText( fps, -4.f, 2.25f );
	glPopAttrib();
#pragma warning(default:4996)
	
	//////////////////////////////////////////////////////////////////////////
	// cegui
	gGUI.GUIRender();
}

void KeyUp()
{
	gCamera.moveCamera( 5.0f );
}


void KeyDown()
{
	gCamera.moveCamera( -5.0f );
}

void KeyLeft()
{
	gCamera.yawCamera( -3.0f );
}


void KeyRight()
{
	gCamera.yawCamera( 3.0f );
}

void GLUTSpecial( int key, int x, int y ){

	switch( key )
	{
	case GLUT_KEY_LEFT:

		gDirectMode = LEFT;
		KeyLeft();
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:

		gDirectMode = RIGHT;
		KeyRight();
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:

		gDirectMode = UP;
		KeyUp();
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:

		gDirectMode = DOWN;
		KeyDown();
		glutPostRedisplay();
		break;
	}
}


void GLUTKeyboard(unsigned char key, int x, int y)
{
	switch (key) {
	  case 27:
		  exit(0);
		  break;
	  case 'w':
	  case 'W':

		  gCamera.pitchCamera( 1.0f );
		  glutPostRedisplay();
		  break;
	  case 's':
	  case 'S':

		  gCamera.pitchCamera( -1.0f );
		  glutPostRedisplay();
		  break;

	  case 'a':
	  case 'A':

		  gCamera.rollCamera( -1.0f );
		  glutPostRedisplay();
		  break;

	  case 'D':
	  case 'd':

		  gCamera.rollCamera( 1.0f );
		  glutPostRedisplay();
		  break;
	}
}

void InitScene( void )
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_TEXTURE_2D);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//float lightpos[]	= { 0.0f, 1000.0f, 0.0f };
	//float lightcolor[]	= { 1.0, 1.0, 1.0, 1.0 };

	//glLightfv( GL_LIGHT0, GL_POSITION, lightpos );
	//glLightfv( GL_LIGHT0, GL_DIFFUSE, lightcolor );
	//glLightfv( GL_LIGHT0, GL_SPECULAR, lightcolor );
	
	// load the terrain
	loadTerrain(MAP_SIZE, &gHeightMap);
	
	// initial the camera
	gCamera.setCamera( gCameraPos[0],gCameraPos[1],gCameraPos[2],
		gViewPos[0],gViewPos[1],gViewPos[2],
		gUpPos[0],gUpPos[1],gUpPos[2]);

	// initial the spirites
	gSpiritMgr = new CSpiriteMgr();

	//////////////////////////////////////////////////////////////////////////
	// font
	gFont.InitFont();

	//////////////////////////////////////////////////////////////////////////
	//cegui
	gGUI.GUIInitialize();
}

void UnInitScene( void )
{
	delete gSpiritMgr;
	gSpiritMgr = NULL;
	freeTerrain();
}
