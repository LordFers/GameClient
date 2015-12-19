#ifndef _GAMEDATA_H
#define _GAMEDATA_H

#include "ByteBuffer.h"
#include "ByteQueue.h"
#include "inventory.hpp"
#include "audio.hpp"

#include <string.h>

#define UBound(n)	sizeof(n) / sizeof(n[0])

#define CASPER_HEAD 500
#define FRAGATA_FANTASMAL 87

#define NUMCIUDADES 5
#define NUMSKILLS 20
#define NUMATRIBUTOS 5
#define NUMCLASES 12
#define NUMRAZAS 5

static const char* MENSAJE_CRIATURA_FALLA_GOLPE = "¡¡¡La criatura falló el golpe!!!";
static const char* MENSAJE_CRIATURA_MATADO = "¡¡¡La criatura te ha matado!!!";
static const char* MENSAJE_RECHAZO_ATAQUE_ESCUDO = "¡¡¡Has rechazado el ataque con el escudo!!!";
static const char* MENSAJE_USUARIO_RECHAZO_ATAQUE_ESCUDO  = "¡¡¡El usuario rechazó el ataque con su escudo!!!";
static const char* MENSAJE_FALLADO_GOLPE = "¡¡¡Has fallado el golpe!!!";
static const char* MENSAJE_SEGURO_ACTIVADO = ">>SEGURO ACTIVADO<<";
static const char* MENSAJE_SEGURO_DESACTIVADO = ">>SEGURO DESACTIVADO<<";
static const char* MENSAJE_PIERDE_NOBLEZA = "¡¡Has perdido puntaje de nobleza y ganado puntaje de criminalidad!! Si sigues ayudando a criminales te convertirás en uno de ellos y serás perseguido por las tropas de las ciudades.";
static const char* MENSAJE_USAR_MEDITANDO = "¡Estás meditando! Debes dejar de meditar para usar objetos.";

static const char* MENSAJE_SEGURO_RESU_ON = "SEGURO DE RESURRECCION ACTIVADO";
static const char* MENSAJE_SEGURO_RESU_OFF = "SEGURO DE RESURRECCION DESACTIVADO";

static const char* MENSAJE_GOLPE_CABEZA = "¡¡La criatura te ha pegado en la cabeza por ";
static const char* MENSAJE_GOLPE_BRAZO_IZQ = "¡¡La criatura te ha pegado el brazo izquierdo por ";
static const char* MENSAJE_GOLPE_BRAZO_DER = "¡¡La criatura te ha pegado el brazo derecho por ";
static const char* MENSAJE_GOLPE_PIERNA_IZQ = "¡¡La criatura te ha pegado la pierna izquierda por ";
static const char* MENSAJE_GOLPE_PIERNA_DER = "¡¡La criatura te ha pegado la pierna derecha por ";
static const char* MENSAJE_GOLPE_TORSO  = "¡¡La criatura te ha pegado en el torso por ";

//' MENSAJE_[12]: Aparecen antes y despues del valor de los mensajes anteriores (MENSAJE_GOLPE_*);
static const char* MENSAJE_1 = "¡¡";
static const char* MENSAJE_2 = "!!";
static const char* MENSAJE_11 = "¡";
static const char* MENSAJE_22 = "!";

static const char* MENSAJE_GOLPE_CRIATURA_1 = "¡¡Le has pegado a la criatura por ";

static const char* MENSAJE_ATAQUE_FALLO = " te atacó y falló!!";

static const char* MENSAJE_RECIVE_IMPACTO_CABEZA = " te ha pegado en la cabeza por ";
static const char* MENSAJE_RECIVE_IMPACTO_BRAZO_IZQ = " te ha pegado el brazo izquierdo por ";
static const char* MENSAJE_RECIVE_IMPACTO_BRAZO_DER = " te ha pegado el brazo derecho por ";
static const char* MENSAJE_RECIVE_IMPACTO_PIERNA_IZQ = " te ha pegado la pierna izquierda por ";
static const char* MENSAJE_RECIVE_IMPACTO_PIERNA_DER = " te ha pegado la pierna derecha por ";
static const char* MENSAJE_RECIVE_IMPACTO_TORSO = " te ha pegado en el torso por ";

static const char* MENSAJE_PRODUCE_IMPACTO_1 = "¡¡Le has pegado a ";
static const char* MENSAJE_PRODUCE_IMPACTO_CABEZA = " en la cabeza por ";
static const char* MENSAJE_PRODUCE_IMPACTO_BRAZO_IZQ = " en el brazo izquierdo por ";
static const char* MENSAJE_PRODUCE_IMPACTO_BRAZO_DER = " en el brazo derecho por ";
static const char* MENSAJE_PRODUCE_IMPACTO_PIERNA_IZQ = " en la pierna izquierda por ";
static const char* MENSAJE_PRODUCE_IMPACTO_PIERNA_DER = " en la pierna derecha por ";
static const char* MENSAJE_PRODUCE_IMPACTO_TORSO = " en el torso por ";

static const char* MENSAJE_TRABAJO_MAGIA = "Haz click sobre el objetivo...";
static const char* MENSAJE_TRABAJO_PESCA = "Haz click sobre el sitio donde quieres pescar...";
static const char* MENSAJE_TRABAJO_ROBAR = "Haz click sobre la víctima...";
static const char* MENSAJE_TRABAJO_TALAR = "Haz click sobre el árbol...";
static const char* MENSAJE_TRABAJO_MINERIA = "Haz click sobre el yacimiento...";
static const char* MENSAJE_TRABAJO_FUNDIRMETAL = "Haz click sobre la fragua...";
static const char* MENSAJE_TRABAJO_PROYECTILES = "Haz click sobre la victima...";

static const char* MENSAJE_ENTRAR_PARTY_1 = "Si deseas entrar en una party con ";
static const char* MENSAJE_ENTRAR_PARTY_2 = ", escribe /entrarparty";

static const char* MENSAJE_NENE = "Cantidad de NPCs: ";

static const char* MENSAJE_FRAGSHOOTER_TE_HA_MATADO = "te ha matado!";
static const char* MENSAJE_FRAGSHOOTER_HAS_MATADO = "Has matado a";
static const char* MENSAJE_FRAGSHOOTER_HAS_GANADO = "Has ganado ";
static const char* MENSAJE_FRAGSHOOTER_PUNTOS_DE_EXPERIENCIA = "puntos de experiencia.";

static const char* MENSAJE_NO_VES_NADA_INTERESANTE = "No ves nada interesante.";
static const char* MENSAJE_HAS_MATADO_A = "Has matado a ";
static const char* MENSAJE_HAS_GANADO_EXPE_1 = "Has ganado ";
static const char* MENSAJE_HAS_GANADO_EXPE_2 = " puntos de experiencia.";
static const char* MENSAJE_TE_HA_MATADO = " te ha matado!";

static const char* MENSAJE_HOGAR = "Has llegado a tu hogar. El viaje ha finalizado.";
static const char* MENSAJE_HOGAR_CANCEL = "Tu viaje ha sido cancelado.";

typedef struct
{
    short sX;
    short sY;

    int filenum;

    short pixelWidth;
    short pixelHeight;

    float tileWidth;
    float tileHeight;

    short numFrames;
    int* frames;

    float speed;
} _GrhData;

typedef struct
{   short grhIndex;
    float frameCounter;
    float speed;
    bool started;
    int loops;
    float angle;
} _Grh;

typedef struct
{   short objindex;
    short amount;
} _Obj;

typedef struct
{   int map;
    short x;
    short y;
} _WorldPos;

typedef struct
{   short x;
    short y;
} _Position;

typedef struct
{   _Grh layer[5];
    short charindex;
    _Grh objgrh;
    short npcindex;
    _Obj objinfo;
    _WorldPos tileexit;
    char blocked;
    short trigger;
} _MapData;

typedef struct
{   short font_size;
    short* ascii_code;
} _Font;

typedef struct
{   short X;
    short Y;
} _AddToUser;

typedef struct
{   _Grh Walk[4+1];
    _Position HeadOffset;
} _BodyData;

typedef struct
{   short Body[4+1];
    short HeadOffsetX;
    short HeadOffsetY;
} _tIndexBodys;

typedef struct
{short Head[4+1];} _tIndexHeads;

typedef struct
{_Grh Head[4+1];} _HeadData;

typedef struct
{_Grh WeaponWalk[4+1];} _WeaponData;

typedef struct
{_Grh ShieldWalk[4+1];} _ShieldData;

typedef struct{
    short Animation;
    short OffsetX;
    short OffsetY;
} _FxData;

typedef struct
{   char Active;

    eHeading Heading;
    _Position Pos;

    short iHead;
    short iBody;

    _BodyData Body;
    _HeadData Head;
    _HeadData Helmet;
    _WeaponData Weapon;
    _ShieldData Shield;

    bool UsingArm;

    _Grh fX;

    short FxIndex;
    char criminal;
    bool attackable;

    std::string name;

    short scrollDirectionX;
    short scrollDirectionY;

    char Moving;

    float MoveOffsetX;
    float MoveOffsetY;

    bool pie;
    bool dead;
    bool invisible;

    char priv;

    std::string dialog;
    int dialog_color;
    short dialog_life;
    short dialog_font_index;
    float offset_counter_y;
} _tChar;

typedef struct {
	int color;
	bool bold;
	bool italic;
} _tFont;

class cGameData{
    protected:
        static cGameData* pI;

    public:
        cGameData();
        ~cGameData();
        static cGameData* p_cGIn(){return pI;}
        static void setInterface(cGameData* newInterface){pI = newInterface;}
        void LoadWeapons();
        void LoadShields();
        void LoadHelmets();
        void LoadHeads();
        void LoadBodys();
        void LoadGrh();
        void LoadFXs();
        void LoadFonts();
		void LoadFontsConsole();
        void LoadMap(int);
        void CharRender(short, short, short);
        void InitGrh(_Grh&, short, bool);
        void ShowNextFrame();
        void ChangeArea(short, short);

        void ConvertCPtoTP(int&, int&);
        void Process_Click(int, int, int);
        short ClickItem(int, int);
        void Char_Dialog_Set(short, std::string, int, short, short);

		const char* IpDelServidor();

        void MakeChar(short, std::string, short, short, eHeading, short, short, short, short, short);
        void RefreshAllChars();
        void MoveTo(eHeading);
        void MoveScreen(eHeading nHeading);
        bool MoveToLegalPos(short, short);
        void MoveCharbyHead(short, eHeading);
        void MoveCharbyPos(short, short, short);
        void DoPasosFx(short);
        void SetCharacterFX(short, short, short);
        void EraseChar(short);
        void ResetCharInfo(short);
        bool HayAgua(short, short);
        void Update_bTecho(short, short);
        short Sgn(short);

        int ambient_color;

        _tChar* charlist;
        _WeaponData* WeaponData;
        _ShieldData* ShieldData;
        _HeadData* HeadData;
        _HeadData* HelmetsData;
        _BodyData* BodyData;
        _GrhData* GrhData;
        _FxData* FxData;
        _MapData** MapData;
        _Font* font_types; //Esto es para las letras renderizadas
		_tFont* FontTypes; //Esto es para las FontTypeNames de la consola
        short* UserSkills;
        short* PorcentajeSkills;
		std::vector<std::string> GuildNames;
		std::vector<std::string> GuildMembers;
		std::vector<std::string> GuildAspirantes;
        //const char** SkillsNames; -> Controlar que se elimine desde el ~cGameData
        _Position UserPos;
        _AddToUser AddToUserPos;

        clsByteQueue outgoingData;
        clsByteQueue incomingData;

        cInventory CharInventory;
        cInventory NPCInventory;

        cAudio Audio;

        short MinXBorder;
        short MaxXBorder;
        short MinYBorder;
        short MaxYBorder;

        short MinLimiteX;
        short MaxLimiteX;
        short MinLimiteY;
        short MaxLimiteY;

        int UserMaxHP;
        int UserMinHP;
        int UserMaxMAN;
        int UserMinMAN;
        int UserMaxSTA;
        int UserMinSTA;
        long UserGLD;
        unsigned char UserLvl;
        int UserPasarNivel;
        int UserExp;
        short UserMap;
        short UserMaxAGU;
        short UserMinAGU;
        short UserMaxHAM;
        short UserMinHAM;
        short UserStrength;
        short UserDexterity;
        short InvSelectedItem;
        bool Geted_Skills;
        short SkillPoints;
        bool MoveInvent;

        short LastChar;
        short NumChars;
        short UserCharIndex;
        char UserEstado;
        char UserMoving;
        char UserParalizado;
        char UserMeditar;
        char UserDescansar;
        char UserNavegando;
		bool Connected;
		bool inCP;
		bool bTecho;

        float timerElapsedTime;
};
#endif
