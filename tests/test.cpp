#include <catch2/catch_test_macros.hpp>
#include "minesweeper.h"

TEST_CASE("Test printBoard() with given charBoard", "[1]") //GOOD
{
    Minesweeper test = Minesweeper(5, 5, 5);
    char customCharBoard[5][5] =   {{'1', '2', '3', '4', '5'},
                                    {'6', '7', '8', '9', '0'},
                                    {'A', 'B', 'C', 'D', 'E'},
                                    {'F', 'G', 'H', 'I', 'J'},
                                    {'K', 'L', 'M', 'N', 'O'}};
    for (unsigned i = 0; i < test.getX(); i++){
        for (unsigned j = 0; j < test.getY(); j++){ 
            test.charBoard[i][j] = customCharBoard[i][j];
        }
    }
    test.printBoard();
}

TEST_CASE("Test countMinesAroundTile()", "[2]")  //GOOD
{ 
    Minesweeper test(3, 3, 1);
    if (test.revealTile(1, 1) == false) //Middle tile is mine, so 0 mines surrounding it
        REQUIRE(test.countMinesAroundTile(1, 1) == 0);

    else                                //Middle tile is empty, so 1 mine surrounding it somewhere
        REQUIRE(test.countMinesAroundTile(1, 1) == 1);

    Minesweeper newTest = Minesweeper(3, 3, 5);

    REQUIRE(newTest.countMinesAroundTile(1, 1) >= 4);
}

TEST_CASE("Test revealTile(), charBoard initialization, and unsigned variables initialization", "[3]") //DONE
{
    Minesweeper test(10, 14, 140);
    for (unsigned i = 0; i < test.getX(); i++){
        for (unsigned j = 0; j < test.getY(); j++){
            REQUIRE(test.charBoard[i][j] == '*');
            REQUIRE(test.revealTile(i, j) == false);
            REQUIRE(test.charBoard[i][j] == 'X');
        }
        REQUIRE(test.charBoard[i].size() == 14);    //Size of each element in the outside vec (columns)
    }
    REQUIRE(test.getX() == 10);
    REQUIRE(test.getY() == 14);
    REQUIRE(test.getMines() == 140);
    REQUIRE(test.charBoard.size() == 10);           //Size of each element in the inside vecs (rows)
}

TEST_CASE("Test validTile()", "[4]")   //GOOD
{
    Minesweeper test = Minesweeper(5, 5, 5);

    SECTION("Valid tiles should return true") {
        REQUIRE(test.validTile(0, 0) == true);
        REQUIRE(test.validTile(3, 3) == true);
        REQUIRE(test.validTile(4, 2) == true);
    }

    SECTION("Invalid tiles should return false") {
        REQUIRE(test.validTile(5, 5) == false);
        REQUIRE(test.validTile(6, 3) == false);
        REQUIRE(test.validTile(2, 6) == false);
        REQUIRE(test.validTile(8, 8) == false);
    }
}

TEST_CASE("Test playGame() and loseGame() function with automatic random input", "[5]") {  //GOOD
    Minesweeper test = Minesweeper(3, 3, 5);

    // Mock user input for the test (not trying to win)
    std::stringstream inputTile;
    inputTile << "1\n" << "1\n" << "0\n";   // 1 1 0
    inputTile << "1\n" << "2\n" << "0\n";   // 1 2 0
    inputTile << "2\n" << "2\n" << "0\n";   // 2 2 0
    inputTile << "1\n" << "1\n" << "1\n";   // 1 1 1
    inputTile << "1\n" << "2\n" << "1\n";   // 1 2 1
    inputTile << "1\n" << "3\n" << "1\n";   // 1 3 1
    inputTile << "2\n" << "1\n" << "1\n";   // 2 1 1
    inputTile << "2\n" << "2\n" << "1\n";   // 2 2 1
    inputTile << "3\n" << "1\n" << "1\n";   // 3 1 1
    //First 3 sets of three are flags, next 5 sets are reveals

    /* Input above numbers in terminal when std::cin is called */
    std::streambuf* orig_cin = std::cin.rdbuf();
    std::cin.rdbuf(inputTile.rdbuf());

    REQUIRE(test.playGame() == 1);  // Will effectively lose every time by picking random tiles
    std::cin.rdbuf(orig_cin);
}