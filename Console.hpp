#ifndef _H_CONSOLE_
#define _H_CONSOLE_

#define MAX_DIALOGS_CONSOLE 200
#define MAX_DIALOGS_RENDER 5

#include <string>

typedef struct {
	std::string text;
	int color;
	bool bold;
} tConsole;

class cConsole {
	public:
		tConsole dialogos[MAX_DIALOGS_CONSOLE];
		int ultimateDialog;
		int countDialogs;

		void AddItem(std::string, int, bool, bool endl = true);
};

#endif