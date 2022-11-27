#include <array>
#include <sstream>

#include "../include/utils.h"

std::string execute_cmd(const std::string& cmd) {
    std::array<char, 128> buffer;
    std::stringstream ss;

    FILE *pipe = popen(cmd.c_str(), "r");
    if (!pipe) throw std::runtime_error("popen() failed!");

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        ss << buffer.data();
    }

    pclose(pipe);
    return ss.str();
}
