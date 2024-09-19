#include "Board.h"
#include "Player.h"

Board::Board() 
{
    resetBoard();
}

void Board::resetBoard()
{
    const int COLOR_COUNT = 3;
    const string COLORS[COLOR_COUNT] = {MAGENTA, GREEN, BLUE};
    Tile new_tile;
    string current_color;
    for (int i = 0; i < _BOARD_SIZE - 1; i++)
    {
        current_color = COLORS[i % COLOR_COUNT];
        // new_tile = {current_color, "regular tile"};
        // _tiles[i] = new_tile;
        new_tile.color = current_color;
        new_tile.tile_type = "regular tile";
        new_tile.has_gummy = false;
        new_tile.gummy_skip_count = 0;
        new_tile.isCandyStore = false;
        new_tile.candyStoreIndex = 0;
        new_tile.isHiddenTreasure = false;
        _tiles[i] = new_tile;
    }

    new_tile.color = ORANGE;
    new_tile.tile_type = "regular tile";
    new_tile.has_gummy = false;
    new_tile.gummy_skip_count = 0;
    new_tile.isCandyStore = false;
    new_tile.candyStoreIndex = 0;
    new_tile.isHiddenTreasure = false;

    _tiles[_BOARD_SIZE - 1] = new_tile;

    _candy_store_count = 0;
    for(int i = 0; i < _MAX_CANDY_STORE; i++)
    {
        _candy_store_position[i] = -1;    
    }

    for(int i = 0; i < 2; i++)
    {
        _player_position[i] = 0;
    }


    
    // new_tile = {ORANGE, "regular tile"};
    // _tiles[_BOARD_SIZE - 1] = new_tile;

    // _candy_store_count = 0;
    // for (int i = 0; i < _MAX_CANDY_STORE; i++)
    // {
    //     _candy_store_position[i] = -1;
    // }

    // _player_position = 0;
}

void Board::displayTile(int position)
{
    if (position < 0 || position >= _BOARD_SIZE)
    {
        return;
    }
    Tile target = _tiles[position];
    cout << target.color << " ";
    for(int i = 0; i < 2; i++)
    {
        if (position == _player_position[i])
        {
            cout << i+1;
        }
        else
        {
            cout << " ";
        }

    }
    
    cout << " " << RESET;
}

void Board::setGummyTile(int tile_location, int skip_count)
{
    if(tile_location < 0 || tile_location >= _BOARD_SIZE)
    {
        return;
    }
    _tiles[tile_location].has_gummy = true;
    _tiles[tile_location].gummy_skip_count = skip_count;
}

void Board::displayBoard()
{
    // First horizontal segment
    for (int i = 0; i <= 23; i++)
    {
        displayTile(i);
    }
    cout << endl;
    // First vertical segment
    for (int i = 24; i <= 28; i++)
    {
        for (int j = 0; j < 23; j++)
        {
            cout << "    ";
        }
        displayTile(i);
        cout << endl;
    }
    // Second horizontal segment
    for (int i = 52; i > 28; i--)
    {
        displayTile(i);
    }
    cout << endl;
    // Second vertical segment
    for (int i = 53; i <= 57; i++)
    {
        displayTile(i);
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        cout << endl;
    }
    // Third horizontal segment
    for (int i = 58; i < _BOARD_SIZE; i++)
    {
        displayTile(i);
    }
    cout << ORANGE << "Castle" << RESET << endl;
}

bool Board::setPlayerPosition(int player_index, int new_position)
{
    if (new_position >= 0 && new_position < _BOARD_SIZE)
    {
        _player_position[player_index] = new_position;
        return true;
    }
    return false;
}

int Board::getBoardSize() const
{
    return _BOARD_SIZE;
}

int Board::getCandyStoreCount() const
{
    return _candy_store_count;
}

int Board::getPlayerPosition(int player_index) const
{
    return _player_position[player_index];
}

Tile Board::getPlayerPositionTile(int player_index)
{
    return _tiles[_player_position[player_index]];
}

bool Board::addCandyStoreIndex(int board_position_index, int candyStoreIndex)
{
    if (_candy_store_count >= _MAX_CANDY_STORE)
    {
        return false;
    }
    _candy_store_position[_candy_store_count] = board_position_index;
    _tiles[board_position_index].isCandyStore = true;
    _tiles[board_position_index].candyStoreIndex = candyStoreIndex;
    _candy_store_count++;
    return true;
}

bool Board::isPositionCandyStore(int board_position)
{
    for (int i = 0; i < 3; i++)
    {
        if(_candy_store_position[i] == board_position)
        {
            return true;
        }
    }
    return false;
}

int Board::toCandyStoreIndex(int board_position)
{
    if(_tiles[board_position].isCandyStore == true)
    {
        return _tiles[board_position].candyStoreIndex;
    }
    else 
    {
        cout << "Oh no! This position does not have a candy store" << endl;
        return 0;
    }
}

bool Board::movePlayer(int player_index, int tile_to_move_forward)
{
    int new_player_position = tile_to_move_forward + _player_position[player_index];
    if(new_player_position < 0 || new_player_position >= _BOARD_SIZE)
    {
        return false;
    }
    _player_position[player_index] = new_player_position;
    return true;
}

bool Board::drawCard(int player_index)
{
    int card_color_index = 1 + (rand() % 100);
    int double_color_index = (rand() % 3) + 1;
    string drawn_card;
    string drawn_card_name;
    bool double_color = false;
    int move_amt = 0;
    bool isPlayerWinner = false;
    srand(time(NULL));

    if(card_color_index >=1 && card_color_index <= 25)
    {
        drawn_card = MAGENTA;
        drawn_card_name = "Magenta";
    }
    else if (card_color_index >= 26 && card_color_index <= 50)
    {
        drawn_card = GREEN;
        drawn_card_name = "Green";
    }
    else if (card_color_index >= 51 && card_color_index <= 75)
    {
        drawn_card = BLUE;
        drawn_card_name = "Blue";
    }
    else if (card_color_index >= 76 && card_color_index <= 100)
    {
        if(double_color_index == 1)
        {
            drawn_card = MAGENTA;
            drawn_card_name = "Magenta";
            double_color = true;
        }
        else if(double_color_index == 2)
        {
            drawn_card = GREEN;
            drawn_card_name = "Green";
            double_color = true;
        }
        else if(double_color_index == 3)
        {
            drawn_card = BLUE;
            drawn_card_name = "Blue";
            double_color = true;
        }
    }

    if (double_color == false)
    {
        for (int i = getPlayerPosition(player_index) + 1; i < 83; i++)
        {
            if (drawn_card == _tiles[i].color) 
            {
                move_amt = i;
                isPlayerWinner = false;
                break;
            }
            else 
            {
                move_amt = i;
                isPlayerWinner = true;
            }
        }
        cout << "You drew a " << drawn_card_name << " card. You are advancing to " << drawn_card_name << " tile." << endl;
    }

    else if(double_color == true)
    {
        for (int i = getPlayerPosition(player_index) + 4; i < 83; i++)
        {
            if (drawn_card == _tiles[i].color)
            {
                move_amt = i;
                isPlayerWinner = false;
                break;
            }
            else 
            {
                move_amt = i;
                isPlayerWinner = true;
            }
        }
        cout << "You drew a double " << drawn_card_name << " card. You are advancing two " << drawn_card_name << " tiles. This is your updated path." << endl;
    }
    
    setPlayerPosition(player_index, move_amt);

    return isPlayerWinner;
}

int Board::findingNextTileWithColor(int starting_location, string color)
{
    for (int i = starting_location; i < _BOARD_SIZE; i++)
    {
        if(_tiles[i].color == color)
        {
            return i;
        }
    }
    return 0;
}

void Board::addHiddenTreasure(int board_position_index)
{
    _tiles[board_position_index].isHiddenTreasure = true; 
}

// void Board::specialTiles(Player player[],int player_index)
// {
//     // if it returns 1 it draws card again, but if it returns 0 that turn is over 
//     int typeOfTile = rand()%4+1;
//     if(typeOfTile == 1) // shortcut tile 
//     {
//         int position = getPlayerPosition(player_index -1);
//         // Handle shortcut logic
//         cout << "You landed on a shortcut tile" <<endl;
//         if (position + 4 >= 83)
//         {
//             // If the player is less than 4 tiles from the castle, move to the castle
//             setPlayerPosition(player_index-1, 83 - 1);
//         }
//         else
//         {
//             setPlayerPosition(player_index-1, (position + 4)); // getPlayerPosition(playerNumber-1)
//         }
//         //return {movingPlayer,otherPlayer};
        

//     }

//     else if(typeOfTile ==2) // gum drop forest 
//     {//gumdrop forest
//         cout << "You landed in the gumdrop forest" << endl;
//          if(getPlayerPosition(player_index-1) - 4 <= 0){

//                 //removeLastPosotion;
//                 setPlayerPosition(player_index-1,0);
                
//             } 
//             else
//             {
//                 setPlayerPosition(player_index-1,getPlayerPosition(player_index)); // this stores the prev position in an arry ana d then will get that 
                
//                 setPlayerPosition(player_index-1,getPlayerPosition(player_index-1));
//             }
           
//             int randomGold = rand() % 6 + + 5;
           
//             if(player[player_index].getGold() - randomGold <= 0)
//             {
//                 player[player_index].setGold(0);
//             } 
//             else
//             {
//                 player[player_index].setGold(player[player_index].getGold() - randomGold);
//             }
//             //return {movingPlayer,otherPlayer};
//         //change player position to 4 steps back
//             //if the player is less than 4 tiles from the start, taken back to start
//         //remove a random number between 5 and 10 from their gold
   
//     }
//     else if(typeOfTile == 3) // icecream tile 
//     {//ice cream tile
     
//         cout << "You landed on an ice cream stop. You get an extra card draw" << endl;
//        //return {};

//     }
//     else if(typeOfTile == 4) // gingerbread tile 
//     {//gingerbread
//          //take the player back to their previous position and remove an immunit candy from the player's inventory
//             cout << "You landed at the Gingerbread House. It transported you back to your last position and took an immunity candy!" << endl;
//            setPlayerPosition(player_index-1,getPlayerPosition(player_index)); // set it to the previous position 
//            displayBoard();
//            // this part of the function will remove one of immunity candie 
//             if(player[player_index].removeCandy("Caramel Comet")==0){
//                 if(player[player_index].removeCandy("Sparkling Sapphire")==0)
//                 {
//                     player[player_index].removeCandy("Bubblegum Blast");
                    
//                 }
//             }
          
           
//             //return {movingPlayer,otherPlayer};
//     } 

//     //return {movingPlayer,otherPlayer};
     
// } 


// // how to place the candy_store on the board 
// // make a candystore class and put it on the board 
// // player lands on candystore
// // pseudocode 
