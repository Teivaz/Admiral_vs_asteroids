#include "Precompiled.h"
#include "GameplayState.h"

#include "Controllers/ShaderManager.h"
#include "Controllers/TextureManager.h"
#include "Controllers/Painter.h"
#include "Objects/Sprite.h"
#include "game/Objects/Sprite.h"

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
    auto t = TextureManager::GetInstance()->getTexture(textures::k_stars_back);

    Painter::GetInstance()->add(new Sprite(t, vec2f(0), vec2f(1), simpleShader));

    t = TextureManager::GetInstance()->getTexture(textures::k_star_flare_penta);

    m_star = new Sprite(t, vec2f(0), vec2f(1), softShader);
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
