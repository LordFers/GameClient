#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include "gamedata.hpp"
#include "engine.hpp"
#include "Protocol.hpp"
#include "FConnect.h"

using namespace std;

char cabecera[263];
cGameData* cGameData::pI = NULL;

void cGameData::LoadGrh()
{
	
    ifstream file("resources/inits/graphics.ind", ios::in|ios::binary|ios::ate);
    if (!file.is_open())
    {
        cout << "Don't exist the file 'graphics.ind'.";
        return;
    }

    int grhCount = 0;
    int Grh = 0;
    int tempint;
    float tempfloat;
    short tempshort;

    file.seekg (0, ios::beg);

    file.read((char *)&tempint, 4);
    file.read((char *)&grhCount, 4);

    GrhData = new _GrhData[grhCount];

    while (Grh < grhCount)
    {
        file.read((char *)&tempint, 4);
        Grh = tempint;

        file.read((char *)&tempint, 2);
        GrhData[Grh].numFrames = tempint;

        if (GrhData[Grh].numFrames <= 0)
        {
            printf("ERROR IN THE GRHINDEX: %d", Grh);
            return;
        }

        GrhData[Grh].frames = new int[GrhData[Grh].numFrames + 1];
        if (GrhData[Grh].numFrames > 1)
        {
            for(int frame = 1; frame <= GrhData[Grh].numFrames; frame++)
            {
                file.read((char *)&tempint, 4);
                GrhData[Grh].frames[frame] = tempint;
                if (GrhData[Grh].frames[frame] <= 0)
                {
                    printf("ERROR IN THE GRHINDEX: %d", Grh);
                    return;
                }
            }

            file.read((char *)&tempfloat, 4);
            if (tempfloat <= 0) {printf("ERROR IN THE GRHINDEX: %d", Grh);return;}
            GrhData[Grh].speed = tempfloat;

            GrhData[Grh].pixelHeight = GrhData[GrhData[Grh].frames[1]].pixelHeight;
            if (GrhData[Grh].pixelHeight <= 0){printf("ERROR IN THE GRHINDEX: %d", Grh); return;}
            GrhData[Grh].pixelWidth = GrhData[GrhData[Grh].frames[1]].pixelWidth;
            if (GrhData[Grh].pixelWidth <= 0){printf("ERROR IN THE GRHINDEX: %d", Grh); return;}
            GrhData[Grh].tileWidth = GrhData[GrhData[Grh].frames[1]].tileWidth;
            if (GrhData[Grh].tileWidth <= 0){printf("ERROR IN THE GRHINDEX: %d", Grh); return;}
            GrhData[Grh].tileHeight = GrhData[GrhData[Grh].frames[1]].tileHeight;
            if (GrhData[Grh].tileHeight <= 0){printf("ERROR IN THE GRHINDEX: %d", Grh); return;}
        }
        else
        {
            file.read((char *)&tempint, 4);
            GrhData[Grh].filenum = tempint;
            if (GrhData[Grh].filenum <= 0){printf("ERROR IN THE GRHINDEX filenum: %d", Grh); return;}

            file.read((char *)&tempshort, 2);
            GrhData[Grh].sX = tempshort;
            if (GrhData[Grh].sX < 0){printf("ERROR IN THE GRHINDEX sX: %d", Grh); return;}

            file.read((char *)&tempshort, 2);
            GrhData[Grh].sY = tempshort;
            if (GrhData[Grh].sY < 0){printf("ERROR IN THE GRHINDEX sY: %d", Grh); return;}

            file.read((char *)&tempshort, 2);
            GrhData[Grh].pixelWidth = tempshort;
            if (GrhData[Grh].pixelWidth <= 0){printf("ERROR IN THE GRHINDEX pW: %d", Grh); return;}

            file.read((char *)&tempshort, 2);
            GrhData[Grh].pixelHeight = tempshort;
            if (GrhData[Grh].pixelHeight <= 0){printf("ERROR IN THE GRHINDEX pH: %d", Grh); return;}

            GrhData[Grh].tileWidth = (float)GrhData[Grh].pixelWidth / 32;
            GrhData[Grh].tileHeight = (float)GrhData[Grh].pixelHeight / 32;

            GrhData[Grh].frames[1] = Grh;
        }
    }

    file.close();
}

void cGameData::LoadBodys()
{
    _tIndexBodys* myBodys;
    ifstream file("resources/inits/bodys.ind", ios::in|ios::binary|ios::ate);
	
    if (!file.is_open())
    {
        cout << "Don't exist the file 'bodys.ind'.";
        return;
    }

    short numBodys;

    file.seekg (0, ios::beg);
    file.read((char *)&cabecera, sizeof(cabecera));
    file.read((char *)&numBodys, 2);

    BodyData = new _BodyData[numBodys + 1];
    myBodys = new _tIndexBodys[numBodys + 1];

    for (int i = 1; i <= numBodys; i++)
    {
        file.read((char *)&myBodys[i].Body[1], 2);
        file.read((char *)&myBodys[i].Body[2], 2);
        file.read((char *)&myBodys[i].Body[3], 2);
        file.read((char *)&myBodys[i].Body[4], 2);

        file.read((char *)&myBodys[i].HeadOffsetX, 2);
        file.read((char *)&myBodys[i].HeadOffsetY, 2);

        if (myBodys[i].Body[1] != 0)
        {
            InitGrh(BodyData[i].Walk[1], myBodys[i].Body[1], false);
            InitGrh(BodyData[i].Walk[2], myBodys[i].Body[2], false);
            InitGrh(BodyData[i].Walk[3], myBodys[i].Body[3], false);
            InitGrh(BodyData[i].Walk[4], myBodys[i].Body[4], false);

            BodyData[i].HeadOffset.x = myBodys[i].HeadOffsetX;
            BodyData[i].HeadOffset.y = myBodys[i].HeadOffsetY;
        }
    }

	InitGrh(BodyData[0].Walk[1], 0, false);
	InitGrh(BodyData[0].Walk[2], 0, false);
	InitGrh(BodyData[0].Walk[3], 0, false);
	InitGrh(BodyData[0].Walk[4], 0, false);

	BodyData[0].HeadOffset.x = 0;
	BodyData[0].HeadOffset.y = 0;

    delete [] myBodys;

    file.close();
}

void cGameData::LoadHeads()
{
    _tIndexHeads* myHeads;
    ifstream file("resources/inits/heads.ind", ios::in|ios::binary|ios::ate);

    if (!file.is_open())
    {
        cout << "Don't exist the file 'heads.ind'.";
        return;
    }

    short numHeads;

    file.seekg (0, ios::beg);
    file.read((char *)&cabecera, sizeof(cabecera));
    file.read((char *)&numHeads, 2);

    HeadData = new _HeadData[numHeads + 1];
    myHeads = new _tIndexHeads[numHeads + 1];

    for (int i = 1; i <= numHeads; i++)
    {
        file.read((char *)&myHeads[i].Head[1], 2);
        file.read((char *)&myHeads[i].Head[2], 2);
        file.read((char *)&myHeads[i].Head[3], 2);
        file.read((char *)&myHeads[i].Head[4], 2);

        if (myHeads[i].Head[1] != 0)
        {
            InitGrh(HeadData[i].Head[1], myHeads[i].Head[1], false);
            InitGrh(HeadData[i].Head[2], myHeads[i].Head[2], false);
            InitGrh(HeadData[i].Head[3], myHeads[i].Head[3], false);
            InitGrh(HeadData[i].Head[4], myHeads[i].Head[4], false);
        }
    }

	InitGrh(HeadData[0].Head[1], 0, false);
	InitGrh(HeadData[0].Head[2], 0, false);
	InitGrh(HeadData[0].Head[3], 0, false);
	InitGrh(HeadData[0].Head[4], 0, false);

    delete [] myHeads;

    file.close();
}

void cGameData::LoadHelmets()
{
    _tIndexHeads* myHeads;
    ifstream file("resources/inits/helmets.ind", ios::in|ios::binary|ios::ate);

    if (!file.is_open())
    {
        cout << "Don't exist the file 'helmets.ind'.";
        return;
    }

    short numHelmets;

    file.seekg (0, ios::beg);
    file.read((char *)&cabecera, sizeof(cabecera));
    file.read((char *)&numHelmets, 2);

    HelmetsData = new _HeadData[numHelmets + 1];
    myHeads = new _tIndexHeads[numHelmets + 1];

    for (int i = 1; i <= numHelmets; i++)
    {
        file.read((char *)&myHeads[i].Head[1], 2);
        file.read((char *)&myHeads[i].Head[2], 2);
        file.read((char *)&myHeads[i].Head[3], 2);
        file.read((char *)&myHeads[i].Head[4], 2);

        if (myHeads[i].Head[1] != 0)
        {
            InitGrh(HelmetsData[i].Head[1], myHeads[i].Head[1], false);
            InitGrh(HelmetsData[i].Head[2], myHeads[i].Head[2], false);
            InitGrh(HelmetsData[i].Head[3], myHeads[i].Head[3], false);
            InitGrh(HelmetsData[i].Head[4], myHeads[i].Head[4], false);
        }
    }
	
	InitGrh(HelmetsData[0].Head[1], 0, false);
	InitGrh(HelmetsData[0].Head[2], 0, false);
	InitGrh(HelmetsData[0].Head[3], 0, false);
	InitGrh(HelmetsData[0].Head[4], 0, false);

    delete [] myHeads;

    file.close();
}

void cGameData::LoadShields()
{
    ifstream file("resources/inits/shields.ind", ios::in|ios::binary|ios::ate);

    if (!file.is_open())
    {
        cout << "Don't exist the file 'shields.ind'.";
        return;
    }

    short numShields;

    file.seekg (0, ios::beg);
    file.read((char *)&numShields, 2);

    ShieldData = new _ShieldData[numShields + 1];

    for (int i = 1; i <= numShields; i++)
    {
        file.read((char *)&ShieldData[i].ShieldWalk[1].grhIndex, 2);
        InitGrh(ShieldData[i].ShieldWalk[1], ShieldData[i].ShieldWalk[1].grhIndex, false);

        file.read((char *)&ShieldData[i].ShieldWalk[2].grhIndex, 2);
        InitGrh(ShieldData[i].ShieldWalk[2], ShieldData[i].ShieldWalk[2].grhIndex, false);

        file.read((char *)&ShieldData[i].ShieldWalk[3].grhIndex, 2);
        InitGrh(ShieldData[i].ShieldWalk[3], ShieldData[i].ShieldWalk[3].grhIndex, false);

        file.read((char *)&ShieldData[i].ShieldWalk[4].grhIndex, 2);
        InitGrh(ShieldData[i].ShieldWalk[4], ShieldData[i].ShieldWalk[4].grhIndex, false);
    }

	InitGrh(ShieldData[0].ShieldWalk[1], 0, false);
	InitGrh(ShieldData[0].ShieldWalk[2], 0, false);
	InitGrh(ShieldData[0].ShieldWalk[3], 0, false);
	InitGrh(ShieldData[0].ShieldWalk[4], 0, false);

    file.close();
}

void cGameData::LoadWeapons()
{
    ifstream file("resources/inits/weapons.ind", ios::in|ios::binary|ios::ate);

    if (!file.is_open())
    {
        cout << "Don't exist the file 'weapons.ind'.";
        return;
    }

    short numWeapons;

    file.seekg (0, ios::beg);
    file.read((char *)&numWeapons, 2);

    WeaponData = new _WeaponData[numWeapons + 1];

    for (int i = 1; i <= numWeapons; i++)
    {
        file.read((char *)&WeaponData[i].WeaponWalk[1].grhIndex, 2);
        InitGrh(WeaponData[i].WeaponWalk[1], WeaponData[i].WeaponWalk[1].grhIndex, false);

        file.read((char *)&WeaponData[i].WeaponWalk[2].grhIndex, 2);
        InitGrh(WeaponData[i].WeaponWalk[2], WeaponData[i].WeaponWalk[2].grhIndex, false);

        file.read((char *)&WeaponData[i].WeaponWalk[3].grhIndex, 2);
        InitGrh(WeaponData[i].WeaponWalk[3], WeaponData[i].WeaponWalk[3].grhIndex, false);

        file.read((char *)&WeaponData[i].WeaponWalk[4].grhIndex, 2);
        InitGrh(WeaponData[i].WeaponWalk[4], WeaponData[i].WeaponWalk[4].grhIndex, false);
    }

	InitGrh(WeaponData[0].WeaponWalk[1], 0, false);
	InitGrh(WeaponData[0].WeaponWalk[2], 0, false);
	InitGrh(WeaponData[0].WeaponWalk[3], 0, false);
	InitGrh(WeaponData[0].WeaponWalk[4], 0, false);

    file.close();
}

void cGameData::LoadFXs()
{
    ifstream file("resources/inits/fxs.ind", ios::in|ios::binary|ios::ate);

    if (!file.is_open())
    {
        cout << "Don't exist the file 'fxs.ind'.";
        return;
    }

    short NumFXs;

    file.seekg (0, ios::beg);
    file.read((char *)&cabecera, sizeof(cabecera));
    file.read((char *)&NumFXs, 2);

    FxData = new _FxData[NumFXs + 1];

    for (int i = 1; i <= NumFXs; i++)
    {
        file.read((char *)&FxData[i].Animation, 2);
        file.read((char *)&FxData[i].OffsetX, 2);
        file.read((char *)&FxData[i].OffsetY, 2);
    }

	FxData[0].Animation = 0;
	FxData[0].OffsetX = 0;
	FxData[0].OffsetY = 0;

    file.close();
}

cGameData::cGameData()
{
	inCP = false;
	Connected = false;
    MoveInvent = false;
    InvSelectedItem = 1;
    bTecho = false;
    UserParalizado = false;
    UserDescansar = false;
    UserMeditar = false;
    UserNavegando = false;
    LastChar = 0;
    UserMoving = 0;
    UserPos.x = 50;
    UserPos.y = 50;
    AddToUserPos.X = 0;
    AddToUserPos.Y = 0;

    CharInventory.posX = MAIN_VIEW_PORT_X - 314;
    CharInventory.posY = MAIN_VIEW_PORT_Y - 200;
    CharInventory.visible = true;

	FontTypes = new _tFont[20];

	for (int i = 0; i <= 20; i++)
	{
		FontTypes[i].color = -1;
		FontTypes[i].bold = false;
		FontTypes[i].italic = false;
	}

    font_types = new _Font[3];
    font_types[0].ascii_code = new short[256];
    font_types[1].ascii_code = new short[256];
    font_types[2].ascii_code = new short[256];

	font_types[0].font_size = 0;
	font_types[1].font_size = 0;
	font_types[2].font_size = 0;

    for (short i = 0; i < 256; ++i)
    {
        font_types[0].ascii_code[i] = 0;
        font_types[1].ascii_code[i] = 0;
        font_types[2].ascii_code[i] = 0;
    }

    charlist = new _tChar[10000];
    for (int i = 0; i < 10000; ++i) ResetCharInfo(i);

    MapData = new _MapData*[101];
    for (int i = 0; i <= 100; i++)
    {MapData[i] = new _MapData[101];}

	for (int x = 0; x <= 100; x++)
	{
		for (int y = 0; y <= 100; y++)
		{
			MapData[x][y].blocked = 0;
			MapData[x][y].npcindex = 0;
			MapData[x][y].trigger = 0;
			MapData[x][y].charindex = 0;
		}
	}
}

cGameData::~cGameData()
{
    delete [] UserSkills;
    delete [] PorcentajeSkills;

    for (int i = 0; i <= 100; i++)
    {delete [] MapData[i];}
    delete [] MapData;

    for (int i = 0; i <= UBound(GrhData); ++i)
    {delete [] GrhData[i].frames;}

    delete [] GrhData;
    delete [] charlist;
	delete [] FontTypes;
    delete [] font_types[0].ascii_code;
    delete [] font_types[1].ascii_code;
    delete [] font_types[2].ascii_code;
    delete [] font_types;
    delete [] BodyData;
    delete [] HeadData;
    delete [] HelmetsData;
    delete [] ShieldData;
    delete [] WeaponData;
    delete cGameData::pI;
}

void cGameData::LoadMap(int curmap)
{
    stringstream filename;
    filename << "resources/maps/mapa" << curmap << ".map";
	
    string strfile = filename.str();
    const char* _file = strfile.c_str();

    ifstream file(_file, ios::in|ios::binary|ios::ate);
    if (!file.is_open())
    {
        cout << "Don't exist the Mapa " << _file << " in the files.";

        return;
    }

    short mapversion = 0;
    short tempint = 0;

    unsigned char byflags = 0;

    file.seekg(0, ios::beg);
    file.read((char *)&mapversion, sizeof(mapversion));
    file.read((char *)&cabecera, sizeof(cabecera));

    file.read((char *)&tempint, sizeof(tempint));
    file.read((char *)&tempint, sizeof(tempint));
    file.read((char *)&tempint, sizeof(tempint));
    file.read((char *)&tempint, sizeof(tempint));

    for (short y = 1; y <= 100; y++)
    {
        for (short x = 1; x <= 100; x++)
        {
            file.read((char *)&byflags, sizeof(byflags));
            MapData[x][y].blocked = (byflags & 1);

            file.read((char *)&tempint, sizeof(tempint));
            MapData[x][y].layer[1].grhIndex = tempint;
            InitGrh(MapData[x][y].layer[1], MapData[x][y].layer[1].grhIndex, true);

            if (byflags & 2)
            {
                file.read((char *)&tempint, sizeof(tempint));
                MapData[x][y].layer[2].grhIndex = tempint;
                InitGrh(MapData[x][y].layer[2], MapData[x][y].layer[2].grhIndex, true);
            }
            else
            {
                MapData[x][y].layer[2].grhIndex = 0;
            }

            if (byflags & 4)
            {
                file.read((char *)&tempint, sizeof(tempint));
                MapData[x][y].layer[3].grhIndex = tempint;
                InitGrh(MapData[x][y].layer[3], MapData[x][y].layer[3].grhIndex, true);
            }
            else
            {
                MapData[x][y].layer[3].grhIndex = 0;
            }

            if (byflags & 8)
            {
                file.read((char *)&tempint, sizeof(tempint));
                MapData[x][y].layer[4].grhIndex = tempint;
                InitGrh(MapData[x][y].layer[4], MapData[x][y].layer[4].grhIndex, true);
            }
            else
            {
                MapData[x][y].layer[4].grhIndex = 0;
            }

            MapData[x][y].trigger = 0;

            if (byflags & 16)
            {
                file.read((char *)&tempint, sizeof(tempint));
                MapData[x][y].trigger = tempint;
            }

            if (MapData[x][y].charindex > 0)
            {
                EraseChar(MapData[x][y].charindex);
            }

            MapData[x][y].charindex = 0;
            MapData[x][y].objinfo.objindex = 0;
            MapData[x][y].objinfo.amount = 0;
            MapData[x][y].objgrh.grhIndex = 0;
        }
    }

    ambient_color = -1;
    file.close();
}

void cGameData::InitGrh(_Grh &Grh, short grhindex, bool started)
{
    Grh.grhIndex = grhindex;
    Grh.frameCounter = 1;

    if (started)
    {
        if (GrhData[Grh.grhIndex].numFrames > 1)
        {
            Grh.started = true;
        }
        else
        {
            Grh.started = false;
        }
    }
    else
    {
        started = true; //REVISAR ESTO
        if (GrhData[Grh.grhIndex].numFrames == 1) started = false;
        Grh.started = started;
    }

    if (Grh.started)
    {
        Grh.loops = -1;
    }
    else
    {
        Grh.loops = 0;
    }

    Grh.frameCounter = 1;
    Grh.speed = GrhData[Grh.grhIndex].speed;
}

void cGameData::LoadFontsConsole()
{
	//FONTTYPE_TALK
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_TALK].color				= -1;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_TALK].bold				= false;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_TALK].italic			= false;
	
	//FONTTYPE_FIGHT
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_FIGHT].color			= 0xffff;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_FIGHT].bold				= true;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_FIGHT].italic			= false;

	//FONTTYPE_WARNING
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_WARNING].color			= 0xff2033df;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_WARNING].bold			= true;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_WARNING].italic			= true;

	//FONTTYPE_INFO
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_INFO].color				= 0xff41be9c;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_INFO].bold				= false;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_INFO].italic			= false;

	//FONTTYPE_INFOBOLD
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_INFOBOLD].color			= 0xff41be9c;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_INFOBOLD].bold			= true;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_INFOBOLD].italic		= false;

	//FONTTYPE_EJECUCION
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_EJECUCION].color		= 0xff828282;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_EJECUCION].bold			= true;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_EJECUCION].italic		= false;

	//FONTTYPE_PARTY
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_PARTY].color			= 0xffffb4fa;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_PARTY].bold				= false;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_PARTY].italic			= false;

	//FONTTYPE_VENENO
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_VENENO].color			= 0xff00ff;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_VENENO].bold			= false;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_VENENO].italic			= false;

	//FONTTYPE_GUILD
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_GUILD].color			= -1;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_GUILD].bold				= true;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_GUILD].italic			= false;

	//FONTTYPE_SERVER
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_SERVER].color			= 0xff00b9;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_SERVER].bold			= true;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_SERVER].italic			= false;

	//FONTTYPE_GUILDMSG
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_GUILDMSG].color			= 0xffe4c71b;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_GUILDMSG].bold			= false;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_GUILDMSG].italic		= false;

	//FONTTYPE_CONSEJO
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CONSEJO].color			= 0xff8282ff;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CONSEJO].bold			= true;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CONSEJO].italic			= false;

	//FONTTYPE_CONSEJOCAOS
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CONSEJOCAOS].color		= 0xffff3c;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CONSEJOCAOS].bold		= true;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CONSEJOCAOS].italic		= false;

	//FONTTYPE_CONSEJOVesA
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CONSEJOVesA].color		= 0xffc8ff;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CONSEJOVesA].bold		= true;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CONSEJOVesA].italic		= false;

	//FONTTYPE_CONSEJOCAOSVesA
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CONSEJOCAOSVesA].color	= 0xffff32;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CONSEJOCAOSVesA].bold	= true;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CONSEJOCAOSVesA].italic = false;

	//FONTTYPE_CENTINELA
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CENTINELA].color		= 0xff00ff;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CENTINELA].bold			= true;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CENTINELA].italic		= false;

	//FONTTYPE_GMMSG
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_GMMSG].color			= -1;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_GMMSG].bold				= false;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_GMMSG].italic			= true;

	//FONTTYPE_GM
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_GM].color				= 0xff1eff1e;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_GM].bold				= true;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_GM].italic				= false;

	//FONTTYPE_CITIZEN
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CITIZEN].color			= 0xff0000c8;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CITIZEN].bold			= true;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CITIZEN].italic			= false;

	//FONTTYPE_CONSE
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CONSE].color			= 0xff1e961e;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CONSE].bold				= true;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CONSE].italic			= false;

	//FONTTYPE_DIOS
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_DIOS].color				= 0xfffafa96;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_DIOS].bold				= true;
	FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_DIOS].italic			= false;
}

void cGameData::LoadFonts()
{
    int a;
    font_types[1].font_size = 9;
    font_types[1].ascii_code[48] = 23703;
    font_types[1].ascii_code[49] = 23704;
    font_types[1].ascii_code[50] = 23705;
    font_types[1].ascii_code[51] = 23706;
    font_types[1].ascii_code[52] = 23707;
    font_types[1].ascii_code[53] = 23708;
    font_types[1].ascii_code[54] = 23709;
    font_types[1].ascii_code[55] = 23710;
    font_types[1].ascii_code[56] = 23711;
    font_types[1].ascii_code[57] = 23712;

    for (a = 0; a <= 25; a++)
    {
        font_types[1].ascii_code[a + 97] = 23651 + a;
    }

    for (a = 0; a <= 25; a++)
    {
        font_types[1].ascii_code[a + 65] = 23677 + a;
    }

    font_types[1].ascii_code[33] = 23713;
    font_types[1].ascii_code[161] = 23714;
    font_types[1].ascii_code[34] = 23715;
    font_types[1].ascii_code[36] = 23716;
    font_types[1].ascii_code[191] = 23717;
    font_types[1].ascii_code[35] = 23718;
    font_types[1].ascii_code[36] = 23719;
    font_types[1].ascii_code[37] = 23720;
    font_types[1].ascii_code[38] = 23721;
    font_types[1].ascii_code[47] = 23722;
    font_types[1].ascii_code[92] = 23723;
    font_types[1].ascii_code[40] = 23724;
    font_types[1].ascii_code[41] = 23725;
    font_types[1].ascii_code[61] = 23726;
    font_types[1].ascii_code[39] = 23727;
    font_types[1].ascii_code[123] = 23728;
    font_types[1].ascii_code[125] = 23729;
    font_types[1].ascii_code[95] = 23730;
    font_types[1].ascii_code[45] = 23731;
    font_types[1].ascii_code[63] = 23716;
    font_types[1].ascii_code[64] = 23732;
    font_types[1].ascii_code[94] = 23733;
    font_types[1].ascii_code[91] = 23734;
    font_types[1].ascii_code[93] = 23735;
    font_types[1].ascii_code[60] = 23736;
    font_types[1].ascii_code[62] = 23737;
    font_types[1].ascii_code[42] = 23738;
    font_types[1].ascii_code[43] = 23739;
    font_types[1].ascii_code[46] = 23740;
    font_types[1].ascii_code[44] = 23741;
    font_types[1].ascii_code[58] = 23742;
    font_types[1].ascii_code[59] = 23743;
    font_types[1].ascii_code[124] = 23744;
    /////////////////
    font_types[1].ascii_code[252] = 23845;
    font_types[1].ascii_code[220] = 23846;
    font_types[1].ascii_code[225] = 23847;
    font_types[1].ascii_code[233] = 23848;
    font_types[1].ascii_code[237] = 23849;
    font_types[1].ascii_code[243] = 23850;
    font_types[1].ascii_code[250] = 23851;
    font_types[1].ascii_code[253] = 23852;
    font_types[1].ascii_code[193] = 23853;
    font_types[1].ascii_code[201] = 23854;
    font_types[1].ascii_code[205] = 23855;
    font_types[1].ascii_code[211] = 23856;
    font_types[1].ascii_code[218] = 23857;
    font_types[1].ascii_code[221] = 23858;
    font_types[1].ascii_code[224] = 23859;
    font_types[1].ascii_code[232] = 23860;
    font_types[1].ascii_code[236] = 23861;
    font_types[1].ascii_code[242] = 23862;
    font_types[1].ascii_code[249] = 23863;
    font_types[1].ascii_code[192] = 23864;
    font_types[1].ascii_code[200] = 23865;
    font_types[1].ascii_code[204] = 23866;
    font_types[1].ascii_code[210] = 23867;
    font_types[1].ascii_code[217] = 23868;
    font_types[1].ascii_code[195] = 23869;
    font_types[1].ascii_code[241] = 23869;
    font_types[1].ascii_code[209] = 23870;

    font_types[1].ascii_code[196] = 23970;
    font_types[1].ascii_code[194] = 23971;
    font_types[1].ascii_code[203] = 23972;
    font_types[1].ascii_code[207] = 23973;
    font_types[1].ascii_code[214] = 23974;
    font_types[1].ascii_code[212] = 23975;

    font_types[1].ascii_code[172] = 23975;
    //
    font_types[2].font_size = 9;
    font_types[2].ascii_code[97] = 24076;
    font_types[2].ascii_code[108] = 24077;
    font_types[2].ascii_code[115] = 24078;
    font_types[2].ascii_code[70] = 24079;
    font_types[2].ascii_code[48] = 24080;
    font_types[2].ascii_code[49] = 24081;
    font_types[2].ascii_code[50] = 24082;
    font_types[2].ascii_code[51] = 24083;
    font_types[2].ascii_code[52] = 24084;
    font_types[2].ascii_code[53] = 24085;
    font_types[2].ascii_code[54] = 24086;
    font_types[2].ascii_code[55] = 24087;
    font_types[2].ascii_code[56] = 24088;
    font_types[2].ascii_code[57] = 24089;
    font_types[2].ascii_code[33] = 24090;
    font_types[2].ascii_code[161] = 24091;
    font_types[2].ascii_code[42] = 24092;
}

int getTagPosition(std::string name)
{
	int buff = vb6::InStr(name, "<");
	if (buff > 0) return buff;

	buff = vb6::InStr(name, "[");
	if (buff > 0) return buff;

	return (vb6::Len(name) + 2);
}

void cGameData::CharRender(short CharIndex, short PixelOffsetX, short PixelOffsetY)
{
    bool moved = false;
    _tChar* chars = &charlist[CharIndex];

	short addoffsetx = 0, addoffsety = 0;

    if (chars->Moving != 0)
    {
        if (chars->scrollDirectionX != 0)
        {
            chars->MoveOffsetX = (chars->MoveOffsetX
                    + SCROLL_PIXELS_PER_FRAME_X * Sgn(chars->scrollDirectionX) * cEngine::p_cGIn()->timerTicksPerFrame);
            if (chars->Body.Walk[chars->Heading].speed > 0.0f)
            {chars->Body.Walk[chars->Heading].started = true;}
            chars->Weapon.WeaponWalk[chars->Heading].started = true;
            chars->Shield.ShieldWalk[chars->Heading].started = true;

            moved = true;

			if (chars->scrollDirectionX < 0) addoffsetx = 1;

            if (((Sgn(chars->scrollDirectionX) == 1) && (chars->MoveOffsetX >= 0))
                || ((Sgn(chars->scrollDirectionX) == -1) && (chars->MoveOffsetX <= 0)))
            {
                chars->MoveOffsetX = 0.0f;
                chars->scrollDirectionX = 0;
            }
        }

        if (chars->scrollDirectionY != 0)
        {
            chars->MoveOffsetY = (chars->MoveOffsetY
                    + SCROLL_PIXELS_PER_FRAME_Y * Sgn(chars->scrollDirectionY) * cEngine::p_cGIn()->timerTicksPerFrame);
            if (chars->Body.Walk[chars->Heading].speed > 0.0f)
            {chars->Body.Walk[chars->Heading].started = true;}
            chars->Weapon.WeaponWalk[chars->Heading].started = true;
            chars->Shield.ShieldWalk[chars->Heading].started = true;

            moved = true;

			if (chars->scrollDirectionY < 0) addoffsety = 1;

            if (((Sgn(chars->scrollDirectionY) == 1) && (chars->MoveOffsetY >= 0))
                || (Sgn(chars->scrollDirectionY == -1) && (chars->MoveOffsetY <= 0)))
            {
                chars->MoveOffsetY = 0.0f;
                chars->scrollDirectionY = 0;
            }
        }
    }

    if (!moved)
    {
        chars->Body.Walk[chars->Heading].started = false;
        chars->Body.Walk[chars->Heading].frameCounter = 1;

        chars->Weapon.WeaponWalk[chars->Heading].started = false;
        chars->Weapon.WeaponWalk[chars->Heading].frameCounter = 1;

        chars->Shield.ShieldWalk[chars->Heading].started = false;
        chars->Shield.ShieldWalk[chars->Heading].frameCounter = 1;

        chars->Moving = 0;
    }

    //Hay un problema en el redondeo.
	PixelOffsetX = PixelOffsetX + floor(chars->MoveOffsetX) + addoffsetx;
	PixelOffsetY = PixelOffsetY + floor(chars->MoveOffsetY) + addoffsety;

    if (chars->iHead > 0)
    {
        if (!chars->invisible)
        {
            if (chars->Body.Walk[chars->Heading].grhIndex > 0)
            {cEngine::p_cGIn()->Draw_Texture(chars->Body.Walk[chars->Heading],
                    PixelOffsetX, PixelOffsetY, true, true, false);}

            if (chars->Head.Head[chars->Heading].grhIndex > 0)
            {
                cEngine::p_cGIn()->Draw_Texture(chars->Head.Head[chars->Heading],
                    PixelOffsetX + chars->Body.HeadOffset.x, PixelOffsetY + chars->Body.HeadOffset.y, true, false, false);

                if (chars->Helmet.Head[chars->Heading].grhIndex > 0)
                {cEngine::p_cGIn()->Draw_Texture(chars->Helmet.Head[chars->Heading],
                    PixelOffsetX + chars->Body.HeadOffset.x, PixelOffsetY + chars->Body.HeadOffset.y -34, true, false, false);
				}

                if (chars->Weapon.WeaponWalk[chars->Heading].grhIndex > 0)
                {cEngine::p_cGIn()->Draw_Texture(chars->Weapon.WeaponWalk[chars->Heading],
                    PixelOffsetX, PixelOffsetY, true, true, false);}

                if (chars->Shield.ShieldWalk[chars->Heading].grhIndex > 0)
                {cEngine::p_cGIn()->Draw_Texture(chars->Shield.ShieldWalk[chars->Heading],
                    PixelOffsetX, PixelOffsetY, true, true, false);}
            }

            if (vb6::Len(chars->name) > 0)
            {
				short pos = getTagPosition(chars->name);

                int colornick = 0xffe13232;
                if (chars->criminal <= 0) colornick = 0xff0080ff;
				if (chars->priv > 1) colornick = 0xff00a046;

				std::string line = vb6::Left(chars->name, pos - 2);
                cEngine::p_cGIn()->Draw_Text(line, (PixelOffsetX + 16) - cEngine::p_cGIn()->Engine_Text_Width(line, false) / 2, PixelOffsetY + 30, 1, false, colornick);
				
				line = vb6::Mid(chars->name, pos, vb6::Len(chars->name));
				cEngine::p_cGIn()->Draw_Text(line, (PixelOffsetX + 16) - cEngine::p_cGIn()->Engine_Text_Width(line, false) / 2, PixelOffsetY + 45, 1, false, colornick);
			}
        }
    }
    else
    {
        if (charlist[CharIndex].Body.Walk[charlist[CharIndex].Heading].grhIndex > 0)
            {cEngine::p_cGIn()->Draw_Texture(charlist[CharIndex].Body.Walk[charlist[CharIndex].Heading],
                    PixelOffsetX, PixelOffsetY, true, true, false);}

		if (vb6::Len(chars->name) > 0)
        {
			int colornick = 0xffe13232;
			if (chars->criminal <= 0) colornick = 0xff0080ff;
            cEngine::p_cGIn()->Draw_Text(chars->name, (PixelOffsetX + 16) - cEngine::p_cGIn()->Engine_Text_Width(chars->name, false) / 2, PixelOffsetY + 30, 1, false, colornick);
        }
    }

    if (charlist[CharIndex].FxIndex > 0)
    {
        cEngine::p_cGIn()->Draw_Texture(charlist[CharIndex].fX, PixelOffsetX, PixelOffsetY, true, true, true);
        if (charlist[CharIndex].fX.started <= 0) charlist[CharIndex].FxIndex = 0;
    }

}

void cGameData::SetCharacterFX(short CharIndex, short fX, short Loops)
{
    if (fX <= 0) return;
    charlist[CharIndex].FxIndex = fX;
    short grhIndex = FxData[fX].Animation;

    if (fX > 0)
    {
        InitGrh(charlist[CharIndex].fX, grhIndex, true);
        charlist[CharIndex].fX.loops = Loops;
    }
}

void cGameData::ShowNextFrame()
{
    static float OffsetCounterX;
    static float OffsetCounterY;

    if (UserMoving)
    {
        if (AddToUserPos.X != 0)
        {
            OffsetCounterX += -SCROLL_PIXELS_PER_FRAME_X * AddToUserPos.X * cEngine::p_cGIn()->timerTicksPerFrame;
            if (abs(OffsetCounterX) >= TILE_PIXEL_WIDTH)
            {
                OffsetCounterX = 0;
                AddToUserPos.X = 0;
                UserMoving = 0;
            }
        }

        if (AddToUserPos.Y != 0)
        {
            OffsetCounterY += -SCROLL_PIXELS_PER_FRAME_Y * AddToUserPos.Y * cEngine::p_cGIn()->timerTicksPerFrame;
            if (abs(OffsetCounterY) >= TILE_PIXEL_HEIGHT)
            {
                OffsetCounterY = 0;
                AddToUserPos.Y = 0;
                UserMoving = 0;
            }
        }
    }

    //ConvertCPtoTP
    cEngine::p_cGIn()->RenderScreen(UserPos.x - AddToUserPos.X, UserPos.y - AddToUserPos.Y, (short)OffsetCounterX, (short)OffsetCounterY);
	cEngine::p_cGIn()->RenderGUI();
}

void cGameData::ConvertCPtoTP(int &x, int &y)
{
    x = UserPos.x + (x / TILE_PIXEL_WIDTH) - ((MAIN_VIEW_PORT_X / TILE_PIXEL_WIDTH) / 2);
    y = UserPos.y + (y / TILE_PIXEL_HEIGHT) - ((MAIN_VIEW_PORT_Y / TILE_PIXEL_HEIGHT) / 2);
}

void cGameData::Process_Click(int x, int y, int event_click)
{
	if (!Connected) return;
    int mouseX = x; int mouseY = y;
    ConvertCPtoTP(x, y);

    char clicX = static_cast<char>(x);
    char clicY = static_cast<char>(y);

    switch (event_click)
    {
        case 1:
            if ((mouseX > CharInventory.posX) && (mouseX < CharInventory.posX + (48 * 6)) && (mouseY > CharInventory.posY + 24) && (mouseY < CharInventory.posY + (47 * 6)))
            {
                if (CharInventory.visible == true)
                {
                    InvSelectedItem = ClickItem(mouseX, mouseY);
                }
                else
                {
                    WriteLeftClick(clicX, clicY);
                }
            }
            else
            {
                if ((mouseX > CharInventory.posX) && (mouseX < CharInventory.posX + 314) && (mouseY > CharInventory.posY) && (mouseY < CharInventory.posY + 16))
                {
                    if (CharInventory.visible == true)
                    {
                        CharInventory.difPosX = mouseX - CharInventory.posX;
                        CharInventory.difPosY = mouseY - CharInventory.posY;
                        MoveInvent = true;
                    }
                    else
                    {
                        WriteLeftClick(clicX, clicY);
                    }
                }
                else
                {
                    WriteLeftClick(clicX, clicY);
                }
            }
        break;
        case 2:
            if ((mouseX > CharInventory.posX) && (mouseX < CharInventory.posX + (48 * 6)) && (mouseY > CharInventory.posY + 24) && (mouseY < CharInventory.posY + (47 * 6)))
            {
                if (CharInventory.visible == true)
                {
                    InvSelectedItem = ClickItem(mouseX, mouseY);

                    switch (CharInventory.Slot[InvSelectedItem].objtype)
                    {
                        case eOBJType_otArmadura: case eOBJType_otWeapon: case eOBJType_otESCUDO: case eOBJType_otCASCO:
                            WriteEquipItem(InvSelectedItem);
                        break;

                        case eOBJType_otPociones:
                            WriteUseItem(InvSelectedItem);
                        break;
                    }
                }
                else
                {
                    WriteRightClick(clicX, clicY);
                }
            }
            else
            {
                WriteRightClick(clicX, clicY);
            }
        break;
    }
}

short cGameData::ClickItem(int x, int y)
{
    int temp_x = ((x - CharInventory.posX) / 48);
    int temp_y = ((y - CharInventory.posY) / 47);

    int TempItem = (temp_x) + (temp_y * (314 / 48)) + 1; //314 es el tama�o del ancho de la interface, es decir, va a dar 6 slots.

    if (TempItem < MAX_INVENTORY_SLOT)
    {
        cout << TempItem << endl;
        if (CharInventory.Slot[TempItem].grhIndex > 0) return TempItem;
    }

    return 0;
}

void cGameData::MoveTo(eHeading Direction)
{
    bool LegalOk = false;

    switch (Direction){
        case eHeading::eHeading_NORTH:
            LegalOk = MoveToLegalPos(UserPos.x, UserPos.y - 1);
                break;
        case eHeading::eHeading_EAST:
            LegalOk = MoveToLegalPos(UserPos.x + 1, UserPos.y);
                break;
        case eHeading::eHeading_SOUTH:
            LegalOk = MoveToLegalPos(UserPos.x, UserPos.y + 1);
                break;
        case eHeading::eHeading_WEST:
            LegalOk = MoveToLegalPos(UserPos.x - 1, UserPos.y);
                break;
    }

    //UserParalizado = false; //LegalOk = true; //UserDescansar = false; //UserMeditar = false;

    if ((LegalOk) && (!UserParalizado))
    {
        WriteWalk(Direction);
        if (!UserDescansar & !UserMeditar)
        {
            MoveCharbyHead(UserCharIndex, Direction);
            MoveScreen(Direction);
        }
    }
    else
    {
        if (charlist[UserCharIndex].Heading != Direction) WriteChangeHeading(Direction);
    }

    //if (trabajando) desactivarMacroTrabajo;
    //Audio.MoveListener(cGameData::p_cGIn()->UserPos.x, cGameData::p_cGIn()->UserPos.y);
}

void cGameData::MoveScreen(eHeading nHeading)
{
    short X = 0; short Y = 0;

    switch (nHeading)
    {
        case eHeading::eHeading_NORTH:
            Y = -1;
                break;

        case eHeading::eHeading_EAST:
            X = 1;
                break;

        case eHeading::eHeading_SOUTH:
            Y = 1;
                break;

        case eHeading::eHeading_WEST:
            X = -1;
                break;
    }

    short tX = UserPos.x + X;
    short tY = UserPos.y + Y;

    AddToUserPos.X = X;
    UserPos.x = tX;
    AddToUserPos.Y = Y;
    UserPos.y = tY;
    UserMoving = 1;

	Update_bTecho(tX, tY); //si agregamos la condicion, ésto lo quitamos.

    return; // por ahora evitaremos �sta condici�n.

    if (tX < TILE_BUFFER_SIZE || tX > X_MAX_MAP_SIZE - TILE_BUFFER_SIZE || tY < TILE_BUFFER_SIZE || tY > Y_MAX_MAP_SIZE - TILE_BUFFER_SIZE)
    {
        return;
    }
    else
    {
        AddToUserPos.X = X;
        UserPos.x = tX;
        AddToUserPos.Y = Y;
        UserPos.y = tY;
        UserMoving = 1;

        Update_bTecho(tX, tY);
    }
}

bool cGameData::MoveToLegalPos(short X, short Y)
{
    if (X < MinXBorder || X > MaxXBorder || Y < MinYBorder || Y > MaxYBorder) return false;
    if (MapData[X][Y].blocked == 1) return false;

    short CharIndex = MapData[X][Y].charindex;

    if (CharIndex > 0)
    {
        if (MapData[UserPos.x][UserPos.y].blocked == 1) return false;
        if ((charlist[CharIndex].iHead != CASPER_HEAD) & (charlist[CharIndex].iBody != FRAGATA_FANTASMAL))
        {
            return false;
        }
        else
        {
            if (HayAgua(UserPos.x, UserPos.y))
            {
                if (!HayAgua(X, Y)) return false;
            }
            else
            {
                if (HayAgua(X, Y)) return false;
            }

            if ((charlist[UserCharIndex].priv > 0) && (charlist[UserCharIndex].priv < 6))
            {
                if (charlist[UserCharIndex].invisible) return false;
            }
        }
    }

    if (UserNavegando != HayAgua(X, Y)) return false;
    return true;
}

void cGameData::MoveCharbyHead(short CharIndex, eHeading nHeading)
{
    short addX = 0; short addY = 0;

    short X = charlist[CharIndex].Pos.x;
    short Y = charlist[CharIndex].Pos.y;

    switch (nHeading)
    {
        case eHeading::eHeading_NORTH:
            addY = -1;
            break;

        case eHeading::eHeading_EAST:
            addX = 1;
            break;

        case eHeading::eHeading_SOUTH:
            addY = 1;
            break;

        case eHeading::eHeading_WEST:
            addX = -1;
            break;
    }

    short nX = X + addX;
    short nY = Y + addY;

    MapData[nX][nY].charindex = CharIndex;

    charlist[CharIndex].Pos.x = nX;
    charlist[CharIndex].Pos.y = nY;

    MapData[X][Y].charindex = 0;

    charlist[CharIndex].MoveOffsetX = -1 * (TILE_PIXEL_WIDTH  * addX);
    charlist[CharIndex].MoveOffsetY = -1 * (TILE_PIXEL_HEIGHT * addY);

    charlist[CharIndex].Moving = 1;
    charlist[CharIndex].Heading = nHeading;

    charlist[CharIndex].scrollDirectionX = addX;
    charlist[CharIndex].scrollDirectionY = addY;

    if (UserEstado == 0) DoPasosFx(CharIndex);
    if ((nY < MinLimiteY) || (nY > MaxLimiteY) || (nX < MinLimiteX) || (nX > MaxLimiteX))
    {
        if (CharIndex != UserCharIndex)
        {
            EraseChar(CharIndex);
        }
    }
}

void cGameData::MoveCharbyPos(short CharIndex, short nX, short nY)
{
    short X = charlist[CharIndex].Pos.x;
    short Y = charlist[CharIndex].Pos.y;

    MapData[X][Y].charindex = 0;

    short addX = nX - X;
    short addY = nY - Y;

    eHeading nHeading;

    if (Sgn(addX) == 1)
    {
        nHeading = eHeading::eHeading_EAST;
    }

    if (Sgn(addX) == -1)
    {
        nHeading = eHeading::eHeading_WEST;
    }

    if (Sgn(addY) == 1)
    {
        nHeading = eHeading::eHeading_SOUTH;
    }

    if (Sgn(addY) == -1)
    {
        nHeading = eHeading::eHeading_NORTH;
    }

    MapData[nX][nY].charindex = CharIndex;

    charlist[CharIndex].Pos.x = nX;
    charlist[CharIndex].Pos.y = nY;

    charlist[CharIndex].MoveOffsetX = -1 * (TILE_PIXEL_WIDTH * addX);
    charlist[CharIndex].MoveOffsetY = -1 * (TILE_PIXEL_HEIGHT * addY);

    charlist[CharIndex].Moving = 1;
    charlist[CharIndex].Heading = nHeading;

    charlist[CharIndex].scrollDirectionX = Sgn(addX);
    charlist[CharIndex].scrollDirectionY = Sgn(addY);

    //FALTA: parche para que no medite cuando camina
    //If .FxIndex = FxMeditar.CHICO Or .FxIndex = FxMeditar.GRANDE Or .FxIndex = FxMeditar.MEDIANO Or .FxIndex = FxMeditar.XGRANDE Or .FxIndex = FxMeditar.XXGRANDE Then

    //If Not EstaPCarea(CharIndex) Then Call Dialogos.RemoveDialog(CharIndex)

    if ((nY < MinLimiteY) || (nY > MaxLimiteY) || (nX < MinLimiteX) || (nX > MaxLimiteX))
    {
        EraseChar(CharIndex);
    }
}

void cGameData::DoPasosFx(short CharIndex)
{
    if (!UserNavegando)
    {
        if (charlist[CharIndex].dead == false)
        {
            charlist[CharIndex].pie = !charlist[CharIndex].pie;
        }

        if (charlist[CharIndex].pie == true)
        {
            Audio.PlayWav("resources/wav/23.wav");
        }
        else
        {
            Audio.PlayWav("resources/wav/24.wav");
        }
    }
    else
    {
        Audio.PlayWav("resources/wav/50.wav");
    }
}

void cGameData::EraseChar(short CharIndex)
{
    if (CharIndex <= 0) return;
    charlist[CharIndex].Active = 0;

    if (CharIndex == LastChar)
    {
        do
        {   --LastChar;
            if (LastChar == 0) break;
        } while(charlist[CharIndex].Active == 1);
    }

    MapData[charlist[CharIndex].Pos.x][charlist[CharIndex].Pos.y].charindex = 0;
    /*RemoveDialog(CharIndex);*/
    ResetCharInfo(CharIndex);
    --NumChars;
}

const char* cGameData::IpDelServidor()
{
	return FConnect_getIpServidor();
}

void cGameData::ResetCharInfo(short CharIndex)
{
    charlist[CharIndex].Active = 0;
    charlist[CharIndex].criminal = 0;
    charlist[CharIndex].attackable = 0;
    charlist[CharIndex].FxIndex = 0;
    charlist[CharIndex].invisible = 0;
    charlist[CharIndex].Moving = 0;
    charlist[CharIndex].dead = false;
    charlist[CharIndex].name = "";
    charlist[CharIndex].pie = false;
    charlist[CharIndex].Pos.x = 0;
    charlist[CharIndex].Pos.y = 0;
    charlist[CharIndex].iHead = 0;
    charlist[CharIndex].iBody = 0;
    charlist[CharIndex].MoveOffsetX = 0.0f;
    charlist[CharIndex].MoveOffsetY = 0.0f;
    charlist[CharIndex].scrollDirectionX = 0.0f;
    charlist[CharIndex].scrollDirectionY = 0.0f;
    charlist[CharIndex].UsingArm = false;
    charlist[CharIndex].dialog = "";
    charlist[CharIndex].dialog_color = 0;
    charlist[CharIndex].dialog_life = 0;
    charlist[CharIndex].dialog_font_index = 0;
    charlist[CharIndex].offset_counter_y = 0.0f;
}

bool cGameData::HayAgua(short X, short Y)
{return ((MapData[X][Y].layer[1].grhIndex >= 1505 & MapData[X][Y].layer[1].grhIndex <= 1520) ||
         (MapData[X][Y].layer[1].grhIndex >= 5665 & MapData[X][Y].layer[1].grhIndex <= 5680) ||
         (MapData[X][Y].layer[1].grhIndex >= 13547 & MapData[X][Y].layer[1].grhIndex <= 13562)) &&
         (MapData[X][Y].layer[2].grhIndex == 0);}

void cGameData::RefreshAllChars()
{
    for (short loopc = 1; loopc <= LastChar; ++loopc)
    {
        if (charlist[loopc].Active == 1)
        {
            MapData[charlist[loopc].Pos.x][charlist[loopc].Pos.y].charindex = loopc;
        }
    }
}

void cGameData::MakeChar(short charindex, string name, short Body, short Head, eHeading Heading, short x, short y, short Weapon, short Shield, short Helmet)
{
    if (charindex > LastChar) LastChar = charindex;
    if (charlist[charindex].Active == 0) ++NumChars;

    if (Weapon == 2) Weapon = 0;
    if (Shield == 2) Shield = 0;
    if (Helmet == 2) Helmet = 0;

    charlist[charindex].name = name;
    charlist[charindex].iBody = Body;
    charlist[charindex].Body = BodyData[Body];
    charlist[charindex].iHead = Head;
    charlist[charindex].Head = HeadData[Head];
    charlist[charindex].Weapon = WeaponData[Weapon];
    charlist[charindex].Shield = ShieldData[Shield];
    charlist[charindex].Helmet = HelmetsData[Helmet];
    charlist[charindex].Heading = Heading;
    charlist[charindex].Moving = 0;
    charlist[charindex].MoveOffsetX = 0.0f;
    charlist[charindex].MoveOffsetY = 0.0f;
    charlist[charindex].Pos.x = x;
    charlist[charindex].Pos.y = y;
    charlist[charindex].Active = 1;
    charlist[charindex].dialog = "";
    charlist[charindex].dialog_color = 0;
    charlist[charindex].dialog_life = 0;
    charlist[charindex].dialog_font_index = 0;
    charlist[charindex].offset_counter_y = 0.0f;

    MapData[x][y].charindex = charindex;
}

void cGameData::Char_Dialog_Set(short charindex, string text, int color, short life, short font_index)
{
    charlist[charindex].dialog = text;
    charlist[charindex].dialog_color = color;
    charlist[charindex].dialog_life = life;
    charlist[charindex].dialog_font_index = font_index;
    charlist[charindex].offset_counter_y = 0.0f;
}

void cGameData::Update_bTecho(short x, short y)
{
    bTecho = false;
    if ((MapData[x][y].trigger == 1)||(MapData[x][y].trigger == 2)||(MapData[x][y].trigger == 4)) bTecho = true;
}

short cGameData::Sgn(short number)
{
    if (number == 0) return 0;
    return number > 0 ? 1 : -1;
}

void cGameData::ChangeArea(short X, short Y)
{
    MinLimiteX = (X / 9 - 1) * 9;
    MaxLimiteX = MinLimiteX + 26;

    MinLimiteY = (Y / 9 - 1) * 9;
    MaxLimiteY = MinLimiteY + 26;

    /*if (MaxLimiteX > X_MAX_MAP_SIZE) MaxLimiteX = X_MAX_MAP_SIZE;
    if (MaxLimiteY > Y_MAX_MAP_SIZE) MaxLimiteY = Y_MAX_MAP_SIZE;
    if (MinLimiteX < X_MIN_MAP_SIZE) MinLimiteX = X_MIN_MAP_SIZE;
    if (MinLimiteY < Y_MIN_MAP_SIZE) MinLimiteY = Y_MIN_MAP_SIZE;*/

    for(unsigned char loopX = 1; loopX <= 100; ++loopX)
    {
        for(unsigned char loopY = 1; loopY <= 100; ++loopY)
        {
            if ((loopY < MinLimiteY) || (loopY > MaxLimiteY) || (loopX < MinLimiteX) || (loopX > MaxLimiteX))
            {
                if (MapData[loopX][loopY].charindex != UserCharIndex)
                {
                    EraseChar(MapData[loopX][loopY].charindex);
                }
                MapData[loopX][loopY].objgrh.grhIndex = 0;
            }
        }
    }

    RefreshAllChars();
}
