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

GameDelegate::GameDelegate()
{}

GameDelegate::~GameDelegate()
{    
}

void GameDelegate::init(int width, int height)
{
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
