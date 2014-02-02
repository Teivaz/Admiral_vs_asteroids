#pragma once
#include "State.h"

class Sprite;
class Widget;

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

    virtual void                onTouchPressed(vec2f, bool leftButton, bool RightButton);
    virtual void                onTouchMoved(vec2f, bool leftButton, bool RightButton);
    virtual void                onTouchReleased(vec2f, bool leftButton, bool RightButton);

private:
    bool                        m_isFinished = false;


    Sprite*                     m_star = nullptr;
    Widget*                     m_gui = nullptr;
};
