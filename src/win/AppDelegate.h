#pragma once

class AppDelegate
{
public:
    EGLNativeWindowType window = nullptr;
    EGLSurface surface = nullptr;
    EGLDisplay display = nullptr;

    void Init();
    void Update(float dt);
    void Render();
    
    void onTouchPressed(int x, int y, bool leftButton, bool RightButton);
    void onTouchMoved(int x, int y, bool leftButton, bool RightButton);
    void onTouchReleased(int x, int y, bool leftButton, bool RightButton);

private:
    bool m_initialized = false;
    vec2i m_screen;
};