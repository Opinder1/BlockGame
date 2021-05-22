#pragma once

#include "file.h"

#include <sstream>

namespace ocode {
    struct ofa_exception : file_exception {};

    // TODO Keep this or find some zip file opener. I probably want a zip file opener because no one wants to have to make OFA files.
    class OFA {
    private:
        uint16 file_count;

        std::unordered_map<std::string, File> files;

    public:
        OFA(const fs::path& path);
        ~OFA();

        bool contains_file(const std::string& file_name);

        File operator[](const std::string& file_name);
    };
}