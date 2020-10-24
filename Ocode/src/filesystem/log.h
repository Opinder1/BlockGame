#pragma once

#include "../typedef.h"

#include <string>
#include <cstdarg>
#include <cstdio>

namespace ocode {
    class LogFile {
    private:
        FILE* file;

    public:
        LogFile(const LogFile&) = delete;
        LogFile(const std::string& name);
        ~LogFile();

        bool initialized();

        void printraw(const void* buffer, uint32 buffer_size);

        void print(const char* format, ...);

        void println(const char* format, ...);
    };

    void printraw(const void* buffer, uint32 buffer_size);

    void print(const char* format, ...);

    void println(const char* format, ...);
}