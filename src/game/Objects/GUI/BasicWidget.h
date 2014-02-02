#pragma once
#include "Widget.h"

class BasicWidget : public Widget
{
public:
    BasicWidget(Sprite*, const string& name);
    virtual ~BasicWidget();
    
    Sprite*                     getSprite();
    virtual void                setAnchor(vec2f);
    virtual void                setAllign(EAllignX, EAllignY);
    virtual void                setOffset(vec2f);
    virtual void                setScale(vec2f);
    virtual void                render();

private:
    Sprite*                     m_sprite = nullptr;
};