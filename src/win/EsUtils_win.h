#pragma once

class AppDelegate;

LRESULT WINAPI ESWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
GLboolean CreateGLWindowWithContext(AppDelegate *d, const char *title, int w, int h);
GLboolean CreateGLWindowWithContext(AppDelegate *d, const char *title, int w, int h, HINSTANCE hInstance);
void WindowLoop(AppDelegate* d);
