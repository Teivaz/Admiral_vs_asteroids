#pragma once

class GameDelegate
{
public:
    GameDelegate();
    ~GameDelegate();

    void init(int screenWidth, int screenHeight);
    void update(float dt);
    void render();

    void onTouchPressed(int x, int y);
    void onTouchMoved(int x, int y, int prevX, int prevY);
    void onTouchReleased(int x, int y, int prevX, int prevY);

    void applicationWillTerminate();
    void onSuspend();
    void onResume();

private:
    vec2i m_screen;
};
