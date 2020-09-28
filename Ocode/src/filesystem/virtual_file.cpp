#include "file.h"

namespace ocode {
    Virtual_File::Virtual_File(std::string file_name, const uint8* file_data, uint32 size) {
        this->name = file_name;
        this->data = file_data;
        this->size = size;
    }

    Virtual_File::~Virtual_File() {
        delete[] this->data;
    }

    void Virtual_File::seek(uint32 pos) {
        if (pos > this->size) {
            pos = this->size;
        }
        else {
            this->stream_pos = pos;
        }
    }

    std::string& Virtual_File::get_name() {
        return this->name;
    }

    uint32 Virtual_File::get_size() {
        return this->size;
    }

    const uint8* Virtual_File::get_data() {
        return this->data;
    }

    bool Virtual_File::eof() {
        return (this->stream_pos >= this->size);
    }

    void Virtual_File::read(std::string& buffer, uint32 string_size) {
        buffer = std::string((char*)this->data + this->stream_pos, string_size);

        this->stream_pos += string_size;
    }

    int Virtual_File::find(uint8 key) {
        uint32 pos = this->stream_pos;

        while (pos < this->size) {
            if (this->data[pos] == key) {
                return pos;
            }
            pos++;
        }

        return this->size;
    }

    bool Virtual_File::read_line(std::string& buffer) {
        uint32 end = this->find('\n');

        int len = end - this->stream_pos;

        if (len < 1) {
            return false;
        }

        if (this->data[end] == '\r') {
            len--;
        }

        buffer = std::string((const char*)(this->data + this->stream_pos), len);

        this->stream_pos += len + 1;

        return true;
    }
}