#pragma once

#include "config.h"

#include "file.h"

#include "log.h"

namespace ocode {
    size_t constexpr hash(char const* input) {
        return *input ? (glm::uint32)*input + 33 * hash(input + 1) : 5381;
    }
}

size_t constexpr operator "" _h(const char* s, size_t) {
    return ocode::hash(s);
}