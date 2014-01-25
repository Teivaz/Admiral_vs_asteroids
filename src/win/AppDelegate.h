#pragma once

class AppDelegate
{
public:
    EGLNativeWindowType window = nullptr;

    void Update(float dt);
    void Render();
};