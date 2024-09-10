#include <fstream>

#include "tools.hpp"

namespace tools {
    std::vector<std::string> read(const std::string& path) {
        std::fstream file(path);

        std::vector<std::string> ids;
        std::string id;

        while (file >> id) {
            if(id.length() <= 32) {
                ids.push_back(id);
            }
        }

        return ids;
    }
}