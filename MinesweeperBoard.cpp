#include "MinesweeperBoard.hpp"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>



using namespace std;

MinesweeperBoard::MinesweeperBoard(int w, int h, GameMode m)
{
    // Initialize board dimensions
    mode = m;
    state = GameState::RUNNING;
    width = w;
    height = h;
    fieldCount = w * h;
    revealedFields = 0;

    // Changes game mode
char gmode;
    std::cout << "\n\nChoose difficulty: Easy - e, Normal - n or Hard - h: ";
    std::cin >> gmode;
    std::cout << "\n";
    if (gmode == 'e' || gmode == 'E')
    {
        mineCount = round(fieldCount * 0.1);
        mode = GameMode::EASY;
    }
    else if (gmode == 'n' || gmode == 'N')
    {
        mineCount = round(fieldCount * 0.2);
        mode = GameMode::NORMAL;
    }
    else if (gmode == 'h' || gmode == 'H')
    {
        mineCount = round(fieldCount * 0.3);
        mode = GameMode::HARD;
    }

    // Fill vector with default fields
    for (int i = 0; i < height; i++)
    {
        vector<Field> temp;
        for (int j = 0; j < width; j++)
        {
            temp.push_back({false,false, false});
        }
        board.push_back(temp);
    }

    // Fill board with debug mode mines
    if (mode == GameMode::DEBUG)
    {
        mineCount = 0;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (i == 0)
                {
                    board[i][j].hasMine = true;
                    mineCount++;
                }
                if (i == j && board[i][j].hasMine == false)
                {
                    board[i][j].hasMine = true;
                    mineCount++;
                }
                if (j == 0 && (i%2) == 0 && board[i][j].hasMine == false)
                {
                    board[i][j].hasMine = true;
                    mineCount++;
                }
            }
        }

    }

    else {
        // Loop for filling board with mines
        int x = mineCount;
        srand(time(NULL));
        while (x > 0) {
            int i = rand() % height;
            int j = rand() % width;
            //cout << "r fields are " << i << j << endl;
            if (board[i][j].hasMine == false) {
                board[i][j].hasMine = true;
                x--;
            }
        }
    }
}

// Function to display all field
void MinesweeperBoard::debug_display() const
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (board[i][j].hasMine == true)
                cout << "[M";
            else
                cout << "[.";
            if (board[i][j].isRevealed == true)
                cout << "o";
            else
                cout << ".";
            if (board[i][j].hasFlag == true)
                cout << "f]";
            else
                cout << ".]";
        }
        cout << endl;
    }
}

// Function to count mines
int MinesweeperBoard::countMines(int row, int col) const
{
    int mines = 0;
    if ((row < 0 || row >= height) || (col < 0 || col >= width))
        return -1;
    else if (board[row][col].isRevealed == false)
        return -1;
    if (row - 1 >= 0 && board[row - 1][col].hasMine == true)
        mines++;
    if (col - 1 >= 0 && board[row][col - 1].hasMine == true)
        mines++;
    if (row + 1 < height && board[row + 1][col].hasMine == true)
        mines++;
    if (col + 1 < width && board[row][col + 1].hasMine == true)
        mines++;
    if (row - 1 >= 0 && col - 1 >= 0 && board[row - 1][col - 1].hasMine == true)
        mines++;
    if (row - 1 >= 0 && col + 1 < width && board[row - 1][col + 1].hasMine == true)
        mines++;
    if (row + 1 < height && col - 1 >= 0 && board[row + 1][col - 1].hasMine == true)
        mines++;
    if (row + 1 < height && col + 1 < width && board[row + 1][col + 1].hasMine == true)
        mines++;
    return mines;
}

// Checking for flag
bool MinesweeperBoard::hasFlag(int row, int col) const
{
    if ((row < 0 || row >= height) || (col < 0 || col >= width))
        return false;
    else if (board[row][col].isRevealed == true)
        return false;
    else if (board[row][col].hasFlag == false)
        return false;
    else if (board[row][col].hasFlag == true)
        return true;
    return false;
}


// Toggling flag
void MinesweeperBoard::toggleFlag(int row, int col)
{
    if (((row < 0 || row >= height) || (col < 0 || col >= width)) || board[row][col].isRevealed == true || state != GameState::RUNNING)
    {}
    else if (board[row][col].hasFlag == false)
        board[row][col].hasFlag = true;
    else if (board[row][col].hasFlag == true)
        board[row][col].hasFlag = false;
}

// Reveal field
void MinesweeperBoard::revealField(int row, int col)
{
    if (((row < 0 || row >= height) || (col < 0 || col >= width)) || board[row][col].isRevealed == true || board[row][col].hasFlag == true || state != GameState::RUNNING)
    {}
    else if (board[row][col].isRevealed == false && board[row][col].hasMine == false)
    {
        board[row][col].isRevealed = true;
        revealedFields++;
        if (revealedFields == fieldCount - mineCount)
            state = GameState::FINISHED_WIN;
        if (getFieldInfo(row,col) == ' ')
            revealNeighbored(row,col);
    }

    else if (board[row][col].isRevealed == false && board[row][col].hasMine == true)
    {
        board[row][col].isRevealed = true;
        state = GameState::FINISHED_LOSS;
    }
}

// Revealing neighbor fields
void MinesweeperBoard::revealNeighbored(int row, int col)
{
    if ((row < 0 || row >= height) || (col < 0 || col >= width))
    {}
    else
    {
        if (row - 1 >= 0)
            revealField(row-1,col);
        if (col - 1 >= 0)
            revealField(row,col-1);
        if (row + 1 < height)
            revealField(row+1,col);
        if (col + 1 < width)
            revealField(row,col+1);
        if (row - 1 >= 0 && col - 1 >= 0)
            revealField(row-1,col-1);
        if (row - 1 >= 0 && col + 1 < width)
            revealField(row-1,col+1);
        if (row + 1 < height && col - 1 >= 0)
            revealField(row+1,col-1);
        if (row + 1 < height && col + 1 < width)
            revealField(row+1,col+1);
    }
}

// Info about field
char MinesweeperBoard::getFieldInfo(int row, int col) const
{
    if ((row < 0 || row >= height) || (col < 0 || col >= width))
        return '#';
    else if (board[row][col].isRevealed == false && board[row][col].hasFlag == true)
        return 'F';
    else if (board[row][col].isRevealed == false && board[row][col].hasFlag == false)
        return '_';
    else if (board[row][col].isRevealed == true && board[row][col].hasMine == true)
        return 'x';
    else if (board[row][col].isRevealed == true && countMines(row,col) == 0)
        return ' ';
    else if (board[row][col].isRevealed == true && countMines(row,col) != 0)
    {
        std::string mc = std::to_string(countMines(row,col));
        return mc[0];
    }
    else return 'e';
}


bool MinesweeperBoard::isRevealed(int row, int col) const
{
    if (board[row][col].isRevealed == true)
        return true;
    else
        return false;
}

GameState MinesweeperBoard::getGameState() const
{
    return state;
}

int MinesweeperBoard::getBoardWidth() const
{
    return width;
}

int MinesweeperBoard::getBoardHeight() const
{
    return height;
}

int MinesweeperBoard::getMineCount() const
{
    return mineCount;
}
