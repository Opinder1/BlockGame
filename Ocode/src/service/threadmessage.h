#pragma once

#include "typedef.h"

#include <any>
#include <memory>

#include <tuple>
#include <functional>
#include <utility>
#include <type_traits>

namespace ocode {
    struct ThreadMessage {
        enum {Stop, Post, Timer};

        uint8 type;
        std::function<void()> action;

        ThreadMessage() : type(0), action(0) {}
        ThreadMessage(uint8 type, std::function<void()> action) : type(type), action(action) {}
    };
}