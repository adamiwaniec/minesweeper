#pragma once

#include <vector>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <chrono>

// Game Initialization:
// - Constructor initializes the game board based on user-defined dimensions and mine count.
// - Mines are randomly placed on the board.
// - The revealed, mineBoard, and charBoard vectors are used to track game progress.
// - Board vectors are 0-indexed, which is different from board labels the player sees.

// Gameplay:
// - playGame function controls the main game loop, allowing players to reveal tiles or flag mines.
// - revealTile function reveals a tile, updating the charBoard with the number of adjacent mines.
// - countMinesAroundTile calculates the number of mines surrounding a given tile.

constexpr bool EMPTY = false;
constexpr bool MINE = true;

class Minesweeper {
public:
    Minesweeper(const size_t& x, const size_t& y, const size_t& mines);
    int playGame();
    void printBoard() const;

private:
    const size_t x, y, mines;
    unsigned revealedEmptyTiles;

    std::vector<std::vector<bool>> revealed;
    std::vector<std::vector<bool>> mineBoard;
    std::vector<std::vector<char>> charBoard;

    bool revealTile(const size_t& x, const size_t& y);
    size_t countMinesAroundTile(const size_t& x, const size_t& y) const;
    bool validTile(const size_t& x, const size_t& y) const;
    void winGame(double t) const;
    void loseGame(double t) const;
    void placeMines();

    size_t getX() const { return x; }
    size_t getY() const { return y; }
    size_t getMines() const { return mines; }

    friend class MinesweeperAI; 
};