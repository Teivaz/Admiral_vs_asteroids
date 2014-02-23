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

namespace Json
{
    void ReadVector(const Value& value, vec2f& vec)
    {
        vec = vec2f(static_cast<float>(value["x"].asDouble()),
                    static_cast<float>(value["y"].asDouble()));
    }
}

float clamp(float a)
{
    return max(min(a, 1.0f), 0.0f);
}
