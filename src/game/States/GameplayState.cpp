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
#include "Objects/GUI/ProgressBarWidget.h"
#include "Controllers/TouchManager.h"

#include "Objects/Scene/Captain.h"
#include "Objects/Scene/CaptainsBridge.h"
#include "Objects/Scene/Sky.h"

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
    virtual void operator()(double val)
    {
        if (n == 1)
            state->onSliderLeft(val * 2 - 1);
        else
            state->onSliderRight(val * 2 - 1);
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

void GameplayState::update(double dt)
{
	for (auto player : m_players)
	{
		player->update(dt);
	}
    ProgressBarWidget* pb = static_cast<ProgressBarWidget*>(m_gui->findChildByName("rightBar2"));
    pb->setValue(m_players.front()->getShipMoveSpeed().Length() / 100.0);
	m_sky->update(dt);
}

void GameplayState::render()
{
}

void GameplayState::onEnter()
{
    CaptainPtr player = CaptainPtr(new Captain("Sheppard", "envader.ship"));
    m_players.push_back(player);

    addLocalControlledPlayer(player);

//    SpriteManager::GetInstance()->createSprite(sprites::k_stars_back, -1, 2, true, -100);

    auto softShader = ShaderManager::GetInstance()->getShader(shaders::k_softLight);


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

	m_sky.reset(new Sky);
	Painter::GetInstance()->onCameraMoved.connect(m_sky.get(), &Sky::onCameraMoved);
	m_sky->setRenderLayer(-1000);
	Painter::GetInstance()->add(m_sky.get());
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

void GameplayState::addLocalControlledPlayer(CaptainPtr player)
{
    onButton.connect(player.get(), &Captain::shoot);
    onSliderLeft.connect(player.get(), &Captain::rotate);
    onSliderRight.connect(player.get(), &Captain::setMainEnginePower);
	player->onMoved.connect(Painter::GetInstance(), &Painter::setSceneCameraPosition);
}
