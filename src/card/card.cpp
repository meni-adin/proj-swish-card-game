
#include "mdn/card.hpp"

mdn::Card::Card(unsigned char dot, unsigned char ring) {
    if (cellsNum <= dot)
        throw std::invalid_argument("Dot argument is too big");
    if (cellsNum <= ring)
        throw std::invalid_argument("Ring argument is too big");
    if (dot == ring)
        throw std::invalid_argument("Dot argument and ring argument can't be equal");
    dot_ = dot, ring_ = ring;
}

unsigned char
mdn::Card::get_dot() const {
    return dot_;
}

unsigned char
mdn::Card::get_ring() const {
    return ring_;
}

unsigned char
mdn::Card::rotate_element(unsigned char elementPosition) {
    return cellsNum - 1u - elementPosition;
}

void
mdn::Card::rotate() {
    dot_ = rotate_element(dot_);
    ring_ = rotate_element(ring_);
}

unsigned char
mdn::Card::flip_element_horizontally(unsigned char elementPosition) {
    int currentRow, currentCol, newCol;

    currentRow = elementPosition / colsNum;
    currentCol = elementPosition % colsNum;
    newCol = colsNum - 1 - currentCol;

    return static_cast<unsigned char>((currentRow * colsNum) + newCol);
}

void
mdn::Card::flip_horizontally() {
    dot_ = flip_element_horizontally(dot_);
    ring_ = flip_element_horizontally(ring_);
}

unsigned char
mdn::Card::flip_element_vertically(unsigned char elementPosition) {
    int currentRow, currentCol, newRow;

    currentRow = elementPosition / colsNum;
    currentCol = elementPosition % colsNum;
    newRow = rowsNum - 1 - currentRow;

    return static_cast<unsigned char>((newRow * colsNum) + currentCol);
}

void
mdn::Card::flip_vertically() {
    dot_ = flip_element_vertically(dot_);
    ring_ = flip_element_vertically(ring_);
}
