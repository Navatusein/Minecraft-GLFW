#include <iostream>
#include <vector>
using namespace std;

class Item{
private:
    string id;// ид в виде стринга для использования букв и цыфр, а также облегчения поиска и т п
    int max_amount;// макс количество
public:
    Item(){// дефолтное положение
        id = "";
        max_amount = 0;
    }

    Item(string id, int amount) : id(id), max_amount(amount){} // создание предмета

    ~Item(){};

    int Max_amount(Item item){
        return item.max_amount;
    }

    string GetID(){
        return id;
    }
};

class InventorySlot : Item{
private:
    Item item; // передмет
    unsigned int amount;// его количество 
public:
    InventorySlot(){};

    InventorySlot(Item item, int amount) : item(item){
        if(amount > Max_amount(item))
        this->amount = Max_amount(item);
        else{
            this->amount = amount;
        }
        
    }// добавляем предмет в слот в енном количистве

    ~InventorySlot(){};

    void changeAmount(int amount){
        this->amount = amount;
    }

    unsigned int GetAmount(){
        return amount;
    }

    Item GetItem(){
        return item;
    }

   
};

class Inventory : Item{
private:
unsigned int size;//количество слотов
vector<InventorySlot> inventory; // инвентарь со слотами 

public:
    Inventory() : size(0) {}

    Inventory(unsigned int size){
        if(size==0 || size>36)
            cout<<"Too  much inventory slots for this object"<<endl;
        else
            this->inventory.resize(size);

    }

    ~Inventory(){}
    
    int FindFree(){
        for(unsigned int i = 0; i < this->size; i++){
            if(inventory[i].GetAmount() == 0){
                return i;
            }
        }
        return 0;

    }


    int FindItem(Item item){
        for(int i = 0; i< this->size;i++){
            if(item.GetID() == inventory[i].GetItem().GetID()){
                return i;
            }
        }
        return 0;
    }

    bool putItem(Item item, unsigned int amount){
            cout<<"You dont have enough space"<<endl;
            return 0;

        int i = FindItem(item);
        if(i == 0){
            i = FindFree();
            if(i == 0){
                cout<<"Your inventory is full!"<<endl;
                return false;
            }
        }

        if(Max_amount(item) < amount || inventory[i].GetAmount() + amount > Max_amount(item)){
            amount -= (Max_amount(item) - inventory[i].GetAmount());
            inventory[i].changeAmount(Max_amount(item));
            int j = FindFree();
            if(i == 0){
                cout<<"No more free space"<<endl;
                return false;
            }
            inventory[j].changeAmount(amount);
            
        }
        inventory[i].changeAmount(inventory[i].GetAmount() + amount);
        return true;
    }
    
    InventorySlot* takeItem(unsigned int slot){
        return &inventory[slot];
    }

};
