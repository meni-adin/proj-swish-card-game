
#include "mdn/Board.hpp"

namespace mdn {
    Board::Board(Board::index_t rowsNum, Board::index_t colsNum) :
        rowsNum{rowsNum}, colsNum{colsNum} {
        rows.resize(rowsNum);
        for (auto &row : rows) {
            row.resize(colsNum);
        }
    }

    Board::index_t
    Board::get_rows_num() const {
        return rowsNum;
    }

    Board::index_t
    Board::get_cols_num() const {
        return colsNum;
    }

    const mdn::Card &
    Board::peek_at_card(const CardCoordinates &cardCoordinates) const {
        validateCardCoordinates(cardCoordinates);
        if (rows[cardCoordinates.row][cardCoordinates.col] == nullptr) {
            throw std::invalid_argument("No card at requested coordinates");
        }
        return *rows[cardCoordinates.row][cardCoordinates.col];
    }

    void
    Board::set_card_at(const CardCoordinates &cardCoordinates, std::unique_ptr<Card> cardPtr) {
        rows[cardCoordinates.row][cardCoordinates.col] = std::move(cardPtr);
    }

    void
    Board::validateCardCoordinates(const CardCoordinates &cardCoordinates) const {
        if (cardCoordinates.row >= rowsNum) {
            throw std::invalid_argument("Row coordinate is outside the board");
        }
        if (cardCoordinates.col >= colsNum) {
            throw std::invalid_argument("Column coordinate is outside the board");
        }
    }
}  // namespace mdn
