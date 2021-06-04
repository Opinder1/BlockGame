#include "file.h"

namespace ocode {
    std::string read_string(std::istream& stream, size_t count) {
        std::string output;
        output.reserve(count);
        std::copy_n(std::istreambuf_iterator(stream), count, std::back_inserter(output));
        return output;
    }

    File load_file(const fs::path& path) {
        if (!fs::exists(path)) throw file_exception{ "File does not exist"sv, path.u8string() };

        std::ifstream file(path, std::ios::binary);
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        if (!file) throw file_exception{ "Could not upen file"sv, path.u8string() };

        size_t file_size = fs::file_size(path);

        std::unique_ptr<char[]> buffer(new char[file_size]);

        file.read(buffer.get(), file_size);

        return File{ buffer.get(), file_size };
    }
}