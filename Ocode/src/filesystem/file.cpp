#include "file.h"

namespace fs = std::filesystem;

namespace ocode {
    int create_file(const std::string& file_name) {
        FILE* file;

        int error = fopen_s(&file, file_name.c_str(), "wb");

        fclose(file);

        return error;
    }

    int delete_file(const std::string& file_name) {
        return 0;
    }

    Virtual_File load_file(const std::string& file_name) {
        FILE* file;

        fopen_s(&file, file_name.c_str(), "rb");

        fseek(file, 0, SEEK_END);
        int size = (int)ftell(file);
        fseek(file, 0, SEEK_SET);

        uint8* buffer = new uint8[size];

        fread(buffer, sizeof(uint8), size, file);

        fclose(file);

        return Virtual_File(file_name, buffer, size);
    }

    int save_file(Virtual_File& file, const std::string& file_name) {
        return 0;
    }

    int file_exists(const std::string& file_name) {
        return fs::exists(file_name);
    }
}