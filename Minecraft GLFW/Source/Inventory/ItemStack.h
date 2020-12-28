#pragma once

/*
This module is not used
*/

#include "Item.h"

class ItemStack{
private:
    Item* item;
    unsigned char count;
public:
    ItemStack();

    ItemStack(Item* item, unsigned char amount);

    ~ItemStack();

    void SetCount(unsigned char count);

    unsigned int GetCount();

    Item* GetItem();
};

