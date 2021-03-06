#pragma once

#ifdef _WIN32

#include "EGL/egl.h"
#include "GLES2/gl2.h"
#include <Windows.h>
#include <winsock2.h>

#ifdef _ANALYZE
#include <vld.h>
#endif

#else // IOS
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
inline T min(T a, T b){return a < b ? a : b;}
template<typename T>
inline T max(T a, T b){return a > b ? a : b;}
#endif

#include "lodepng.h"
#include "json/json.h"
#include <vector>
#include <list>
#include <string>
#include <map>
#include <algorithm>
#include <memory>
#include <thread>

#include "utils/CustomGLTypes.h"

#define VECTRY_INLINE
#include "include/vectry.h"
using namespace vectry;

using std::string;
using std::vector;
using std::shared_ptr;

#if defined _DEBUG && defined _WIN32
#include <assert.h>
#define ASSERT assert
void PLOG(const char* x, ...);
#else
inline void PLOG(const char* x, ...){}
#define ASSERT __noop
#endif

#include "utils/Singleton.h"
#include "sigslot.h"
using namespace sigslot;

const double PI = 3.1416f;

#define MakeShared(T) \
    class T; \
    typedef shared_ptr<T> T##Ptr

#define ACCESSOR(x)			decltype(x) get##x##() const {return x;}
#define ACCESSOR_REF(x)		const decltype(x)& get##x##() const {return x;}
#define MUTATOR(x)			void set##x##(decltype(x) value) {x = value;}
#define MUTATOR_REF(x)		void set##x##(const decltype(x)& value) {x = value;}
#define MUTATOR_MOVE(x)		void set##x##(decltype(x)&& value) {x = value;}

namespace Json
{
    void ReadVector(const Value& value, vec2d& vec);
}

double clamp(double);
