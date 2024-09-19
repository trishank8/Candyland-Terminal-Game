#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

#include "CandyStore.h"
using namespace std;

struct Character
{
    string name;
    int stamina;
    int gold;
    int num_of_candies;
    const static int NUM_OF_CANDIES = 9;
    Candy candies[NUM_OF_CANDIES];
};

class Player
{
    public: 
    Player();
    Player(int stamina, double gold, string name, Candy candy_arr[], int CANDY_ARR_SIZE);
    int getCandyAmt();
    void setStamina(int stamina);
    int getStamina();
    void setGold(double gold);
    double getGold() const;
    void printInventory();
    Candy findCandy(string candy_name);
    bool addCandy(Candy store_candy);
    void replaceCandy(string existing_candy, Candy replace);
    bool removeCandy(string candy_name);
    string getName();
    void setName(string name);
    string getCharacter();
    void setCharacter(string name);
    void printDetails();
    void setCharResources(Character character);
    bool eligibleTurn();
    void setTurnSkipCount(int skip_count);
    bool getRobbersRepelFlag();
    void setRobbersRepelFlag(bool has_repel_flag);
    bool checkMagical();
    bool playRockPaperScissors();
    void printInventoryForFile(ofstream& results);
    void printDetailsInFile(ofstream& results);
    

    private:
    int _stamina;
    double _gold;
    string _name;
    string _char_name;
    const static int NUM_OF_CANDIES = 9;
    Candy _inventory[NUM_OF_CANDIES];
    int _candy_amt;
    int _turn_skip_count;
    bool _has_rob_repel;

};


#endif