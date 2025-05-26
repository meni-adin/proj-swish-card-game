
#include <vector>
#include "nlohmann/json.hpp"

namespace mdn {
    namespace TestUtils {
        nlohmann::json loadJsonFileContent(const std::string &filepath);
    }
}
