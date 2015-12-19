#ifndef _H_MAIN_
#define _H_MAIN_

#define WIN32_LEAN_AND_MEAN
#define _WINSOCKAPI_

#include "engine.hpp"
#include "winsock_ao.hpp"
#include <iostream>
#include <tchar.h>

#include <d3d9.h>

static  PIXELFORMATDESCRIPTOR pfd=
{
    sizeof(PIXELFORMATDESCRIPTOR), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA,
    32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 8, 0, PFD_MAIN_PLANE, 0, 0, 0, 0
};

class cMain{
    public:
        void KeyEvents(char);
        void Check_Keys();
		bool prgRun;
        bool keys[256];
        HWND hwnd;
};

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
TCHAR szClassName[ ] = _T("GLWindow");

#endif // _H_MAIN_