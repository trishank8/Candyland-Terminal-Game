------------------------
HOW TO COMPILE AND RUN
------------------------
Compile: g++ -std=c++17 candyLandDriver.cpp Board.cpp Player.cpp CandyStore.cpp -o
proj2
Run: ./a.out
------------------------
DEPENDENCIES
------------------------
Board.h, Player.h, CandyStore.h, riddle.txt, candies.txt, character.txt must be in the same
directory as the cpp files in order to compile.
------------------------
SUBMISSION INFORMATION
------------------------
CSCI1300 Fall 2023 Project 2
Author: Trisha Nookala
Recitation: 303 - Nick Cooper
Date: December 07, 2023
------------------------
ABOUT THIS PROJECT
------------------------
This project implements an interactive board game fashioned after the game
CandyLand. There are two players who go through the board. They have to draw card as they go through
the board. They can draw cards of magenta, green and blue or double cards of colors magenta, green, and blue.
As they move through the board the players can land on tiles such as a special tile, hidden treasure, and calamities 
where they go through mini games and try to win/solve them. Players visit candy store and buy candies. They can use 
their candies against each other to try and get an advantage. The goal of the game is for the players to reach the Castle. 
Whoever reaches the Castle first ends up as the winner. 




