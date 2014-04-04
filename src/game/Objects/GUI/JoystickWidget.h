#pragma once
#include "Widget.h"

class JoystickWidget : public Widget
{
public:
    class CallbackFunctor
    {
    public:
        virtual ~CallbackFunctor(){};
        virtual void operator()(bool)
        {}
    };
public:
    JoystickWidget(Sprite* idle, Sprite* pressed, const string& name);
    virtual ~JoystickWidget();

    virtual void                setPosition(const vec2d&);
    virtual void                setScale(const vec2d&);
    virtual void                render();

    bool                        isPressed()
    {
        return m_pressed;
    }
    
    virtual void                onTouchBegan(TouchPtr);
    virtual void                onTouchMoved(TouchPtr);
    virtual void                onTouchEnded(TouchPtr);

    void                        setCallback(CallbackFunctor*);

private:
    bool                        _isPointInside(const vec2d&);
    void                        _onButton(bool);

private:
    Sprite*                     m_spriteIdle = nullptr;
    Sprite*                     m_spritePressed = nullptr;
    bool                        m_pressed = false;
    CallbackFunctor*            m_callback = nullptr;
};
