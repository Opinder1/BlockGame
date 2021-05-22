#pragma once

#include <sstream>

#include "file.h"

#include "zlib/zlib.h"
#include "libzip/zip.h"

namespace ocode {
    struct ofa_exception : file_exception {};

    struct zip_exception : file_exception {};

    std::string decompress(const std::string& input, glm::uint32 output_size);

    File load_compressed_file(const fs::path& path);

    // TODO add compress and save_compressed_file functions

    class OFA {
    private:
        glm::uint16 file_count;

        std::unordered_map<std::string, File> files;

    public:
        OFA(const fs::path& path);

        bool contains_file(const std::string& file_name);

        const File& operator[](const std::string& file_name);
    };

    // TODO Work more on expanding functionality
    class ZIP {
    private:
        zip_t* zip;

    public:
        ZIP(const fs::path& path);
        ~ZIP();

        File operator[](const std::string& file_name);
    };
}