#pragma once

#ifdef WIN32

#include "EGL/egl.h"
#include "GLES2/gl2.h"
#include <Windows.h>

#else

#import <Availability.h>

#ifndef __IPHONE_5_0
#warning "This project uses features only available in iOS SDK 5.0 and later."
#endif

#ifdef __OBJC__
#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>
#import <Foundation/Foundation.h>
#endif

template<typename T>
inline T min(T a, T b)
{
    return a < b ? a : b;
}
template<typename T>
inline T max(T a, T b)
{
    return a > b ? a : b;
}

#endif

//#include "sigslot.h"
#include "lodepng.h"
#include "json/json.h"
#include <vector>
#include <list>
#include <string>
#include <map>
#include <algorithm>

#include "utils/CustomGLTypes.h"
#include "utils/VectorGeometry.h"

//using namespace sigslot;

using std::string;

#ifdef _DEBUG
#define ASSERT(x) _ASSERT(x)
#define PLOG printf
#else
#define PLOG(x)
#define ASSERT(x)
#endif

#include "utils/Singleton.h"
