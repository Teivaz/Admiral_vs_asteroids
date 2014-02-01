#pragma once
#include "State.h"

//class 

class GameplayState : public State
{
public:
    GameplayState();
    virtual ~GameplayState();

    virtual void                update(float dt);
    virtual void                render();

    virtual void                onEnter();
    virtual void                onFinish();
    virtual void                pause(bool);
    virtual bool                isFinished() const;

private:
    bool                        m_isFinished = false;


    GameObject*                 m_star = nullptr;

};
