#ifndef UNITY_H
#define UNITY_H

#include <stdlib.h>
#include <stdio.h>
#include "mathex.h"
#include "CPage.h"
#include "ccamera.h"
#include "LSUtility.h"
#include "CSpiritMgr.h"
#include "CBullet.h"
#include "math3d.h"
#include "cfont.h"
#include "ctimer.h"
#include "cgui.h"
#include "gl/glut.h"

/* Define the macro */
#define TRUE		1
#define FALSE		0
#define NULL		0

#define NEAR_CLIP	(1.0f)
#define FAR_CLIP	(2000.0f)



/* Set the camera param */
extern GLfloat gCameraPos[3];
extern GLfloat gViewPos[3];
extern GLfloat gUpPos[3];

/*extern CCamera gCamera;*/
extern CCamera gCamera;

/* Define the texture ID */
extern FILE * pFileLog;
extern float gSpeed;
extern CPageMgr gPageMgr;
extern enum DirectMode{ UP, DOWN, LEFT, RIGHT } gDirectMode ;


/* function */
extern void GLUTReshape(int w, int h);
extern void GLUTRenderScene( void );
extern void RenderScene();
extern void DrawRect( float x, float y, float z, float r );
extern void DrawLandScale( float x, float y, float z, float w, float h );
extern void DrawLandScaleTest( float x, float y, float z, float w, float h, const float color[] );
extern void NinthGrid();
extern bool makeCheckImages();
extern void KeyDown();
extern void KeyUp();
extern void KeyRight();
extern void KeyLeft();
extern void GLUTSpecial( int key, int x, int y );
extern void GLUTKeyboard(unsigned char key, int x, int y);
extern void InitScene(void);
extern void UnInitScene(void);



/*  ROAM */
#endif	//UNITY_H
