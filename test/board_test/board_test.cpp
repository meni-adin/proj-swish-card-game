#include <filesystem>
#include <gmock/gmock.h>
#include <tuple>

#include "mdn/Board.hpp"
#include "mdn/test_utils.hpp"
#include "nlohmann/json.hpp"

using namespace testing;

static nlohmann::json        g_jsonContent;
static const nlohmann::json &c_jsonContent = g_jsonContent;

struct DefaultTestSuiteData {
    uint8_t                             rowsNum;
    uint8_t                             colsNum;
    std::vector<std::vector<mdn::Card>> cards;
};

static DefaultTestSuiteData        g_defaultTestSuiteData;
static const DefaultTestSuiteData &c_defaultTestSuiteData = g_defaultTestSuiteData;

class BoardTestSuiteEnvironment : public ::testing::Environment {
public:
    static const nlohmann::json
    get_json() {
        return mdn::TestUtils::load_json_file_Content(MDN_BOARD_TEST_TESTS_DATA_FILE_PATH);
    }

    void
    SetUp() override {
        g_jsonContent = get_json();

        const auto &jsonBoardDimensions = c_jsonContent["boardDimensions"];
        g_defaultTestSuiteData.rowsNum  = jsonBoardDimensions["rowsNum"].get<uint8_t>();
        g_defaultTestSuiteData.colsNum  = jsonBoardDimensions["colsNum"].get<uint8_t>();

        const auto &jsonBoardCards = c_jsonContent["boardCards"];
        for (const auto &curJsonRow : jsonBoardCards) {
            std::vector<mdn::Card> row;
            for (const auto &curJsonCard : curJsonRow) {
                row.emplace_back(curJsonCard["dot"].get<uint8_t>(), curJsonCard["ring"].get<uint8_t>());
            }
            ASSERT_EQ(row.size(), c_defaultTestSuiteData.colsNum);
            g_defaultTestSuiteData.cards.push_back(row);
        }
        ASSERT_EQ(c_defaultTestSuiteData.cards.size(), c_defaultTestSuiteData.rowsNum);
    }
};

class BoardTestSuit : public ::testing::Test {
protected:
    static std::unique_ptr<mdn::Board>
    get_default_board() {
        const auto &jsonBoardDimensions = c_jsonContent["boardDimensions"];
        uint8_t     rowsNum             = jsonBoardDimensions["rowsNum"].get<uint8_t>();
        uint8_t     colsNum             = jsonBoardDimensions["colsNum"].get<uint8_t>();
        auto        board               = std::make_unique<mdn::Board>(rowsNum, colsNum);

        const auto &jsonBoardCards = c_jsonContent["boardCards"];
        for (uint8_t rowNum = 0; rowNum < rowsNum; ++rowNum) {
            const auto &curJsonRow = jsonBoardCards[rowNum];
            for (uint8_t colNum = 0; colNum < colsNum; ++colNum) {
                const auto &curJsonCard = curJsonRow[colNum];
                mdn::Card   card{curJsonCard["dot"].get<uint8_t>(), curJsonCard["ring"].get<uint8_t>()};
                board->set_card_at(mdn::Board::CardCoordinates{rowNum, colNum}, std::make_unique<mdn::Card>(card));
            }
        }

        return board;
    }
};

namespace {
    class BoardCreationTestSuit : public BoardTestSuit {};

    TEST_F(BoardCreationTestSuit, createBoard) {
        const mdn::Board board{c_defaultTestSuiteData.rowsNum, c_defaultTestSuiteData.colsNum};
    }

    TEST_F(BoardCreationTestSuit, createZeroSizedBoard) {
        const mdn::Board board{0, 0};
    }

    TEST_F(BoardCreationTestSuit, createNonSquareBoard) {
        const mdn::Board board{5, 19};
    }
}  // namespace

namespace {
    class BoardDataTestSuit : public BoardTestSuit {};

    mdn::Board::index_t
        defaultRowsNum = 3,
        defaultColsNum = 5;

    TEST_F(BoardDataTestSuit, getRowsNum) {
        const mdn::Board board{defaultRowsNum, defaultColsNum};
        ASSERT_EQ(board.get_rows_num(), defaultRowsNum);
    }

    TEST_F(BoardDataTestSuit, getColsNum) {
        const mdn::Board board{defaultRowsNum, defaultColsNum};
        ASSERT_EQ(board.get_cols_num(), defaultColsNum);
    }

    TEST_F(BoardDataTestSuit, setCard) {
        mdn::Board                        board{c_defaultTestSuiteData.rowsNum, c_defaultTestSuiteData.colsNum};
        const mdn::Card                   card{1, 2};
        const mdn::Board::CardCoordinates cardCoordinates{0, 0};
        board.set_card_at(cardCoordinates, std::make_unique<mdn::Card>(card));
        const auto retrievedCard = board.peek_at_card(cardCoordinates);
        ASSERT_EQ(card, retrievedCard);
    }

    TEST_F(BoardDataTestSuit, fillBoard) {
        auto board = get_default_board();
    }
}  // namespace

namespace {
    class BoardNegativeTestSuit : public BoardTestSuit {};

    TEST_F(BoardNegativeTestSuit, peakAtInvalidRow) {
        auto                              board = get_default_board();
        const mdn::Board::CardCoordinates cardCoordinates{board->get_rows_num(), static_cast<mdn::Board::index_t>(board->get_cols_num() - 1)};
        EXPECT_THROW(board->peek_at_card(cardCoordinates), std::invalid_argument);
    }

    TEST_F(BoardNegativeTestSuit, peakAtInvalidColumn) {
        auto                              board = get_default_board();
        const mdn::Board::CardCoordinates cardCoordinates{static_cast<mdn::Board::index_t>(board->get_rows_num() - 1), board->get_cols_num()};
        EXPECT_THROW(board->peek_at_card(cardCoordinates), std::invalid_argument);
    }

    TEST_F(BoardNegativeTestSuit, peakAtNullCell) {
        mdn::Board                        board{1, 1};
        const mdn::Board::CardCoordinates cardCoordinates{0, 0};
        EXPECT_THROW(board.peek_at_card(cardCoordinates), std::invalid_argument);
    }
}  // namespace

int
main(int argc, char *argv[]) {
    ::testing::AddGlobalTestEnvironment(new BoardTestSuiteEnvironment);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
