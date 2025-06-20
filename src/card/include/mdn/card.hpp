
#ifndef MDN_CARD_HPP
#define MDN_CARD_HPP

#include <stdexcept>
#include <string>
#include <vector>

namespace mdn {
    class Card {
    public:
        static constexpr uint8_t
            rowsNum{4},
            colsNum{3},
            cellsNum{rowsNum * colsNum};

        Card(uint8_t dot, uint8_t ring);

        Card(const Card &cardToCopy);

        bool
        operator==(const Card &rhs) const;

        uint8_t
        get_dot() const;

        uint8_t
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
        uint8_t dot_, ring_;

        uint8_t
        rotate_element(uint8_t element);

        uint8_t
        flip_element_horizontally(uint8_t element);

        uint8_t
        flip_element_vertically(uint8_t element);
    };
}  // namespace mdn

#endif  // MDN_CARD_HPP
