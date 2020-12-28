#pragma once

/*
This module is not used
*/

class Item {
private:
    unsigned short ID;
    unsigned char MaxCount;
public:
    Item(unsigned short ID, unsigned char amount);

    unsigned char GetMaxCount();

    unsigned short GetID();

};;
