#include "minesweeper.h"

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
  Minesweeper test(_x, _y, _mines);
  test.playGame();
  return 0;
}
