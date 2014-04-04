#include "Precompiled.h"
#include "JoystickWidget.h"
#include "../Sprite.h"
#include "Controllers/Touch.h"

JoystickWidget::JoystickWidget(Sprite* idle, Sprite* pressed, const string& name)
: m_spriteIdle(idle)
, m_spritePressed(pressed)
{
    m_name = name;
}

JoystickWidget::~JoystickWidget()
{
    delete m_spriteIdle;
    delete m_spritePressed;
    delete m_callback;
}

void JoystickWidget::setPosition(const vec2d& p)
{
    m_spriteIdle->setPosition(p);
    m_spritePressed->setPosition(p);
    Widget::setPosition(p);
}

void JoystickWidget::setScale(const vec2d& s)
{
    m_spriteIdle->setScale(s);
    m_spritePressed->setScale(s);
    Widget::setScale(s);
}

void JoystickWidget::render()
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

bool JoystickWidget::_isPointInside(const vec2d& pt)
{
    return m_spriteIdle->isPointInside(pt);
}

void JoystickWidget::onTouchBegan(TouchPtr t)
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

void JoystickWidget::onTouchMoved(TouchPtr t)
{
}

void JoystickWidget::onTouchEnded(TouchPtr t)
{
    _onButton(false);
}

void JoystickWidget::_onButton(bool value)
{
    m_pressed = value;
    if (m_callback)
    {
        (*m_callback)(value);
    }
}

void JoystickWidget::setCallback(CallbackFunctor* c)
{
    ASSERT(m_callback == nullptr && "Single callback only avaliable");
    m_callback = c;
}
