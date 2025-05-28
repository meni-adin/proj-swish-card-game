
#ifndef MDN_CARD_HPP
#define MDN_CARD_HPP

#include <vector>

namespace mdn{
    class Card {
    public:
        static constexpr unsigned char
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
        flip_horizontally();

        void
        flip_vertically();

        static std::vector<Card>
        import_cards(const std::string &file_name);

    private:
        unsigned char dot_, ring_;

        unsigned char
        rotate_element(unsigned char element);

        unsigned char
        flip_element_horizontally(unsigned char element);

        unsigned char
        flip_element_vertically(unsigned char element);
    };
}

#endif // MDN_CARD_HPP