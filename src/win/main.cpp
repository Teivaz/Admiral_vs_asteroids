#include "Precompiled.h"
#include "EsUtils_win.h"
#include "AppDelegate.h"

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, TCHAR *lpCmdLine, int nCmdShow)

int main(int argn, char** argv)
{
    AppDelegate delegate;
    CreateGLWindowWithContext(&delegate, "Admiral vs Asteroids", 1136, 640);
    delegate.Init();
    WindowLoop(&delegate);

    return 0;
}
