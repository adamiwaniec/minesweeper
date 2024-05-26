#pragma once

#include "Minesweeper.h"
#include <vector>

class MinesweeperAI {
public:
    explicit MinesweeperAI(Minesweeper* game);
    int playWithAI();

private:
    Minesweeper* game;
    std::vector<std::vector<bool>> safeTiles;

    std::vector<std::pair<size_t, size_t>> getNeighbors(const size_t& x, const size_t& y) const;
    bool isSafe(const size_t& x, const size_t& y) const;
    bool makeMove();
    bool pickRandomTile();
};