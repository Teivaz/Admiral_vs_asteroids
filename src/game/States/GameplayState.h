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
    
    void                        onButton(bool);
    void                        onSlider(int, float);
private:
    void                        _setMovingSpeed(vec2f);

private:
    bool                        m_isFinished = false;

    vec2f                       m_movingDirection;
    float                       m_movingSpeed = 0;
    Sprite*                     m_star = nullptr;
    Widget*                     m_gui = nullptr;
};
