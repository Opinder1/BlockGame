#pragma once

#include "typedef.h"

#include <unordered_map>
#include <string>

#include "file.h"
#include "log.h"

namespace ocode {
    struct File_Meta {
        uint32 compressed_size;
        uint32 size;
        uint32 pos;
    };

    class OFA : public Partial_File {
    private:
        uint32 meta_compressed_size;
        uint32 meta_size;
        uint16 file_count;

        std::unordered_map<std::string, File_Meta> files;

        void error(std::string reason);

    public:
        OFA(std::string archive_name);

        ~OFA();

        void print_files();

        bool contains_file(std::string& file_name);

        Virtual_File operator[](std::string& file_name);
    };
}