#include <fstream>
#include <utility>
#include <vector>

#include "mdn/test_utils.hpp"

nlohmann::json mdn::TestUtils::load_json_file_Content(const std::string &filepath) {
    nlohmann::json jsonContent;

    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    file >> jsonContent;

    return jsonContent;
}
