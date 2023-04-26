#pragma once
#include <vector>
#include "MinesweeperBoard.hpp"


class MSBoardTextView
{
public:
    MSBoardTextView(MinesweeperBoard& m);
    void display();

private:
    MinesweeperBoard& mb;
};

