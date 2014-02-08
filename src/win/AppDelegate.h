#pragma once

class GameDelegate;

class AppDelegate
{
public:
    AppDelegate();
    ~AppDelegate();

    EGLNativeWindowType window = nullptr;
    EGLSurface surface = nullptr;
    EGLDisplay display = nullptr;
    bool done = false;

    void Init();
    void Update(float dt);
    void Render();
    
    void onTouchPressed(int x, int y);
    void onTouchMoved(int x, int y);
    void onTouchReleased(int x, int y);

    void ApplicationWillTerminate();
    void OnSuspend();
    void OnResume();

private:
    bool m_initialized = false;
    vec2i m_screen;
    GameDelegate* m_gameDelegate = nullptr;
};