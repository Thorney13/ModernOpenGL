#include "fileUtils.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

std::string get_file_contents(const char* filename)
{
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + std::string(filename));
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}