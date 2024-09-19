#include "Player.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

Player::Player()
{
    _stamina = 0;
    _gold = 0.0;
    _name  = "";
    Candy blank = {"Empty","", 0.0,"","",0};
    for (int i = 0; i < NUM_OF_CANDIES; i++)
    {
        _inventory[i] = blank;
    }
    _candy_amt = 0;
    _turn_skip_count = 0;
    _has_rob_repel = false;
}

Player::Player(int stamina, double gold, string name, Candy candy_arr[], const int CANDY_ARR_SIZE)
{
    Candy blank = {"Empty","",0.0,"","",0};
    _stamina = stamina;
    _gold = gold;
    _name = name;
    _candy_amt = 0;
    if(candy_arr[0].name == "")
    {
        for(int i = 0; i < CANDY_ARR_SIZE; i++)
        {
            if(candy_arr[i].name.length() == 0)
            {
                _inventory[i] = blank;
            }
        }
        _candy_amt = 0;
        _turn_skip_count = 0;
        _has_rob_repel = false;
    }
    else if (CANDY_ARR_SIZE < 4)
    {
        for (int i = 0; i < CANDY_ARR_SIZE; i++)
        {
            _inventory[i] = candy_arr[i];
        }
    }
    _candy_amt = 0;
    _turn_skip_count = 0;
    _has_rob_repel = false;

    for (int i = 0; i < 4; i++)
    {
        if(_inventory[i].name != "" && _inventory[i].name != "Empty")
        {
            _candy_amt++;
        }
    }
}

int Player::getCandyAmt()
{
    return _candy_amt;
}

void Player::setStamina(int stamina)
{
    _stamina = stamina;
}

int Player::getStamina()
{
    return _stamina;
}

void Player::setGold(double gold)
{
    _gold = gold;
}

double Player::getGold() const
{
    return _gold;
}
void Player::setName(string name)
{
    _name = name;
}
string Player::getName()
{
    return _name;
}

void Player::setCharacter(string character)
{
    _char_name = character;
}

string Player::getCharacter()
{
    return _char_name;
}

void Player::setCharResources(Character character)
{
    _char_name = character.name;
    _stamina = _stamina + character.stamina;
    _gold = _gold + character.gold;

    for(int i = 0; i < character.num_of_candies; i++)
    {
        //this loads the candy inventory using the candies of the character 
        _inventory[i] = character.candies[i];
        _candy_amt++;
    }
}

void Player::printInventory()
{
    for (int i = 0; i < _candy_amt; i++)
    {
        cout << "[" << _inventory[i].name << "]" << endl;
    }
}

void Player::printDetails()
{
    cout << "Player Name: " << _name << endl;
    cout << "Player Character: " << _char_name << endl;
    cout << "Player Stamina: " << _stamina << endl;
    cout << "Player Gold: " << _gold << endl;
    cout << "Player Inventory: " << endl;
    printInventory();
}

void Player::printInventoryForFile(ofstream& results)
{
    for (int i = 0; i < _candy_amt; i++)
    {
       results << "[" << _inventory[i].name << "]" << endl;
    }
}

void Player::printDetailsInFile(ofstream& results) 
{
    results << "Player Name: " << _name << endl;
    results << "Player Character: " << _char_name << endl;
    results << "Player Stamina: " << _stamina << endl;
    results << "Player Gold: " << _gold << endl;
    results << "Player Inventory: " << endl;
    printInventoryForFile(results);
}

Candy Player::findCandy(string candy_name)
{
    string candy_lower = "";
    for (int i = 0; i < candy_name.length(); i++)
    {
        char lower = tolower(candy_name[i]);
        candy_lower = candy_lower + lower;
    }

    // chacks to see if the candies match
    Candy temp; 
    temp.name = "";
    for (int i = 0; i < NUM_OF_CANDIES; i++)
    {
        string curr_name = _inventory[i].name;
        string curr_lower = "";
        for (int j = 0; j < curr_name.length(); j++)
        {
            curr_lower += tolower(curr_name[j]);
        }
        if (curr_lower == candy_lower)
        {
            temp = _inventory[i];
            return temp;
        }
    }
    return temp;
}

bool Player::addCandy(Candy store_candy)
{
    if (_candy_amt == NUM_OF_CANDIES)
    {
        _inventory[_candy_amt] = store_candy;
        _candy_amt++;
        return true;
    }
    else 
    {
        return false;
    }
}

void Player::replaceCandy(string exist_candy, Candy replace)
{
    for(int i = 0; i < _candy_amt; i++)
    {
        // user will enter candy they want to replace
        // checks to see if it already exists in their curr inventory
        if(_inventory[i].name == exist_candy)
        {
            // replaces the index with existing candy for the new replacement candy
            // this only happens if the player wants to replace their candy if they have filled out their inventory
            _inventory[i] = replace;
        }
    }
}

bool Player::removeCandy(string candy_name)
{
    string candy_name_lower = "";
    for (int i = 0; i < candy_name.length(); i++)
    {
        char lower = tolower(candy_name[i]);
        candy_name_lower = candy_name_lower +lower;
    }
    int index = -1;
    for (int i = 0; i < NUM_OF_CANDIES; i++)
    {
        string curr_candy = _inventory[i].name;
        // converting the current candy name to lowercase
        string curr_candy_lower = "";
        for (int j = 0; j < curr_candy.length(); j++)
        {
            curr_candy_lower += tolower(curr_candy[j]);
        }

        if (curr_candy_lower == candy_name_lower)
        {
            index = i;
            break;
        }
    }

    if(index == -1)
    {
        return false;
    }
    else 
    {
        for (int i = index; i < NUM_OF_CANDIES - 1; i++)
        {
            _inventory[i] = _inventory[i+1];
        }
        _candy_amt--;
        return true;
    }
}

bool Player::eligibleTurn()
{
    bool val = true;
    if(_turn_skip_count != 0)
    {
        val = false;
        _turn_skip_count--;
    }
    // if stamina = 0, then player must skip 2 turns before they can take their next turn
    else if(_stamina == 0)
    {
        val = false;
        _turn_skip_count = 2;
    }
    return val;
}

void Player::setTurnSkipCount(int skip_count)
{
    _turn_skip_count = skip_count;
}

bool Player::getRobbersRepelFlag()
{
    return _has_rob_repel;
}

void Player::setRobbersRepelFlag(bool has_repel_flag)
{
    has_repel_flag = false;
    _has_rob_repel = has_repel_flag;
}

bool Player::checkMagical()
{
    for(int i = 0; i < 9; i++)
    {
        if(_inventory[i].candy_type == "magical") 
        {
            return true; 
        }
        else
        {
            return false; 
        }

    }
    return false;  
}


bool Player::playRockPaperScissors()
{
    bool player_won = false;
    bool play_again = true;

    do 
    {
        string pick = "";
        cout << "Enter rock, paper, or scissors (r, p, s)" << endl;
        do 
        {
            getline(cin, pick);
        }while (pick != "r" && pick != "p" && pick != "s");

        char rps[3] = {'r', 'p', 's'};
        int rand_rps = (rand() % 3);

        switch(pick[0])
        {
            case 'r':
            {
                if(rps[rand_rps] == 'r')
                {
                    // tie
                    cout << rps[rand_rps] << endl;
                    cout << "It was a tie! Play again" << endl;
                    player_won = false;
                    play_again = true;
                }

                if(rps[rand_rps] == 'p')
                {
                    // comp wins
                    cout << rps[rand_rps] << endl;
                    cout << "Computer Won! Better luck next time!" << endl;
                    player_won = false;
                    play_again = false;
                }

                if(rps[rand_rps] == 's')
                {
                    // player wins 
                    cout << rps[rand_rps] << endl;
                    cout << "Congratulations! You won!" << endl;
                    player_won = true;
                    play_again = false;
                }
            }
            break;

            case 'p':
            {
                if(rps[rand_rps] == 'r')
                {
                    // player wins
                    cout << rps[rand_rps] << endl;
                    cout << "Congratulations! You won!" << endl;
                    player_won = true;
                    play_again = false;
                }

                if(rps[rand_rps] == 'p')
                {
                    // tie
                    cout << rps[rand_rps] << endl;
                    cout << "It was a tie! Play again" << endl;
                    player_won = false;
                    play_again = true;
                }

                if(rps[rand_rps] == 's')
                {
                    // comp wins
                    cout << rps[rand_rps] << endl;
                    cout << "Computer Won! Better luck next time!" << endl;
                    player_won = false;
                    play_again = false;
                }
            }
            break;

            case 's':
            {
                if(rps[rand_rps] == 'r')
                {
                    // comp wins
                    cout << rps[rand_rps] << endl;
                    cout << "Computer Won! Better luck next time!" << endl;
                    player_won = false;
                    play_again = false;
                }

                if(rps[rand_rps] == 'p')
                {
                    // player wins
                    cout << rps[rand_rps] << endl;
                    cout << "Congratulations! You won!" << endl;
                    player_won = true;
                    play_again = false;
                }

                if(rps[rand_rps] == 's')
                {
                    // tie
                    cout << rps[rand_rps] << endl;
                    cout << "It was a tie! Play again" << endl;
                    player_won = false;
                    play_again = true;
                }
            }
            break;
        }
    } while (play_again == true);
    return player_won;
}



