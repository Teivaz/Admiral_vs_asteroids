#include "Precompiled.h"
#include "Widget.h"
#include "../Sprite.h"
#include "Controllers/Touch.h"

Widget::Widget()
{

}

Widget::~Widget()
{
    for (Widget* child : m_children)
    {
        delete child;
    }
}

void Widget::setPosition(const vec2f& p)
{
    for (Widget* child : m_children)
    {
        child->setPosition(p);
    }
}

void Widget::setScale(const vec2f& s)
{
    for (Widget* child : m_children)
    {
        child->setScale(s);
    }
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
    auto it = std::find(m_parent->m_children.begin(), m_parent->m_children.end(), this);
    if (it != m_parent->m_children.end())
        m_parent->m_children.erase(it);
    m_parent = nullptr;
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

void Widget::onTouchBegan(Touch* t)
{
    if (t->isConsumed())
        return;
    for (Widget* w : m_children)
    {
        w->onTouchBegan(t);
    }
}

void Widget::onTouchMoved(Touch* t)
{
}

void Widget::onTouchEnded(Touch* t)
{
}
