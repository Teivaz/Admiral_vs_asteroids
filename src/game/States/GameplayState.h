#pragma once
#include "State.h"

class Sprite;
class Widget;
MakeShared(Captain);

class GameplayState : public State, has_slots<>
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
    
    void                        addLocalControlledPlayer(CaptainPtr player);

    // Events

    signal1<bool>               onButton;
    signal1<float>              onSliderLeft;
    signal1<float>              onSliderRight;

//    signal2<int, 

private:
    void                        _setMovingSpeed(vec2f);

private:
    bool                        m_isFinished = false;

    vec2f                       m_movingDirection;
    float                       m_movingSpeed = 0;
	GameObject*                 m_star = nullptr;
    Widget*                     m_gui = nullptr;
    GameObject*                 m_laserBeam = nullptr;

    vector<CaptainPtr>          m_players;
};
