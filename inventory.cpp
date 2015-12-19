#include "inventory.hpp"
//cInventory* cInventory::pI = 0;

cInventory::~cInventory()
{
    delete [] Slot;
}

cInventory::cInventory()
{
    for(unsigned char i = 0; i <= 24; ++i)
    {
        Slot[i].grhIndex = 0;
        Slot[i].equipped = false;
        Slot[i].amount = 0;
        Slot[i].name = "";
        Slot[i].value = 0.0f;
        Slot[i].objtype = 0;
        Slot[i].objindex = 0;
        Slot[i].minhit = 0;
        Slot[i].maxhit = 0;
        Slot[i].mindef = 0;
        Slot[i].maxdef = 0;
    }

    difPosX = 0;
    difPosY = 0;

    posX = 0;
    posY = 0;

    visible = false;
}

void cInventory::SetItem(unsigned char slot, short objindex, short amount, bool equipped, short grhIndex, short objtype, short maxhit, short minhit, short maxdef, short mindef, float value, std::string name)
{
    Slot[slot].grhIndex = grhIndex;
    Slot[slot].equipped = equipped;
    Slot[slot].amount = amount;
    Slot[slot].name = name;
    Slot[slot].value = value;
    Slot[slot].objtype = objtype;
    Slot[slot].objindex = objindex;
    Slot[slot].minhit = minhit;
    Slot[slot].maxhit = maxhit;
    Slot[slot].mindef = mindef;
    Slot[slot].maxdef = maxdef;
}
