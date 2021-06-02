#pragma once

#include <GLM/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <unordered_map>

#define WIN32

#include <libzippp/libzippp.h>

using namespace std::string_literals;
using namespace std::string_view_literals;

namespace fs = std::filesystem;

namespace lz = libzippp;

namespace ocode {
    struct file_exception {
        std::string_view message;
        std::string name;
    };

    using File = std::string;

    using FileReader = std::stringstream;
    
    std::string read_string(std::istream& stream, size_t count);

    File load_file(const fs::path& path);
}