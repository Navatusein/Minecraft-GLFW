#pragma once

/*
This module is not used
*/

#include <vector>
#include <iostream>

#include "Item.h"
#include "ItemStack.h"

class Inventory{
private:
    unsigned short size;
    std::vector<ItemStack*> inventory;

public:
    Inventory(unsigned int size);

    ~Inventory();

    unsigned short FindFree();

    unsigned short FindItem(ItemStack* item);

    bool putItem(ItemStack* item, unsigned short slot);

    ItemStack* takeItem(unsigned short slot);
};

