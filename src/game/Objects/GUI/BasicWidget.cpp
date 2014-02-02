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

}

Sprite* BasicWidget::getSprite()
{
    return m_sprite;
}

void BasicWidget::setAnchor(vec2f anchor)
{
    vec2f size = m_sprite->getSize();
    m_sprite->setPosition(vec2f(size.x * anchor.x, size.y * anchor.y));
}

void BasicWidget::setAllign(EAllignX, EAllignY)
{

}

void BasicWidget::setOffset(vec2f)
{

}

void BasicWidget::setScale(vec2f s)
{
    m_sprite->setScale(s);
}

void BasicWidget::render()
{
    m_sprite->render();
    Widget::render();
}
