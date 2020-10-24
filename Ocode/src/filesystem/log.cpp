#include "log.h"

namespace ocode {
    LogFile::LogFile(const std::string& name) {
        fopen_s(&file, (name + ".log").c_str(), "w");
    }

    bool LogFile::initialized() {
        return file != NULL;
    }

    LogFile::~LogFile() {
        fclose(file);
    }

    void LogFile::printraw(const void* buffer, uint32 buffer_size) {
        fprintf(file, "[PRINTRAW] ");

        fwrite(buffer, 1, buffer_size, stdout);
        fwrite("\n", 1, 1, stdout);

        fwrite(buffer, 1, buffer_size, file);
        fwrite("\n", 1, 1, file);
    }

    void LogFile::print(const char* format, ...) {
        fprintf(file, "[PRINTLN] ");

        va_list args, fargs;
        va_start(args, format);
        va_copy(fargs, args);

        vprintf(format, args);
        va_end(args);

        vfprintf(file, format, fargs);
        va_end(fargs);
    }

    void LogFile::println(const char* format, ...) {
        fprintf(file, "[PRINTLN] ");

        va_list args, fargs;
        va_start(args, format);
        va_copy(fargs, args);

        vprintf(format, args);
        va_end(args);

        vfprintf(file, format, fargs);
        va_end(fargs);

        printf("\n");
        fwrite("\n", 1, 1, file);
    }

    void printraw(const void* buffer, uint32 buffer_size) {
        fwrite(buffer, 1, buffer_size, stdout);
        fwrite("\n", 1, 1, stdout);
    }

    void print(const char* format, ...) {
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
    }

    void println(const char* format, ...) {
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);

        printf("\n");
    }
}
