#include "Player.h"
#include "Board.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
using namespace std;

// g++ -Wall -Werror -Wpedantic -std=c++17 candyLandDriver.cpp Board.cpp Player.cpp CandyStore.cpp

// function to lead the character from the file
vector <Character> loadCharacters(string file_name) // used this in hw7
{
    //character name|stamina|gold|candies
    ifstream char_file;
    char_file.open(file_name);
    Character character;
    vector <Character> characters;
    string stamina;
    string gold;
    string line;

    //char_file.open(file_name);

    // do this till the end of the file    
    while (getline(char_file, line))  
    {
        stringstream ss(line);
        // read character name
        getline(ss, character.name, '|');
        if (character.name == "")
        {
            continue;
        }

        getline(ss, stamina, '|');
        // using stoi because string stream only works for strings
        character.stamina = stoi(stamina);
            
        // read gold value of character    
        getline(ss, gold, '|');
        character.gold = stoi(gold);

        character.num_of_candies = 0;
        // get all the candies
        while(ss.good())
        {
            string tmp;
            getline(ss, tmp, ',');
            character.candies[character.num_of_candies].name = tmp;
            character.num_of_candies++;
        }

        characters.push_back(character);

    }
    return characters;
}


// function to load candies
vector <Candy> loadCandies(string file_name) // used in hw7
{
    // Name|Description|Effect type|Effect value|Candy type|Price
    ifstream candy_file;
    candy_file.open(file_name);
    Candy candy;
    vector <Candy> candies;
    string line;

    //candy_file.open(file_name);
    getline(candy_file,line);   
    while (getline(candy_file, line))
    {
        stringstream ss(line);
        getline(ss, candy.name, '|');
        getline(ss, candy.description, '|');
        getline(ss, candy.effect_type, '|');
        string effect_value;
        getline(ss, effect_value, '|');
        // turns string to int as stringstream doesn't work for anything but strings
        candy.effect_value = stoi(effect_value);


        getline(ss, candy.candy_type, '|');

        string price;
        getline(ss, price, '|');
        candy.price = stoi(price);
            

        candies.push_back(candy);
    }
    return candies;
}

// fucntion to load riddles
vector <Riddle> loadRiddles(string file_name) // used in hw7
{
    ifstream riddles_file;
    riddles_file.open(file_name);
    Riddle riddle;
    vector <Riddle> riddles;
    string line;

    //riddles_file.open(file_name);

    while (getline(riddles_file, line))
    {
        stringstream ss(line);
        getline(ss, riddle.riddle, '|');
        
        getline(ss, riddle.answer, '|');  
        riddles.push_back(riddle);
    }
    return riddles;
}

// this details of candy from Candy vector into candy of character
void update(vector <Character>& character, vector <Candy>& candies)
{
    int len = character.size();

    for (int i = 0; i < len; i++)
    {
        for(int j = 0; j < character.at(i).num_of_candies; j++) 
        {
            for (int k = 0; k < candies.size(); k++)
            {
                if (candies[k].name == character.at(i).candies[j].name)
                {
                    // placing candy details in the candy of character
                    character.at(i).candies[j].description = candies[k].description;
                    character.at(i).candies[j].effect_type = candies[k].effect_type;
                    character.at(i).candies[j].effect_value = candies[k].effect_value;
                    character.at(i).candies[j].candy_type = candies[k].candy_type;
                    character.at(i).candies[j].price = candies[k].price;
                }
            }
        } 
    }
}

// displays the char details and candies of the character that you pass
void displayChar(vector <Character> characters)
{
    int len = characters.size();

    for (int i = 0; i < len; i++)
    {
        cout << "--------------------------------------------------------------------------------------------------" << endl;
        cout << "Name: " << characters[i].name << "\nStamina: " << characters[i].stamina << "\nGold: " << characters[i].gold << "\nCandies are listed below: " << endl;
        // multiple candies to go along 
        for (int j = 0; j < characters[i].num_of_candies; j++)
        {
            cout << "[" << characters[i].candies[j].name << "]" << endl;
        }
    }
}

// displaychardetails - gives all the details 
void displayCharDetails(vector <Character> characters)
{
    int len = characters.size();

    for (int i = 0; i < len; i++)
    {
        cout << "--------------------------------------------------------------------------------------------------" << endl;
        cout << "Name: " << characters[i].name << "\nStamina: " << characters[i].stamina << "\nGold: " << characters[i].gold << "\nCandies are listed below: " << endl;
        // multiple candies to go along 
        for (int j = 0; j < characters[i].num_of_candies; j++)
        {
            cout << "[" << characters[i].candies[j].name << "," << endl << characters[i].candies[j].description << "," << characters[i].candies[j].effect_type << "]" << endl;
        }
    }
}


//checks to see if the character name that was entered is actually in the character vector
bool isCharExist(string character, vector <Character> characters)
{
    bool val = false; 
    int size = characters.size();

    for (int i = 0; i < size; i++)
    {
        // checks to see if the name that was entered exists as a character in the vector
        if(characters.at(i).name == character)
        {
            val = true;
            break;
        }
    }
    return val;
}

// it matches the charcter that the player inputs to the character in the vector
Character matchingChar(string character_name, vector <Character> characters)
{
    Character returning;
    int size = characters.size();
    for (int i = 0; i < size; i++)
    {
        // checks to see if the input of the char name is the same as a character in the character vector
        if(characters.at(i).name == character_name)
        {
            returning = characters.at(i);
            break;
        }
    }
    return returning;
}

// Checks to see if the candies match the name in candy vector
Candy matchingCandy(string candy_name, vector <Candy> candies)
{
    Candy returning;
    int size = candies.size();

    for (int i = 0; i < size; i++)
    {
        // checks to see if the input of the candy name is the same as a candy in the candy vector
        if (candies[i].name == candy_name)
        {
            returning = candies[i];
            break;
        }
    }
    return returning;
}

// making the candies randomized (3) -> for the candyStore
// try removing the random index part -> the cout statement
void randCandies(vector <Candy> candies)
{
    int size = candies.size();

    srand(time(0));

    for (int i = 0; i < 3; i++)
    {
        int random_index = (rand() % size); // randomly picks 3 candies to display at the store
        // cout << "Random Index " << random_index;
        cout << "---------------------------------------------------------------------------------------" << endl;
        cout << "Name: " << candies[random_index].name << endl << " Description: " << candies[random_index].description << endl << " Effect: " << candies[random_index].effect_type << endl << " Effect value: " << candies[random_index].effect_value << endl;
        cout << "Candy type: " << candies[random_index].candy_type << endl << "Price: " << candies[random_index].price << endl;
    }

}


// making the candy work for the players
void usingCandy(Board& board, Candy use, Player& curr_player, Player& other_player)
{
    string candy_type = use.candy_type;

    if (candy_type == "gummy")
    {
        // player wants to use gummy candy -> decide tile location (1-83) so that they can add the candy there
        cout << "Where do you want to place your " << use.name << " candy?" << endl;
        string position;
        getline(cin, position, '\n'); // filters the inputs & make sure whitespaces are included
        int tile_position = stoi(position);
        int value = abs(use.effect_value);
        board.setGummyTile(tile_position - 1, value);
        cout << "You have placed your gummy candy on the tile " << tile_position << ". The player that lands on this tile cannot advance from this tile for " << value << " turn(s)." << endl;
    }

    else if(candy_type == "poison")
    {
        char poision;
        do 
        {
            //checks to see if it is y/n
            cout << "Do you want to use " << use.name << " against your opponent? (y/n) " << endl;
            cin >> poision;
        } while ((poision != 'y') && (poision != 'n'));

        if(poision == 'y')
        {
            Candy found;  // this is for checking if opponent has an immunity candy 
            
            // what candy goes to the other
            // Bubblegum Blast will only protect against -> Lucky Licorice.
            // Sparkling Sapphire will only protect against -> Lucky Licorice and Venomous Vortex.
            // Caramel Comet will protect against all the poison candies -> Lucky Licorice, Venomous Vortex, and Toxic Taffy.
            
            bool bubblegum_blast = false;
            bool sparkling_sapphire = false;
            bool caramel_comet = false;
            bool opponent_stamina_lost = true;

            found = other_player.findCandy("Bubblegum Blast");
            if(found.name == "Bubblegum Blast")
            {
                bubblegum_blast = true;
            }

            found = other_player.findCandy("Sparkling Sapphire");
            if(found.name == "Sparkling Sapphire")
            {
                sparkling_sapphire = true;
            }

            found = other_player.findCandy("Caramel Comet");
            if(found.name == "Caramel Comet")
            {
                caramel_comet = true;
            }

            // Want to use the right candy so we don't overuse the immunity. i.e. Lucky Licorice can be fine with Bubblegum blast
            if(use.name == "Toxic Taffy")
            {
                // Need Caramet Comet
                if(caramel_comet)
                {
                    // remove this immunity candy from prevPlayer and no change to stamina
                    other_player.removeCandy("Caramel Comet");
                     opponent_stamina_lost = false;
                    cout << "You have used " << use.name << " candy but your opponent has Caramel Comet candy to protect against your poison candy." << endl;
                }
            }
            else if(use.name == "Venomous Vortex")
            {
                if(sparkling_sapphire)
                {
                    // remove this immunity candy from prevPlayer and no change to stamina
                    other_player.removeCandy("Sparkling Sapphire");
                     opponent_stamina_lost = false;
                    cout << "You have used " << use.name << " candy but your opponent has Sparkling Sapphire candy to protect against your poison candy." << endl;
                }
                else if(caramel_comet)
                {
                    // remove this immunity candy from prevPlayer and no change to stamina
                    other_player.removeCandy("Caramel Comet");
                     opponent_stamina_lost = false;
                    cout << "You have used " << use.name << " candy but your opponent has Caramel Comet candy to protect against your poison candy." << endl;
                }

            }
            else if(use.name == "Lucky Licorice")
            {
                if(bubblegum_blast)
                {
                    // remove this immunity candy from prevPlayer and no change to stamina
                    other_player.removeCandy("Bubblegum Blast");
                     opponent_stamina_lost = false;
                    cout << "You have used " << use.name << " candy but your opponent has Bubblegum Blast candy to protect against your poison candy." << endl;
                }
                else if(sparkling_sapphire)
                {
                    // remove this immunity candy from prevPlayer and no change to stamina
                    other_player.removeCandy("Sparkling Sapphire");
                     opponent_stamina_lost = false;
                    cout << "You have used " << use.name << " candy but your opponent has Sparkling Sapphire candy to protect against your poison candy." << endl;
                }
                else if(caramel_comet)
                {
                    // remove this immunity candy from prevPlayer and no change to stamina
                    other_player.removeCandy("Caramel Comet");
                     opponent_stamina_lost = false;
                    cout << "You have used " << use.name << " candy but your opponent has Caramel Comet candy to protect against your poison candy." << endl;
                }

            }

            // Only decrease stamina from prev player if they don't have any immunity candy
            if( opponent_stamina_lost == true)
            {
                int other_player_stamina = other_player.getStamina();
                int stamina = use.effect_value;
                // decrease old player stamina. this candy stamina is in negative
                int new_stamina = other_player_stamina + stamina;
                if(new_stamina < 0)
                {
                    new_stamina = 0;
                }
                other_player.setStamina(stamina);

            }
        }  
    }
    else if(candy_type == "magical")
    {
        int stamina = curr_player.getStamina();
        int candy_stamina = use.effect_value;

        // sets the new stamina value for that player
        curr_player.setStamina(stamina + candy_stamina);

        cout << "You have used " << use.name << " candy. This has increased your stamina by " << use.effect_value << " points." << endl;

    }
    else
    {
        cout << "Sorry! Unknown candy type (might be a spelling or caps error). You missed your turn, type carefully next time!" << endl;
    }
}

//add the candies to the candy store
void addCandyToStore(CandyStore candy_store[3], vector<Candy> &candies)
{
    for(int i = 0; i < 3; i++)
    {
        for(int j= 0; j< 3; j++)
        {
            int k = rand() % (candies.size());
            candy_store[i].addCandy(candies[k]); // adds rand index to the candy store
        }
    }  
}

void setCandyStores(CandyStore candy_store[3], Board &b)
{
    int store_loc = rand() % 25;
    // calling the function to put the store on a rand magenta tile -> we use the board 
    store_loc = b.findingNextTileWithColor(store_loc, MAGENTA); 
    // putting the candy store to a certain location -> first store has index 0
    b.addCandyStoreIndex(store_loc, 0); 
    
    // for store in 28-54 tiles -> get rand num b/w 27-51 and then search for next green tile to place the 2nd candystore
    store_loc = 27 + rand() % 25;
    store_loc = b.findingNextTileWithColor(store_loc, GREEN);
    b.addCandyStoreIndex(store_loc, 1);

    // for store in 55-82 tiles -> get rand num b/w 54-79 -> search for next blue tile to place the 3rd candy store
    store_loc = 54 + rand() % 25;
    store_loc = b.findingNextTileWithColor(store_loc, BLUE);
    b.addCandyStoreIndex(store_loc, 2);
}

void candiesInStore(vector <Candy> &candies, CandyStore stores[]) // doing this to put random candies into the stores
{
    for(int i = 0; i < 3; i++) // set to 3 since only 3 stores
    {
        for(int j = 0; j < 3; j++) // sets only 3 candies when landed on stores
        {
            int rando = (rand() % (candies.size() - 1)); // this gets 3 rand candies from the candies vector which we loaded before
            stores[i].addCandy(candies[rando]); // from the candies vector it takes a rand candy and puts in the store called
        }
    }
 
}

void hiddenTreasureLoc(Board &b, int num_of_treasures) 
{
    for (int i = 0; i < num_of_treasures; i++) 
    {
        int hidden_treasure_loc = rand() % 83;
        b.addHiddenTreasure(hidden_treasure_loc);
    }
}

// void checksFullInvent(Player& curr_player, const string& candy_name, const string& bought) 
// {
//     Candy bought = matchingChar(candy_name, candies);
//     if (curr_player.getCandyAmt() == 9) {
//         cout << "Oh no, your inventory is full! Would you like to replace the candy you bought with one in your inventory? (y/n): ";
//         char substitute;
//         cin >> substitute;
//         if (substitute == 'y') {
//             cout << "Which candy would you like to substitute?" << endl;
//             cin.ignore(1000, '\n');
//             string sub;
//             getline(cin, sub, '\n');
//             cout << sub << " replaces " << candy_name << endl;
//             curr_player.replaceCandy(sub, bought);
//         }
//     } else {
//         // adds candy to the player inventory
//         curr_player.addCandy(bought);
//     }
// }

// void calamities(Player player[])
// {
//     int player_ix = 0;
//     int calamities = rand() % 100;

//         if (calamities < 40)
//         {
//             int rand_calamities = rand() % 100;

//             if (rand_calamities < 30) // Candy Bandits
//             {
//                 int curr_gold, new_gold;
//                 int rand_bandit = (rand() % 9) + 1;
//                 cout << "Bad luck! Your gold coins were stolen by the Candy Bandits" << endl;
//                 curr_gold = player[player_ix].getGold();
//                 new_gold = curr_gold - rand_bandit;
//                 player[player_ix].setGold(new_gold);
//                 cout << "Your new gold amount is " << new_gold << endl;
//             }
//             else if (rand_calamities > 30 && rand_calamities < 65) // Lollipop Labyrinth
//             {
//                 cout << "Oops! You got lost in the Lollipop Labyrinth! " << endl;
//                 cout << "You have lost a turn trying to escape, but if you play a game of Rock Paper Scissors and win, you can get your turn back!" << endl;
                                
//                 if (player[player_ix].playRockPaperScissors() == true)
//                 {
//                     cout << "Congrats! You got out of the Lollipop Labyrinth and did not lose a turn. I guess luck is on your side!" << endl;
//                 }
//                 else
//                 {
//                     player[player_ix].setTurnSkipCount(1);
//                     cout << "AWW NO! You lost a turn because you didn't win!" << endl;
//                 }

//             }
//             else if (rand_calamities > 65 && rand_calamities < 80) // Candy Avalanche
//             {
//                 int rand_avalanche = (rand() % 5) + 5;
//                 cout << "Watch out! A candy avalanche has struck! You have lost " << rand_avalanche << " gold coins! You must lose a turn to recover!" << endl;
//                 cout << "BUT you can save yourself and recover your turn and your gold by winning a game of Rock Paper Scissors!" << endl;
//                 if (player[player_ix].playRockPaperScissors() == true)
//                 {
//                     cout << "You sucessfully recovered and didn't lose a turn or gold!" << endl;
//                 }
//                 else
//                 {
//                     int curr_gold, new_gold;
//                     curr_gold = player[player_ix].getGold();
//                     new_gold = curr_gold - rand_avalanche;
//                     player[player_ix].setGold(new_gold);
//                     player[player_ix].setTurnSkipCount(1);
                                
//                     cout << "AW NO! You have lost a turn and " << rand_avalanche << " gold coins!" << endl;
//                 }
                        
//             }
//             else // Sticky Taffy
//             {
//                 cout << "Oh no! You got stuck in the sticky taffy trap!" << endl;
//                 cout << "But there is hope for a quick escape! If you have a magical candy in your inventory, you can use it to escape!" << endl;
            
//                 if(player[player_ix].checkMagical() == true)
//                 {
//                     cout << "YAY, you escaped the Sticky Taffy Trap since you had a magical candy!" << endl;
//                 }
//                 else
//                 {
//                     player[player_ix].setTurnSkipCount(1);
//                     cout << "Unfortunately, you lost a turn since you did not have magical candy!" << endl;
//                 }

//              }
//         }
// }

// calamities implemented in main

int main()
{
    int num_players;
    string player1_name;
    string player2_name;
    const static int NUM_OF_PLAYERS = 2;
    Player player[NUM_OF_PLAYERS];
    Board b;
    CandyStore candy_store[3] = {CandyStore("Store 1"), CandyStore("Store 2"), CandyStore("Store 3")};

    vector <Character> characters;
    Character character;
    string char_file;

    vector <Candy> candies;
    vector <Riddle> riddles;

    b.resetBoard();

    // Loads the characters from the character.txt file
    characters = loadCharacters("character.txt");

    //loads the candies from candies.txt file
    candies = loadCandies("candies.txt");

    update(characters, candies); // updates 

    // loads the riddles from riddles.txt
    riddles = loadRiddles("riddles.txt");
    srand(time(0));

    // adds the candies to stores
    addCandyToStore(candy_store, candies); 

    // sets all the stores
    setCandyStores(candy_store, b); 

    // for hidden treasure location
    hiddenTreasureLoc(b, 3);

    // this is the beginning of the game
    cout << "Welcome to the game of Candyland! Please enter the number of participants (DO NOT ENTER NON-NUMERICAL VALUES!): " << endl;
    cin >> num_players;

    if(num_players != 2) // validates that there can only be 2 participants
    {
        cout << "The number of participants can only be 2! Please enter the number of players again: " << endl;
        cin >> num_players;
    }
    
    for (int i = 0 ; i < num_players; i++)
    {
        string name_of_player;
        string char_name;
        string candy_name;
        string sub;

        cout << "Enter the name of Player " << i+1 << endl; // i+1 is used to display player numbers starting from 1 -> as array indices start from 0
        cin >> name_of_player;
        player[i].setName(name_of_player); // sets the name of the player in the array of player objects
        // calls a setName on i player object and passes the name that was entered as an argument.

        cout << "Awesome! Here is a list of characters you can select from: " << endl;

        displayChar(characters); // displayes the characters so that they can choose

        bool temp;
        // if (i == 1)
        // {
        //     cout << "You cannot chose " << char_name << endl;
        // }
        do
        {
          // ensure that the player picks a valid character from the options
          cout << "Who do you select? " << endl;
          cin >> char_name;
          temp = isCharExist(char_name, characters); // checks if the character selected exists and stores F/T in temp to validate
        } while (temp != true); // runs only if the temp is true

        // takes input and assigns it to the same character
        Character chosen = matchingChar(char_name, characters);
        
        // assigns the character's attributes to the character the player chose
        player[i].setCharResources(chosen);

        char visit;
        do
        {
          cout << "Do you want to visit the candy store? (y/n)" << endl;
          cin >> visit;
        } while ((visit != 'y') && (visit != 'n'));

        if(visit == 'n')
        {
            continue; // goes throught the program w/o visiting the candy store -> skips that part of the code
        }

        cout << "Here is a list of candies in the candy store:" << endl;

        randCandies(candies); // gives 3 random candies that the player can chose from

        cout << "Which candy would you like to buy? ";

        // filters input and ensures that whitespaces -> included 
        cin.ignore(1000, '\n');
        getline(cin, candy_name, '\n');

        // takes input and assigns it to the matching candy
        Candy bought;
        bought = matchingCandy(candy_name, candies);

        // checks if the inventory is full or not
        if(player[i].getCandyAmt() == 9) // total amt of candies is 9
        {
            cout << "Oh no, your inventory is full! Would you like to replace the candy you bought with one in your inventory? (y/n): ";
            char substitute;
            cin >> substitute;
            if(substitute == 'y')
            {
                cout << "Which candy would you like to substitute?" << endl;
                cin.ignore(1000, '\n');
                getline(cin, sub, '\n');
                cout << sub << " replaces " << candy_name << endl;
                player[i].replaceCandy(sub, bought);
            }

        }
        else
        {
          // adds candy to the player inventory
          player[i].addCandy(bought);
        }

        cout << "Here is your updated candy inventory" << endl;
        player[i].printInventory();

    }

    int winner_ix = 0; // index for the winner
    bool winner = false;
    int player_ix = 0; // the player array index

    do
    {
        bool next = false; // this is the next person who plays
        int pos_ix; // this is the players position -> the index

        do
        {
            cout << "It's " << player[player_ix].getName() << " turn" << endl;
            cout << "Please select a menu option below" << endl;
            cout << "1. Draw a card" << endl;
            cout << "2. Use candy" << endl;
            cout << "3. Show player stats" << endl;

            char input;
            cin >> input;

            switch(input)
            {

                case '1':
                {
                   cout << "To draw a card Press D or d" << endl;
                   cin >> input;
                   if(input == 'D' || input == 'd')
                   {
                     if(player[player_ix].eligibleTurn() == true) // checks to see if player is eligible for the turn
                     {
                        winner = b.drawCard(player_ix); //

                        b.displayBoard();

                        int stamina = player[player_ix].getStamina(); // each turn -> 1 stamina lost for player
                        stamina--;
                        player[player_ix].setStamina(stamina); // sets the new stamina for player
                        

                        // Calamaties

                        int calamities = rand() % 100;

                        if (calamities < 40)
                        {
                            int rand_calamities = rand() % 100;

                            if (rand_calamities < 30) // Candy Bandits
                            {
                                int curr_gold, new_gold;
                                int rand_bandit = (rand() % 9) + 1;
                                cout << "Bad luck! Your gold coins were stolen by the Candy Bandits" << endl;
                                curr_gold = player[player_ix].getGold();
                                new_gold = curr_gold - rand_bandit;
                                player[player_ix].setGold(new_gold);
                                cout << "Your new gold amount is " << new_gold << endl;
                            }
                            else if (rand_calamities > 30 && rand_calamities < 65) // Lollipop Labyrinth
                            {
                                cout << "Oops! You got lost in the Lollipop Labyrinth! " << endl;
                                cout << "You have lost a turn trying to escape, but if you play a game of Rock Paper Scissors and win, you can get your turn back!" << endl;
                                
                                if (player[player_ix].playRockPaperScissors() == true)
                                {
                                    cout << "Congrats! You got out of the Lollipop Labyrinth and did not lose a turn. I guess luck is on your side!" << endl;
                                }
                                else
                                {
                                    player[player_ix].setTurnSkipCount(1);
                                    cout << "AWW NO! You lost a turn because you didn't win!" << endl;
                                }

                            }
                            else if (rand_calamities > 65 && rand_calamities < 80) // Candy Avalanche
                            {
                                int rand_avalanche = (rand() % 5) + 5;
                                cout << "Watch out! A candy avalanche has struck! You have lost " << rand_avalanche << " gold coins! You must lose a turn to recover!" << endl;
                                cout << "BUT you can save yourself and recover your turn and your gold by winning a game of Rock Paper Scissors!" << endl;
                                if (player[player_ix].playRockPaperScissors() == true)
                                {
                                    cout << "You sucessfully recovered and didn't lose a turn or gold!" << endl;
                                }
                                else
                                {
                                    int curr_gold, new_gold;
                                    curr_gold = player[player_ix].getGold();
                                    new_gold = curr_gold - rand_avalanche;
                                    player[player_ix].setGold(new_gold);
                                    player[player_ix].setTurnSkipCount(1);
                                
                                    cout << "AW NO! You have lost a turn and " << rand_avalanche << " gold coins!" << endl;
                                }
                        
                            }
                            else // Sticky Taffy
                            {
                                cout << "Oh no! You got stuck in the sticky taffy trap!" << endl;
                                cout << "But there is hope for a quick escape! If you have a magical candy in your inventory, you can use it to escape!" << endl;
            
                                if(player[player_ix].checkMagical() == true)
                                {
                                    cout << "YAY, you escaped the Sticky Taffy Trap since you had a magical candy!" << endl;
                                }
                                else
                                {
                                    player[player_ix].setTurnSkipCount(1);
                                    cout << "Unfortunately, you lost a turn since you did not have magical candy!" << endl;
                                }

                            }
                        }

                        // End of the calamaties
                       
                        pos_ix = b.getPlayerPosition(player_ix);
                        
                        bool is_store = b.isPositionCandyStore(pos_ix); // checks to see if the pos of the player is a candy store
                        if(is_store == true)
                        {
                            cout << "CANDIES! You landed on a candy store!" << endl;
                        
                            int candyStoreIndex = b.toCandyStoreIndex(pos_ix); // ensures that the player is on a candy store -> returns store index
                            
                            char visit_store;

                            do
                            {           
                                cout << "Do you want to visit the candy store? (y/n)" << endl;
                                cin >> visit_store;
                            } while ((visit_store != 'y') && (visit_store != 'n'));

                            if(visit_store == 'y')
                            {
                                string candy_name, sub;
                                double player_gold = player[player_ix].getGold();

                                // prints the candies of that store
                                candy_store[candyStoreIndex].printInventory();
                                cout << "Which candy would you like to buy? ";
                               
                                cin.ignore(1000, '\n'); // filters input and ensures that whitespaces -> included 
                                getline(cin, candy_name, '\n');

                                Candy boughtCandy = matchingCandy(candy_name, candies);

                                if(player[player_ix].getCandyAmt() == 9)
                                // chose 3 because the fewest number of candies a character has is 3 (so that means the inventory is full)
                                {
                                    cout << "You do not have sufficient place in the candy inventory, Would you like to substitute your candy with any existing candy?(y/n): ";
                                    char subsChoice;
                                    cin >> subsChoice;
                                    if(subsChoice == 'y')
                                    {
                                        cout << "Which candy would you like to substitute?" << endl;
                                        cin.ignore(1000, '\n');
                                        getline(cin, sub, '\n');
                                        cout << sub << " replaces " << candy_name << endl;
                                        player[player_ix].replaceCandy(sub, boughtCandy);
                                        candy_store[candyStoreIndex].removeCandy(candy_name);
                                    }

                                }
                                else if (player_gold >= boughtCandy.price)
                                {
                                    // adds candy to player inventory
                                    player[player_ix].addCandy(boughtCandy);
                                    player_gold = player_gold - boughtCandy.price;
                                    player[player_ix].setGold(player_gold);
                                    candy_store[candyStoreIndex].removeCandy(candy_name);
                                    candy_store[candyStoreIndex].printInventory();

                                }
                                else
                                {
                                    cout << "Sorry you don't have enough gold to purchase this candy" << endl;
                                }

                                cout << "Here is your updated candy inventory" << endl;
                                player[player_ix].printInventory();
                            }

                        }
                        cout << "Player " << player_ix + 1 << " position  is " << pos_ix+1 << endl;
                        Tile player_tile = b.getPlayerPositionTile(player_ix);

                        if(player_tile.has_gummy == true) // is gummy candy on the tile
                        {
                            cout << "Player " << player[player_ix].getName() << " is on a tile with gummy candy and will skip " << player_tile.gummy_skip_count << " turns" << endl;
                            player[player_ix].setTurnSkipCount(player_tile.gummy_skip_count);
                        }

                        if(player_tile.isHiddenTreasure == true)  // if the tile is a hidden treasure tile
                        {
                            srand(time(0));
                            string answer;
                            int rand_riddle = rand() % riddles.size();
                            bool solving;
                           
                            do
                            {
                                solving = false;
                            
                                cout << "EXCITING! You landed on a hidden treasure! If you solve this riddle, you can get a reward!" << endl;
                                cout << riddles[rand_riddle].riddle << endl;
                                
                                cin.ignore(1000, '\n'); // filters input and ensures that whitespaces -> included 
                                getline(cin, answer, '\n');

                                if (answer == riddles[rand_riddle].answer)
                                {
                                    cout << "SO SMART! You were correct! Here is your reward!" << endl;

                                    int rand_treasure = rand () % 100;

                                    if (rand_treasure < 10) // Gold Windall
                                    {
                                        int curr_gold, new_gold;
                                        int rand_windfall = (rand() % 20) + 20;
                                        cout << "RICHES! You were blessed with a Gold Windfall and got " << rand_windfall << " units of Gold!" << endl;
                                        curr_gold = player[player_ix].getGold();
                                        new_gold = curr_gold + rand_windfall;
                                        player[player_ix].setGold(new_gold);
                                    }
                                    else if (rand_treasure > 10 && rand_treasure < 40) // Stamina Refill 
                                    {
                                        int stamina_amt, new_stamina;
                                        int rand_refill = (rand() % 20) + 10;
                                        cout << "Guess what! you just got a stamina refill!! It was " << rand_refill << " units of Stamina!" << endl;
                                        stamina_amt = player[player_ix].getStamina();
                                        new_stamina = stamina_amt + rand_refill;
                                        player[player_ix].setStamina(new_stamina);
                                        
                                    }
                                    else if (rand_treasure > 40 && rand_treasure < 70) // This is for Robber's Repel
                                    {
                                        player[player_ix].setRobbersRepelFlag(true);
                                        cout << "Defense is always necessary! Here is the Robber's Repel Shield which will protect you from any robbers!" << endl;
                                    }
                                    else if (rand_treasure > 70 && rand_treasure < 100)
                                    {
                                        int randomCandyAcquisition = rand() % 100;

                                        if (randomCandyAcquisition < 30) // Hunter's Truffle
                                        {
                                            solving = true;
                                        }
                                        else if (randomCandyAcquisition > 30 && randomCandyAcquisition < 100) // Jellybean of Vigor
                                        {
                                            int stamina_amt, new_stamina;
                                            cout << "Your reward is the honorable Jellybean of Vigor! Enjoy 50 units of Stamina!" << endl;
                                            stamina_amt = player[player_ix].getStamina();
                                            
                                            if(stamina_amt < 100) // checks to see if stamina of the player is > 100 or < 100 and if less adds 50. if not caps at 100
                                            {
                                                new_stamina = stamina_amt + 50;
                                                if(new_stamina > 100)
                                                {
                                                    new_stamina = 100;
                                                }
                                                player[player_ix].setStamina(new_stamina); // updates the stamina
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    cout << "Better luck next time! That was the wrong answer :(" << endl;
                                }

                            }while(solving == true); // only if the player is solving the riddle
   
                        }
                
                        int old_pos_ix = 0;
                        int old_ix =0 ;


                        if(old_pos_ix == pos_ix) // same tile constraint
                        {
                            cout << " Player " << player_ix + 1 << " stepped on same tile as previous player" << endl;
                            if (player[player_ix].getRobbersRepelFlag() == false)
                            {
                                srand(time(0));
                                int gold_stolen, read_gold, new_gold;
                                gold_stolen = (rand() % 25) + 5; // range from 5-30 gold coins for stealing
                                read_gold = player[player_ix].getGold();
                                new_gold = read_gold - gold_stolen; // the new gold amount after stolen
                                player[player_ix].setGold(new_gold);

                                read_gold = player[old_ix].getGold();
                                player[old_ix].setGold(read_gold + gold_stolen);  // adds the amt stolen to other players gold

                                cout << "Player " << old_ix + 1 << " has stolen " << gold_stolen << " gold coins from you!" << endl;
                            }
                            else
                            {
                                cout << "Player " << player_ix << " has the Robber's Repel Shield to protect them!" << endl;
                                
                            }
                        }
                        
                        else // special tile
                        {
                            // b.specialTiles( player, player_ix);
                            // specialTiles(moving, other, number)

                            int typeOfTile = rand()%4+1;
                            if(typeOfTile == 1) // shortcut tile 
                            {
                                int position = b.getPlayerPosition(player_ix -1);
                                // Handle shortcut logic
                                cout << "You landed on a shortcut tile" <<endl;
                                if (position + 4 >= 83)
                                {
                                    // If the player is less than 4 tiles from the castle, move to the castle
                                    b.setPlayerPosition(player_ix-1, 83 - 1);
                                }
                                else
                                {
                                    b.setPlayerPosition(player_ix-1, (position + 4)); // getPlayerPosition(playerNumber-1)
                                }
                                
                            }

                            else if(typeOfTile ==2) // gum drop forest 
                            {
                                cout << "You landed in the gumdrop forest" << endl;
                                if(b.getPlayerPosition(player_ix-1) - 4 <= 0){

                                        //removeLastPosotion
                                        b.setPlayerPosition(player_ix-1,0);
                                        
                                    } 
                                    else
                                    {
                                        b.setPlayerPosition(player_ix-1, b.getPlayerPosition(player_ix)); // this stores the prev position in an arry ana d then will get that 
                                        
                                        b.setPlayerPosition(player_ix-1, b.getPlayerPosition(player_ix-1));
                                    }
                                
                                    int randomGold = rand() % 6 + + 5;
                                
                                    if(player[player_ix].getGold() - randomGold <= 0)
                                    {
                                        player[player_ix].setGold(0);
                                    } 
                                    else
                                    {
                                        player[player_ix].setGold(player[player_ix].getGold() - randomGold);
                                    }   
                                //change player position to 4 steps back
                                //if the player is less than 4 tiles from the start, taken back to start
                                //remove a random number between 5 and 10 from their gold
                            }

                            else if(typeOfTile == 3) // icecream tile 
                            {
                            
                                cout << "You landed on an ice cream stop. You get an extra card draw" << endl;
                                b.drawCard(player_ix);
                                //b.displayBoard();
                            }

                            else if(typeOfTile == 4) // gingerbread tile 
                            {
                                //take the player back to their previous position and remove an immunit candy from the player's inventory
                                cout << "You landed at the Gingerbread House. It transported you back to your last position and took an immunity candy!" << endl;
                                b.setPlayerPosition(player_ix-1, b.getPlayerPosition(player_ix)); // set it to the previous position 
                                //b.displayBoard();
                                // this part of the function will remove one of immunity candie 
                                    if(player[player_ix].removeCandy("Caramel Comet")==0)
                                    {
                                        if(player[player_ix].removeCandy("Sparkling Sapphire")==0)
                                        {
                                            player[player_ix].removeCandy("Bubblegum Blast");
                                            
                                        }
                                    }
                                
                            } 
                            
                        }
                     }

                     else
                     {
                        // the player is not eligible for the turn then we print this
                        cout << "Player " << player[player_ix].getName() << " not eligible for a turn currently" << endl;
                     }


                     if (winner == true)
                     {
                        winner_ix = player_ix;
                     }
                     
                   }
                   next = true;
                }break;

                case '2':
                {
                    string input_candy;

                    cout << "Here is a list of your candies you cann chose from: " << endl;
                    player[player_ix].printInventory();
                    cout << "Which candy would you like to use?" << endl;

                    cin.ignore(1000, '\n'); // filters input and ensures that whitespaces -> included 
                    getline(cin, input_candy, '\n');

                    Candy candyToUse = matchingCandy(input_candy, candies); 

                    if(player_ix == 0) 
                    {
                        usingCandy(b, candyToUse, player[0], player[1]);

                    }
                    if(player_ix == 1)
                    {
                        usingCandy(b, candyToUse, player[1], player[0]);

                    }
                    player[player_ix].removeCandy(input_candy); // removes the candy from the players inventory

                }break;

                case '3':
                {
                    cout << "These are your stats: " << endl;
                    player[player_ix].printDetails();
                }
                break;
            }

        } while(next == false); //checks if someone turn is
        
        // updates the player turns
        if (player_ix == 1)
        {
            player_ix = 0; // this will set player 1 turn
        }
        else
        {
            player_ix++; // this will set player 2 turn
        }
 

    } while (winner == false); // if no one won
    
    if (winner == true) // if someone won printing the details
    {
        if (winner_ix == 1)
        {
            cout << "OMG " << player[winner_ix].getName() << " WON" <<endl;
            cout << "Check the file to see the stats! " << endl;

            ofstream results;
            results.open("results.txt");
            for (int i = 0; i < 2; i++)
            {
                player[i].printDetailsInFile(results);
            }

            results.close();
            cout << "Thank you for playing!!" << endl;
            return 0;

        }

        if (winner_ix == 0)
        {
            cout << "OMG " << player[winner_ix].getName() << " WON" <<endl;
            cout << "Check the file to see the stats! " << endl;

            ofstream results;
            results.open("results.txt");
            for (int i = 0; i < 2; i++)
            {
                player[i].printDetailsInFile(results);
            }

            results.close();
            cout << "Thank you for playing!!" << endl;
            return 0;

        }
        
    }

    // print the stats in a results.txt file -> write into it

}





    
    


   
    




