#include "Precompiled.h"
#include "FileUtils.h"

#ifdef WIN32
#include <stdio.h>
#include <stdlib.h>
#else

#endif

using namespace FileUtils;

void OpenFile(const char* file, char** outdata, size_t& size, location loc)
{
#ifdef WIN32
	if(loc == app)
	{
		size = 0;
		*outdata = nullptr;
		std::string fileName(file);
		FILE* f = fopen(fileName.c_str(), "r");
		if(f == nullptr)
			return;
		fseek(f , 0 , SEEK_END);
		size = = ftell (pFile);
		*outdata = new char[size];
		result = fread (*outdata, 1, size, f);
		fclose(f);
	}
#else

#endif
}
