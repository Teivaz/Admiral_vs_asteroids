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
#include "Controllers/TouchManager.h"

class ButtonCallBack : public ButtonWidget::CallbackFunctor
{
public:
    ButtonCallBack(GameplayState*_state) :state(_state){}
    virtual void operator()(bool btn)
    {
        state->onButton(btn);
    }
private:
    GameplayState* state;
};

GameplayState::GameplayState()
{

}

GameplayState::~GameplayState()
{

}

void GameplayState::update(float dt)
{
    m_star->adjustRotation(dt/1000);
    m_star->adjustPosition(m_movingSpeed * dt);
}

void GameplayState::render()
{
    m_gui->render();
}

void GameplayState::onEnter()
{

    SpriteManager::GetInstance()->createSprite(sprites::k_stars_back, -1, 2, true, 1);

    auto softShader = ShaderManager::GetInstance()->getShader(shaders::k_softLight);

    m_star = SpriteManager::GetInstance()->createSprite(sprites::k_star_flare_penta, 0, 1.1, true, 0);
    m_star->setPosition(-m_star->getSize() / 2);
    m_star->setShader(softShader);
    Painter::GetInstance()->add(m_star);

    m_gui = GuiManager::GetInstance()->LoadGui("gui.json");
    TouchManager::GetInstance()->addReceiever(m_gui);
    ButtonWidget* btn = static_cast<ButtonWidget*>(m_gui->findChildByName("fire!"));
    if (btn)
    {
        btn->setCallback(new ButtonCallBack(this));
    }
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

void GameplayState::_setMovingSpeed(vec2f speed)
{
    //m_movingSpeed = speed;
}

void GameplayState::onButton(bool b)
{
    m_star->adjustPosition(b?0.1:-0.1);
}
