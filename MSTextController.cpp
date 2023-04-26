#include "MinesweeperBoard.hpp"
#include "MSTextController.hpp"
#include "MSBoardTextView.hpp"
#include <iostream>

MSTextController::MSTextController(MinesweeperBoard& m, MSBoardTextView& v):mb(m), view(v)
{}

void MSTextController::play() const
{
    view.display();
    while (mb.getGameState() == GameState::RUNNING)
    {
        char o;
        int r,c;
        std::cout << "\nEnter, reveal or flag and row, column separated by a space. \nExample: r 0 0 (reveal field 0, 0)";
        std::cin >> o;
        std::cin >> r;
        std::cin >> c;
        if (o=='f' || o=='F')
            mb.toggleFlag(r,c);
        else if (o=='r' || o== 'R')
            mb.revealField(r,c);
        view.display();
    }
    if (mb.getGameState() == GameState::FINISHED_LOSS)
        std::cout << "You lose.\n";
    else if (mb.getGameState() == GameState::FINISHED_WIN)
        std::cout << "Congratulations! You won.\n";
}
