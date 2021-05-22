#pragma once

#include "../typedef.h"

#include <string>
#include <cstdarg>
#include <cstdio>

// TODO use FileReader from file.h

namespace ocode {
    class LogFile {
    private:
        // TODO Probably use fstream instead of FILE but idk
        FILE* file;

    public:
        LogFile(const LogFile&) = delete;
        // TODO Ideally use fs::path instead of std::string
        LogFile(const std::string& name);
        ~LogFile();

        bool initialized();

        void printraw(const void* buffer, uint32 buffer_size);

        void print(const char* format, ...);

        void println(const char* format, ...);
    };
}