#include "Precompiled.h"

#if (defined _WIN32 && defined _DEBUG)
#include <varargs.h>

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

namespace Json
{
    void ReadVector(const Value& value, vec2d& vec)
    {
        vec = vec2d(static_cast<double>(value["x"].asDouble()),
                    static_cast<double>(value["y"].asDouble()));
    }
}

double clamp(double a)
{
    return max(min(a, 1.0f), 0.0f);
}
