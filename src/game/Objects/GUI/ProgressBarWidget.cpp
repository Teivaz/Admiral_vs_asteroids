#include "Precompiled.h"
#include "ProgressBarWidget.h"
#include "../Sprite.h"
#include "Controllers/Touch.h"

ProgressBarWidget::ProgressBarWidget(Sprite* back, Sprite* full, const string& name, double value)
: m_spriteBack(back)
, m_spriteFull(full)
, m_value(value)
{
    m_name = name;
}

ProgressBarWidget::~ProgressBarWidget()
{
    delete m_spriteBack;
    delete m_spriteFull;
}

void ProgressBarWidget::setPosition(const vec2d& p)
{
    m_spriteBack->setPosition(p);
    m_spriteFull->setPosition(p);
    Widget::setPosition(p);
}

void ProgressBarWidget::setScale(const vec2d& s)
{
    m_spriteBack->setScale(s);
    m_spriteFull->setScale(s);
    Widget::setScale(s);
}

void ProgressBarWidget::render()
{
    m_spriteFull->render();
    m_spriteBack->render();
    Widget::render();
}

bool ProgressBarWidget::_isPointInside(const vec2d& pt)
{
    return m_spriteBack->isPointInside(pt);
}
