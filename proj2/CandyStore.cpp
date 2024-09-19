#include <iostream>
#include "CandyStore.h"
using namespace std;

CandyStore::CandyStore()
{
    _store_name = "";
    _store_stock = 0;

}

CandyStore::CandyStore(string store_name)
{
    _store_name = store_name;
    _store_stock = 0;

    for(int i= 0; i <3; i++)
    {
        Candy candy;
        candy.name = "";
        candy.description = "";
        candy.effect_type = "";
        candy.effect_value = 0; 
        candy.candy_type = "";
        candy.price = 0;
        _store_inventory[i] = candy;
    }
}

CandyStore::CandyStore(string store_name, int store_stock)
{
    _store_name = store_name;
    _store_stock = store_stock;




    // this would be in the parameters after int store_stock if i want to implement the below part -> Candy store_inventory[]
    // if(_store_stock < CANDY_STORE_NUM)
    // {
    //     for(int i = 0; i< _store_stock; i++)
    //     {
    //         _store_inventory[i] = store_inventory[i];
    //     }

    // }
    // else 
    // {
    //     for(int i = 0; i< STORE_CANDY_NUM; i++)
    //     {   
    //         _store_inventory[i] = store_inventory[i];
    //     }

    // }
}

bool CandyStore::addCandy(Candy store_candy)
{
    if (_store_stock == CANDY_STORE_NUM)
    {
        cout << "Store has maximum number. Cannot add more candies!" << endl;
        return false;
    }

    _store_inventory[_store_stock] = store_candy;
    _store_stock++;
    return true;
}

bool CandyStore::removeCandy(string candy_name)
{
    bool candy_removed = false;
    for (int i = 0; i < _store_stock; i++)
    {
        if(_store_inventory[i].name == candy_name)
        {
            for (int j = i + 1; j < _store_stock; j++)
            {
                cout << "Copying " << _store_inventory[j].name << " into " << _store_inventory[j-1].name << endl;
                _store_inventory[j-1] = _store_inventory[j];
            }
            _store_stock--;
            candy_removed = true;
            break;
        }

    }
    return candy_removed;
}

// void CandyStore::randCandies(vector <Candy> candies)
// {
//     int size = candies.size();

//     srand(time(0));

//     for (int i = 0; i < 3; i++)
//     {
//         int random_index = (rand() % size); // randomly picks 3 candies to display at the store
//         cout << "Random Index " << random_index;
//         cout << "--------------------------------------------------------------------------------------------------" << endl;
//         cout << "Name: " << candies[random_index].name << endl << " Description: " << candies[random_index].description << endl << " Effect: " << candies[random_index].effect_type << endl << " Effect value: " << candies[random_index].effect_value << endl;
//         cout << "Candy type: " << candies[random_index].candy_type << endl << "Price: " << candies[random_index].price << endl;
//     }

// }

void CandyStore::printInventory() 
{
    // we are printing all of the candies in the array using a for loop
    cout << "Store Name: " << _store_name << endl;
    cout << "List of candies in this store: " << endl;
    //vector <Candy> candies;
    //randCandies(candies); //this will keep changing the candies 
    if (_store_stock == 0) // store stock needs to set 
    {
        cout << "There are no candies in " << _store_name << endl;
        return;
    }

    for (int i = 0; i < _store_stock; i++)
    { 
        cout << "Name: " << _store_inventory[i].name << endl;
        cout << "Description: " << _store_inventory[i].description << endl;
        cout << "Effect: " << _store_inventory[i].effect_type << endl;
        cout << "Effect Value: " << _store_inventory[i].effect_value << endl;
        cout << "Candy Type: " << _store_inventory[i].candy_type << endl;
        cout << "Price: " << _store_inventory[i].price << endl;
    }
}


// string CandyStore::getStoreName() const
// {
//     return _storeName;
// }

// void CandyStore::setStoreName(string storeName)
// {
//     _storeName = storeName; 
// }

// int CandyStore::getStoreStock()
// {
//     return _storeStock; 
// }

// void CandyStore::setStoreStock(int storeStock)
// {
//     _storeStock = storeStock; 
// }
