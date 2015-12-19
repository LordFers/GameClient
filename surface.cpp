#include "surface.hpp"

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <windows.h>
#include <tchar.h>
#include "engine.hpp"

using namespace std;

void surface::GetTexture(LPDIRECT3DTEXTURE9 &pTexture, int filenum, int &textureWidth, int &textureHeight)
{
    map<int, _Texture>::iterator iter = TextureDB.find(filenum);
    if (iter != TextureDB.end())
    {
        pTexture = TextureDB[filenum].pTexture;
        textureWidth = TextureDB[filenum].texture_width;
        textureHeight = TextureDB[filenum].texture_height;
        return;
    }

    _Texture textura_new;

    stringstream filename;
    filename << "resources/graphics/" << filenum << ".bmp";
    std::string strfile = filename.str();
	const char* file = strfile.c_str();

    D3DXIMAGE_INFO texture_info;
    D3DXCreateTextureFromFileExA(cEngine::p_cGIn()->Direct3DDevice, file, D3DX_FROM_FILE, D3DX_FROM_FILE, 1, 0,
                                D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE,
                                0xff000000, &texture_info, NULL, &pTexture);

    textureWidth = texture_info.Width;
    textureHeight = texture_info.Height;
    textura_new.texture_width = textureWidth;
    textura_new.texture_height = textureHeight;
    textura_new.pTexture = pTexture;

    TextureDB.insert(pair<int, _Texture>(filenum, textura_new));
}
