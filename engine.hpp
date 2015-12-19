#ifndef _H_ENGINE_
#define _H_ENGINE_

#include "gamedata.hpp"
#include "surface.hpp"

#include <math.h>
#include <string>
#include <iostream>

#define MAIN_VIEW_PORT_X 1280
#define MAIN_VIEW_PORT_Y 720

#define TILE_PIXEL_WIDTH 32
#define TILE_PIXEL_HEIGHT 32

#define SCROLL_PIXELS_PER_FRAME_X 8
#define SCROLL_PIXELS_PER_FRAME_Y 8

#define HALF_WINDOW_TILE_WIDTH (MAIN_VIEW_PORT_X / TILE_PIXEL_WIDTH) / 2
#define HALF_WINDOW_TILE_HEIGHT (MAIN_VIEW_PORT_Y / TILE_PIXEL_HEIGHT) / 2

#define WINDOW_TILE_WIDTH (HALF_WINDOW_TILE_WIDTH * 2) + 1
#define WINDOW_TILE_HEIGHT (HALF_WINDOW_TILE_HEIGHT * 2) + 1

#define TILE_BUFFER_SIZE (HALF_WINDOW_TILE_WIDTH + 1)

#define X_MAX_MAP_SIZE 100
#define X_MIN_MAP_SIZE 1

#define Y_MAX_MAP_SIZE 100
#define Y_MIN_MAP_SIZE 1

#define DegreeToRadian 0.0174532925f
#define engineBaseSpeed 0.018f

#define VertexFVF (D3DFVF_XYZRHW | D3DFVF_TEX1 | D3DFVF_SPECULAR | D3DFVF_DIFFUSE)

typedef struct{
    float X;
    float Y;
    float Z;
    float W;
    int color;
    int specular;
    float tU;
    float tV;
} _TLVertex;

class cEngine{
    protected:
        static cEngine* pI;

    public:
        ~cEngine();
        void Initialize(HWND);
        void RenderScene();
        void DrawVertex(int, short, short, short, short, short, short, bool, int);

        static void setInterface(cEngine * newInterface){pI = newInterface;}
        static cEngine* p_cGIn(){return pI;}

        void Draw_Texture(_Grh&, short, short, bool, bool, bool);
        void Draw_GrhIndex(short, short, short, int);
        void RenderScreen(short, short, short, short);
        void Draw_Text(std::string, short, short, int, bool, int);
        void RenderGUI();
        void CreateFont();
        void Draw_DX_Text(std::string, short, short, int);
        int Engine_Text_Width(std::string, bool);
        int Engine_Text_Height(std::string, bool);

        LPDIRECT3D9 Direct3D;
        LPDIRECT3DDEVICE9 Direct3DDevice;
        ID3DXFont* dxfont;
		IDirect3DStateBlock9* D3DStateBlock;

		bool prgRun;

        long lFrameTimer;
        long FramesPerSecCounter;
        long FPS;
        float timerTicksPerFrame;

        _Grh grhInventory;
};
#endif // _H_ENGINE_

