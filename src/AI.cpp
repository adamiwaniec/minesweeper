#include "AI.h"

MinesweeperAI::MinesweeperAI(Minesweeper* game)
    : game(game), safeTiles(game->getX(), std::vector<bool>(game->getY(), false)) {}

std::vector<std::pair<size_t, size_t>> MinesweeperAI::getNeighbors(const size_t& x, const size_t& y) const { //return vec of x,y pairs
    std::vector<std::pair<size_t, size_t>> neighbors;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue; //Skip curr tile
            size_t newX = x + i;
            size_t newY = y + j;
            if (game->validTile(newX, newY)) neighbors.emplace_back(newX, newY);
        }
    }
    return neighbors;
}

bool MinesweeperAI::isSafe(const size_t& x, const size_t& y) const {
    return game->validTile(x, y) && game->charBoard[x][y] == '*' && !safeTiles[x][y];
}

bool MinesweeperAI::makeMove() {

    bool moveAgain = 0;
    for (size_t i = 0; i < game->getX(); ++i) {
        for (size_t j = 0; j < game->getY(); ++j) {
            if (game->charBoard[i][j] >= '1' && game->charBoard[i][j] <= '8') {  //ignores 0, *, and F
                int tileNumber = game->charBoard[i][j] - '0';  //convert char to int
                auto neighbors = getNeighbors(i, j);
                int unrevealedCount = 0;
                int flaggedCount = 0;

                /*Count flags and unrevealed tiles around curr*/
                for (auto& [i, j] : neighbors) { 
                    if (game->charBoard[i][j] == 'F') {
                        flaggedCount++;
                    } else if (game->charBoard[i][j] == '*') {
                        unrevealedCount++;
                    }
                }

                /*Reveal tiles if tile # = flags*/
                if (flaggedCount == tileNumber) {
                    for (auto& [i, j] : neighbors) {
                        if (isSafe(i, j)) {
                            safeTiles[i][j] = true;
                            return game->revealTile(i, j);
                        }
                    }
                /*Flag remaining confirmed mines*/
                } else if (unrevealedCount == tileNumber - flaggedCount) {
                    for (auto& [i, j] : neighbors) {
                        if (game->charBoard[i][j] == '*') {
                            game->charBoard[i][j] = 'F';
                            moveAgain = 1;    //Need to loop again at the end if only placed flags
                        }
                    }
                }
            }
        }
    }
    if(moveAgain == 1){ return makeMove(); }
    

    /* If no logical move found, make a random move */
    return pickRandomTile();
}



bool MinesweeperAI::pickRandomTile(){
    std::vector<std::pair<size_t, size_t>> unrevealedTiles;
    for (size_t i = 0; i < game->getX(); ++i) {
        for (size_t j = 0; j < game->getY(); ++j) {
            if (game->charBoard[i][j] == '*') {
                unrevealedTiles.emplace_back(i, j);
            }
        }
    }
    if (!unrevealedTiles.empty()) {
        auto [randX, randY] = unrevealedTiles[rand() % unrevealedTiles.size()];
        return game->revealTile(randX, randY);
    }
    return false;
}

void pause(){ 
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int MinesweeperAI::playWithAI() {
    game->printBoard();
    pause();

    while (makeMove() == true) {
        if (game->revealedEmptyTiles == (game->getX() * game->getY()) - game->getMines()) {
            game->winGame(0);
            //std::cout << "AI won the game!\n";
            return 0;
        }
        game->printBoard();
        pause();
    }
    game->loseGame(0);
    //std::cout << "AI lost the game.\n";
    return 1;
}