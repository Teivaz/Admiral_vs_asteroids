#pragma once
#include "Widget.h"

class ProgressBarWidget : public Widget
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
    ProgressBarWidget(Sprite* back, Sprite* full, const string& name, double value);
    virtual ~ProgressBarWidget();

    virtual void                setPosition(const vec2d&);
    virtual void                setScale(const vec2d&);
    virtual void                render();

    double                      getValue()
    {
        return m_value;
    }

private:
    bool                        _isPointInside(const vec2d&);
    void                        _onButton(bool);

private:
    Sprite*                     m_spriteBack = nullptr;
    Sprite*                     m_spriteFull = nullptr;
    double                      m_value = 0.0f;
};
