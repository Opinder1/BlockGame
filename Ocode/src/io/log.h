#pragma once

#include <iostream>
#include <fstream>

#include "file.h"

inline struct _newline {} newline;

namespace ocode {
    class LogFile {
    private:
        std::ofstream stream;

    public:
        LogFile(const fs::path& name) : stream(name) {}

        template<class Type>
        LogFile& operator<<(Type t) {
            stream << t;
            std::cout << t;

            return *this;
        }

        template<>
        LogFile& operator<<(_newline) {
            stream << std::endl;
            std::cout << std::endl;

            return *this;
        }
        
    };
}