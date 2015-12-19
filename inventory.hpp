#ifndef _H_INVENTORY_
#define _H_INVENTORY_

#define MAX_INVENTORY_SLOT 25
#include <string>

typedef struct{
    short objindex;
    std::string name;
    short grhIndex;
    short amount;
    bool equipped;
    unsigned char objtype;
    short maxhit;
    short minhit;
    short maxdef;
    short mindef;
    float value;
} _tInventory;

class cInventory{
    //protected:
    //    static cInventory* pI;

    public:
        ~cInventory();
        cInventory();

        //static void setInterface(cInventory * newInterface){pI = newInterface;}
        //static cInventory* p_cGIn(){return pI;}

        void SetItem(unsigned char, short, short, bool, short, short, short, short, short, short, float, std::string);
        _tInventory Slot[MAX_INVENTORY_SLOT];

        int posX;
        int posY;
        int difPosX;
        int difPosY;
        bool visible;
};
#endif // _H_INVENTORY_
