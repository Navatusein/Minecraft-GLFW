#include "Inventory.h"

Inventory::Inventory(unsigned int size) {
    inventory.resize(size);
}

unsigned short Inventory::FindFree() {
    for (unsigned int i = 0; i < this->size; i++) {
        if (inventory[i] == nullptr) {
            return i;
        }
    }
    return 0;

}

unsigned short Inventory::FindItem(ItemStack* item) {
    for (int i = 0; i < this->size; i++) {
        if (item->GetItem()->GetID() == inventory[i]->GetItem()->GetID()) {
            return i;
        }
    }
    return 0;
}

bool Inventory::putItem(ItemStack* item, unsigned short slot) {
    if (slot > size) {
        return 0;
    }

    if (inventory[slot] == nullptr) {
        inventory[slot] = item;
    }
    else if (item->GetItem()->GetID() == inventory[slot]->GetItem()->GetID()) {
        if (inventory[slot]->GetItem()->GetMaxCount() != inventory[slot]->GetCount()) {
            unsigned char tempCount = inventory[slot]->GetItem()->GetMaxCount() - inventory[slot]->GetCount();
            if (tempCount >= item->GetCount()) {
                inventory[slot]->SetCount(inventory[slot]->GetItem()->GetMaxCount() + item->GetCount());
                delete item;
            }
            else {
                inventory[slot]->SetCount(inventory[slot]->GetItem()->GetMaxCount() + tempCount);
                item->SetCount(item->GetCount() - tempCount);
            }
        }
    }

    return false;
}

ItemStack* Inventory::takeItem(unsigned short slot) {
    ItemStack* temp;
    temp = inventory[slot];
    inventory[slot] = nullptr;
    return temp;

}
