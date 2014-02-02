#include "Precompiled.h"
#include "ButtonWidget.h"
#include "../Sprite.h"

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

bool ButtonWidget::isPointInside(const vec2f& pt)
{
    return m_spriteIdle->isPointInside(pt);
}
