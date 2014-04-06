#include "Precompiled.h"
#include "MainMenuState.h"


#include "Controllers/Painter.h"
#include "Objects/GUI/ButtonWidget.h"
#include "Objects/GUI/SliderWidget.h"
#include "Objects/GUI/GuiManager.h"
#include "Controllers/TouchManager.h"

#include "GameplayState.h"
#include "StateMachine.h"

MainMenuState::MainMenuState()
{
}

MainMenuState::~MainMenuState()
{
    delete m_gui;
}

void MainMenuState::update(double dt)
{
}

void MainMenuState::render()
{
}

void MainMenuState::onEnter()
{
    m_gui = GuiManager::GetInstance()->LoadGui("main_menu.json");
    TouchManager::GetInstance()->addReceiever(m_gui);
    ButtonWidget* btn = static_cast<ButtonWidget*>(m_gui->findChildByName("single"));
    if (btn)
    {
        btn->onChanged.connect(this, &MainMenuState::onSingleButton);
    }
    btn = static_cast<ButtonWidget*>(m_gui->findChildByName("multi"));
    if (btn)
    {
        btn->onChanged.connect(this, &MainMenuState::onMultiButton);
    }
    Painter::GetInstance()->add(m_gui);
}

void MainMenuState::onFinish()
{
}

void MainMenuState::pause(bool)
{
}

bool MainMenuState::isFinished() const
{
    return m_isFinished;
}

void MainMenuState::onSingleButton(bool pressed)
{
    if (!pressed)
    {
        StateMachine::GetInstance()->pushState(new GameplayState);
        m_isFinished = true;
    }
}
void MainMenuState::onMultiButton(bool pressed)
{
    if (!pressed)
    {
        //StateMachine::GetInstance()->pushState(new GameplayState);
        //m_isFinished = true;
    }
}
void MainMenuState::onSettingsButton(bool pressed)
{
    if (!pressed)
    {
        //StateMachine::GetInstance()->pushState(new GameplayState);
        //m_isFinished = true;
    }
}
void MainMenuState::onAboutButton(bool pressed)
{

}