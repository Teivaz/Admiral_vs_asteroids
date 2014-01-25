#include "Precompiled.h"
#include "EsUtils_win.h"
#include "AppDelegate.h"

#define WINDOW_CLASS "opengles2.0"



LRESULT WINAPI ESWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT  lRet = 1;

    AppDelegate* ad = (AppDelegate*)(LONG_PTR)GetWindowLongPtr(hWnd, GWL_USERDATA);

    switch (uMsg)
    {
    case WM_CREATE:
        break;

    case WM_PAINT:
    {
                     ad->Render();
                     ValidateRect(ad->window, NULL);
    }
        break;
    case WM_KEYDOWN:
    {
                       //
    }
        break;

    case WM_KEYUP:
    {
                     //
    }
        break;

    case WM_LBUTTONDOWN:
    {
                           // Touched
    }
        break;

    case WM_LBUTTONUP:
    {
                         // Touch release
    }
        break;

    case WM_MOUSEMOVE:
    {
                         // Touch drag
    }
        break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

GLboolean CreateGLWindowWithContext(AppDelegate *delegate, const char *title, int w, int h)
{
    WNDCLASS wndclass = { 0 };
    DWORD wStyle = 0;
    RECT windowRect;
    HINSTANCE hInstance = GetModuleHandle(NULL);
    HDC hDC = 0;

    wndclass.style = CS_OWNDC;
    wndclass.lpfnWndProc = (WNDPROC)ESWindowProc;
    wndclass.hInstance = hInstance;
    wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndclass.lpszClassName = "ogles2.0";

    if (!RegisterClass(&wndclass))
        return FALSE;

    wStyle = WS_VISIBLE | WS_POPUP | WS_BORDER | WS_SYSMENU | WS_CAPTION;

    windowRect.left = 0;
    windowRect.top = 0;
    windowRect.right = w;
    windowRect.left = h;

    AdjustWindowRect(&windowRect, wStyle, FALSE);

    delegate->window = CreateWindow(
        "ogles2.0",
        title,
        wStyle,
        0,
        0,
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top,
        NULL,
        NULL,
        hInstance,
        NULL);
    SetWindowLongPtr(delegate->window, GWL_USERDATA, (LONG)(LONG_PTR)delegate);

    if (delegate->window == NULL)
        return GL_FALSE;

    //ShowWindow(delegate->window, TRUE);

    hDC = GetDC(delegate->window);

    EGLDisplay& eglDisplay = delegate->display;
    EGLConfig			eglConfig = 0;
    EGLSurface& eglSurface = delegate->surface;
    EGLContext eglContext = 0;
    EGLNativeWindowType	eglWindow = delegate->window;

    if (!hDC)
    {
        MessageBox(0, ("Failed to create the device context"), ("Error"), MB_OK | MB_ICONEXCLAMATION);
    }
    eglDisplay = eglGetDisplay(hDC);
    if (eglDisplay == EGL_NO_DISPLAY)
        eglDisplay = eglGetDisplay((EGLNativeDisplayType)EGL_DEFAULT_DISPLAY);
    EGLint iMajorVersion, iMinorVersion;
    if (!eglInitialize(eglDisplay, &iMajorVersion, &iMinorVersion))
    {
        MessageBox(0, ("eglInitialize() failed."), ("Error"), MB_OK | MB_ICONEXCLAMATION);
    }
    eglBindAPI(EGL_OPENGL_ES_API);

    const EGLint pi32ConfigAttribs[] =
    {
        EGL_LEVEL, 0,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_NATIVE_RENDERABLE, EGL_FALSE,
        EGL_DEPTH_SIZE, EGL_DONT_CARE,
        EGL_NONE
    };
    EGLint iConfigs;
    if (!eglChooseConfig(eglDisplay, pi32ConfigAttribs, &eglConfig, 1, &iConfigs) || (iConfigs != 1))
    {
        MessageBox(0, ("eglChooseConfig() failed."), ("Error"), MB_OK | MB_ICONEXCLAMATION);
    }
    eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, eglWindow, NULL);
    if (eglSurface == EGL_NO_SURFACE)
    {
        eglGetError(); // Clear error
        eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, NULL, NULL);
    }
    EGLint ai32ContextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
    eglContext = eglCreateContext(eglDisplay, eglConfig, NULL, ai32ContextAttribs);
    eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);




    return GL_TRUE;
}

void WindowLoop(AppDelegate* delegate)
{
    MSG msg = { 0 };
    int done = 0;
    DWORD lastTime = GetTickCount();

    while (!done)
    {
        int gotMsg = (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0);
        DWORD curTime = GetTickCount();
        float deltaTime = (float)(curTime - lastTime) / 1000.0f;
        lastTime = curTime;

        if (gotMsg)
        {
            if (msg.message == WM_QUIT)
            {
                done = 1;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
            SendMessage(delegate->window, WM_PAINT, 0, 0);

        // Call update function if registered
        delegate->Update(deltaTime);
    }

}
