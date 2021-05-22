#include "file.h"

namespace ocode {
    std::string read_string(std::istream& stream, size_t count) {
        std::string output;
        output.reserve(count);
        std::copy_n(std::istreambuf_iterator(stream), count, std::back_inserter(output));
        return output;
    }

    // TODO needs to be tested
    File load_file(const fs::path& path) {
        if (!fs::exists(path)) throw file_exception{ "File does not exist" };

        std::ifstream file(path, std::ios::binary);
        if (!file) throw file_exception{ "Could not upen file" };

        size_t file_size = fs::file_size(path);

        std::unique_ptr<char[]> buffer(new char[file_size]);
        if (buffer == nullptr) throw file_exception{ "Could not allocate memory for file" };

        file.read(buffer.get(), file_size);
        if (!file) throw file_exception{ "Error while reading file" };

        return { buffer.get(), file_size };
    }
}