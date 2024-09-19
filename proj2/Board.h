#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include "Player.h"
#define RED "\033[;41m"     /* Red */
#define GREEN "\033[;42m"   /* Green */
#define BLUE "\033[;44m"    /* Blue */
#define MAGENTA "\033[;45m" /* Magenta */
#define CYAN "\033[;46m"    /* Cyan */
#define ORANGE "\033[48;2;230;115;0m"  /* Orange (230,115,0)*/
#define RESET "\033[0m"

using namespace std;

// struct Candy
// {
//     string name;
//     string description;
//     double price;
//     string candy_type;
// };

struct Tile
{
    string color;
    string tile_type;
    bool has_gummy;
    int gummy_skip_count;
    bool isCandyStore;
    int candyStoreIndex;
    bool isHiddenTreasure;

};

struct Riddle
{
    string riddle;
    string answer;
};


class Board
{
private:
    const static int _BOARD_SIZE = 83;
    Tile _tiles[_BOARD_SIZE];
    const static int _MAX_CANDY_STORE = 3;
    int _candy_store_position[_MAX_CANDY_STORE];
    int _candy_store_count;
    const static int NUM_OF_PLAYERS = 2;
    int _player_position[NUM_OF_PLAYERS];
    // To add more players - need an array or vector of positions for 

public:
    Board();

    void resetBoard();
    void displayTile(int);
    void setGummyTile(int tile_location, int skip_count);
    
    void displayBoard();

    bool setPlayerPosition(int player_index, int position);

    int getBoardSize() const;
    int getCandyStoreCount() const;
    int getPlayerPosition(int player_index) const;
    Tile getPlayerPositionTile(int player_index);

    bool addCandyStoreIndex(int ,int);
    bool isPositionCandyStore(int); 
    int toCandyStoreIndex(int board_position);

    bool movePlayer(int player_Index, int tile_to_move_forward); // change arguments for  multiple players - have to make it work for multiple people so we would need to put in an argument where it would choose the player and then move that player
    bool drawCard(int player_index);
    int findingNextTileWithColor(int starting_location, string color);
    void addHiddenTreasure(int board_position_index);
    void specialTiles(Player player[], int player_index);
};

// add functionality to report which candy store exists on a tile
// can add to either board or candystore class

// class CandyStore
// {
//     private:
//     vector <Candy> store_candy; // figure out how to work with this
//     string store_name; // and how to work with this
//     string store_clerk;
//     double store_gold;

//     public:
//     CandyStore();
//     // display 3 candies
//     void displayCandies();

//     // add candies
//     void addCandy(); // can be void or bool

//     // menu for the store
//     void storeMenu();
//     // remove candy
//     void removeCandy();

//     // function to buy candy

// };

#endif

// bool movePlayer (int player, int tile_move_forward, Player  )
//void Board::