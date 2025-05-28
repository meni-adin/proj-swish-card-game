#include <filesystem>
#include <tuple>
#include <gmock/gmock.h>

#include "mdn/card.hpp"
#include "mdn/test_utils.hpp"
#include "nlohmann/json.hpp"

using namespace testing;

struct CardInitializer {
    unsigned char dot, ring;
};

const nlohmann::json &get_json() {
    static nlohmann::json jsonContent;
    jsonContent = mdn::TestUtils::load_json_file_Content(MDN_CARD_TEST_TESTS_DATA_FILE_PATH);
    return jsonContent;
}

namespace {
    class CardCreation : public ::testing::TestWithParam<CardInitializer> {};

    TEST_P(CardCreation, createCard) {
        const auto& original = GetParam();
        mdn::Card(original.dot, original.ring);
    }

    std::vector<CardInitializer>
    load_card_creation_tests_data() {
        std::vector<CardInitializer> testCases;
        const auto jsonContent = get_json();

        for (const auto &item : jsonContent["positive"]) {
            CardInitializer original{item["original"]["dot"].get<unsigned char>(), item["original"]["ring"].get<unsigned char>()};
            testCases.emplace_back(original);
        }

        return testCases;
    }

    INSTANTIATE_TEST_SUITE_P(
        CardCreationTestSuit,
        CardCreation,
        ValuesIn(load_card_creation_tests_data())
    );
}

namespace {
    class CardRotation : public ::testing::TestWithParam<std::tuple<CardInitializer, CardInitializer>> {};

    TEST_P(CardRotation, createCard) {
        const auto& [original, rotated] = GetParam();
        mdn::Card card{original.dot, original.ring};
        card.rotate();
        ASSERT_EQ(card.get_dot(), rotated.dot);
        ASSERT_EQ(card.get_ring(), rotated.ring);

        static unsigned char lut[] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        ASSERT_EQ(card.get_dot(), lut[original.dot]);
        ASSERT_EQ(card.get_ring(), lut[original.ring]);
    }

    std::vector<std::tuple<CardInitializer, CardInitializer>>
    load_card_rotation_tests_data() {
        std::vector<std::tuple<CardInitializer, CardInitializer>> testCases;
        const auto jsonContent = get_json();

        for (const auto &item : jsonContent["positive"]) {
            CardInitializer original{item["original"]["dot"].get<unsigned char>(), item["original"]["ring"].get<unsigned char>()};
            CardInitializer rotated{item["rotated"]["dot"].get<unsigned char>(), item["rotated"]["ring"].get<unsigned char>()};
            testCases.emplace_back(original, rotated);
        }

        return testCases;
    }

    INSTANTIATE_TEST_SUITE_P(
        CardRotationTestSuit,
        CardRotation,
        ValuesIn(load_card_rotation_tests_data())
    );
}

namespace {
    class CardFlippingHorizontally : public ::testing::TestWithParam<std::tuple<CardInitializer, CardInitializer>> {};

    TEST_P(CardFlippingHorizontally, createCard) {
        const auto& [original, flipped_horizontally] = GetParam();
        mdn::Card card{original.dot, original.ring};
        card.flip_horizontally();
        ASSERT_EQ(card.get_dot(), flipped_horizontally.dot);
        ASSERT_EQ(card.get_ring(), flipped_horizontally.ring);

        static unsigned char lut[] = {2, 1, 0, 5, 4, 3, 8, 7, 6, 11, 10, 9};
        ASSERT_EQ(card.get_dot(), lut[original.dot]);
        ASSERT_EQ(card.get_ring(), lut[original.ring]);
    }

    std::vector<std::tuple<CardInitializer, CardInitializer>>
    load_card_flipping_horizontally_tests_data() {
        std::vector<std::tuple<CardInitializer, CardInitializer>> testCases;
        const auto jsonContent = get_json();

        for (const auto &item : jsonContent["positive"]) {
            CardInitializer original{item["original"]["dot"].get<unsigned char>(), item["original"]["ring"].get<unsigned char>()};
            CardInitializer flipped_horizontally{item["flipped-horizontally"]["dot"].get<unsigned char>(), item["flipped-horizontally"]["ring"].get<unsigned char>()};
            testCases.emplace_back(original, flipped_horizontally);
        }

        return testCases;
    }

    INSTANTIATE_TEST_SUITE_P(
        CardFlippingHorizontallyTestSuit,
        CardFlippingHorizontally,
        ValuesIn(load_card_flipping_horizontally_tests_data())
    );
}

namespace {
    class CardFlippingVertically : public ::testing::TestWithParam<std::tuple<CardInitializer, CardInitializer>> {};

    TEST_P(CardFlippingVertically, createCard) {
        const auto& [original, flipped_vertically] = GetParam();
        mdn::Card card{original.dot, original.ring};
        card.flip_vertically();
        ASSERT_EQ(card.get_dot(), flipped_vertically.dot);
        ASSERT_EQ(card.get_ring(), flipped_vertically.ring);

        static unsigned char lut[] = {9, 10, 11, 6, 7, 8, 3, 4, 5, 0, 1, 2};
        ASSERT_EQ(card.get_dot(), lut[original.dot]);
        ASSERT_EQ(card.get_ring(), lut[original.ring]);
    }

    std::vector<std::tuple<CardInitializer, CardInitializer>>
    load_card_flipping_vertically_tests_data() {
        std::vector<std::tuple<CardInitializer, CardInitializer>> testCases;
        const auto jsonContent = get_json();

        for (const auto &item : jsonContent["positive"]) {
            CardInitializer original{item["original"]["dot"].get<unsigned char>(), item["original"]["ring"].get<unsigned char>()};
            CardInitializer flipped_vertically{item["flipped-vertically"]["dot"].get<unsigned char>(), item["flipped-vertically"]["ring"].get<unsigned char>()};
            testCases.emplace_back(original, flipped_vertically);
        }

        return testCases;
    }

    INSTANTIATE_TEST_SUITE_P(
        CardFlippingVerticallyTestSuit,
        CardFlippingVertically,
        ValuesIn(load_card_flipping_vertically_tests_data())
    );
}

namespace {
    class CardNegativeTestSuit : public ::testing::TestWithParam<CardInitializer> {};

    TEST_P(CardNegativeTestSuit, createCardNegative) {
        const auto& input = GetParam();
        EXPECT_THROW(mdn::Card(input.dot, input.ring), std::invalid_argument);
    }

    std::vector<CardInitializer>
    load_card_creation_negative_tests_data() {
        std::vector<CardInitializer> testCases;
        const auto jsonContent = get_json();

        for (const auto &item : jsonContent["negative"]) {
            CardInitializer cardInitializer{item["dot"].get<unsigned char>(), item["ring"].get<unsigned char>()};
            testCases.emplace_back(cardInitializer);
        }

        return testCases;
    }

    INSTANTIATE_TEST_SUITE_P(
        CardCreationNegativeTestSuit,
        CardNegativeTestSuit,
        ValuesIn(load_card_creation_negative_tests_data())
    );
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
