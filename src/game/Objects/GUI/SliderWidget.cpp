#include "Precompiled.h"
#include "SliderWidget.h"
#include "../Sprite.h"
#include "Controllers/Touch.h"

SliderWidget::SliderWidget(Sprite* sprite, const string& name, const vec2d& travel, double value/* = 0*/)
: m_sprite(sprite)
, m_default(value)
, m_travel(travel)
, m_origin(sprite->getPosition())
{
    m_name = name;
    setProgress(value);
}

SliderWidget::~SliderWidget()
{
    delete m_sprite;
    delete m_callback;
}

void SliderWidget::setPosition(const vec2d& p)
{
    m_sprite->setPosition(p);
}
void SliderWidget::setScale(const vec2d& s)
{
    m_sprite->setScale(s);
}
void SliderWidget::render()
{
    m_sprite->render();
    Widget::render();
}

void SliderWidget::onTouchBegan(TouchPtr t)
{
    if (t->isConsumed())
    {
        return;
    }
    if (_isPointInside(t->startPoint()))
    {
        t->consume(this);
    }
}

void SliderWidget::onTouchMoved(TouchPtr t)
{
    vec2d travel = t->currentPoint() - m_origin;
    double p = m_travel.Dot(travel);
    p /= m_travel.SqLength();
    setProgress(p);
}

void SliderWidget::onTouchEnded(TouchPtr t)
{
    setProgress(m_default);
}

void SliderWidget::setCallback(CallbackFunctor* c)
{
    ASSERT(m_callback == nullptr);
    m_callback = c;
}

bool SliderWidget::_isPointInside(const vec2d& p)
{
    return m_sprite->isPointInside(p);
}

void SliderWidget::setProgress(double p)
{
    p = max(0.0, p);
    p = min(1.0, p);
    m_progress = p;
    m_sprite->setPosition(m_origin + m_travel*p);
    if (m_callback)
    {
        (*m_callback)(p);
    }
}
