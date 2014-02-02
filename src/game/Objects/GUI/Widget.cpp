#include "Precompiled.h"
#include "Widget.h"
#include "../Sprite.h"

Widget::Widget()
{

}

Widget::~Widget()
{
}

void Widget::setAnchor(vec2f anchor)
{
}

void Widget::setAllign(EAllignX x, EAllignY y)
{
    switch (x)
    {
    case ELeft:
        break;

    case ECenterX:
        break;

    case ERight:
    default:
        break;
    }
    switch (y)
    {
    case ETop:
        break;

    case ECenterY:
        break;

    case EBottom:
    default:
        break;
    }
}

void Widget::setOffset(vec2f)
{

}

void Widget::setScale(vec2f s)
{
}

void Widget::addChild(Widget* w)
{
    auto it = std::find(m_children.begin(), m_children.end(), w);
    if (it != m_children.end())
    {
        return;
    }
    m_children.push_back(w);
    w->_setParent(this);
}

Widget* Widget::getParent()
{
    return m_parent;
}

Widget* Widget::findChildByName(const string& name, bool deep/* = false*/)
{
    for (Widget* child : m_children)
    {
        if (child->getName() == name)
            return child;
    }
    if (deep)
    {
        for (Widget* child : m_children)
        {
            Widget* w = child->findChildByName(name, true);
            if (w)
                return w;
        }
    }
    return nullptr;
}
void Widget::removeFromParent(Widget*)
{

}

const string& Widget::getName() const
{
    return m_name;
}

void Widget::render()
{
    for (Widget* w : m_children)
    {
        w->render();
    }
}

void Widget::_setParent(Widget* parent)
{
    m_parent = parent;
}
