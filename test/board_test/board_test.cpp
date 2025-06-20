#include <filesystem>
#include <gmock/gmock.h>
#include <tuple>

#include "mdn/board.hpp"
#include "mdn/test_utils.hpp"
#include "nlohmann/json.hpp"

using namespace testing;

// struct BoardInitializer {
//     uint8_t dot, ring;
// };

// const nlohmann::json &
// get_json() {
//     static nlohmann::json jsonContent;
//     jsonContent = mdn::TestUtils::load_json_file_Content(MDN_BOARD_TEST_TESTS_DATA_FILE_PATH);
//     return jsonContent;
// }

namespace {
    class BoardCreationTestSuit : public ::testing::Test {
    protected:
        static constexpr uint8_t
            defaultBoardRowsNum = 4,
            defaultBoardColsNum = 4;
    };

    TEST_F(BoardCreationTestSuit, createBoard) {
        const mdn::Board board{1, 1};
    }

    TEST_F(BoardCreationTestSuit, fillBoard) {
        mdn::Board board{defaultBoardRowsNum, defaultBoardColsNum};
        const mdn::Card card{1, 2};
        board.set_card_at(mdn::CardCoordinates{0, 0}, std::make_unique<mdn::Card>(card));
        const auto retrievedCard = board.peek_at_card(mdn::CardCoordinates{1, 0});
        // (void) retrievedCard;
        ASSERT_EQ(card, retrievedCard);
    }
}  // namespace

// namespace {
//     class BoardNegativeTestSuit : public ::testing::TestWithParam<BoardInitializer> {};

// TEST_P(BoardNegativeTestSuit, createBoardNegative) {
//     const auto &input = GetParam();
//     EXPECT_THROW(mdn::Board(input.dot, input.ring), std::invalid_argument);
// }

// std::vector<BoardInitializer>
// load_board_creation_negative_tests_data() {
//     std::vector<BoardInitializer> testCases;
//     const auto                   jsonContent = get_json();

// for (const auto &item : jsonContent["negative"]) {
//     BoardInitializer boardInitializer{item["dot"].get<uint8_t>(), item["ring"].get<uint8_t>()};
//     testCases.emplace_back(boardInitializer);
// }

// return testCases;
// }

// INSTANTIATE_TEST_SUITE_P(
//     BoardCreationNegativeTestSuit,
//     BoardNegativeTestSuit,
//     ValuesIn(load_board_creation_negative_tests_data()));
// }  // namespace

int
main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
