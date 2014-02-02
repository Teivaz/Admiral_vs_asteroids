#include "Precompiled.h"
#include "ButtonWidget.h"
#include "../Sprite.h"
#include "Controllers/Touch.h"

ButtonWidget::ButtonWidget(Sprite* idle, Sprite* pressed, const string& name)
: m_spriteIdle(idle)
, m_spritePressed(pressed)
{
    m_name = name;
}

ButtonWidget::~ButtonWidget()
{
    delete m_spriteIdle;
    delete m_spritePressed;
    delete m_callback;
}

void ButtonWidget::setPosition(const vec2f& p)
{
    m_spriteIdle->setPosition(p);
    m_spritePressed->setPosition(p);
    Widget::setPosition(p);
}

void ButtonWidget::setScale(const vec2f& s)
{
    m_spriteIdle->setScale(s);
    m_spritePressed->setScale(s);
    Widget::setScale(s);
}

void ButtonWidget::render()
{
    if (m_pressed)
    {
        m_spritePressed->render();
    }
    else
    {
        m_spriteIdle->render();
    }
    Widget::render();
}

bool ButtonWidget::_isPointInside(const vec2f& pt)
{
    return m_spriteIdle->isPointInside(pt);
}

void ButtonWidget::onTouchBegan(Touch* t)
{
    if (t->isConsumed())
        return;
    if (_isPointInside(t->startPoint()))
    {
        t->consume(this);
        _onButton(true);
    }
    else
    {
        Widget::onTouchBegan(t);
    }
}

void ButtonWidget::onTouchMoved(Touch* t)
{
}

void ButtonWidget::onTouchEnded(Touch* t)
{
    _onButton(false);
}

void ButtonWidget::_onButton(bool value)
{
    m_pressed = value;
    if (m_callback)
    {
        (*m_callback)(value);
    }
}

void ButtonWidget::setCallback(CallbackFunctor* c)
{
    ASSERT(m_callback == nullptr && "Single callback only avaliable");
    m_callback = c;
}
