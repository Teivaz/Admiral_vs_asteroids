#pragma once
#include "State.h"

class Sprite;
class Widget;
MakeShared(Captain);
MakeShared(Sky);

class GameplayState : public State, has_slots<>
{
public:
    GameplayState();
    virtual ~GameplayState();

    virtual void                update(double dt);
    virtual void                render();

    virtual void                onEnter();
    virtual void                onFinish();
    virtual void                pause(bool);
    virtual bool                isFinished() const;
    
    void                        addLocalControlledPlayer(CaptainPtr player);

    // Events

    signal1<bool>               onButton;
    signal1<double>              onSliderLeft;
    signal1<double>              onSliderRight;

//    signal2<int, 

private:
    void                        _setMovingSpeed(vec2d);

private:
    bool                        m_isFinished = false;

    vec2d                       m_movingDirection;
    double                       m_movingSpeed = 0;
	GameObject*                 m_star = nullptr;
    Widget*                     m_gui = nullptr;
    GameObject*                 m_laserBeam = nullptr;

    vector<CaptainPtr>          m_players;
	SkyPtr						m_sky;
};
