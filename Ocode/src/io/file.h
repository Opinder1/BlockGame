#pragma once

#include <GLM/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <unordered_map>

namespace fs = std::filesystem;

namespace ocode {
    struct file_exception {
        std::string message;
    };

    using File = std::string;

    using FileReader = std::stringstream;
    
    std::string read_string(std::istream& stream, size_t count);

    File load_file(const fs::path& path);
}