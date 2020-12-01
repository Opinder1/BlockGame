#include "error.h"

#ifdef __GNUC__
#define LINUX
#else
#define WINDOWS
#endif

#ifdef LINUX
#include <unistd.h>
#endif

#ifdef WINDOWS
#include <windows.h>
#endif

void error_box(const char* title, const char* format, ...) {
	char message[256];

	va_list args;
	va_start(args, format);
	vsprintf_s(message, format, args);
	va_end(args);

#ifdef WINDOWS
	int val = MessageBoxA(NULL, message, title, MB_OK | MB_ICONERROR);
#endif

	std::terminate();
} 