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

}

void GameplayState::render()
{

}

void GameplayState::onEnter()
{
    ShaderManager::GetInstance()->getShader(shaders::k_simple_shader);
    auto t = TextureManager::GetInstance()->getTexture(textures::k_stars_back);
    Painter::GetInstance()->add(new Sprite(t, vec2f(0), vec2f(1)));
    t = TextureManager::GetInstance()->getTexture(textures::k_stars_level2);
    Painter::GetInstance()->add(new Sprite(t, vec2f(0), vec2f(1)));
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
