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

    void LogFile::printraw(const void* buffer, glm::uint32 buffer_size) {
        //fprintf(file, "[PRINTRAW] ");

        fwrite(buffer, 1, buffer_size, stdout);
        fwrite("\n", 1, 1, stdout);

        fwrite(buffer, 1, buffer_size, file);
        fwrite("\n", 1, 1, file);
    }

    void LogFile::print(const char* format, ...) {
        //fprintf(file, "[PRINTLN] ");

        va_list args, fargs;
        va_start(args, format);
        va_copy(fargs, args);

        vprintf(format, args);
        va_end(args);

        vfprintf(file, format, fargs);
        va_end(fargs);
    }

    void LogFile::println(const char* format, ...) {
        //fprintf(file, "[PRINTLN] ");

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
}
