#include "MinesweeperBoard.hpp"
#include "MSBoardTextView.hpp"

class MSTextController
{
    public:
        MSTextController(MinesweeperBoard& m, MSBoardTextView& v);
        void play() const;

    private:
        MinesweeperBoard& mb;
        MSBoardTextView& view;
};
