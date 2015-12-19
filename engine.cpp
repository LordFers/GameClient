#include "GUI.h"
#include "engine.hpp"
#include "inventory.hpp"

using namespace std;
surface SurfaceDB;
cEngine* cEngine::pI = NULL;

cEngine::~cEngine()
{
    delete cEngine::pI;
}

void cEngine::Initialize(HWND hwnd)
{
    Direct3D = Direct3DCreate9(D3D_SDK_VERSION);

    D3DPRESENT_PARAMETERS D3DWindow;
    ZeroMemory(&D3DWindow, sizeof(D3DWindow));

    D3DWindow.Windowed = true;
    D3DWindow.SwapEffect = D3DSWAPEFFECT_DISCARD;
	D3DWindow.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;// D3DPRESENT_INTERVAL_ONE; //D3DPRESENT_INTERVAL_IMMEDIATE
    D3DWindow.hDeviceWindow = hwnd;
    D3DWindow.BackBufferFormat = D3DFMT_X8R8G8B8;
    D3DWindow.BackBufferWidth = MAIN_VIEW_PORT_X;
    D3DWindow.BackBufferHeight = MAIN_VIEW_PORT_Y;
    D3DWindow.EnableAutoDepthStencil = true;
    D3DWindow.AutoDepthStencilFormat = D3DFMT_D16;

    Direct3D->CreateDevice(D3DADAPTER_DEFAULT,
                      D3DDEVTYPE_HAL,
                      hwnd,
                      D3DCREATE_HARDWARE_VERTEXPROCESSING,
                      &D3DWindow,
                      &Direct3DDevice);

    Direct3DDevice->SetFVF(VertexFVF);
    Direct3DDevice->SetRenderState(D3DRS_LIGHTING, false);
    Direct3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	Direct3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	Direct3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Direct3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	Direct3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	// setup scene alpha blending
	Direct3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	Direct3DDevice->CreateStateBlock(D3DSBT_ALL, &D3DStateBlock);

    CreateFont();
	GUI::setInterface(new GUI());
	GUI::p_cGIn()->Initialize(Direct3DDevice);

	//When all is okay, prgRun true.
	prgRun = true;
}

void cEngine::RenderScene()
{
    Direct3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, 0, 1.0f, 0);
    Direct3DDevice->BeginScene();
	cGameData *Game = cGameData::p_cGIn();
	if (Game->Connected | Game->inCP) Game->ShowNextFrame();

		CEGUI::System::getSingleton().renderAllGUIContexts();
		D3DStateBlock->Apply();
		if (Game->Connected) Draw_Text("60.1% - (20326/106500)", MAIN_VIEW_PORT_X / 2.25, MAIN_VIEW_PORT_Y - 35, 1, false, -1);
    Direct3DDevice->EndScene();
    Direct3DDevice->Present(NULL, NULL, NULL, NULL);
}

/*void cEngine::RenderConsole()
{
	cGameData *Game = cGameData::p_cGIn();
	int ultdialog = Game->Console.ultimateDialog;
	int index = 0;
	for (int i = 0; i < 5; ++i)
	{
		index = (ultdialog - 5) + i + 1;
		if (index < 0) index = 0;
		if (!Game->Console.dialogos[index].text.c_str()) Game->Console.dialogos[index].text = "";

		Draw_DX_Text(Game->Console.dialogos[index].text, 32, 600 + i * 16, Game->Console.dialogos[index].color);
	}
}*/ //lo reemplazamos por cegui

void cEngine::CreateFont()
{
    D3DXCreateFontA(Direct3DDevice, 10, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
                    DEFAULT_PITCH|FF_DONTCARE, "Verdana", &dxfont);
}

void cEngine::Draw_DX_Text(string text, short x, short y, int color)
{
    static RECT textbox;
    int lenstring = strlen(text.c_str());

	SetRect(&textbox, x, y, MAIN_VIEW_PORT_X, MAIN_VIEW_PORT_Y);
    dxfont->DrawTextA(NULL, text.c_str(), lenstring, &textbox, NULL, color);
}

void cEngine::Draw_GrhIndex(short grhIndex, short x, short y, int color)
{
    if (grhIndex <= 0) return;

    DrawVertex(grhIndex, x, y,
            cGameData::p_cGIn()->GrhData[grhIndex].pixelWidth,
            cGameData::p_cGIn()->GrhData[grhIndex].pixelHeight,
            cGameData::p_cGIn()->GrhData[grhIndex].sX,
            cGameData::p_cGIn()->GrhData[grhIndex].sY, false, color);
}

void cEngine::Draw_Texture(_Grh &grh, short x, short y, bool center, bool animate, bool alpha)
{
    if (grh.grhIndex <= 0) return;
    if (cGameData::p_cGIn()->GrhData[grh.grhIndex].numFrames == 0) return;
    if (animate)
    {
        if (grh.started)
        {
			grh.frameCounter = grh.frameCounter + (cGameData::p_cGIn()->timerElapsedTime * cGameData::p_cGIn()->GrhData[grh.grhIndex].numFrames / grh.speed);
            if (grh.frameCounter > cGameData::p_cGIn()->GrhData[grh.grhIndex].numFrames)
            {
                grh.frameCounter = ((int)grh.frameCounter % (int)cGameData::p_cGIn()->GrhData[grh.grhIndex].numFrames) + 1;
                if (grh.loops != -1)
                {
                    if (grh.loops > 0)
                    {
                        grh.loops--;
                    }
                    else
                    {
                        grh.started = false;
                    }
                }
            }
        }
    }


	if (grh.frameCounter + 0.5f < 1.0f) grh.frameCounter = 1.0f;
	int currentGrhIndex = cGameData::p_cGIn()->GrhData[grh.grhIndex].frames[(int)(grh.frameCounter + 0.5f)];

    if (center)
    {
        if (cGameData::p_cGIn()->GrhData[currentGrhIndex].tileWidth != 1)
        {
            x = x - (int)(cGameData::p_cGIn()->GrhData[currentGrhIndex].tileWidth * TILE_PIXEL_WIDTH / 2) + TILE_PIXEL_WIDTH / 2;
        }

        if (cGameData::p_cGIn()->GrhData[currentGrhIndex].tileHeight != 1)
        {
            y = y - (int)(cGameData::p_cGIn()->GrhData[currentGrhIndex].tileHeight * TILE_PIXEL_HEIGHT) + TILE_PIXEL_HEIGHT;
        }
    }

    if (currentGrhIndex == 0) return;
    if (cGameData::p_cGIn()->GrhData[currentGrhIndex].filenum == 0) return;

    DrawVertex(currentGrhIndex, x, y,
            cGameData::p_cGIn()->GrhData[currentGrhIndex].pixelWidth,
            cGameData::p_cGIn()->GrhData[currentGrhIndex].pixelHeight,
            cGameData::p_cGIn()->GrhData[currentGrhIndex].sX,
            cGameData::p_cGIn()->GrhData[currentGrhIndex].sY, alpha, cGameData::p_cGIn()->ambient_color);
}

void cEngine::DrawVertex(int grhindex, short x, short y, short src_width, short src_height, short sX, short sY, bool blend, int vtxcolor)
{
    if (blend)
    {
        Direct3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
        Direct3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
    }

    int textureWidth, textureHeight;
    LPDIRECT3DTEXTURE9 pTexture;

    SurfaceDB.GetTexture(pTexture, cGameData::p_cGIn()->GrhData[grhindex].filenum, textureWidth, textureHeight);

    float src_right = sX + src_width;
    float src_bottom = sY + (src_height);
    float dest_right = x + (src_right - sX);
    float dest_bottom = y + (src_bottom - sY);

    _TLVertex vertex[4];
	vertex[0] = {(float)x,  dest_bottom, 0.0f, 1.0f, vtxcolor, 0, (float)sX / textureWidth, ((float)src_bottom + 1.0f) / textureHeight};
	vertex[1] = {(float)x,  (float)y, 0.0f, 1.0f, vtxcolor, 0, (float)sX / textureWidth, (float)sY / textureHeight };
	vertex[2] = {dest_right, dest_bottom, 0.0f, 1.0f, vtxcolor, 0, ((float)src_right + 1.0f) / textureWidth, ((float)src_bottom + 1.0f) / textureHeight};
	vertex[3] = {dest_right, (float)y, 0.0f, 1.0f, vtxcolor, 0, ((float)src_right + 1.0f) / textureWidth, (float)sY / textureHeight};

    Direct3DDevice->SetTexture(NULL, pTexture);
    Direct3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(vertex[0]));

    if (blend)
    {
        Direct3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
        Direct3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    }
}

void cEngine::RenderScreen(short tilex, short tiley, short PixelOffsetX, short PixelOffsetY)
{
    cGameData* GameData = cGameData::p_cGIn();

    short y; short x;
    short screenminY = 0; short screenmaxY = 0;
    short screenminX = 0; short screenmaxX = 0;
    short minY; short maxY;
    short minX; short maxX;
    short ScreenX = 0; short ScreenY = 0;
    short minXOffset = 0; short minYOffset = 0;

    screenminY = tiley - HALF_WINDOW_TILE_HEIGHT;
    screenmaxY = tiley + HALF_WINDOW_TILE_HEIGHT;
    screenminX = tilex - HALF_WINDOW_TILE_WIDTH;
    screenmaxX = tilex + HALF_WINDOW_TILE_WIDTH;

    minY = screenminY - TILE_BUFFER_SIZE;
    maxY = screenmaxY + TILE_BUFFER_SIZE;
    minX = screenminX - TILE_BUFFER_SIZE;
    maxX = screenmaxX + TILE_BUFFER_SIZE;

    if (minY < X_MIN_MAP_SIZE)
    {
        minYOffset = Y_MIN_MAP_SIZE - minY;
        minY = Y_MIN_MAP_SIZE;
    }

    if (maxY > Y_MAX_MAP_SIZE) maxY = Y_MAX_MAP_SIZE;

    if (minX < X_MIN_MAP_SIZE)
    {
        minXOffset = X_MIN_MAP_SIZE - minX;
        minX = X_MIN_MAP_SIZE;
    }

    if (maxX > X_MAX_MAP_SIZE) maxX = X_MAX_MAP_SIZE;

    if (screenminY > Y_MIN_MAP_SIZE)
    {
        screenminY = screenminY - 1;
    }
    else
    {
        screenminY = 1;
        ScreenY = 1;
    }

    if (screenmaxY < Y_MAX_MAP_SIZE) screenmaxY = screenmaxY + 1;

    if (screenminX > X_MIN_MAP_SIZE)
    {
        screenminX = screenminX - 1;
    }
    else
    {
        screenminX = 1;
        ScreenX = 1;
    }

    if (screenmaxX < X_MAX_MAP_SIZE) screenmaxX = screenmaxX + 1;

    if (screenmaxX > X_MAX_MAP_SIZE) screenmaxX = X_MAX_MAP_SIZE;
    if (screenmaxY > Y_MAX_MAP_SIZE) screenmaxY = Y_MAX_MAP_SIZE;
    if (screenminX < X_MIN_MAP_SIZE) screenminX = X_MIN_MAP_SIZE;
    if (screenminY < Y_MIN_MAP_SIZE) screenminY = Y_MIN_MAP_SIZE;

    for (y = screenminY; y <= screenmaxY; y++)
    {
        for(x = screenminX; x <= screenmaxX; x++)
        {
            Draw_Texture(GameData->MapData[x][y].layer[1],
                (ScreenX - 1) * TILE_PIXEL_WIDTH + PixelOffsetX,
                (ScreenY - 1) * TILE_PIXEL_HEIGHT + PixelOffsetY, true, true, false);

            if (GameData->MapData[x][y].layer[2].grhIndex != 0)
            {
                Draw_Texture(GameData->MapData[x][y].layer[2],
                    (ScreenX - 1) * TILE_PIXEL_WIDTH + PixelOffsetX,
                    (ScreenY - 1) * TILE_PIXEL_HEIGHT + PixelOffsetY, true, true, false);
            }

            ScreenX++;
        }
        ScreenX = ScreenX - x + screenminX;
        ScreenY++;
    }

    ScreenY = minYOffset - TILE_BUFFER_SIZE;
    for (y = minY; y <= maxY; y++)
    {
        ScreenX = minXOffset - TILE_BUFFER_SIZE;
        for(x = minX; x <= maxX; x++)
        {
            if (GameData->MapData[x][y].objgrh.grhIndex != 0)
            {
                Draw_Texture(GameData->MapData[x][y].objgrh, ScreenX * TILE_PIXEL_WIDTH + PixelOffsetX,
                     ScreenY * TILE_PIXEL_HEIGHT + PixelOffsetY, true, true, false);
            }

			if (GameData->Connected)
			{
				if (GameData->MapData[x][y].charindex > 0)
				{
					GameData->CharRender(GameData->MapData[x][y].charindex, (ScreenX * TILE_PIXEL_WIDTH + PixelOffsetX), (ScreenY * TILE_PIXEL_HEIGHT + PixelOffsetY));
				}
			}

            if (GameData->MapData[x][y].layer[3].grhIndex != 0)
            {
                Draw_Texture(GameData->MapData[x][y].layer[3], ScreenX * TILE_PIXEL_WIDTH + PixelOffsetX,
                    ScreenY * TILE_PIXEL_HEIGHT + PixelOffsetY, true, true, false);
            }
            ScreenX++;
        }
        ScreenY++;
    }

    ScreenY = minYOffset - TILE_BUFFER_SIZE;
    for (y = minY; y <= maxY; y++)
    {
        ScreenX = minXOffset - TILE_BUFFER_SIZE;
        for(x = minX; x <= maxX; x++)
        {
            if (GameData->bTecho == false)
            {
                if (GameData->MapData[x][y].layer[4].grhIndex > 0)
                {
                    Draw_Texture(GameData->MapData[x][y].layer[4], ScreenX * 32 + PixelOffsetX,
                        ScreenY * 32 + PixelOffsetY, true, true, false);
                }
            }

            if (GameData->MapData[x][y].charindex > 0)
            {
                short charindex = GameData->MapData[x][y].charindex;
                if (GameData->charlist[charindex].dialog != "")
                {
                    if (GameData->charlist[charindex].offset_counter_y < 10)
                    {
                        GameData->charlist[charindex].offset_counter_y++;
                    }

                    short screen_x = (ScreenX * 32) + (static_cast<short>(GameData->charlist[charindex].MoveOffsetX) + PixelOffsetX);
                    short screen_y = (ScreenY * 32) + (static_cast<short>(GameData->charlist[charindex].MoveOffsetY) + PixelOffsetY);

                    Draw_Text(GameData->charlist[charindex].dialog, screen_x + 14 - Engine_Text_Width(GameData->charlist[charindex].dialog, true) / 4, screen_y + GameData->charlist[charindex].Body.HeadOffset.y - Engine_Text_Height(GameData->charlist[charindex].dialog, true) - GameData->charlist[charindex].offset_counter_y - 25, GameData->charlist[charindex].dialog_font_index, true, GameData->charlist[charindex].dialog_color);
                }
            }

            ScreenX++;
        }
        ScreenY++;
    }
}

int cEngine::Engine_Text_Width(string text, bool multi_line)
{
    cGameData* GameData = cGameData::p_cGIn();
    unsigned char a, b = 0, c, d, e, f;
    int width_text = 0;
    short grhIndex;
    d = 0;
    if (!multi_line)
    {
            for (a = 0; a < strlen(text.c_str()); a++)
            {
                b = text[a];
                if (b > 255) b = 0;
                grhIndex = GameData->font_types[1].ascii_code[b];
                if ((b != 32) && (b != 5) && (b != 129) && (b != 9) && (b != 4) && (b != 255) && (b != 2) && (b != 151) && (b != 152))
                {
                    if (grhIndex <= 0)
                    {
                        width_text += 5;
                    }
                    else
                    {
                        width_text += GameData->GrhData[GameData->GrhData[grhIndex].frames[1]].pixelWidth; //+1
                    }
                }
                else
                {
                    width_text += 4;
                }
            }
    }
    else
    {
        e = 0;
        f = 0;
        for (a = 0; a < strlen(text.c_str()); a++)
        {
            b = text[a];
            if (b > 255) b = 0;
            grhIndex = GameData->font_types[1].ascii_code[b];
            if ((b == 32) || (b == 13))
            {
                if (e >= 20)
                {
                    f++;
                    e = 0;
                    d = 0;
                }
                else
                {
                    if (b == 32) d += 4;
                }
            }
            else
            {
                if (grhIndex > 12)
                {
                    d += GameData->GrhData[GameData->GrhData[grhIndex].frames[1]].pixelWidth; //+1
                    if (d > width_text) width_text = d;
                }
            }
        }
    }
    return width_text;
}

int cEngine::Engine_Text_Height(string text, bool multi_line)
{
    cGameData* GameData = cGameData::p_cGIn();
    unsigned char a, b = 0, c, d, e, f;
    int height_text = 0;
    short grhIndex;
    d = 0;
    if (!multi_line)
    {
        height_text = 0;
    }
    else
    {
    e = 0;
	f = 0;
	for (a = 0; a < strlen(text.c_str()); a++)
        {
	    b = (int)text[a];
	    if (b > 255) b = 0;
	    if ((b == 32) || (b == 13))
	    {
	        if (e >= 20)
		{
		    f++;
		    e = 0;
		    d = 0;
		}
		else
		{
		    if (b == 32) d += 4;
		}
            }
	    e++;
	}
	height_text = f * 14;
    }

return height_text;
}

void cEngine::Draw_Text(string text, short x, short y, int font_index, bool multi_line, int colortexto)
{
    cGameData* GameData = cGameData::p_cGIn();
    unsigned char a, b = 0, c, d, e, f;
    short grhIndex;
    if (text == "") return;
    d = 0;
    if (!multi_line)
    {
        for (a = 0; a < strlen(text.c_str()); a++)
        {
            b = text[a];
            if (b > 255) b = 0;
            grhIndex = GameData->font_types[font_index].ascii_code[b];
            if (b != 32)
            {
                if (grhIndex != 0)
                {
                    //mega sombra O-matica
                    grhIndex = (GameData->font_types[font_index].ascii_code[b] + 100);
                    Draw_GrhIndex(grhIndex, (x + d) + 1, y + 1, colortexto);
                    grhIndex = (GameData->font_types[font_index].ascii_code[b]);
                    Draw_GrhIndex(grhIndex, (x + d) + 1, y, colortexto);
                    d = d + GameData->GrhData[GameData->GrhData[grhIndex].frames[1]].pixelWidth;
                }
            }
            else
            {
                d = d + 4;
            }
        }
    }
    else
    {
        e = 0;
        f = 0;
        for (a = 0; a < strlen(text.c_str()); a++)
        {
            b = (int)text[a];
            grhIndex = GameData->font_types[1].ascii_code[b];
            if (b > 255) b = 0;
            if (b == 32 || b == 13)
            {
                if (e >= 20)
                {
                    f++;
                    e = 0;
                    d = 0;
                }
                else
                {
                    if (b == 32) d = d + 4;
                }
            }
            else
            {
                if (grhIndex > 12)
                {
                    grhIndex = GameData->font_types[font_index].ascii_code[b] + 100;
                    Draw_GrhIndex(grhIndex, (x + d) + 1, y + 1 + f * 14, colortexto);

                    grhIndex = GameData->font_types[font_index].ascii_code[b];
                    Draw_GrhIndex(grhIndex, (x + d), y + f * 14, colortexto);
                    d = d + GameData->GrhData[GameData->GrhData[grhIndex].frames[1]].pixelWidth;
                }
            }
            e++;
        }
    }
}

template <typename T> string NumberToString (T Number)
{
    ostringstream ss;
    ss << Number;
	return (string)ss.str();
}

void cEngine::RenderGUI()
{
	if (!cGameData::p_cGIn()->Connected) return;
    int normalcolor = D3DCOLOR_ARGB(200, 255, 255, 255);

    cGameData* GameData = cGameData::p_cGIn();
    cInventory* charInv = &GameData->CharInventory;
    cInventory* NPCInv = &GameData->NPCInventory;

    short charX = charInv->posX; short charY = charInv->posY; short countA = 1; short countB = 1;
    short npcX = 100; short npcY = 400;

    if (NPCInv->visible)Draw_GrhIndex(24193, npcX, npcY, normalcolor);
    if (charInv->visible)Draw_GrhIndex(24193, charX, charY, normalcolor);

    Draw_GrhIndex(24197, 8, 8, -1);

    string strB_number = NumberToString<int>(GameData->UserMinHP) + "/" + NumberToString<int>(GameData->UserMaxHP);
    short lenstr = strlen(strB_number.c_str());

    Draw_DX_Text(strB_number, 123 - lenstr, 29, -1);
    for (short i = 1; i <= 24; ++i)
    {
        if (countA > 6)
        {
            countA = 1;
            countB++;
        }

        if (charInv->visible)
        {
            if (charInv->Slot[i].amount > 0)
            {
                int colorinv = D3DCOLOR_ARGB(255, 128, 128, 128);
                if (GameData->InvSelectedItem == i) colorinv = D3DCOLOR_ARGB(255, 255, 255, 255);

                if (charInv->Slot[i].equipped)
                {
                    if (GameData->InvSelectedItem == i)
                    {
                        Draw_GrhIndex(charInv->Slot[i].grhIndex, (charX + 20) + ((countA-1) * 48), (charY + 18) + ((countB-1) * 47), -8323200);
                    }
                    else
                    {
                        Draw_GrhIndex(charInv->Slot[i].grhIndex, (charX + 20) + ((countA-1) * 48), (charY + 18) + ((countB-1) * 47), 2155937664);
                    }
                }
                else
                {
                    Draw_GrhIndex(charInv->Slot[i].grhIndex, (charX + 20) + ((countA-1) * 48), (charY + 18) + ((countB-1) * 47), colorinv);
                }

                Draw_DX_Text(NumberToString<short>(charInv->Slot[i].amount), (charX + 20) + ((countA-1) * 48), (charY + 18) + ((countB-1) * 47), colorinv);
            }
        }

        if (NPCInv->visible)
        {
            if (NPCInv->Slot[i].amount > 0)
            {
                int colorinv = D3DCOLOR_ARGB(255, 128, 128, 128);

                Draw_Text(NumberToString<short>(NPCInv->Slot[i].amount), (npcX + 20) + ((countA-1) * 48), (npcY + 18) + ((countB-1) * 47), 1, false, colorinv);
                Draw_GrhIndex(NPCInv->Slot[i].grhIndex, (npcX + 20) + ((countA-1) * 48), (npcY + 18) + ((countB-1) * 47), colorinv);
            }
        }

        countA++;
    }

	//FPS
    Draw_Text(NumberToString<long>(FPS) + " FPS", MAIN_VIEW_PORT_X - 56, 12, 1, false, -1);
}