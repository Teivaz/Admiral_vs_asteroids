#include "Precompiled.h"
#include "EsUtils_win.h"
#include "AppDelegate.h"

int main(int argn, char** argv)
{
    AppDelegate delegate;
    CreateGLWindowWithContext(&delegate, "Hello", 800, 600);
    WindowLoop(&delegate);

    return 0;
}
