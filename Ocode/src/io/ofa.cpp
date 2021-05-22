#include "ofa.h"

namespace ocode {
    OFA::OFA(const fs::path& path) {
        FileReader file = load_compressed_file(path);

        file_count = file.read<uint16>();

        for (uint16 file_index = 0; file_index < file_count; file_index++) {
            uint16 file_name_size = file.read<uint16>();
            if (file_name_size == 0) throw ofa_exception{ "Invalid file name size" };

            std::string file_name(file.read<char>(file_name_size), file_name_size);

            uint64 file_size = file.read<uint64>();
            if (file_size == 0) throw ofa_exception{ "Invalid file size" };

            uint8* file_data = file.read_copy<uint8>(file_size);

            files.emplace(file_name, File{ file_size, file_data });
        }
    }

    OFA::~OFA() {
        for (auto& file : files) {
            delete[] file.second.data;
        }
    }

    bool OFA::contains_file(const std::string& file_name) {
        return this->files.find(file_name) != this->files.end();
    }

    File OFA::operator[](const std::string& file_name) {
        if (!this->contains_file(file_name)) {
            throw ofa_exception{ "Could not find the file in the archive" };
        }

        return this->files.at(file_name);
    }
}