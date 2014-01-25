#include "Precompiled.h"
#include "EsUtils_win.h"
#include "AppDelegate.h"

#define WINDOW_CLASS "opengles2.0"



LRESULT WINAPI ESWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT  lRet = 1;
    switch (uMsg)
    {
    case WM_CREATE:
        break;

    case WM_PAINT:
    {
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
    return lRet;
}

GLboolean CreateGLWindowWithContext(AppDelegate *delegate, const char *title, int w, int h)
{{
    const char CLASS_NAME[] = "Sample Window Class";

    WNDCLASS wc = {};

    wc.lpfnWndProc = ESWindowProc;
    HINSTANCE hInstance = wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        "Learn to Program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, SW_SHOW);
    return 0;
}
    WNDCLASS wndclass = {0};
    DWORD windowStyle = 0;
    RECT windowRect;
    HINSTANCE hInstance = GetModuleHandle(NULL);

    wndclass.style = CS_OWNDC;
    wndclass.lpfnWndProc = (WNDPROC)ESWindowProc;
    wndclass.hInstance = hInstance;
    wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndclass.lpszClassName = WINDOW_CLASS;
    RegisterClass(&wndclass);

    windowStyle = WS_VISIBLE | WS_POPUP | WS_BORDER | WS_SYSMENU | WS_CAPTION;
    SetRect(&windowRect, 0, 0, w, h);
    //AdjustWindowRectEx(&windowRect, WS_CAPTION | WS_SYSMENU, false, 0);
    AdjustWindowRect(&windowRect, windowStyle, FALSE);

    HWND window = CreateWindowEx(
        0,
        WINDOW_CLASS,
        title,
        //windowStyle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
//        windowRect.left, windowRect.top, windowRect.right, windowRect.bottom,
        NULL,
        NULL,
        hInstance,
        NULL);
    //HWND window = CreateWindowEx(0, WINDOW_CLASS, title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, GetModuleHandle(0), 0);
    ShowWindow(window, TRUE);
    delegate->window = window;

    HDC hDC = 0;
    hDC = GetDC(window);
    if (!hDC)
    {
        MessageBox(0, ("Failed to create the device context"), ("Error"), MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }
    EGLDisplay eglDisplay = eglGetDisplay(hDC);
    EGLint iMajorVersion, iMinorVersion;
    if (!eglInitialize(eglDisplay, &iMajorVersion, &iMinorVersion))
    {
        MessageBox(0, ("eglInitialize() failed."), ("Error"), MB_OK | MB_ICONEXCLAMATION);
    }
    eglBindAPI(EGL_OPENGL_ES_API);
    EGLint iConfigs;
    EGLConfig eglConfig = 0;
    const EGLint pi32ConfigAttribs[] =
    {
        EGL_LEVEL, 
        0,
        EGL_SURFACE_TYPE, 
        EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE, 
        EGL_OPENGL_ES2_BIT,
        EGL_NATIVE_RENDERABLE, 
        EGL_FALSE,
        EGL_DEPTH_SIZE, 
        EGL_DONT_CARE,
        EGL_NONE
    };
    eglChooseConfig(eglDisplay, pi32ConfigAttribs, &eglConfig, 1, &iConfigs);
    EGLSurface eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, window, NULL);
    if (eglSurface == EGL_NO_SURFACE)
    {
        eglGetError();
        eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, NULL, NULL);
    }
    EGLint ai32ContextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
    EGLContext eglContext = eglCreateContext(eglDisplay, eglConfig, NULL, ai32ContextAttribs);
    eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);


    //SetWindowLongPtr(window, GWL_USERDATA, (LONG)(LONG_PTR)context);

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
