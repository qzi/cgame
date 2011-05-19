#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <GL/glut.h>

#include "cmatrix.h"
#include "cvector.h"
#include "cterrain.h"
#include "ctexture.h"

#include "md2.h"
#include "cfont.h"
#include "cpick.h"
#include "cmodel.h"
//#include "CSpiriteMgr.h"


#include "Utility.h"		//  using the landscape

//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")


bool mouseisdown=false;
bool loopr=false;
int mx,my;
int ry=30;
int rx=30;

float red[3]={1,0,0}; 
float blue[3]={0,0,1}; 
float green[3]={0,1,0}; 
float yellow[3]={1,1,0};


//////////////////// md2 model test /////////////////////////////
CMD2Model		Ogro;
CMD2Model		Weapon;
animType_t      animType = STAND;

bool			bTextured	= true;
bool			bLighGL		= false;
bool			bAnimated	= true;
float			angle		= 0.0;
extern float	g_angle;
/////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// cmodel with assimp


//CModel gModel;

//////////////////////////////////////////////////////////////////////////
// cspiritemgr

//CSpiriteMgr gSpiriteMgr;
//CSpirit * gSpirit[3];


//////////////////////////// terrain test //////////////////////////////////
// terrain test 
CTerrain terrain;

//////////////////////////////////////////////////////////////////////////
//camera
//CCamera gCameraOne;


//////////////////////////// font test //////////////////////////////////////
CFont font;
//////////////////////////////////////////////////////////////////////////


///////////////////////// pick test //////////////////////////////////

//GLfloat V0[3]={1.0,0.0,-1.0 };
//GLfloat V1[3]={0.0,1.0,-1.0 };
//GLfloat V2[3]={0.0,0.0,-2.0 };
//GLfloat V0[3]={1.0,0.0,-10.0 };
//GLfloat V1[3]={0.0,1.0,-10.0 };
//GLfloat V2[3]={0.0,0.0,-20.0 };
//CVector3 V0( 1.0,0.0,-1.0 );
//CVector3 V1( 0.0,1.0,-1.0 );
//CVector3 V2( 0.0,0.0,-2.0 );
//GLfloat g_color =1.0f;

//////////////////////////////////////////////////////////////////////////

void timer(int p)
{
	ry-=5;
	//glutPostRedisplay();                 //marks the current window as needing to be redisplayed. 

}
void mouse(int button, int state, int x, int y) 
{ 
	if(button == GLUT_LEFT_BUTTON) 
	{
		if(state == GLUT_DOWN) 
		{    mouseisdown=true; loopr=false;
			{
				pick( x, y );
			}
		}
		else
			mouseisdown=false;
	}
	if (button== GLUT_RIGHT_BUTTON)
		if(state == GLUT_DOWN) 
		{loopr=true; glutTimerFunc(33,timer,0);}
} 
void motion(int x, int y) 
{ 
	if(mouseisdown==true) 
	{ 
		ry+=x-mx;
		rx+=y-my;
		mx=x;
		my=y;
		glutPostRedisplay(); 
	} 
} 
void special(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_LEFT:
		ry-=5;
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		ry+=5;
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:
		rx+=5;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		rx-=5;
		glutPostRedisplay();
		break;
	}
}

void keyboard(unsigned char key, int x, int y){

	switch (key) {
	   case 27:
		   exit(0);
	   case 'C':
	   case 'c':
		   {
			   if (animType == STAND)
			   {
				   animType = RUN;
				   Ogro.SetAnim( animType );
			   }else{
				   if (animType = RUN)
				   {
					   animType = STAND;
					   Ogro.SetAnim( animType );
				   }
			   }

			   break;
		   }
	}
	glutPostRedisplay();
}

void display() 
{ 
	glClearColor(1,1,1,1); 
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); 
	glLoadIdentity(); 

	gCamera.setLook();

	// fps
	//CTimer::GetInstance()->Update();
	//float timesec = CTimer::GetInstance()->GetTimeMSec() / 1000.0;

	// print fps statistics
	std::cout << "\r   fps = " << std::setprecision(4) << CTimer::GetInstance()->GetFps();


	glTranslatef(-2.0f,0.0f,-12.0f);
	glRotatef(ry,0,1,0);       
	glRotatef(rx,1,0,0);
	//glColor3fv(green);
	//glutWireTeapot(0.5);
	//glutWireCube(2.0);

	//terrain.render();

	//////////////////////////////////////////////////////////////////////////
	// md2 model test

	glPushMatrix();
	if( g_angle > 360.0 )
		g_angle -= 360.0;

	if( g_angle < 0.0 )
		g_angle += 360.0;

	if( angle < 0.0 )
		angle += 360.0;

	if( angle > 360.0 )
		angle -= 360.0;


	glTranslatef( 0.0, 0.0, -25.0 );
	glRotatef( angle, 0.0, 1.0, 0.0 );
	glScalef(40.0f,40.0f,40.0f);

	// draw models
	//Ogro.DrawModel( bAnimated ? timesec : 0.0 );
	//Weapon.DrawModel( bAnimated ? timesec : 0.0 );
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	

	//////////////////////////////////////////////////////////////////////////
	glPushMatrix();
	font.PrintText("吕超",-3.0f,2.0f); /**<　在指定位置输出字符串 */
	glPopMatrix();

	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	/// pick

	glPushMatrix();
	//glVertex3fv(V0);// 如果加了glTranslatef之类的变换函数，射线应该反向变化
	//glVertex3fv(V1);
	//glVertex3fv(V2);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glBegin(GL_TRIANGLES);
	glColor3f(g_color,0.0,1.0);
	glVertex3f(V0.x,V0.y,V0.z);// 如果加了glTranslatef之类的变换函数，射线应该反向变化
	glVertex3f(V1.x,V1.y,V1.z);
	glVertex3f(V2.x,V2.y,V2.z);
	glEnd();
	glPopMatrix();

	//////////////////////////////////////////////////////////////////////////
	// cmodel with assimp
	//glPushMatrix();
	//glScalef( 3.0f, 3.0f, 3.0f );
	//if ( gModel.m_bInitalized)
	//{
	//	gModel.Render();
	//}
	//glPopMatrix();

	//////////////////////////////////////////////////////////////////////////
	// cspirit and cspiritmgr
	//glPushMatrix();

	//		gSpirit[0] = NewCSpirit( gSpirit[0], "./TEST/", "gl-14.3ds" );
	//		gSpirit[0]->SetPosition( 5.2f,0.0f,0.0f );
	//		gSpirit[0]->SetScale( 1.2f );
	//		gSpirit[1] = NewCSpirit( gSpirit[1], "./TEST/", "gl-14c.3ds");
	//		gSpirit[1]->SetPosition( 0.0f,0.0f,0.0f );
	//		gSpirit[2] = NewCSpirit( gSpirit[2], "./TEST/", "cannon1.3ds");
	//		gSpirit[2]->SetPosition( 2.0f,0.0f,0.0f );
	//		gSpirit[2]->SetScale( 0.2f );

	//		gSpiriteMgr.AddSpirit( gSpirit[0] );
	//		gSpiriteMgr.AddSpirit( gSpirit[1] );
	//		gSpiriteMgr.AddSpirit( gSpirit[2] );

	//		//gSpiriteMgr.DeleteSpirit( gSpirit[1] );  // without clean the memory
	//	
	//	gSpiriteMgr.UpdateSprites();

	//glPopMatrix();


	//////////////////////////////////////////////////////////////////////////
	// paging roam system


	glPushMatrix();
	gPageMgr.SetCameraPos( gCamera.getPosition().x,gCamera.getPosition().y,gCamera.getPosition().z );
	gPageMgr.SetViewPos( gCamera.getView().x,gCamera.getView().y,gCamera.getView().z );
	gPageMgr.Render();
	glPopMatrix();

	//////////////////////////////////////////////////////////////////////////
	glutSwapBuffers();
	//glutPostRedisplay();
} 

void idle(){

	if (loopr)
		glutTimerFunc(33,timer,0);
	glutPostRedisplay();
}

void reshape(int w, int h){

	float s = 700.0f;
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho((GLdouble)-s, (GLdouble)s,(GLdouble) -s,(GLdouble) s,(GLdouble) s,(GLdouble) -s);
	gluPerspective(45.0, w/h,
		1.0, 1000.0);  /* Znear and Zfar */
	glMatrixMode(GL_MODELVIEW);

}

void GameInit(){

	glClearDepth(1.0f);											
	glDepthFunc(GL_LEQUAL);	
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);	
	glEnable(GL_TEXTURE_2D);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//////////////////////////////////////////////////////////////////////////
	// terrain
	//terrain.initTerrain();

	// font test

	// md2 test 

	// enable texture mapping
	glEnable( GL_TEXTURE_2D );

	/////////////////////////////////////////////

	/*CTimer::GetInstance()->Initialize();*/
	CTextureManager::GetInstance()->Initialize();

	// load and initialize the Ogros model
	Ogro.LoadModel( "models/Ogros.md2" );
	Ogro.LoadSkin( "models/igdosh.pcx" );
	//	Ogro.LoadModel( "models/grunt.md2" );
	//	Ogro.LoadSkin( "models/grunt.pcx" );
	//	Ogro.LoadModel( "models/cybrpnk/tris.md2" );
	//	Ogro.LoadSkin( "models/cybrpnk/vicious.pcx" );
	Ogro.SetAnim( 0 );
	Ogro.ScaleModel( 0.25 );

	// load and initialize Ogros' weapon model
	Weapon.LoadModel( "models/Weapon.md2" );
	Weapon.LoadSkin( "models/Weapon.pcx" );
	//	Weapon.LoadModel( "models/cybrpnk/weapon.md2" );
	//	Weapon.LoadSkin( "models/cybrpnk/weapon.pcx" );
	Weapon.SetAnim( JUMP );
	Weapon.ScaleModel( 0.25 );

	//////////////////////////////////////////////////////////////////////////
	///cmodel with assimp
	// load the model
	//gModel.InitialModel( "./TEST/", "11.obj" );

	//////////////////////////////////////////////////////////////////////////
	// spirite
	//gSpirite.SetSpirites( "./TEST/", "11.obj" );
	//gSpirite.InitSprit();


	//InitSpirtes();

	//////////////////////////////////////////////////////////////////////////
	// paging roam system

	loadTerrain(MAP_SIZE, &gHeightMap);
	//////////////////////////////////////////////////////////////////////////
	//camera
	gCamera.setCamera( gCameraPos[0],gCameraPos[1],gCameraPos[2],
		gViewPos[0],gViewPos[1],gViewPos[2],
		gUpPos[0],gUpPos[1],gUpPos[2]);


	//////////////////////////////////////////////////////////////////////////
	// opengl lighting initialization
	glDisable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );

	float lightpos[]	= { 10.0, 10.0, 100.0 };
	float lightcolor[]	= { 1.0, 1.0, 1.0, 1.0 };

	glLightfv( GL_LIGHT0, GL_POSITION, lightpos );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, lightcolor );
	glLightfv( GL_LIGHT0, GL_SPECULAR, lightcolor );

}

void GameShutDown(){

	//gSpiriteMgr.CleanupSprites();
	UnInitScene();
}


int main(int argc, char** argv) 
{ 
	glutInit(&argc, argv); 
	glutInitDisplayMode ( GLUT_DOUBLE| GLUT_RGBA | GLUT_DEPTH ); 
	glutInitWindowSize (800, 800);
	glutInitWindowPosition(100,100);      
	glutCreateWindow ("CGame Demo");
	
	//GameInit();

	glutIdleFunc(idle);
	//glutReshapeFunc(reshape);
	//glutDisplayFunc (display); 
	/* roam below */
	InitScene();
	glutReshapeFunc( GLUTReshape );
	glutDisplayFunc( GLUTRenderScene );
	glutSpecialFunc( GLUTSpecial );
	glutKeyboardFunc( GLUTKeyboard );
	/* roam below */
	glutMouseFunc(mouse);        
	glutMotionFunc(motion); 
	//glutSpecialFunc(special);
	//glutKeyboardFunc(keyboard);

	glutMainLoop(); 
	
	GameShutDown();
	return 0; 
} 
