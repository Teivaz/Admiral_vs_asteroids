#pragma once

namespace FileUtils
{
enum location
{
	app,
	home
}

void OpenFile(const char* file, char** outdata, size_t& size, location);

};
#ifdef WIN32

#else

#endif