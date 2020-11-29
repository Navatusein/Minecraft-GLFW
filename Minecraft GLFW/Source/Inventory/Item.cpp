#include "Item.h"

Item::Item(unsigned short ID, unsigned char amount) : ID(ID), MaxCount(amount) {}

unsigned char Item::GetMaxCount() {
    return MaxCount;
}

unsigned short Item::GetID() {
    return ID;
}

