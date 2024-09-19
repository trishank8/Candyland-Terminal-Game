#ifndef CANDYSTORE_H
#define CANDYSTORE_H

#include <iostream>
#include <vector>
using namespace std;

struct Candy
{
    string name;
    string description;
    double price;
    string candy_type;
    string effect_type;
    int effect_value;
};

class CandyStore
{
    public:
    CandyStore();
    CandyStore(string store_name);
    CandyStore(string store_name, int candy_stock);
    bool addCandy(Candy store_candy); 
    bool removeCandy(string candy_name);
    void randCandies(vector <Candy> candies);
    void printInventory();


    private:
    string _store_name;
    int _store_stock;
    const static int CANDY_STORE_NUM = 3;
    Candy _store_inventory[CANDY_STORE_NUM]; 
};

#endif