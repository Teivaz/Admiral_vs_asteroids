#include "Precompiled.h"
#include "GameplayState.h"

#include "Controllers/ShaderManager.h"
#include "Controllers/TextureManager.h"
#include "Controllers/Painter.h"
#include "Objects/Sprite.h"
#include "game/Objects/Sprite.h"
#include "Controllers/SpriteManager.h"

GameplayState::GameplayState()
{

}

GameplayState::~GameplayState()
{

}

void GameplayState::update(float dt)
{
    m_star->adjustRotation(dt/100);
}

void GameplayState::render()
{

}

void GameplayState::onEnter()
{
    auto simpleShader = ShaderManager::GetInstance()->getShader(shaders::k_simple);
    auto softShader = ShaderManager::GetInstance()->getShader(shaders::k_softLight);
    Sprite* s = SpriteManager::GetInstance()->createSprite(sprites::k_knob);

    m_star = SpriteManager::GetInstance()->createSprite(sprites::k_star_flare_penta);
    m_star->setPosition(-m_star->getSize() / 2);
    m_star->setScale(0.09);
    Painter::GetInstance()->add(m_star);
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
