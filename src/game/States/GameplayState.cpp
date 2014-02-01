#include "Precompiled.h"
#include "GameplayState.h"

#include "Controllers/ShaderManager.h"
#include "Controllers/TextureManager.h"
#include "Controllers/Painter.h"
#include "Objects/Sprite.h"

GameplayState::GameplayState()
{

}

GameplayState::~GameplayState()
{

}

void GameplayState::update(float dt)
{
    PLOG("dt = %f\n", dt);
    m_star->adjustRotation(dt);
}

void GameplayState::render()
{

}

void GameplayState::onEnter()
{
    auto s = ShaderManager::GetInstance()->getShader(shaders::k_simple);
    auto t = TextureManager::GetInstance()->getTexture(textures::k_stars_back);
    Painter::GetInstance()->add(new Sprite(t, vec2f(0), vec2f(1), s));
    t = TextureManager::GetInstance()->getTexture("star_flare_penta.png");

    m_star = new Sprite(t, vec2f(0), vec2f(1));
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
