#include "file.h"

namespace fs = std::filesystem;

// TODO Put in compression place. Idk if it should inherit from file exception or not
struct zip_exception : ocode::file_exception {};

// TODO Ideally should be in some compression place idk. I should probably use some library to open .zip because its standard
uint8* decompress(uint8* input, uint32 input_size, uint32 output_size) {
    uint8* output = new uint8[output_size];

    if (output == NULL) throw zip_exception{ "Could not allocate memory for uncompressed file" };

    int code = 0; //uncompress(output, (uLongf*)&output_size, input, input_size);

    if (code == Z_BUF_ERROR) throw zip_exception{ "Could not uncompress file (Buffer Error)" };
    if (code == Z_MEM_ERROR) throw zip_exception{ "Could not uncompress file (Memory Error)" };
    if (code == Z_DATA_ERROR) throw zip_exception{ "Could not uncompress file (Data Error)" };

    return output;
}

namespace ocode {
    File load_file(const fs::path& path) {
        if (!fs::exists(path)) throw file_exception{ "File does not exist" };

        std::ifstream file(path, std::ios::binary);
        if (!file) throw file_exception{ "Could not upen file" };

        size_t file_size = fs::file_size(path);

        uint8* buffer = new uint8[file_size];
        if (buffer == NULL) throw file_exception{ "Could not allocate memory for file" };

        file.read((char*)buffer, file_size);
        if (!file) throw file_exception{ "Error while reading file" };

        return { file_size, buffer };
    }

    File load_compressed_file(const fs::path& path) {
        FileReader compressed_file = load_file(path);

        uint32 input_size = compressed_file.read<uint32>();
        uint32 output_size = compressed_file.read<uint32>();
        uint8* input = compressed_file.read<uint8>(input_size);

        uint8* output = decompress(input, input_size, output_size);

        return { output_size, output };
    }

    FileReader::FileReader(const File& file) : file(file), stream_pos(0) {

    }
    
    FileReader::~FileReader() {
        delete[] file.data;
    }
    
    void FileReader::seek(size_t pos) {
        if (pos < file.size) {
            this->stream_pos = pos;
        }
    }

    size_t FileReader::get_size() const {
        return file.size;
    }

    bool FileReader::eof() {
        return stream_pos >= file.size;
    }
}