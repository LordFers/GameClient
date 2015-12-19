#include "FConnect.h"
#include "winsock_ao.hpp"
#include "Protocol.hpp"
#include "gamedata.hpp"
#include "engine.hpp"
#include "GUI.h"
#include "FCreateCharacter.h"

bool MouseButtonUp(const CEGUI::EventArgs&);
bool MouseButtonUp_Exit(const CEGUI::EventArgs &e);
bool MouseButtonUp_CP(const CEGUI::EventArgs &e);

void FConnect_Load()
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	CEGUI::Window* FConnect = winRoot->getChild("AllForm")->getChild("ConnectArea");

	FConnect->getChild("Connect")->setVisible(true);
	FConnect->getChild("Connect")->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 480), CEGUI::UDim(0, 280)));
	FConnect->getChild("Connect/ButtonConnect")->subscribeEvent(CEGUI::FrameWindow::EventMouseButtonUp, MouseButtonUp);
	FConnect->getChild("Connect/ButtonCreatePJ")->subscribeEvent(CEGUI::FrameWindow::EventMouseButtonUp, MouseButtonUp_CP);
	FConnect->getChild("ButtonExit")->subscribeEvent(CEGUI::FrameWindow::EventMouseButtonUp, MouseButtonUp_Exit);
}

void FConnect_Visible(bool prg)
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	CEGUI::Window* FConnect = winRoot->getChild("AllForm")->getChild("ConnectArea");
	
	if (FConnect->isVisible() == prg) return;

	FConnect->setVisible(prg);
	FConnect->getChild("Connect")->getChild("PasswordText")->setText("");
}

const char* FConnect_getIpServidor()
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	CEGUI::Window* FConnect = winRoot->getChild("AllForm")->getChild("ConnectArea");
	return FConnect->getChild("IPText")->getText().c_str();
}

void FConnect_Login()
{
	if (cGameData::p_cGIn()->Connected) return;

	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	CEGUI::Window* FConnect = winRoot->getChild("AllForm")->getChild("ConnectArea")->getChild("Connect");

	const char* username = FConnect->getChild("UserText")->getText().c_str();
	const char* userpassword = FConnect->getChild("PasswordText")->getText().c_str();

	cGameData::p_cGIn()->Audio.PlayWav("resources/wav/click.wav");

	cWinsock::p_cGIn()->Init_cWinsock();
	WriteLoginExistingChar(username, userpassword);
	FlushBuffer();
}

bool MouseButtonUp_CP(const CEGUI::EventArgs &e)
{
	if (cGameData::p_cGIn()->Connected) return false;
	cWinsock::p_cGIn()->Init_cWinsock();
	WriteThrowDices();
	return false;
}

bool MouseButtonUp_Exit(const CEGUI::EventArgs &e)
{
	cEngine::p_cGIn()->prgRun = false;
	return false;
}

bool MouseButtonUp(const CEGUI::EventArgs &e)
{
	if (cGameData::p_cGIn()->Connected) return false;
	FConnect_Login();
	return false;
}