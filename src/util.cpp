#include "util.hpp"

namespace muser::util {
    std::string random_template_file() {
        char buffer[L_tmpnam];
        tmpnam_s (buffer, L_tmpnam);
        // Temporary solution. this substr is used because the generated filename is prefixed '\\' or '/'
        return std::string(buffer).substr(1);
    }
}  // namespace muser::util