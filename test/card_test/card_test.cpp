#include <filesystem>
#include <gmock/gmock.h>

#include "mdn/card.hpp"
#include "mdn/test_utils.hpp"
#include "nlohmann/json.hpp"

using namespace testing;

namespace {
    std::vector<std::pair<std::string, bool>> loadTestsData(const std::string &filepath) {
        nlohmann::json jsonContent;
        std::vector<std::pair<std::string, bool>> testCases;

        jsonContent = mdn::TestUtils::loadJsonFileContent(filepath);

        for (const auto &item : jsonContent) {
            testCases.emplace_back(
                item["input"].get<std::string>(),
                item["expected"].get<bool>());
        }

        return testCases;
    }
}


class CardTestSuit : public ::testing::TestWithParam<std::pair<std::string, bool>> {};

TEST_P(CardTestSuit, isUniqueTest) {
    const auto& [input, expected] = GetParam();
    ASSERT_EQ(mdn::chapter_01_problem_01_solution::isUnique(input), expected)
        << "Failed for input: " << input;
}

INSTANTIATE_TEST_SUITE_P(
    CardCreationTestSuit,
    CardTestSuit,
    ValuesIn(loadTestsData(MDN_CHAPTER_01_PROBLEM_01_TEST_TESTS_DATA_FILE_PATH))
);

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
