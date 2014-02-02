#pragma once
#include "Widget.h"

class ButtonWidget : public Widget
{
public:
    ButtonWidget(Sprite* idle, Sprite* pressed, const string& name);
    virtual ~ButtonWidget();

    virtual void                setPosition(const vec2f&);
    virtual void                setScale(const vec2f&);
    virtual void                render();

    bool                        isPointInside(const vec2f&);
    void                        setPressed(bool s)
    {
        m_pressed = s;
    }

private:
    Sprite*                     m_spriteIdle = nullptr;
    Sprite*                     m_spritePressed = nullptr;
    bool                        m_pressed = false;
};
