#pragma once
#include "Widget.h"

class SliderWidget : public Widget
{
public:
    class CallbackFunctor
    {
    public:
        virtual ~CallbackFunctor(){}
        virtual void operator()(float)
        {}
    };
public:
    SliderWidget(Sprite*, const string& name, const vec2f& travel, float value = 0.0f);
    virtual ~SliderWidget();

    virtual void                setPosition(const vec2f&);
    virtual void                setScale(const vec2f&);
    virtual void                render();

    float                       getProgress()
    {
        return m_progress;
    }
    void                        setProgress(float);

    virtual void                onTouchBegan(Touch*);
    virtual void                onTouchMoved(Touch*);
    virtual void                onTouchEnded(Touch*);

    void                        setCallback(CallbackFunctor*);

private:
    bool                        _isPointInside(const vec2f&);

private:
    Sprite*                     m_sprite = nullptr;
    float                       m_progress = 0.0f;
    float                       m_default = 0.0f;
    CallbackFunctor*            m_callback = nullptr;
    vec2f                       m_travel;
    vec2f                       m_origin;
};
