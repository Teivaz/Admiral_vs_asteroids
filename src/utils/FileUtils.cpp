#include "Precompiled.h"
#include "FileUtils.h"

#ifdef WIN32
#include <stdio.h>
#include <stdlib.h>
#else

#endif

using std::string;

namespace FileUtils
{

    void LoadFile(const char* file, char** outdata, size_t& size, location loc)
    {
#ifdef WIN32
        if (loc == app)
        {
            size = 0;
            *outdata = nullptr;
            std::string fileName(file);
            FILE* f = fopen(fileName.c_str(), "rb");
            if (f == nullptr)
                return;
            fseek(f, 0, SEEK_END);
            size = ftell(f);
            rewind(f);
            *outdata = new char[size];
            fread(*outdata, 1, size, f);
            fclose(f);
        }
#else

        size = 0;
        *outdata = nullptr;

        NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
        CFBundleRef bundle = CFBundleGetMainBundle();
        CFURLRef bundleUrl = CFBundleCopyBundleURL(bundle);
        CFStringRef sr = CFURLCopyFileSystemPath(bundleUrl, kCFURLPOSIXPathStyle);
        char rootPath[1024];
        CFStringGetCString(sr, rootPath, sizeof(rootPath), kCFStringEncodingASCII)
            string path = rootPath;

        switch (loc)
        {
        case app:
            AppendPath(path, file);
            break;

        case documents:
            AppendPath(path, "../Documents");
            AppendPath(path, file);
            break;

        case lib:
            AppendPath(path, "../Library");
            AppendPath(path, file);
            break;

        default:
            return;

        }
        NSString *docPath = [NSString stringWithCString:path.c_str()
        encoding:[NSString defaultCStringEncoding]];
        NSString *dataFile = [NSString stringWithContentsOfFile:docPath 
        usedEncoding:NSUTF8StringEncoding 
                 error:NULL];



#endif
    }

    void AppendPath(string& src, const string& path0) {
        if (src.empty()) {
            src = path0;
        }
        else {
            char lastChar = src[src.size() - 1];
            if (lastChar == '/' || lastChar == '\\') {
                src += path0;
            }
            else {
                src.append("/");
                src.append(path0);
            }
        }
    }
}