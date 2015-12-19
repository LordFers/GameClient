#ifndef _H_SURFACE_
#define _H_SURFACE_
#include <iostream>
#include <map>
#include <d3dx9.h>

typedef struct{
    LPDIRECT3DTEXTURE9 pTexture; //pointer to Texture (DX9)
    int texture_width;
    int texture_height;
} _Texture;

class surface{
    public:
        void GetTexture(LPDIRECT3DTEXTURE9&, int, int&, int&);
        std::map <int, _Texture> TextureDB;
};

#endif // _H_SURFACE_
