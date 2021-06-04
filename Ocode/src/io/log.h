#pragma once

#include <iostream>
#include <fstream>

#include "file.h"

namespace ocode {
    inline struct _newline {} newl;
    inline struct _endline {} endl;

    struct log_exception : file_exception {};

    class LogFile {
    private:
        std::ofstream stream;

    public:
        LogFile(const fs::path& path);

        template<class Type>
        LogFile& operator<<(Type t) {
            stream << t;
            std::cout << t;

            return *this;
        }

        template<>
        LogFile& operator<<(_newline) {
            stream << '\n';
            std::cout << '\n';

            return *this;
        }

        template<>
        LogFile& operator<<(_endline) {
            stream << std::endl;
            std::cout << std::endl;

            return *this;
        }
        
    };
}