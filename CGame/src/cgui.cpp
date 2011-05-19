#include "cgui.h"



#ifdef _MSC_VER
# if defined(DEBUG) || defined (_DEBUG)
#	if defined(CEGUI_STATIC)
#		pragma comment (lib, "CEGUIOpenGLRenderer_Static_d.lib")
#	else
#		pragma comment (lib, "CEGUIOpenGLRenderer_d.lib")
#		pragma comment (lib, "CEGUIBase_d.lib")
#	endif
# else
#	if defined(CEGUI_STATIC)
#		pragma comment (lib, "CEGUIOpenGLRenderer_Static.lib")
#	else
#		pragma comment (lib, "CEGUIOpenGLRenderer.lib")
#		pragma comment (lib, "CEGUIBase.lib")
#	endif
# endif
#endif

#define TRUE		1
#define FALSE		0
using namespace CEGUI;

CGUI::CGUI()
{
	

	m_Initialized = FALSE;
}

CGUI::~CGUI()
{

}

bool CGUI::GUIInitialize()
{		  
	// Bootstrap CEGUI::System with an OpenGLRenderer object that uses the
	// current GL viewport, the DefaultResourceProvider, and the default
	// ImageCodec.
	m_pRenderer = &CEGUI::OpenGLRenderer::bootstrapSystem();
	// Create an OpenGLRenderer object that uses the current GL viewport as
	// the default output surface.
	m_pRenderer = &CEGUI::OpenGLRenderer::create();

	// initialise the required dirs for the DefaultResourceProvider
	CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>
		(CEGUI::System::getSingleton().getResourceProvider());

	rp->setResourceGroupDirectory("schemes", "./CEGUI/CEGUI-SDK-0.7.5-vc9/datafiles/schemes/");
	rp->setResourceGroupDirectory("imagesets", "./CEGUI/CEGUI-SDK-0.7.5-vc9/datafiles/imagesets/");
	rp->setResourceGroupDirectory("fonts", "./CEGUI/CEGUI-SDK-0.7.5-vc9/datafiles/fonts/");
	rp->setResourceGroupDirectory("layouts", "./CEGUI/CEGUI-SDK-0.7.5-vc9/datafiles/layouts/");
	rp->setResourceGroupDirectory("looknfeels", "./CEGUI/CEGUI-SDK-0.7.5-vc9/datafiles/looknfeel/");
	rp->setResourceGroupDirectory("lua_scripts", "./CEGUI/CEGUI-SDK-0.7.5-vc9/datafiles/lua_scripts/");

	// This is only really needed if you are using Xerces and need to
	// specify the schemas location
	rp->setResourceGroupDirectory("schemas", "../datafiles/xml_schemas/");

	// set the default resource groups to be used
	CEGUI::Imageset::setDefaultResourceGroup("imagesets");
	CEGUI::Font::setDefaultResourceGroup("fonts");
	CEGUI::Scheme::setDefaultResourceGroup("schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
	CEGUI::WindowManager::setDefaultResourceGroup("layouts");
	CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");

	// setup default group for validation schemas
	CEGUI::XMLParser* parser = CEGUI::System::getSingleton().getXMLParser();
	if (parser->isPropertyPresent("SchemaDefaultResourceGroup"))
		parser->setProperty("SchemaDefaultResourceGroup", "schemas");

	
	// create (load) the TaharezLook scheme file
	// (this auto-loads the TaharezLook looknfeel and imageset files)
	CEGUI::SchemeManager::getSingleton().create( "TaharezLook.scheme" );
	
	// create (load) a font.
	// The first font loaded automatically becomes the default font, but note
	// that the scheme might have already loaded a font, so there may already
	// be a default set - if we want the "Commonweath-10" font to definitely
	// be the default, we should set the default explicitly afterwards.
	CEGUI::FontManager::getSingleton().create( "DejaVuSans-10.font" );

	System::getSingleton().setDefaultFont( "DejaVuSans-10" );

	System::getSingleton().setDefaultMouseCursor( "TaharezLook", "MouseArrow" );

	//System::getSingleton().setDefaultToolTip( "TaharezLook/Tooltip" );

	using namespace CEGUI;
	WindowManager& wmgr = WindowManager::getSingleton();

	Window* myRoot = wmgr.createWindow( "DefaultWindow", "root" );
	System::getSingleton().setGUISheet( myRoot );

	FrameWindow* fWnd = static_cast<FrameWindow*>(
		wmgr.createWindow( "TaharezLook/FrameWindow", "testWindow" ));

	myRoot->addChildWindow( fWnd );

	// position a quarter of the way in from the top-left of parent.
	fWnd->setPosition( UVector2( UDim( 0.25f, 0 ), UDim( 0.25f, 0 ) ) );

	// set size to be half the size of the parent
	fWnd->setSize( UVector2( UDim( 0.5f, 0 ), UDim( 0.5f, 0 ) ) );

	fWnd->setText( "Hello World!" );

	// update the m_initialize
	m_Initialized = TRUE;

	return m_Initialized;
}

bool CGUI::GUIRender(){

	// draw GUI (should not be between glBegin/glEnd pair)
	CEGUI::System::getSingleton().renderGUI();

	return TRUE;
}
