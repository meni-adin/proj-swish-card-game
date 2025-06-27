#define _XOPEN_SOURCE_EXTENDED 1
#include "mdn/GraphicsCLI.hpp"

#include <ncurses.h>

namespace mdn {
    GraphicsCLI::GraphicsCLI() {
        board_win = newwin(boardHeight, boardWidth, (LINES - boardHeight) / 2, (COLS - boardWidth) / 2);
        keypad(board_win, TRUE);
    }

    void
    GraphicsCLI::initBoard() {
        #error print board
    }

}  // namespace mdn
