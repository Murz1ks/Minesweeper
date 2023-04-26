#include <iostream>
#include "MSBoardTextView.hpp"
#include "MinesweeperBoard.hpp"

MSBoardTextView::MSBoardTextView(MinesweeperBoard& m):mb(m)
{}

void MSBoardTextView::display()
{
    std::cout << "\n    ";
    for (int k = 0; k < mb.getBoardWidth(); k++)
        std::cout << k << "    ";
    std::cout << std::endl;
    for (int i = 0; i < mb.getBoardHeight(); i++)
    {
        std::cout << i << " ";
        for (int j = 0; j < mb.getBoardWidth(); j++)
        {
            std::cout << "[ " << mb.getFieldInfo(i,j) << " ]";
        }
        std::cout << std::endl;
    }
}

