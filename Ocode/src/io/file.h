#pragma once

#include "../typedef.h"

#include <string>
#include <fstream>
#include <filesystem>
#include <unordered_map>

#include "zlib/zlib.h"

namespace fs = std::filesystem;

namespace ocode {
    struct file_exception {
        std::string message;
    };

    struct File {
        size_t size;
        uint8* data;
    };

    File load_file(const fs::path& path);

    File load_compressed_file(const fs::path& path);

    class FileReader {
    private:
        File file;

        size_t stream_pos;

    public:
        FileReader(const FileReader&) = delete;
        FileReader(const File& file);
        ~FileReader();

        void seek(size_t pos);

        size_t get_size() const;

        bool eof();

        template<class Type>
        Type read() {
            if (stream_pos + sizeof(Type) > file.size) throw file_exception{ "Read out of bounds" };

            Type buffer = *(Type*)(file.data + stream_pos);

            stream_pos += sizeof(Type);

            return buffer;
        }

        template<class Type>
        void read(Type& buffer) {
            if (stream_pos + sizeof(Type) > file.size) throw file_exception{ "Read out of bounds" };

            buffer = *(Type*)(file.data + stream_pos);

            stream_pos += sizeof(Type);
        }

        template<class Type>
        Type* read(size_t size) {
            if (stream_pos + size > file.size) throw file_exception{ "Read out of bounds" };

            uint8* data = file.data + stream_pos;

            this->stream_pos += size;

            return (Type*)data;
        }

        template<class Type>
        Type* read_copy(size_t size) {
            if (stream_pos + size > file.size) throw file_exception{ "Read out of bounds" };

            uint8* data = new uint8[size];
            memcpy_s(data, size, file.data + stream_pos, size);

            this->stream_pos += size;

            return (Type*)data;
        }
    };
}