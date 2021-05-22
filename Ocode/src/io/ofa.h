#pragma once

#include "file.h"

#include <sstream>

namespace ocode {
    struct ofa_exception : file_exception {};

    struct zip_exception : file_exception {};

    std::string decompress(const std::string& input, glm::uint32 output_size);

    File load_compressed_file(const fs::path& path);

    // TODO add compress and save_compressed_file functions

    // TODO Keep this or find some zip file opener. I probably want a zip file opener because no one wants to have to make OFA files.
    class OFA {
    private:
        glm::uint16 file_count;

        std::unordered_map<std::string, File> files;

    public:
        OFA(const fs::path& path);

        bool contains_file(const std::string& file_name);

        const File& operator[](const std::string& file_name);
    };
}