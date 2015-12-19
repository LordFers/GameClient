#include "Console.hpp"

void cConsole::AddItem(std::string text, int color, bool bold, bool endl)
{
	dialogos[countDialogs].text = text;
	dialogos[countDialogs].color = color;
	dialogos[countDialogs].bold = bold;

	if (endl) countDialogs++;
	ultimateDialog = countDialogs;
}