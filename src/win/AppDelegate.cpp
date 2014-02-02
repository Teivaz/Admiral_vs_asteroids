#include "Precompiled.h"
#include "AppDelegate.h"
#include "utils/FileUtils.h"

#include "States/StateMachine.h"
#include "States/GameplayState.h"
#include "Controllers/ShaderManager.h"
#include "Controllers/TextureManager.h"
#include "Controllers/Painter.h"
#include "Controllers/SpriteManager.h"
#include "Objects/GUI/GuiManager.h"

void AppDelegate::Init()
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    Painter::SetInstance(new Painter);
    StateMachine::SetInstance(new StateMachine);
    ShaderManager::SetInstance(new ShaderManager);
    TextureManager::SetInstance(new TextureManager);
    SpriteManager::SetInstance(new SpriteManager);
    GuiManager::SetInstance(new GuiManager);

    RECT rectangle;
    GetClientRect(window, &rectangle);
    m_screen = vec2i(rectangle.right - rectangle.left, rectangle.bottom - rectangle.top);
    GuiManager::GetInstance()->setAppSize(m_screen.x, m_screen.y);

    SpriteManager::GetInstance()->loadAtlas("sprites.json");

    //GameplayState s;
    StateMachine::GetInstance()->pushState(new GameplayState);
    m_initialized = true;
}

void AppDelegate::Update(float dt)
{
    if (!m_initialized)
    {
        return;
    }
    StateMachine::GetInstance()->update(dt);
}

void AppDelegate::Render()
{
    if (!m_initialized)
    {
        return;
    }

    glClear(GL_COLOR_BUFFER_BIT);
    Painter::GetInstance()->render();
    StateMachine::GetInstance()->render();
    eglSwapBuffers(display, surface);
}


void AppDelegate::onTouchPressed(int x, int y, bool leftButton, bool RightButton)
{
    State* state = StateMachine::GetInstance()->getCurrentState();
    if (state)
    {
        vec2f pos = vec2f(x, m_screen.y - y);
        pos.x /= m_screen.x;
        pos.y /= m_screen.y;
        pos *= 2.0f;
        pos -= 1.0f;
        state->onTouchPressed(pos, leftButton, RightButton);
    }
}

void AppDelegate::onTouchMoved(int x, int y, bool leftButton, bool RightButton)
{
    State* state = StateMachine::GetInstance()->getCurrentState();
    if (state)
    {
        vec2f pos = vec2f(x, m_screen.y - y);
        pos.x /= m_screen.x;
        pos.y /= m_screen.y;
        pos *= 2.0f;
        pos -= 1.0f;
        state->onTouchMoved(pos, leftButton, RightButton);
    }
}

void AppDelegate::onTouchReleased(int x, int y, bool leftButton, bool RightButton)
{
    State* state = StateMachine::GetInstance()->getCurrentState();
    if (state)
    {
        vec2f pos = vec2f(x, m_screen.y - y);
        pos.x /= m_screen.x;
        pos.y /= m_screen.y;
        pos *= 2.0f;
        pos -= 1.0f;
        state->onTouchReleased(pos, leftButton, RightButton);
    }
}

