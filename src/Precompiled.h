
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

#endif

//#include "sigslot.h"
#include "lodepng.h"
#include "json/json.h"
#include <vector>
#include <string>
#include <map>

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