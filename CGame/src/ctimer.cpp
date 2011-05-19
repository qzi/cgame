#include "ctimer.h"
#include <gl/glut.h>

// initialize singleton
CTimer *CTimer::m_singleton = 0;

unsigned long CTimer::GetTimeMSec( void )
{
	return glutGet( GLUT_ELAPSED_TIME );
}

void CTimer::Initialize( void )
{
	m_currentTime = GetTimeMSec(); m_lastTime = 0;
}

void CTimer::Update( void )
{
	m_lastTime = m_currentTime; m_currentTime = GetTimeMSec();
}

float CTimer::GetFps( void )
{
	return ((float)1000.0 / (float)(m_currentTime - m_lastTime));
}

unsigned long CTimer::GetTime( void )
{
	return m_currentTime;
}
