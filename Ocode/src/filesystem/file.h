#pragma once

#include "../typedef.h"

#include <string>
#include <cstdio>
#include <fstream>
#include <filesystem>

#include "zlib/zlib.h"

// Remove this file completely

namespace ocode {
    class Virtual_File {
    private:
        uint32 stream_pos = 0;

    protected:
        std::string name;

        const uint8* data;

        uint32 size;

    public:
        Virtual_File(const Virtual_File&) = delete;
        Virtual_File(const std::string& file_name, const uint8* file_data, uint32 size);
        ~Virtual_File();

        void seek(uint32 pos);

        const std::string& get_name() const;

        uint32 get_size() const;

        const uint8* get_data() const;

        bool eof();

        template<class Type>
        void read(Type& buffer) {
            buffer = *(Type*)(this->data + this->stream_pos);

            this->stream_pos += sizeof(Type);
        }

        void read(std::string& buffer, uint32 string_size);

        int find(uint8 key);

        bool read_line(std::string& buffer);
    };

    class Partial_File {
    protected:
        std::string file_name;

        FILE* file;

    public:
        Partial_File(const Partial_File&) = delete;
        Partial_File(const std::string& file_name);

        ~Partial_File();

        template<class Type>
        void read_scalar(Type& buffer) {
            fread(&buffer, sizeof(Type), 1, this->file);
        }

        Virtual_File load_partial(const std::string& partial_name, uint32 begin, uint32 size);

        Virtual_File load_partial_compressed(const std::string& partial_name, uint32 begin, uint32 compressed_size, uint32 size);
    };

    // Should return File object (would be auto closed if not used)
    int create_file(const std::string& file_name);

    int delete_file(const std::string& file_name);

    Virtual_File load_file(const std::string& file_name);

    int save_file(Virtual_File& file, const std::string& file_name);

    int file_exists(const std::string& file_name);

    void create_folder_if_not_exist(const std::string& folder_name);

    std::string get_folder(const std::string& file_name);
}