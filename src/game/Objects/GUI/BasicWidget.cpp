#include "Precompiled.h"
#include "BasicWidget.h"
#include "../Sprite.h"

BasicWidget::BasicWidget(Sprite* sprite, const string& name)
: m_sprite(sprite)
{
    m_name = name;
}

BasicWidget::~BasicWidget()
{
    delete m_sprite;
}

void BasicWidget::setPosition(const vec2d& p)
{
    m_sprite->setPosition(p);
    Widget::setPosition(p);
}

void BasicWidget::setScale(const vec2d& s)
{
    m_sprite->setScale(s);
    Widget::setScale(s);
}

void BasicWidget::render()
{
    m_sprite->render();
    Widget::render();
}
