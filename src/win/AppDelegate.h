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
};