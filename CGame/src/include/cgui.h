#ifndef CGUI_H
#define CGUI_H

#include <CEGUI.h>
#include <RendererModules/OpenGL/CEGUIOpenGLRenderer.h>
#include <CEGUIDefaultResourceProvider.h>
#include <CEGUISystem.h>
#include <CEGUIWindowManager.h>


namespace CEGUI{

	class OpenGLRenderer;
	class ResourceProvider;
	class System;

	class CGUI{
	public:

		CGUI();
		~CGUI();

		bool GUIInitialize();
		bool GUIRender();
		bool m_Initialized;

	protected:
		CEGUI::OpenGLRenderer * m_pRenderer;
	};
};

#endif	//CGUI_H