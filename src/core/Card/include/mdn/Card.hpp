
#ifndef MDN_CARD_HPP
#define MDN_CARD_HPP

#include <stdexcept>
#include <string>
#include <vector>

namespace mdn {
    class Card {
    public:
        using index_t = uint8_t;

        static constexpr index_t
            rowsNum{4},
            colsNum{3},
            cellsNum{rowsNum * colsNum};

        Card(index_t dot, index_t ring);

        bool
        operator==(const Card &rhs) const;

        index_t
        get_dot() const;

        index_t
        get_ring() const;

        void
        rotate();

        void
        flip_horizontally();

        void
        flip_vertically();

        Card
        normalize(const Card &card);

        static std::vector<Card>
        import_cards(const std::string &file_name);

    private:
        index_t dot_, ring_;

        index_t
        rotate_element(index_t element);

        index_t
        flip_element_horizontally(index_t element);

        index_t
        flip_element_vertically(index_t element);
    };
}  // namespace mdn

#endif  // MDN_CARD_HPP
