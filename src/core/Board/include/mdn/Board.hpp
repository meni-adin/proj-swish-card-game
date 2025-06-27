
#ifndef MDN_BOARD_HPP
#define MDN_BOARD_HPP

#include <stdexcept>
#include <string>
#include <vector>

#include "mdn/Card.hpp"

namespace mdn {

    class Board {
    public:
        using index_t = uint8_t;

        struct CardCoordinates {
            index_t row;
            index_t col;
        };

        Board(index_t rowsNum, index_t colsNum);

        index_t
        get_rows_num() const;

        index_t
        get_cols_num() const;

        const mdn::Card &
        peek_at_card(const CardCoordinates &cardCoordinates) const;

        void
        set_card_at(const CardCoordinates &cardCoordinates, std::unique_ptr<Card> cardPtr);

    private:
        const index_t                                        rowsNum, colsNum;
        std::vector<std::vector<std::unique_ptr<mdn::Card>>> rows;

        void
        validateCardCoordinates(const CardCoordinates &cardCoordinates) const;
    };
}  // namespace mdn

#endif  // MDN_BOARD_HPP
