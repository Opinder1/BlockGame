#pragma once

#include "config.h"

#include "file.h"

#include "log.h"

namespace ocode {
    size_t constexpr hash(char const* input) {
        return *input ? (glm::uint32)*input + 33 * hash(input + 1) : 5381;
    }

    template<class... Args>
    std::string format(const std::string_view fmt, const Args&... args) {
        int size = std::snprintf(nullptr, 0, fmt.data(), args ...) + 1;

        if (size <= 0) { throw std::runtime_error("Error during formatting."); }

        std::unique_ptr<char[]> buf(new char[size]);

        std::snprintf(buf.get(), size, fmt.data(), args...);

        return std::string(buf.get(), buf.get() + size - 1);
    }

    template<class... Args>
    int scan(const std::string& input, const std::string_view fmt, Args&... args) {
        return sscanf_s(input.c_str(), fmt.data(), args...);
    }

}

size_t constexpr operator "" _h(const char* s, size_t) {
    return ocode::hash(s);
}