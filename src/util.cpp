#include "util.hpp"

namespace muser::util {
    std::string random_template_file() {
        char buffer[L_tmpnam_s];
        tmpnam_s (buffer);
        // auto temp_dir = std::filesystem::temp_directory_path();
        // auto path = std::filesystem::absolute(temp_dir);
        return std::string(buffer);
    }
}  // namespace muser::util