#include "Precompiled.h"
#include "AppDelegate.h"
#include "utils/FileUtils.h"

#include "States/StateMachine.h"
#include "States/GameplayState.h"
#include "Controllers/ShaderManager.h"
#include "Controllers/TextureManager.h"

void AppDelegate::Init()
{
    StateMachine::CreateInstance();
    ShaderManager::CreateInstance();
    TextureManager::CreateInstance();

    //GameplayState s;
    StateMachine::GetInstance()->pushState(new GameplayState);
}

void AppDelegate::Update(float dt)
{
    StateMachine::GetInstance()->update(dt);
}

void AppDelegate::Render()
{
    StateMachine::GetInstance()->render();
}
