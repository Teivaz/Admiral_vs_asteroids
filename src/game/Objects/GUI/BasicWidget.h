#pragma once
#include "Widget.h"

class BasicWidget : public Widget
{
public:
    BasicWidget(Sprite*, const string& name);
    virtual ~BasicWidget();

    virtual void                setPosition(const vec2f&);
    virtual void                setScale(const vec2f&);
    virtual void                render();

private:
    Sprite*                     m_sprite = nullptr;
};