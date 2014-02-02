#include "Precompiled.h"
#include "GameplayState.h"

#include "Controllers/ShaderManager.h"
#include "Controllers/TextureManager.h"
#include "Controllers/Painter.h"
#include "Objects/Sprite.h"
#include "game/Objects/Sprite.h"
#include "Controllers/SpriteManager.h"
#include "Objects/GUI/GuiManager.h"
#include "Objects/GUI/Widget.h"
#include "Objects/GUI/ButtonWidget.h"

GameplayState::GameplayState()
{

}

GameplayState::~GameplayState()
{

}

void GameplayState::update(float dt)
{
    m_star->adjustRotation(dt/1000);
}

void GameplayState::render()
{
    m_gui->render();
}

void GameplayState::onEnter()
{

    SpriteManager::GetInstance()->createSprite(sprites::k_stars_back, -1, 2, true, 1);

    auto simpleShader = ShaderManager::GetInstance()->getShader(shaders::k_simple);
    auto softShader = ShaderManager::GetInstance()->getShader(shaders::k_softLight);
    Sprite* s = SpriteManager::GetInstance()->createSprite(sprites::k_knob, 0, 1.1);

    m_star = SpriteManager::GetInstance()->createSprite(sprites::k_star_flare_penta, 0, 1.1);
    m_star->setPosition(-m_star->getSize() / 2);
    m_star->setShader(softShader);
    Painter::GetInstance()->add(m_star);

    m_gui = GuiManager::GetInstance()->LoadGui("gui.json");
}

void GameplayState::onFinish()
{

}

void GameplayState::pause(bool)
{

}

bool GameplayState::isFinished() const
{
    return m_isFinished;
}

void GameplayState::onTouchPressed(vec2f pos, bool leftButton, bool RightButton)
{
    ButtonWidget* b = static_cast<ButtonWidget*>(m_gui->findChildByName("fire!"));
    b->setPressed(b->isPointInside(pos));
}

void GameplayState::onTouchMoved(vec2f, bool leftButton, bool RightButton)
{

}

void GameplayState::onTouchReleased(vec2f, bool leftButton, bool RightButton)
{
    ButtonWidget* b = static_cast<ButtonWidget*>(m_gui->findChildByName("fire!"));
    b->setPressed(false);
}
