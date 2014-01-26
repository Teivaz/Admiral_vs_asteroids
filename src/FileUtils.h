#pragma once

namespace FileUtils
{
    enum location
    {
        app,
        documents,
        lib
    };

void OpenFile(const char* file, char** outdata, size_t& size, location);
void AppendPath(std::string& src, const std::string& path0);

};
#ifdef WIN32

#else

#endif
