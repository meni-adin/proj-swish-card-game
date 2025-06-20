
#ifndef MDN_BOARD_HPP
#define MDN_BOARD_HPP

#include <stdexcept>
#include <string>
#include <vector>

#include "mdn/card.hpp"

namespace mdn {
    struct CardCoordinates {
        uint8_t row;
        uint8_t col;
    };

    class Board {
    public:
        Board(uint8_t rowsNum, uint8_t colsNum);

        uint8_t
        get_rows_num() const;

        uint8_t
        get_cols_num() const;

        const mdn::Card &
        peek_at_card(const CardCoordinates &cardCoordinates) const;

        void
        set_card_at(const CardCoordinates &cardCoordinates, std::unique_ptr<Card> cardPtr);

    private:
        const uint8_t                                        rowsNum, colsNum;
        std::vector<std::vector<std::unique_ptr<mdn::Card>>> rows;

        void
        validateCardCoordinates(const CardCoordinates &cardCoordinates) const ;
    };
}  // namespace mdn

#endif  // MDN_BOARD_HPP
