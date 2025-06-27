
#include "mdn/Card.hpp"

namespace mdn {
    Card::Card(Card::index_t dot, Card::index_t ring) {
        if (cellsNum <= dot) {
            throw std::invalid_argument("Dot argument is too big");
        }
        if (cellsNum <= ring) {
            throw std::invalid_argument("Ring argument is too big");
        }
        if (dot == ring) {
            throw std::invalid_argument("Dot argument and ring argument can't be equal");
        }
        dot_ = dot, ring_ = ring;
    }

    bool
    Card::operator==(const Card &rhs) const {
        return (this->dot_ == rhs.dot_) && (this->ring_ == rhs.ring_);
    }

    Card::index_t
    Card::get_dot() const {
        return dot_;
    }

    Card::index_t
    Card::get_ring() const {
        return ring_;
    }

    Card::index_t
    Card::rotate_element(Card::index_t elementPosition) {
        return cellsNum - 1u - elementPosition;
    }

    void
    Card::rotate() {
        dot_  = rotate_element(dot_);
        ring_ = rotate_element(ring_);
    }

    Card::index_t
    Card::flip_element_horizontally(Card::index_t elementPosition) {
        int currentRow, currentCol, newCol;

        currentRow = elementPosition / colsNum;
        currentCol = elementPosition % colsNum;
        newCol     = colsNum - 1 - currentCol;

        return static_cast<Card::index_t>((currentRow * colsNum) + newCol);
    }

    void
    Card::flip_horizontally() {
        dot_  = flip_element_horizontally(dot_);
        ring_ = flip_element_horizontally(ring_);
    }

    Card::index_t
    Card::flip_element_vertically(Card::index_t elementPosition) {
        int currentRow, currentCol, newRow;

        currentRow = elementPosition / colsNum;
        currentCol = elementPosition % colsNum;
        newRow     = rowsNum - 1 - currentRow;

        return static_cast<Card::index_t>((newRow * colsNum) + currentCol);
    }

    void
    Card::flip_vertically() {
        dot_  = flip_element_vertically(dot_);
        ring_ = flip_element_vertically(ring_);
    }

    Card
    Card::normalize(const Card &card) {
        (void)card;
        throw std::logic_error("Function not implemented yet");
    }
}  // namespace mdn
