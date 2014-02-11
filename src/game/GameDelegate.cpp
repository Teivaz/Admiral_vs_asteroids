#include "Precompiled.h"
#include "GameDelegate.h"
#include "utils/FileUtils.h"

#include "States/StateMachine.h"
#include "States/GameplayState.h"
#include "Controllers/ShaderManager.h"
#include "Controllers/TextureManager.h"
#include "Controllers/Painter.h"
#include "Controllers/SpriteManager.h"
#include "Objects/GUI/GuiManager.h"
#include "Controllers/TouchManager.h"

#if USE_TEST_TRIANGLE
static const char* vsc = "\
attribute vec2 pos;\
void main()\
{ gl_Position =  vec4(pos, 0.0, 1.0); }";
static const char* fsc = "\
precision mediump float;\
void main()\
{ gl_FragColor =  vec4(1.0, 0.0, 0.0, 1.0); }";
#endif

GameDelegate::GameDelegate()
{}

GameDelegate::~GameDelegate()
{
    StateMachine::DeleteInstance();
    Painter::DeleteInstance();
    ShaderManager::DeleteInstance();
    TextureManager::DeleteInstance();
    SpriteManager::DeleteInstance();
    GuiManager::DeleteInstance();
    TouchManager::DeleteInstance();

#if USE_TEST_TRIANGLE
    glDeleteBuffers(1, &buf);
    glDeleteProgram(prog);
#endif
}

void GameDelegate::init(int width, int height)
{

#if USE_TEST_TRIANGLE
    GLint status;
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vs, 1, &vsc, NULL);
    glShaderSource(fs, 1, &fsc, NULL);
    glCompileShader(vs);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
    prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glBindAttribLocation(prog, 10, "pos");
    glLinkProgram(prog);
    glEnableVertexAttribArray(10);
    glGetProgramiv(prog, GL_LINK_STATUS, &status);
    glGenBuffers(1, &buf);
    glBindBuffer(GL_ARRAY_BUFFER, buf);
    float verts[6] = { -0.5, -0.5, 0, 0.5, 0.5, -0.5 };
    //float verts[6] = { -1, -1, 0, 1, 1, -1 };
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), verts, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteShader(vs);
    glDeleteShader(fs);
#endif

    m_screen = vec2i(width, height);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    Painter::CreateInstance();
    StateMachine::CreateInstance();
    ShaderManager::CreateInstance();
    TextureManager::CreateInstance();
    SpriteManager::CreateInstance();
    GuiManager::CreateInstance();
    TouchManager::CreateInstance();

    GuiManager::GetInstance()->setAppSize(m_screen.x, m_screen.y);

    // loading
    SpriteManager::GetInstance()->loadAtlas("sprites.json");
    StateMachine::GetInstance()->pushState(new GameplayState);

}

void GameDelegate::update(float dt)
{
    StateMachine::GetInstance()->update(dt);
    Painter::GetInstance()->update(dt);
}

void GameDelegate::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    Painter::GetInstance()->render();
    StateMachine::GetInstance()->render();

#if USE_TEST_TRIANGLE
    GLint params;
    glBindBuffer(GL_ARRAY_BUFFER, buf);
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &params);
    glUseProgram(prog);
    glEnableVertexAttribArray(10);
    glVertexAttribPointer(10, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &params);
    glDrawArrays(GL_TRIANGLES, 0, 3);
#endif

}

void GameDelegate::onTouchPressed(int x, int y)
{
    vec2f pos = vec2f(static_cast<float>(x), m_screen.y - static_cast<float>(y));
    pos.x /= m_screen.x;
    pos.y /= m_screen.y;
    pos *= 2.0f;
    pos -= 1.0f;
    TouchManager::GetInstance()->onTouchBegan(pos);
}

void GameDelegate::onTouchMoved(int x, int y, int prevX, int prevY)
{
    vec2f pos = vec2f(static_cast<float>(x), m_screen.y - static_cast<float>(y));
    pos.x /= m_screen.x;
    pos.y /= m_screen.y;
    pos *= 2.0f;
    pos -= 1.0f;
    vec2f prevPos = vec2f(static_cast<float>(prevX), m_screen.y - static_cast<float>(prevY));
    prevPos.x /= m_screen.x;
    prevPos.y /= m_screen.y;
    prevPos *= 2.0f;
    prevPos -= 1.0f;
    TouchManager::GetInstance()->onTouchMoved(pos, prevPos);
}

void GameDelegate::onTouchReleased(int x, int y, int prevX, int prevY)
{
    vec2f pos = vec2f(static_cast<float>(x), m_screen.y - static_cast<float>(y));
    pos.x /= m_screen.x;
    pos.y /= m_screen.y;
    pos *= 2.0f;
    pos -= 1.0f;
    vec2f prevPos = vec2f(static_cast<float>(x), m_screen.y - static_cast<float>(y));
    prevPos.x /= m_screen.x;
    prevPos.y /= m_screen.y;
    prevPos *= 2.0f;
    prevPos -= 1.0f;
    TouchManager::GetInstance()->onTouchEnded(pos, prevPos);
}

void GameDelegate::applicationWillTerminate()
{

}

void GameDelegate::onSuspend()
{

}

void GameDelegate::onResume()
{

}
