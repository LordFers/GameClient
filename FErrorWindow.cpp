#include "FErrorWindow.h"
#include "GUI.h"

void FErrorWindow_Load()
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	CEGUI::Window* FErrorWindow = winRoot->getChild("AllForm")->getChild("ConnectArea");
	winRoot->getChild("AllForm")->getChild("ErrorWindow")->setVisible(true);
}

void FErrorWindow_UnLoad()
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	CEGUI::Window* FErrorWindow = winRoot->getChild("AllForm")->getChild("ConnectArea");
	winRoot->getChild("AllForm")->getChild("ErrorWindow")->setVisible(false);
}