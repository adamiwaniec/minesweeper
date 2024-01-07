#pragma once

#include <vector>
#include <ctime>
#include <algorithm>
#include <stdbool.h>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <sstream>

// Game Initialization:
// - Constructor initializes the game board based on user-defined dimensions and mine count.
// - Mines are randomly placed on the board.
// - The revealed, mineBoard, and charBoard vectors are used to track game progress.
// - Board vectors are 0-indexed, which is different from board labels the player sees.

// Gameplay:
// - playGame function controls the main game loop, allowing players to reveal tiles or flag mines.
// - revealTile function reveals a tile, updating the charBoard with the number of adjacent mines.
// - countMinesAroundTile calculates the number of mines surrounding a given tile.


static bool EMPTY = false;
static bool MINE = true;

class Minesweeper {
    public:
        Minesweeper(); 
        Minesweeper(const size_t& x, const size_t& y, const size_t& mines);    //use size_t instead to prevent negative numbers?
        ~Minesweeper();

        int playGame();
        void winGame(double t);
        void loseGame(double t);
        bool revealTile (const size_t & _x, const size_t & _y);
        size_t countMinesAroundTile(const size_t & _x, const size_t & _y);
        bool validTile(const size_t & _x, const size_t & _y);
        void printBoard();

        void printMineBoard();
        void setX(unsigned n);
        unsigned getX();
        void setY(unsigned n);
        unsigned getY();
        void setMines(unsigned n);
        unsigned getMines();

       // char** charBoard;
        std::vector<std::vector<char>> charBoard;   //Board of chars the player sees in terminal

        unsigned revealedEmptyTiles;

    private:
        size_t x;
        size_t y;
        unsigned mines;

       // bool** revealed; 
       // bool** mineBoard;
        std::vector<std::vector<bool>> revealed;    //true = revealed, false = not revealed 
        std::vector<std::vector<bool>> mineBoard;   //MINE or EMPTY (t/f)
};

