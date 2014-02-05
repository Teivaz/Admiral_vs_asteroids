#include "Precompiled.h"

#include <varargs.h>

#if (defined _WIN32 && defined _DEBUG)
void PLOG(const char* x, ...)
{
    va_list params;
    char buf[2048];
    va_start(params, x);
    vsprintf_s(buf, sizeof(buf), x, params);
    printf("%s", buf);
    OutputDebugString(buf);
    va_end(params);
}

#endif
