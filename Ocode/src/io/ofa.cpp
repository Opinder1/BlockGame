#include "ofa.h"

namespace ocode {
    std::string decompress(const std::string& input, glm::uint32 output_size) {
        std::unique_ptr<char[]> output(new char[output_size]);
        if (output == nullptr) throw zip_exception{ "Could not allocate memory for uncompressed file" };

        // TODO Add zlib library
        int code = 0; // uncompress((Bytef*)output.get(), (uLongf*)&output_size, (const Bytef*)input.data(), (uLong)input.size());

        if (code == Z_BUF_ERROR) throw zip_exception{ "Could not uncompress file (Buffer Error)" };
        if (code == Z_MEM_ERROR) throw zip_exception{ "Could not uncompress file (Memory Error)" };
        if (code == Z_DATA_ERROR) throw zip_exception{ "Could not uncompress file (Data Error)" };

        return { output.get(), output_size };
    }

    File load_compressed_file(const fs::path& path) {
        FileReader file(load_file(path));

        glm::uint32 input_size, output_size;

        file >> input_size >> output_size;

        std::string input = read_string(file, input_size);

        return decompress(input, output_size);
    }

    OFA::OFA(const fs::path& path) {
        FileReader file(load_compressed_file(path));

        file >> file_count;

        for (glm::uint16 file_index = 0; file_index < file_count; file_index++) {
            glm::uint16 file_name_size; file >> file_name_size;
            if (file_name_size == 0) throw ofa_exception{ "Invalid file name size" };

            std::string file_name = read_string(file, file_name_size);

            glm::uint64 file_size; file >> file_size;
            if (file_size == 0) throw ofa_exception{ "Invalid file size" };

            files.emplace(file_name, read_string(file, file_size));
        }
    }

    bool OFA::contains_file(const std::string& file_name) {
        return files.find(file_name) != files.end();
    }

    const File& OFA::operator[](const std::string& file_name) {
        if (!contains_file(file_name)) {
            throw ofa_exception{ "Could not find the file" };
        }

        return files.at(file_name);
    }
}