#include "FMain.h"
#include "Protocol.hpp"
#include "engine.hpp"
#include "GUI.h"

bool onCloseClicked(const CEGUI::EventArgs &e);
bool onCloseClicked_ClanesWindow(const CEGUI::EventArgs &e);
bool onCloseClicked_MiClanWindow(const CEGUI::EventArgs &e);
bool Exit_MouseButtonUp(const CEGUI::EventArgs&);
bool Deslogin_MouseButtonUp(const CEGUI::EventArgs&);
bool FMain_ClanesButton(const CEGUI::EventArgs &e);
bool FMain_ClanesList(const CEGUI::EventArgs &e);
bool FMain_SolicitudWindow_EnviarButton(const CEGUI::EventArgs &e);
bool FMain_SolicitarButton(const CEGUI::EventArgs &e);
bool FMain_MyClanes_MembersButton(const CEGUI::EventArgs &e);
bool FMain_MyClanes_ClanesButton(const CEGUI::EventArgs &e);
bool FMain_MyClanes_AspirantesButton(const CEGUI::EventArgs &e);
bool FMain_Aspirantes_RejectButton(const CEGUI::EventArgs &e);
bool FMain_Aspirantes_AcceptButton(const CEGUI::EventArgs &e);
bool FMain_SendText_MouseUp(const CEGUI::EventArgs &e);

void FMain_Load()
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	CEGUI::Window* FMainArea = winRoot->getChild("AllForm")->getChild("MainArea");

	FMainArea->setVisible(true);
	FMainArea->getChild("Console")->setVisible(true);
	FMainArea->getChild("CantidadText")->setVisible(false);
	FMainArea->getChild("ClanesWindow")->setVisible(false);
	FMainArea->getChild("ComercioUsuarioWindow")->setVisible(false);
	FMainArea->getChild("ExpBar")->setVisible(true);
	FMainArea->getChild("InfoButton")->setVisible(false);
	FMainArea->getChild("LanzarButton")->setVisible(false);
	FMainArea->getChild("MenuWindow")->setVisible(false);
	FMainArea->getChild("MiClanWindow")->setVisible(false);
	FMainArea->getChild("MinimapaRect")->setVisible(false);
	FMainArea->getChild("MoveSpellDownButton")->setVisible(false);
	FMainArea->getChild("MoveSpellUpButton")->setVisible(false);
	FMainArea->getChild("NpcBancoWindow")->setVisible(false);
	FMainArea->getChild("NpcComercioWindow")->setVisible(false);
	FMainArea->getChild("OpcionesWindow")->setVisible(false);
	FMainArea->getChild("PosRect")->setVisible(false);
	FMainArea->getChild("SpellButton")->setVisible(false);
	FMainArea->getChild("SpellList")->setVisible(false);
	FMainArea->getChild("TeclasWindow")->setVisible(false);

	FMainArea->getChild("MenuWindow")->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked, onCloseClicked);
	FMainArea->getChild("MenuWindow/DesloginButton")->subscribeEvent(CEGUI::FrameWindow::EventMouseButtonUp, Deslogin_MouseButtonUp);
	FMainArea->getChild("MenuWindow/ExitButton")->subscribeEvent(CEGUI::FrameWindow::EventMouseButtonUp, Exit_MouseButtonUp);
	FMainArea->getChild("MenuWindow/ClanesButton")->subscribeEvent(CEGUI::FrameWindow::EventMouseButtonUp, FMain_ClanesButton);
	FMainArea->getChild("ClanesWindow")->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked, onCloseClicked_ClanesWindow);
	FMainArea->getChild("ClanesWindow/ClanesList")->subscribeEvent(CEGUI::FrameWindow::EventMouseButtonUp, FMain_ClanesList);
	FMainArea->getChild("ClanesWindow/SolicitarButton")->subscribeEvent(CEGUI::FrameWindow::EventMouseButtonUp, FMain_SolicitarButton);
	FMainArea->getChild("ClanesWindow/SolicitudWindow/EnviarButton")->subscribeEvent(CEGUI::FrameWindow::EventMouseButtonUp, FMain_SolicitudWindow_EnviarButton);
	FMainArea->getChild("MiClanWindow")->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked, onCloseClicked_MiClanWindow);
	FMainArea->getChild("MiClanWindow/MiembrosButton")->subscribeEvent(CEGUI::FrameWindow::EventMouseButtonUp, FMain_MyClanes_MembersButton);
	FMainArea->getChild("MiClanWindow/AspirantesButton")->subscribeEvent(CEGUI::FrameWindow::EventMouseButtonUp, FMain_MyClanes_AspirantesButton);
	FMainArea->getChild("MiClanWindow/ClanesButton")->subscribeEvent(CEGUI::FrameWindow::EventMouseButtonUp, FMain_MyClanes_ClanesButton);
	FMainArea->getChild("MiClanWindow/AspirantesWindow/AceptarButton")->subscribeEvent(CEGUI::FrameWindow::EventMouseButtonUp, FMain_Aspirantes_AcceptButton);
	FMainArea->getChild("MiClanWindow/AspirantesWindow/RechazarButton")->subscribeEvent(CEGUI::FrameWindow::EventMouseButtonUp, FMain_Aspirantes_RejectButton);
	FMainArea->getChild("Console/Submit")->subscribeEvent(CEGUI::FrameWindow::EventMouseButtonUp, FMain_SendText_MouseUp);
}

void FMain_UnLoad()
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	CEGUI::Window* FMain = winRoot->getChild("AllForm")->getChild("MainArea")->getChild("MenuWindow");
}

void FMain_Menu_Visible(bool prg)
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	CEGUI::Window* FMain = winRoot->getChild("AllForm/MainArea/MenuWindow");
	
	FMain->setVisible(prg);
}

void FMain_GuildList_Visible(bool prg)
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	CEGUI::Window* FMain = winRoot->getChild("AllForm/MainArea/ClanesWindow");
	
	FMain->setVisible(prg);
}

void FMain_GuildLeader_Visible(bool prg, bool isLeader)
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	CEGUI::Window* FMain = winRoot->getChild("AllForm/MainArea/MiClanWindow");

	FMain->setVisible(prg);
	FMain->getChild("ClanesWindow")->setVisible(prg);
	FMain->getChild("AspirantesButton")->setEnabled(isLeader);
	FMain->getChild("MiembrosWindow/EcharButton")->setEnabled(isLeader);
	FMain->getChild("OtrosButton")->setEnabled(false);
	FMain->getChild("ClanesWindow")->setVisible(false);
	FMain->getChild("AspirantesWindow")->setVisible(false);
	FMain->getChild("MiembrosWindow")->setVisible(true);
}

void FMain_GuildNews_setText(const char* newstext)
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	CEGUI::Window* FMain = winRoot->getChild("AllForm/MainArea/ClanesWindow/DeskText");

	FMain->setText(newstext);
	FMain->setVisible(true);
}

bool FMain_MyClanes_MembersButton(const CEGUI::EventArgs &e)
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	CEGUI::Window* FMain = winRoot->getChild("AllForm/MainArea/MiClanWindow");

	FMain->getChild("AspirantesWindow")->setVisible(false);
	FMain->getChild("ClanesWindow")->setVisible(false);
	FMain->getChild("MiembrosWindow")->setVisible(true);
	
	FMain_Reload_GuildMember();

	return false;
}

bool FMain_MyClanes_AspirantesButton(const CEGUI::EventArgs &e)
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	CEGUI::Window* FMain = winRoot->getChild("AllForm/MainArea/MiClanWindow");

	FMain->getChild("AspirantesWindow")->setVisible(true);
	FMain->getChild("ClanesWindow")->setVisible(false);
	FMain->getChild("MiembrosWindow")->setVisible(false);

	FMain_Reload_GuildAspirantes();

	return false;
}

bool FMain_MyClanes_ClanesButton(const CEGUI::EventArgs &e)
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	CEGUI::Window* FMain = winRoot->getChild("AllForm/MainArea/MiClanWindow");

	FMain->getChild("AspirantesWindow")->setVisible(false);
	FMain->getChild("ClanesWindow")->setVisible(true);
	FMain->getChild("MiembrosWindow")->setVisible(false);

	FMain_Reload_GuildList();

	return false;
}

void FMain_Reload_GuildList()
{
	cGameData* GameData = cGameData::p_cGIn();
	if (GameData->GuildNames.size() <= 0) if (GameData->GuildNames[0].c_str() == NULL) return;

	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();

	if (winRoot->getChild("AllForm/MainArea/ClanesWindow/ClanesList")->isVisible())
	{
		CEGUI::Listbox* GuildList = static_cast<CEGUI::Listbox*>(winRoot->getChild("AllForm/MainArea/ClanesWindow/ClanesList"));
		GuildList->resetList();

		for (int i = 0; i < GameData->GuildNames.size(); ++i)
		{
			GuildList->addItem(new CEGUI::ListboxTextItem(GameData->GuildNames[i]));
		}

		winRoot->getChild("AllForm/MainArea/ClanesWindow/MiclanButton")->setEnabled(false);
	}
	
	if (winRoot->getChild("AllForm/MainArea/MiClanWindow/ClanesWindow/ClanesList")->isVisible())
	{
		CEGUI::Listbox* GuildListLeader = static_cast<CEGUI::Listbox*>(winRoot->getChild("AllForm/MainArea/MiClanWindow/ClanesWindow/ClanesList"));
		GuildListLeader->resetList();

		for (int i = 0; i < GameData->GuildNames.size(); ++i)
		{
			GuildListLeader->addItem(new CEGUI::ListboxTextItem(GameData->GuildNames[i]));
		}
	}
	
}

void FMain_Reload_GuildAspirantes()
{
	cGameData* GameData = cGameData::p_cGIn();
	if (GameData->GuildNames.size() <= 0) if (GameData->GuildNames[0].c_str() == NULL) return;

	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();

	if (winRoot->getChild("AllForm/MainArea/MiClanWindow/AspirantesWindow/AspirantesList")->isVisible())
	{
		CEGUI::Listbox* GuildAspirantes = static_cast<CEGUI::Listbox*>(winRoot->getChild("AllForm/MainArea/MiClanWindow/AspirantesWindow/AspirantesList"));
		GuildAspirantes->resetList();

		for (int i = 0; i < GameData->GuildAspirantes.size(); ++i)
		{
			GuildAspirantes->addItem(new CEGUI::ListboxTextItem(GameData->GuildAspirantes[i]));
		}
	}

}

void FMain_Reload_GuildMember()
{
	cGameData* GameData = cGameData::p_cGIn();
	if (GameData->GuildNames.size() <= 0) if (GameData->GuildNames[0].c_str() == NULL) return;

	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();

	if (winRoot->getChild("AllForm/MainArea/MiClanWindow/MiembrosWindow/MiembrosList")->isVisible())
	{
		CEGUI::Listbox* GuildMembers = static_cast<CEGUI::Listbox*>(winRoot->getChild("AllForm/MainArea/MiClanWindow/MiembrosWindow/MiembrosList"));
		GuildMembers->resetList();

		for (int i = 0; i < GameData->GuildMembers.size(); ++i)
		{
			GuildMembers->addItem(new CEGUI::ListboxTextItem(GameData->GuildMembers[i]));
		}
	}

}

void FMain_AddItem_Console(const char* text, int color, bool bold, bool italic)
{
	CEGUI::Window* Console = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("AllForm/MainArea/Console");
	CEGUI::Listbox *outputWindow = static_cast<CEGUI::Listbox*>(Console->getChild("History"));
	CEGUI::ListboxTextItem* newItem = new CEGUI::ListboxTextItem(text);

	newItem->setTextColours(color);

	if (outputWindow->getItemCount() >= 200) outputWindow->resetList();

	CEGUI::Scrollbar* scrollVert = static_cast<CEGUI::Scrollbar*>(outputWindow->getVertScrollbar());
	outputWindow->addItem(newItem);
	scrollVert->setUnitIntervalScrollPosition(1.0f);
}

void FMain_SendText()
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	CEGUI::Window* FMain = winRoot->getChild("AllForm/MainArea/Console/Editbox");

	if (FMain->isActive())
	{
		ParseUserCommand(FMain->getText().c_str());
		FMain->setText("");
		FMain->setEnabled(false);
		FMain->deactivate();
		winRoot->getChild("AllForm/MainArea/Console/Submit")->setEnabled(false);
	}
	else
	{
		FMain->setText("");
		FMain->setEnabled(true);
		FMain->activate();
		winRoot->getChild("AllForm/MainArea/Console/Submit")->setEnabled(true);
	}
}

void FMain_Visible(bool prg)
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	winRoot->getChild("AllForm/MainArea")->setVisible(prg);
	winRoot->getChild("AllForm/MainArea/ExpBar")->setVisible(prg);
}

template <typename T> std::string NumberToString(T Number)
{
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}

void FMain_setExpBar(float value)
{
	CEGUI::Window* childExpBar = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("AllForm")->getChild("MainArea")->getChild("ExpBar");
	CEGUI::ProgressBar* ExpBar = static_cast<CEGUI::ProgressBar*>(childExpBar);
	ExpBar->setProgress(value);
	CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("AllForm/MainArea/ExpBar")->setText(NumberToString(value * 100) + "%");
}

bool onCloseClicked(const CEGUI::EventArgs &e)
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	winRoot->getChild("AllForm/MainArea/MenuWindow")->setVisible(false);
	cGameData::p_cGIn()->Audio.PlayWav("resources/wav/click.wav");
	return false;
}

bool onCloseClicked_ClanesWindow(const CEGUI::EventArgs &e)
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	winRoot->getChild("AllForm/MainArea/ClanesWindow")->setVisible(false);
	cGameData::p_cGIn()->Audio.PlayWav("resources/wav/click.wav");
	return false;
}

bool onCloseClicked_MiClanWindow(const CEGUI::EventArgs &e)
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	winRoot->getChild("AllForm/MainArea/MiClanWindow")->setVisible(false);
	cGameData::p_cGIn()->Audio.PlayWav("resources/wav/click.wav");
	return false;
}

bool FMain_Aspirantes_AcceptButton(const CEGUI::EventArgs &e)
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	CEGUI::Window* FMain = winRoot->getChild("AllForm/MainArea/MiClanWindow/AspirantesWindow/AspirantesList");

	CEGUI::Listbox* ClanesList = static_cast<CEGUI::Listbox*>(FMain);

	int countList = 0;

	for (int i = 0; i < ClanesList->getItemCount(); ++i)
	{
		if (ClanesList->getListboxItemFromIndex(i)->isSelected()) countList = i;
	}

	WriteGuildAcceptNewMember(cGameData::p_cGIn()->GuildAspirantes[countList]);
}

bool FMain_Aspirantes_RejectButton(const CEGUI::EventArgs &e)
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	CEGUI::Window* FMain = winRoot->getChild("AllForm/MainArea/MiClanWindow/AspirantesWindow/AspirantesList");

	CEGUI::Listbox* ClanesList = static_cast<CEGUI::Listbox*>(FMain);

	int countList = 0;

	for (int i = 0; i < ClanesList->getItemCount(); ++i)
	{
		if (ClanesList->getListboxItemFromIndex(i)->isSelected()) countList = i + 1;
	}
	std::cout << "aspi: " << cGameData::p_cGIn()->GuildAspirantes[countList - 1] << std::endl;

	WriteGuildRejectNewMember(cGameData::p_cGIn()->GuildAspirantes[countList - 1], "Sos pt");
}

bool Deslogin_MouseButtonUp(const CEGUI::EventArgs &e)
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	winRoot->getChild("AllForm/MainArea/MenuWindow")->setVisible(false);
	cGameData::p_cGIn()->Audio.PlayWav("resources/wav/click.wav");
	WriteQuit();
	return false;
}

bool FMain_SolicitudWindow_EnviarButton(const CEGUI::EventArgs &e)
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	CEGUI::Window* FMain = winRoot->getChild("AllForm/MainArea/ClanesWindow");
	FMain->getChild("SolicitudWindow")->setVisible(false);

	cGameData::p_cGIn()->Audio.PlayWav("resources/wav/click.wav");
	
	WriteGuildRequestMembership(FMain->getChild("NombreText")->getText().c_str(), FMain->getChild("SolicitudWindow/SolicitudText")->getText().c_str());
	return false;
}

bool FMain_SolicitarButton(const CEGUI::EventArgs &e)
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	winRoot->getChild("AllForm/MainArea/ClanesWindow/SolicitudWindow")->setVisible(true);
	winRoot->getChild("AllForm/MainArea/ClanesWindow/SolicitudWindow/SolicitudText")->setText("Qué tal, me interesaría unirme a tu Clan.");
	return false;
}

bool Exit_MouseButtonUp(const CEGUI::EventArgs &e)
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	winRoot->getChild("AllForm/MainArea/MenuWindow")->setVisible(false);
	WriteQuit();
	cEngine::p_cGIn()->prgRun = false;
	return false;
}

bool FMain_ClanesButton(const CEGUI::EventArgs &e)
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	CEGUI::Window* FMain = winRoot->getChild("AllForm/MainArea/ClanesWindow/ClanesList");
	
	cGameData::p_cGIn()->Audio.PlayWav("resources/wav/click.wav");

	WriteRequestGuildLeaderInfo();
	FMain_Menu_Visible(false);

	return false;
}

bool FMain_ClanesList(const CEGUI::EventArgs &e)
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	CEGUI::Window* FMain = winRoot->getChild("AllForm/MainArea/ClanesWindow/ClanesList");
	CEGUI::Window* NameText = winRoot->getChild("AllForm/MainArea/ClanesWindow/NombreText");

	CEGUI::Listbox* ClanesList = static_cast<CEGUI::Listbox*>(FMain);
	
	int countList = 0;
	
	for (int i = 0; i < ClanesList->getItemCount(); ++i)
	{
		if (ClanesList->getListboxItemFromIndex(i)->isSelected()) countList = i + 1;
	}

	if (countList > 0) NameText->setText(cGameData::p_cGIn()->GuildNames[countList-1]);

	return false;
}

bool FMain_SendText_MouseUp(const CEGUI::EventArgs &e)
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	CEGUI::Window* FMain = winRoot->getChild("AllForm/MainArea/Console/Editbox");

	ParseUserCommand(FMain->getText().c_str());
	FMain->setText("");
	FMain->setEnabled(false);
	FMain->deactivate();
	winRoot->getChild("AllForm/MainArea/Console/Submit")->setEnabled(false);

	return false;
}

bool FMain_GetActive_SendText()
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	CEGUI::Window* FMain = winRoot->getChild("AllForm/MainArea/Console/Editbox");

	return FMain->isActive();
}