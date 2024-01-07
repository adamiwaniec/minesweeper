#include "minesweeper.h"

/************** Class functions **************/

Minesweeper::Minesweeper(const size_t& _x, const size_t& _y, const size_t& _mines)
 : revealedEmptyTiles(0), x(_x), y(_y), mines(_mines){
    //revealedEmptyTiles = 0;

    if ((mines > x * y) || (x < 1) || (y < 1)){
        std::cout << "Error: Make sure entry is within bounds." << std::endl;
        return;
    }

    /* Initialization using vectors */
    revealed.assign(x, std::vector<bool>(y, false));
    mineBoard.assign(x, std::vector<bool>(y, EMPTY));
    charBoard.assign(x, std::vector<char>(y, '*'));

    /* Initialization using 2D arrays
    revealed = new bool* [x];
    mineBoard = new bool* [x];
    charBoard = new char* [x];

    for (unsigned i = 0; i < x; i++){
        revealed[i] = new bool[y];
        mineBoard[i] = new bool[y];
        charBoard[i] = new char[y];

        for (unsigned j = 0; j < y; j++){
            revealed[i][j] = false;
            mineBoard[i][j] = EMPTY;
            charBoard[i][j] = '*';
        }
    }
    */
    
    /* Place mines randomly on mineBoard by choosing random tiles */   //***Can possibly shorten using for loop
    srand((size_t) time(0));
    size_t i = 0;
    while (i < mines){
        size_t randX = rand() % x;
        size_t randY = rand() % y;
        if (mineBoard[randX][randY] == EMPTY){
            mineBoard[randX][randY] = MINE;
            i++; 
        }
    }
}

Minesweeper::~Minesweeper()
{   
    /* Only needed if using arrays
    for (unsigned i = 0; i < x; i++){
        delete[] revealed[i];
        delete[] mineBoard[i];
        delete[] charBoard[i];
    }
    delete[] revealed;
    delete[] mineBoard;
    delete[] charBoard;
    */
}

bool Minesweeper::revealTile(const size_t & _x, const size_t & _y) 
{
    /* Return true if empty or invalid tile, false if mine */

    if (!validTile(_x, _y) || revealed[_x][_y] == true) return true; //Base case
    revealed[_x][_y] = true;
    revealedEmptyTiles++;
    if (mineBoard[_x][_y] == MINE){
        charBoard[_x][_y] = 'X';
        return false;
    }
    
    charBoard[_x][_y] =  '0' + static_cast<char>(countMinesAroundTile(_x, _y));

    /* Reveal adjacent tiles with 0 mines using recursion */
    if (charBoard[_x][_y] == '0'){
        revealTile(_x + 1, _y);     // RIGHT
        revealTile(_x + 1, _y + 1); // RIGHT UP
        revealTile(_x + 1, _y - 1); // RIGHT DOWN
        revealTile(_x, _y + 1);     // UP
        revealTile(_x, _y - 1);     // DOWN
        revealTile(_x - 1, _y);     // LEFT
        revealTile(_x - 1, _y + 1); // LEFT UP
        revealTile(_x - 1, _y - 1); // LEFT DOWN
    }
    return true;
}

size_t Minesweeper::countMinesAroundTile(const size_t & _x, const size_t & _y)
{
    /* //Check how many surrounding tiles are mines */
    size_t count = 0; //mine count
    if (validTile(_x + 1, _y) && (mineBoard[_x + 1][_y] == MINE)) count++;          //RIGHT
    if (validTile(_x + 1, _y - 1) && (mineBoard[_x + 1][_y - 1] == MINE)) count++;  //RIGHT DOWN
    if (validTile(_x + 1, _y + 1) && (mineBoard[_x + 1][_y + 1] == MINE)) count++;  //RIGHT UP
    if (validTile(_x, _y - 1) && (mineBoard[_x][_y - 1] == MINE)) count++;          //MIDDLE DOWN
    if (validTile(_x, _y + 1) && (mineBoard[_x][_y + 1] == MINE)) count++;          //MIDDLE UP
    if (validTile(_x - 1, _y) && (mineBoard[_x - 1][_y] == MINE)) count++;          //LEFT
    if (validTile(_x - 1, _y - 1) && (mineBoard[_x - 1][_y - 1] == MINE)) count++;  //LEFT DOWN
    if (validTile(_x - 1, _y + 1) && (mineBoard[_x - 1][_y + 1] == MINE)) count++;  //LEFT UP
    return count;
}

bool Minesweeper::validTile(const size_t & _x, const size_t & _y)
{
    return !((_x >= x) || (_y >= y) || (_x < 0) || (_y < 0));
}

int Minesweeper::playGame() //Return 0 if win, 1 if lose
{   
    auto start = std::chrono::high_resolution_clock::now(); //Record starting time
    while(1){
        printBoard();
        unsigned _x, _y;
        bool boolean;
        std::cout << "Reveal or flag tile: (#)row (#)col (1 = reveal, 0 = flag)" << std::endl;
        std::cin >> _x >> _y >> boolean;                

        if (!std::cin.good() || (validTile(--_x, --_y) == false)){  //Check if valid input, decrement x and y due to vector arrays being 0-indexed
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input: Make sure entry is within bounds." << std::endl;
            continue;
        }
        
        if (boolean == 0){  //FLAG TILE
            if (revealed[_x][_y] == false)
                charBoard[_x][_y] = 'F';
            continue;
        }
        else{               //REVEAL TILE
            if (revealed[_x][_y] == false){ 
                if (revealTile(_x, _y) == false){ // This reveals tile and returns false if mine
                    printBoard();
                    auto stop = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
                    loseGame(((float) duration.count())/ (float) 1000);  //Return duration of time in seconds
                    return 1;
                }
            }
        }

        if (revealedEmptyTiles == (x * y) - mines){ //All mines are found, game is over
            printBoard();
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            winGame(((float) duration.count())/ (float) 1000);
            return 0;
        }
    }
    return 1;
}

void Minesweeper::winGame(double t)
{   
    std::cout << std::endl << "********* CONGRATS! You won in " << t  << " seconds. *********" << std::endl << std::endl;
}

void Minesweeper::loseGame(double t)
{
    std::cout << std::endl << "********* You lost in " << t << " seconds. *********" << std::endl << std::endl;
}

void Minesweeper::printBoard()
{
    //Add labels for the columns (integers)
    std::cout << "    ";
    for (unsigned i = 0; i < y; i++) {
        std::cout << std::setw(2) << i + 1 << " ";
    }
    std::cout << std::endl;

    // Add a line underneath the top labels
    std::cout << "   ";
    for (unsigned i = 0; i < y; i++) {
        std::cout << "---";
    }
    std::cout << std::endl;

    // Print row/col labels and charBoard
    for (unsigned i = 0; i < x; i++) {
        std::cout << std::setw(2) << i + 1 << " |";
        for (unsigned j = 0; j < y; j++) {
            std::cout << " " << charBoard[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Add a line above the bottom labels
    std::cout << "   ";
    for (unsigned i = 0; i < y; i++) {
        std::cout << "---";
    }

    std::cout << std::endl;

    //Add labels on bottom (same as top ones)
    std::cout << "    ";
    for (unsigned i = 0; i < y; i++) {
        std::cout << std::setw(2) << i + 1 << " ";
    }
    std::cout << std::endl;

}

/****** Functions used for testing ******/

void Minesweeper::setX(unsigned n) { x = n; }
unsigned Minesweeper::getX() { return x; }

void Minesweeper::setY(unsigned n) { y = n; }
unsigned Minesweeper::getY() { return y; }

void Minesweeper::setMines(unsigned n) { mines = n; }
unsigned Minesweeper::getMines() { return mines; }

void Minesweeper::printMineBoard()
{
    // column labels
    std::cout << "   ";
    for (unsigned j = 0; j < y; j++) {
        std::cout << " " << j + 1 << " ";
    }
    std::cout << std::endl;

    //char matrix
    for (unsigned i = 0; i < x; i++) {
        std::cout << i + 1 << " |";
        for (unsigned j = 0; j < y; j++) {
            if (mineBoard[i][j] == MINE)
                std::cout << " " << 'X' << " ";
            else 
                std::cout << " " << '0' << " ";
        }
        std::cout << std::endl;
    }
}
