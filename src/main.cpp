#include "minesweeper.h"
#include "minesweeper.cpp"
#include "AI.h"
#include "AI.cpp"
#include <iostream>
#include <string>
#include <vector>

int main() {
    size_t _x, _y, _mines;
    std::cout << "********* Enter board dimensions and # of mines: (#rows #columns #mines) *********" << std::endl;
    std::cin >> _y >> _x >> _mines;
    if (!std::cin.good()) {
        std::cin.clear();  // Clear error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // clear input
        std::cout << "Invalid input: Make sure entry is within bounds." << std::endl;
        return 1;
    }

    std::string choice;
    std::cout << "Play solo or with AI? (solo/ai)" << std::endl;
    std::cin >> choice;

    Minesweeper game(_x, _y, _mines);

    if (choice == "solo") {
        game.playGame();
    } else if (choice == "ai") {
        std::cin.ignore(); // To clear the newline character from the input buffer
        MinesweeperAI ai(&game);
        ai.playWithAI();
    } else {
        std::cout << "Invalid choice. Exiting." << std::endl;
        return 1;
    }
    return 0;
}