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
#include "Objects/GUI/SliderWidget.h"
#include "Controllers/TouchManager.h"
#include "Objects/Scene/LaserBeam.h"
#include "Objects/Scene/Ship.h"

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

class SliderCallBack : public SliderWidget::CallbackFunctor
{
public:
    SliderCallBack(int _n, GameplayState* _state) : n(_n), state(_state) {}
    virtual void operator()(float val)
    {
        state->onSlider(n, val);
    }
private:
    GameplayState* state;
    int n;
};

GameplayState::GameplayState()
{

}

GameplayState::~GameplayState()
{
    delete m_gui;
    delete m_star;
}

void GameplayState::update(float dt)
{
    m_star->adjustRotation(m_movingSpeed* dt / 1000);

    m_ship->update(dt);
}

void GameplayState::render()
{
//    m_gui->render();
}

void GameplayState::onEnter()
{
    SpriteManager::GetInstance()->createSprite(sprites::k_stars_back, -1, 2, true, -100);

    auto softShader = ShaderManager::GetInstance()->getShader(shaders::k_softLight);

    m_star = SpriteManager::GetInstance()->createSprite(sprites::k_star_flare_penta, 0, 1.1f, false, 0);
    m_star->setPosition(-m_star->getSize() / 2);
    m_star->setShader(softShader);
    //Painter::GetInstance()->add(m_star);

    m_gui = GuiManager::GetInstance()->LoadGui("gui.json");
    TouchManager::GetInstance()->addReceiever(m_gui);
    ButtonWidget* btn = static_cast<ButtonWidget*>(m_gui->findChildByName("fire!"));
    if (btn)
    {
        btn->setCallback(new ButtonCallBack(this));
    }
    SliderWidget* sl = static_cast<SliderWidget*>(m_gui->findChildByName("rotate"));
    if (sl)
    {
        sl->setCallback(new SliderCallBack(1, this));
    }
    sl = static_cast<SliderWidget*>(m_gui->findChildByName("move"));
    if (sl)
    {
        sl->setCallback(new SliderCallBack(2, this));
    }
    Painter::GetInstance()->add(m_gui);

    m_ship.reset(new Ship);
	m_ship->setCamera(Painter::GetInstance()->getSceneCamera());
    Painter::GetInstance()->add(m_ship.get());
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

void GameplayState::onButton(bool b)
{
    m_star->adjustPosition(b?0.1f:-0.1f);
    if (b)
        m_ship->shoot();
}

void GameplayState::onSlider(int n, float v)
{
    if (n == 1)
    {
        m_ship->setRotationSpeed(2 * (v - 0.5f));
    }
    else
    {
        m_ship->setEnginePower(2 * (v - 0.5f));
    }
}
