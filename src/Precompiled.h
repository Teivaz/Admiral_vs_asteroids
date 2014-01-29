
#ifdef WIN32
#include "EGL/egl.h"
#include "GLES2/gl2.h"
#include <Windows.h>
#endif

#include "sigslot.h"
#include "lodepng.h"
#include "json/json.h"
#include <vector>
#include <string>
#include <map>

#include "utils/CustomGLTypes.h"
#include "utils/VectorGeometry.h"

using namespace sigslot;

using std::string;

#ifdef _DEBUG
#define ASSERT(x) _ASSERT(x)
#define PLOG(x) printf(x)
#else
#define PLOG(x)
#define ASSERT(x)
#endif

#include "utils/Singleton.h"