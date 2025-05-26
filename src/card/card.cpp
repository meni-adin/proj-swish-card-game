
#include "mdn/card.hpp"

Card::Card(unsigned char dot, unsigned char ring) {
    if (cellsNum <= dot)
        throw std::invalid_argument("Dot argument is too big");
    if (cellsNum <= ring)
        throw std::invalid_argument("Ring argument is too big");
    if (dot == ring)
        throw std::invalid_argument("Dot argument and ring argument can't be equal");
    dot_ = dot, ring_ = ring;
}

unsigned char
Card::get_dot() const {
    return dot_;
}

unsigned char
Card::get_ring() const {
    return ring_;
}

void
Card::rotate() {
    static char lut[] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    dot_ = lut[dot_];
    ring_ = lut[ring_];
}

void
Card::flip_short() {
    static char lut[] = {9, 10, 11, 6, 7, 8, 3, 4, 5, 0, 1, 2};
    dot_ = lut[dot_];
    ring_ = lut[ring_];
}

void
Card::flip_long() {
    static char lut[] = {2, 1, 0, 5, 4, 3, 8, 7, 6, 11, 10, 9};
    dot_ = lut[dot_];
    ring_ = lut[ring_];
}
