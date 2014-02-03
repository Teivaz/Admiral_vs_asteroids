#include "Precompiled.h"
#include "EsUtils_win.h"
#include "AppDelegate.h"

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, TCHAR *lpCmdLine, int nCmdShow)

#define IPHONE5 1136, 640
#define IPHONE4 960, 640

int main(int argn, char** argv)
{
    AppDelegate delegate;
    CreateGLWindowWithContext(&delegate, "Admiral vs Asteroids", IPHONE5);
    delegate.Init();
    WindowLoop(&delegate);

    return 0;
}
