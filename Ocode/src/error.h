#ifdef __GNUC__
#define LINUX
#else
#define WINDOWS_OFF
#endif

#ifdef WINDOWS
#include <windows.h>
#endif

#include <cstdio>
#include <cstdarg>
#include <exception>

void error_box(const char* title, const char* format, ...);