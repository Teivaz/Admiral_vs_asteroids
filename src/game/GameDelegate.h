#pragma once

#define USE_TEST_TRIANGLE 0

class GameDelegate
{
public:
    GameDelegate();
    ~GameDelegate();

    void init(int screenWidth, int screenHeight);
    void update(double dt);
    void render();

    void onTouchPressed(int x, int y);
    void onTouchMoved(int x, int y, int prevX, int prevY);
    void onTouchReleased(int x, int y, int prevX, int prevY);

    void applicationWillTerminate();
    void onSuspend();
    void onResume();

private:
    vec2i m_screen;

#if USE_TEST_TRIANGLE
    GLuint prog;
    GLuint buf;
#endif
};
