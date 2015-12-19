#include "GUI.h"
#include "Forms.h"

GUI* GUI::pI = NULL;

GUI::~GUI()
{
	delete GUI::pI;
}

void GUI::Initialize(LPDIRECT3DDEVICE9 Direct3DDevice)
{
	try {
		CEGUI::Direct3D9Renderer& Renderer = CEGUI::Direct3D9Renderer::create(Direct3DDevice);
		CEGUI::System::create(Renderer); //CEGUI::Direct3D9Renderer::bootstrapSystem(Direct3DDevice);
		CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());

		rp->setResourceGroupDirectory("schemes", "resources/gui/src/");
		rp->setResourceGroupDirectory("imagesets", "resources/gui/images/");
		rp->setResourceGroupDirectory("fonts", "resources/gui/fonts/");
		rp->setResourceGroupDirectory("layouts", "resources/gui/src/");
		rp->setResourceGroupDirectory("looknfeels", "resources/gui/scripts/");
		rp->setResourceGroupDirectory("lua_scripts", "resources/gui/scripts/");

		// set the default resource groups to be used
		CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
		CEGUI::Font::setDefaultResourceGroup("fonts");
		CEGUI::Scheme::setDefaultResourceGroup("schemes");
		CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
		CEGUI::WindowManager::setDefaultResourceGroup("layouts");
		CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");

		// setup default group for validation schemas
		CEGUI::XMLParser* parser = CEGUI::System::getSingleton().getXMLParser();
		if (parser->isPropertyPresent("SchemaDefaultResourceGroup")) parser->setProperty("SchemaDefaultResourceGroup", "schemas");

		CEGUI::SchemeManager::getSingleton().createFromFile("GlossySerpent.scheme");
		CEGUI::FontManager::getSingleton().createFromFile("DejaVuSans-10.font");

		CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont("DejaVuSans-10");
		//CEGUI::System::getSingleton().setDefaultMouseCursor( "TaharezLook", "MouseArrow" ); //Cursor of Mouse
		CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultTooltipType("GlossySerpent/Tooltip");
		CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setVisible(false);

		CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

		CEGUI::Window* winRoot = wmgr.createWindow("DefaultWindow", "root_wnd");
		CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(winRoot);

		CEGUI::Window* tempWin = wmgr.loadLayoutFromFile("GUI.aoc");
		winRoot->addChild(tempWin);

		FConnect_Load();
		FMain_Load();
		FCreateCharacter_Load();
		FErrorWindow_UnLoad();
	}
	catch (CEGUI::GenericException &e) {
		MessageBoxA(NULL, e.getMessage().c_str(), "Error GUI 1", NULL);
	}
}

void GUI::injectKeyUp(CEGUI::Key::Scan scan_code)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(scan_code);
}

void GUI::injectKeyDown(CEGUI::Key::Scan scan_code)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(scan_code);
}

void GUI::injectChar(CEGUI::utf32 code_point)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectChar(code_point);
}

void GUI::injectMouseMove(float posX, float posY)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMousePosition(posX, posY);
}

void GUI::injectMouseButtonDown()
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::MouseButton::LeftButton);
}

void GUI::injectMouseButtonUp()
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::MouseButton::LeftButton);
}

void GUI::injectTimePulse(float timeElapsed)
{
	CEGUI::System::getSingleton().injectTimePulse(timeElapsed);
}