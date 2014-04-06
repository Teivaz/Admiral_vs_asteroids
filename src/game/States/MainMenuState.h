#pragma once
#include "State.h"

class Sprite;
class Widget;
MakeShared(Captain);
MakeShared(Sky);

class MainMenuState : public State, public has_slots<>
{
public:
    MainMenuState();
    virtual ~MainMenuState();

    virtual void                update(double dt);
    virtual void                render();

    virtual void                onEnter();
    virtual void                onFinish();
    virtual void                pause(bool);
    virtual bool                isFinished() const;
    
    // Events

    void                        onSingleButton(bool);
    void                        onMultiButton(bool);
    void                        onSettingsButton(bool);
    void                        onAboutButton(bool);

private:
    bool                        m_isFinished = false;

    Widget*                     m_gui = nullptr;
};
