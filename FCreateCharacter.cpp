#include "FCreateCharacter.h"
#include "GUI.h"
#include "Forms.h"
#include "gamedata.hpp"
#include "Protocol.hpp"
#include <sstream>

bool MouseButtonUp_Back(const CEGUI::EventArgs &e);
bool MouseButtonUp_ThrowDices(const CEGUI::EventArgs &e);
bool MouseButtonUp_CreateCharacter(const CEGUI::EventArgs &e);

void FCreateCharacter_Load()
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	CEGUI::Window* FCreateCharacter = winRoot->getChild("AllForm")->getChild("CrearPJArea");

	CEGUI::Combobox* RazaCombo = static_cast<CEGUI::Combobox*>(FCreateCharacter->getChild("RazaCombo"));
	std::string Razas[5] = { "Humano", "Elfo", "Elfo Oscuro", "Gnomo", "Enano" };
	for (int i = 0; i < 5; ++i) {
		RazaCombo->addItem(new CEGUI::ListboxTextItem(Razas[i]));
	}

	CEGUI::Combobox* GeneroCombo = static_cast<CEGUI::Combobox*>(FCreateCharacter->getChild("GeneroCombo"));
	std::string Genero[2] = { "Hombre", "Mujer" };
	for (int i = 0; i < 2; ++i) {
		GeneroCombo->addItem(new CEGUI::ListboxTextItem(Genero[i]));
	}

	CEGUI::Combobox* ClaseCombo = static_cast<CEGUI::Combobox*>(FCreateCharacter->getChild("ClaseCombo"));
	std::string Clases[12] = { "Mago", "Clerigo", "Guerrero", "Asesino", "Ladron", "Bardo", "Druida", "Bandido", "Paladin", "Cazador", "Trabajador", "Pirata" };
	for (int i = 0; i < 12; ++i) {
		ClaseCombo->addItem(new CEGUI::ListboxTextItem(Clases[i]));
	}

	CEGUI::Combobox* HogarCombo = static_cast<CEGUI::Combobox*>(FCreateCharacter->getChild("HogarCombo"));
	std::string Hogar[5] = { "Ullathorpe", "Nix", "Banderbill", "Lindos", "Arghâl" };
	for (int i = 0; i < 5; ++i) {
		HogarCombo->addItem(new CEGUI::ListboxTextItem(Hogar[i]));
	}

	FCreateCharacter->getChild("BackButton")->subscribeEvent(CEGUI::FrameWindow::EventMouseButtonUp, MouseButtonUp_Back);
	FCreateCharacter->getChild("ThrowDices")->subscribeEvent(CEGUI::FrameWindow::EventMouseButtonUp, MouseButtonUp_ThrowDices);
	FCreateCharacter->getChild("CrearPJButton")->subscribeEvent(CEGUI::FrameWindow::EventMouseButtonUp, MouseButtonUp_CreateCharacter);

	FCreateCharacter->setVisible(false);
}

void FCreateCharacter_Visible(bool prg)
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	CEGUI::Window* FCreateCharacter = winRoot->getChild("AllForm")->getChild("CrearPJArea");

	if (FCreateCharacter->isVisible() == prg) return;

	FCreateCharacter->setVisible(prg);
	FCreateCharacter->getChild("NameText")->setText("BetaTester");
	cGameData::p_cGIn()->inCP = prg;
}

template <typename T> std::string NumberToString(T Number)
{
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}

void FCreateCharacter_setAttributes(char strength, char agility, char intelligence, char charisma, char constitution)
{
	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	CEGUI::Window* FCreateCharacter = winRoot->getChild("AllForm")->getChild("CrearPJArea");

	FCreateCharacter->getChild("FuerzaValue")->setText(NumberToString((int)strength));
	FCreateCharacter->getChild("AgilidadValue")->setText(NumberToString((int)agility));
	FCreateCharacter->getChild("InteligenciaValue")->setText(NumberToString((int)intelligence));
	FCreateCharacter->getChild("CarismaValue")->setText(NumberToString((int)charisma));
	FCreateCharacter->getChild("ConstitucionValue")->setText(NumberToString((int)constitution));
}

bool MouseButtonUp_CreateCharacter(const CEGUI::EventArgs &e)
{
	if (cGameData::p_cGIn()->Connected) return false;

	CEGUI::Window* winRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	CEGUI::Window* FCreateCharacter = winRoot->getChild("AllForm")->getChild("CrearPJArea");
	
	CEGUI::Combobox* RazaCombo = static_cast<CEGUI::Combobox*>(FCreateCharacter->getChild("RazaCombo"));
	CEGUI::Combobox* GeneroCombo = static_cast<CEGUI::Combobox*>(FCreateCharacter->getChild("GeneroCombo"));
	CEGUI::Combobox* ClaseCombo = static_cast<CEGUI::Combobox*>(FCreateCharacter->getChild("ClaseCombo"));
	CEGUI::Combobox* HogarCombo = static_cast<CEGUI::Combobox*>(FCreateCharacter->getChild("HogarCombo"));

	CEGUI::String username = FCreateCharacter->getChild("NameText")->getText();
	CEGUI::String userpassworda = FCreateCharacter->getChild("PasswordTextA")->getText();
	CEGUI::String userpasswordb = FCreateCharacter->getChild("PasswordTextB")->getText();
	CEGUI::String useremaila = FCreateCharacter->getChild("EMailTextA")->getText();
	CEGUI::String useremailb = FCreateCharacter->getChild("EMailTextB")->getText();
	
	short countA = 0;
	const char* charname = useremaila.c_str();

	for (int i = 0; i < useremaila.length(); ++i)
	{
		if (charname[i] == '@')
		{
			countA++;
		}
	}

	if ((countA != 1) | (useremaila.length() < 6))
	{
		MessageBoxA(NULL, "Ha ingresado una dirección de E-Mail inválida, porfavor verifique que su dirección sea la correcta.", "Creando personaje: ", NULL);
		return false;
	}

	if (useremaila != useremailb)
	{
		MessageBoxA(NULL, "Las direcciones de E-Mail no coinciden, porfavor verifique que ambas sean correctas.", "Creando personaje: ", NULL);
		return false;
	}

	if (userpassworda.length() < 8)
	{
		MessageBoxA(NULL, "Debe ingresar una contraseña alfanumérica mayor a 8 caracteres.", "Creando personaje: ", NULL);
		return false;
	}

	if (userpassworda != userpasswordb)
	{
		MessageBoxA(NULL, "Las contraseñas no coinciden, porfavor verifique que ambas sean correctas.", "Creando personaje: ", NULL);
		return false;
	}

	if (!RazaCombo->getSelectedItem())
	{
		MessageBoxA(NULL, "Debes seleccionar la Raza de tu personaje.", "Creando personaje: ", NULL);
		return false;
	}

	if (!GeneroCombo->getSelectedItem())
	{
		MessageBoxA(NULL, "Debes seleccionar el Genero de tu personaje.", "Creando personaje: ", NULL);
		return false;
	}

	if (!ClaseCombo->getSelectedItem())
	{
		MessageBoxA(NULL, "Debes seleccionar la Clase de tu personaje.", "Creando personaje: ", NULL);
		return false;
	}

	if (!HogarCombo->getSelectedItem())
	{
		MessageBoxA(NULL, "Debes seleccionar una Ciudad de Origen para el Hogar de tu personaje.", "Creando personaje: ", NULL);
		return false;
	}

	char userraza = 1;
	char usergenero = 1;
	char userclase = 1;
	char userhogar = 1;
	short userhead = 8;

	for (int i = 0; i < RazaCombo->getItemCount(); ++i)
	{
		if (RazaCombo->getListboxItemFromIndex(i)->isSelected()) userraza = i + 1;
	}

	for (int i = 0; i < GeneroCombo->getItemCount(); ++i)
	{
		if (GeneroCombo->getListboxItemFromIndex(i)->isSelected()) usergenero = i + 1;
	}

	for (int i = 0; i < ClaseCombo->getItemCount(); ++i)
	{
		if (ClaseCombo->getListboxItemFromIndex(i)->isSelected()) userclase = i + 1;
	}

	for (int i = 0; i < HogarCombo->getItemCount(); ++i)
	{
		if (HogarCombo->getListboxItemFromIndex(i)->isSelected()) userhogar = i + 1;
	}
	
	WriteLoginNewChar(username.c_str(), userpassworda.c_str(), userraza, usergenero, userclase, userhead, useremaila.c_str(), userhogar);
	return false;
}

bool MouseButtonUp_ThrowDices(const CEGUI::EventArgs &e)
{
	if (cGameData::p_cGIn()->Connected) return false;
	WriteThrowDices();
	return false;
}

bool MouseButtonUp_Back(const CEGUI::EventArgs &e)
{
	FCreateCharacter_Visible(false);
	FMain_Visible(false);
	FConnect_Visible(true);
	return false;
}