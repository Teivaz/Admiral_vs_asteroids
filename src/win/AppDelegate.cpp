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
    GuiManager::GetInstance()->setAppSize(rectangle.right - rectangle.left, rectangle.bottom - rectangle.top);

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
