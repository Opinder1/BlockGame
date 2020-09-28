#include "file.h"

namespace ocode {
    Partial_File::Partial_File(std::string file_name) {
        this->file_name = file_name;
        fopen_s(&this->file, file_name.c_str(), "rb");
    }

    Partial_File::~Partial_File() {
        fclose(this->file);
    }

    Virtual_File Partial_File::load_partial(std::string partial_name, uint32 begin, uint32 size) {
        fseek(this->file, begin, SEEK_SET);

        uint8* buffer = new uint8[size];

        fread(buffer, sizeof(uint8), size, this->file);

        return Virtual_File(partial_name, buffer, size);
    }

    Virtual_File Partial_File::load_partial_compressed(std::string partial_name, uint32 begin, uint32 compressed_size, uint32 size) {
        fseek(this->file, begin, SEEK_SET);

        uint8* compressed_buffer = new uint8[compressed_size];
        uint8* buffer = new uint8[size];

        fread(compressed_buffer, sizeof(uint8), compressed_size, this->file);

        int code = uncompress(buffer, (uLongf*)&size, compressed_buffer, compressed_size);

        if (code == Z_BUF_ERROR) {
            //Error;
        }
        else if (code == Z_MEM_ERROR) {
            //Error;
        }
        else if (code == Z_DATA_ERROR) {
            //Error;
        }

        delete[] compressed_buffer;

        return Virtual_File(partial_name, buffer, size);
    }
}