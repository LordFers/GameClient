#include "main.hpp"
#include "GUI.h"
#include "ByteQueue.h"
#include "Protocol.hpp"
#include "Watch.h"
#include "Forms.h"

using namespace std;
cMain Main;
cEngine* Engine;
cGameData* GameData;
cWinsock Winsock;

int main ()
{
    MSG messages;
    WNDCLASSEX wincl;

    /* The Window structure */
    wincl.hInstance = GetModuleHandleW(NULL);
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);

	wincl.hCursor = LoadCursor(NULL, IDC_ARROW); //VERIFY WITHOUT ICON

    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    int center_x = (GetSystemMetrics(SM_CXSCREEN) - MAIN_VIEW_PORT_X) / 2;
    int center_y = (GetSystemMetrics(SM_CYSCREEN) - MAIN_VIEW_PORT_Y) / 2;

    if (!RegisterClassEx (&wincl))return 0;

    Main.hwnd = CreateWindowEx (0, szClassName, _T("Argentum Online OpenGL/DirectX"), WS_POPUP | WS_VISIBLE | WS_SYSMENU,
           center_x, center_y-20, MAIN_VIEW_PORT_X, MAIN_VIEW_PORT_Y, HWND_DESKTOP, NULL, GetModuleHandleW(NULL), NULL);

    cGameData::setInterface(new cGameData());
    GameData = cGameData::p_cGIn();
    GameData->LoadGrh();
    GameData->LoadBodys();
    GameData->LoadHeads();
    GameData->LoadHelmets();
    GameData->LoadWeapons();
    GameData->LoadShields();
    GameData->LoadFXs();
    GameData->LoadFonts();
	GameData->LoadFontsConsole();

    cEngine::setInterface(new cEngine());
    Engine = cEngine::p_cGIn();
    Engine->Initialize(Main.hwnd);

    GameData->MinXBorder = X_MIN_MAP_SIZE + (HALF_WINDOW_TILE_WIDTH / 2);
    GameData->MaxXBorder = X_MAX_MAP_SIZE - (HALF_WINDOW_TILE_WIDTH / 2);
    GameData->MinYBorder = Y_MIN_MAP_SIZE + (HALF_WINDOW_TILE_HEIGHT / 2);
    GameData->MaxYBorder = Y_MAX_MAP_SIZE - (HALF_WINDOW_TILE_HEIGHT / 2);

	Winsock.setWinsock(&Winsock);
    Watch watch;

	Main.prgRun = true;
    while (Engine->prgRun)
    {
        if (PeekMessage(&messages,NULL,0,0,PM_REMOVE))
        {
            TranslateMessage(&messages);
            DispatchMessage(&messages);
        }
        else
        {
			Engine->RenderScene();
			Main.Check_Keys();

			//Socket Buffer:
			cWinsock::p_cGIn()->SocketReceive();
			FlushBuffer();

            if (GetTickCount() >= Engine->lFrameTimer + 1000)
            {
                Engine->lFrameTimer = GetTickCount();
                Engine->FPS = Engine->FramesPerSecCounter;
                Engine->FramesPerSecCounter = 0;

                for (int i = 1; i <= GameData->LastChar; ++i)
                {
                    if (GameData->charlist[i].dialog != "")
                    {
                        GameData->charlist[i].dialog_life--;
                        if (GameData->charlist[i].dialog_life <= 0)
                        {
                            GameData->charlist[i].dialog = "";
                            GameData->charlist[i].dialog_color = 0;
                            GameData->charlist[i].dialog_life = 0;
                            GameData->charlist[i].offset_counter_y = 0;
                            GameData->charlist[i].dialog_font_index = 0;
                        }
                    }
                }
            }

            Engine->FramesPerSecCounter++;
            GameData->timerElapsedTime = watch.Elapsed();
			GUI::p_cGIn()->injectTimePulse(GameData->timerElapsedTime * 0.001f);
            Engine->timerTicksPerFrame = GameData->timerElapsedTime * engineBaseSpeed;
        }
    }

    cout << "Closing..." << endl;
    return messages.wParam;
}

CEGUI::utf32 keycodeToUTF32(unsigned int scanCode)
{
	CEGUI::utf32 utf = 0;

	BYTE keyboardState[256];
	unsigned char ucBuffer[3];
	static WCHAR deadKey = '\0';

	// Retrieve the keyboard layout in order to perform the necessary convertions
	HKL hklKeyboardLayout = GetKeyboardLayout(0); // 0 means current thread 
												  // This seemingly cannot fail 
												  // If this value is cached then the application must respond to WM_INPUTLANGCHANGE 

												  // Retrieve the keyboard state
												  // Handles CAPS-lock and SHIFT states
	if (GetKeyboardState(keyboardState) == FALSE)
		return utf;

	UINT virtualKey = MapVirtualKeyEx(scanCode, 3, hklKeyboardLayout);
	if (virtualKey == 0) // No translation possible
		return utf;

	int ascii = ToAsciiEx(virtualKey, scanCode, keyboardState, (LPWORD)ucBuffer, 0, hklKeyboardLayout);
	if (deadKey != '\0' && ascii == 1)
	{
		// A dead key is stored and we have just converted a character key
		// Combine the two into a single character
		WCHAR wcBuffer[3];
		WCHAR out[3];
		wcBuffer[0] = ucBuffer[0];
		wcBuffer[1] = deadKey;
		wcBuffer[2] = '\0';
		if (FoldStringW(MAP_PRECOMPOSED, (LPWSTR)wcBuffer, 3, (LPWSTR)out, 3))
			utf = out[0];
		else
		{
			// FoldStringW failed
			DWORD dw = GetLastError();
			switch (dw)
			{
			case ERROR_INSUFFICIENT_BUFFER:
			case ERROR_INVALID_FLAGS:
			case ERROR_INVALID_PARAMETER:
				break;
			}
		}
		deadKey = '\0';
	}
	else if (ascii == 1)
	{
		// We have a single character
		utf = ucBuffer[0];
		deadKey = '\0';
	}
	else
	{
		// Convert a non-combining diacritical mark into a combining diacritical mark
		switch (ucBuffer[0])
		{
		case 0x5E: // Circumflex accent: â
			deadKey = 0x302;
			break;
		case 0x60: // Grave accent: à
			deadKey = 0x300;
			break;
		case 0xA8: // Diaeresis: ü
			deadKey = 0x308;
			break;
		case 0xB4: // Acute accent: é
			deadKey = 0x301;
			break;
		case 0xB8: // Cedilla: ç
			deadKey = 0x327;
			break;
		default:
			deadKey = ucBuffer[0];
		}
	}

	return utf;
}

UINT virtualkey2scancode(WPARAM wParam, LPARAM lParam)
{
	if (HIWORD(lParam) & 0x0F00)
	{
		UINT scancode = MapVirtualKey(wParam, 0);
		return scancode | 0x80;
	}
	else
	{
		return HIWORD(lParam) & 0x00FF;
	}
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int lx, ly;

    switch (message)
    {
		case WM_CHAR:
			GUI::p_cGIn()->injectChar(keycodeToUTF32(virtualkey2scancode(wParam, lParam)));
			break;
        case WM_LBUTTONDOWN:

            lx = LOWORD(lParam);
            ly = HIWORD(lParam);

			GUI::p_cGIn()->injectMouseButtonDown();
			
            GameData->Process_Click(lx, ly, 1);
            GameData->ConvertCPtoTP(lx, ly); //Arreglar ésto, para que no haya interferencia a la hora de usar el formulario de CEGUI y que haga clic al mapa.

            if (Main.keys[VK_SHIFT]) WriteWarpChar("yo", GameData->UserMap, (unsigned char)lx, (unsigned char)ly);

        break;

        case WM_LBUTTONUP:
            GameData->MoveInvent = false;
			GUI::p_cGIn()->injectMouseButtonUp();
        break;

        case WM_RBUTTONDOWN:
            int rx, ry;
            rx = LOWORD(lParam);
            ry = HIWORD(lParam);
            GameData->Process_Click(rx, ry, 2);
        break;

        case WM_MOUSEMOVE:
            int mx, my;
            mx = LOWORD(lParam);
            my = HIWORD(lParam);

			GUI::p_cGIn()->injectMouseMove(mx, my);

            if (GameData->MoveInvent)
            {
                GameData->CharInventory.posX = mx - GameData->CharInventory.difPosX;
                GameData->CharInventory.posY = my - GameData->CharInventory.difPosY;
            }

        break;

        case WM_DESTROY:
            PostQuitMessage (0);
        break;

        case WM_KEYDOWN:
			Main.keys[wParam] = true;
			Main.KeyEvents(wParam);
			GUI::p_cGIn()->injectKeyDown(static_cast<CEGUI::Key::Scan>(virtualkey2scancode(wParam, lParam)));
        break;

        case WM_KEYUP:
            Main.keys[wParam] = false;
			if (wParam == VK_CONTROL) if (GameData->Connected) WriteAttack();
			GUI::p_cGIn()->injectKeyUp(static_cast<CEGUI::Key::Scan>(virtualkey2scancode(wParam, lParam)));
        break;

        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

void cMain::KeyEvents(char KEY_PRESS)
{
    switch (KEY_PRESS)
    {
        case VK_ESCAPE:
			if (GameData->Connected) FMain_Menu_Visible(true);
            break;
		case VK_RETURN:
			if (GameData->Connected) FMain_SendText();
			break;
        case 0x41:
			if (GameData->Connected) if (!FMain_GetActive_SendText()) WritePickUp();
            break;
        case 0x49:
			if (GameData->Connected) if (!FMain_GetActive_SendText()) {
            GameData->CharInventory.visible = !GameData->CharInventory.visible;}
            break;
        case 0x54:
			if (GameData->Connected) if (!FMain_GetActive_SendText()) WriteDrop(GameData->InvSelectedItem, 1);
            break;
        case VK_F8:
			if (GameData->Connected) WriteInvisible();
            break;
    }
}

void cMain::Check_Keys()
{
	if (!GameData->Connected) return;
    if (!GameData->UserMoving)
    {
        if (Main.keys[VK_UP])
        {
			GameData->MoveTo(eHeading::eHeading_NORTH);
            return;
        }

        if (Main.keys[VK_DOWN])
        {
			GameData->MoveTo(eHeading::eHeading_SOUTH);
            return;
        }

        if (Main.keys[VK_LEFT])
        {
			GameData->MoveTo(eHeading::eHeading_WEST);
            return;
        }

        if (Main.keys[VK_RIGHT])
        {
			GameData->MoveTo(eHeading::eHeading_EAST);
            return;
        }
    }
}