
#ifndef MDN_CARD_HPP
#define MDN_CARD_HPP

#include <vector>

class Card {
public:
    static constexpr char
        rowsNum{4},
        colsNum{3},
        cellsNum{rowsNum * colsNum};

    Card(unsigned char dot, unsigned char ring);

    unsigned char
    get_dot() const;

    unsigned char
    get_ring() const;

    void
    rotate();

    void
    flip_short();

    void
    flip_long();

    static std::vector<Card>
    import_cards(const std::string &file_name);

private:
    unsigned char dot_, ring_;
};

#endif // MDN_CARD_HPP