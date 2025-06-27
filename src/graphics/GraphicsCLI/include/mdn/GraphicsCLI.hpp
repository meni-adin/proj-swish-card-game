
#ifndef MDN_GRAPHICS_CLI_HPP
#define MDN_GRAPHICS_CLI_HPP

#include "mdn/IGraphics.hpp"

namespace mdn {
    class GraphicsCLI : public mdn::IGraphics {
    public:
        GraphicsCLI();

    private:
        static constexpr int
            boardHeight = 24,
            boardWidth = 50;
        WINDOW *board_win;

        void
        initBoard();
    };
}  // namespace mdn

#endif  // MDN_GRAPHICS_CLI_HPP
