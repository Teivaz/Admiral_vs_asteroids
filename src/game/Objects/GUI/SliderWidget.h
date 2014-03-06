#pragma once
#include "Widget.h"

class SliderWidget : public Widget
{
public:
    class CallbackFunctor
    {
    public:
        virtual ~CallbackFunctor(){}
        virtual void operator()(double)
        {}
    };
public:
    SliderWidget(Sprite*, const string& name, const vec2d& travel, double value = 0.0f);
    virtual ~SliderWidget();

    virtual void                setPosition(const vec2d&);
    virtual void                setScale(const vec2d&);
    virtual void                render();

    double                       getProgress()
    {
        return m_progress;
    }
    void                        setProgress(double);

    virtual void                onTouchBegan(TouchPtr);
    virtual void                onTouchMoved(TouchPtr);
    virtual void                onTouchEnded(TouchPtr);

    void                        setCallback(CallbackFunctor*);

private:
    bool                        _isPointInside(const vec2d&);

private:
    Sprite*                     m_sprite = nullptr;
    double                       m_progress = 0.0f;
    double                       m_default = 0.0f;
    CallbackFunctor*            m_callback = nullptr;
    vec2d                       m_travel;
    vec2d                       m_origin;
};
