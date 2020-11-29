#include "ItemStack.h"

ItemStack::ItemStack() : item(nullptr), count(0) {}

ItemStack::ItemStack(Item* item, unsigned char amount) : item(item), count(count) {}

ItemStack::~ItemStack() {
    delete item;
}

void ItemStack::SetCount(unsigned char count) {
    this->count = count;
}

unsigned int ItemStack::GetCount() {
    return count;
}

Item* ItemStack::GetItem() {
    return item;
}
