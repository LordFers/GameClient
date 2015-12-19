#ifndef _H_GUI_
#define _H_GUI_

#include "GUILoad.h"
#include "GUIRender.h"

#include <d3d9.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Direct3D9/Renderer.h>

class GUI{
protected:
	static GUI* pI;

	public:
		~GUI();

		static void setInterface(GUI * newInterface) { pI = newInterface; }
		static GUI* p_cGIn() { return pI; }

		void Initialize(LPDIRECT3DDEVICE9);
		void injectKeyUp(CEGUI::Key::Scan);
		void injectKeyDown(CEGUI::Key::Scan);
		void injectChar(CEGUI::utf32 code_point);
		void injectMouseButtonDown();
		void injectMouseButtonUp();
		void injectMouseMove(float, float);
		void injectTimePulse(float);
};

#endif