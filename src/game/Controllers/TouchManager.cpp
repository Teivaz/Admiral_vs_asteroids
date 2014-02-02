#include "Precompiled.h"
#include "TouchManager.h"
#include "Touch.h"
#include "TouchReceiver.h"

TouchManager::TouchManager()
{
}

TouchManager::~TouchManager()
{
}

void TouchManager::onTouchBegan(const vec2f& point)
{
    Touch* touch = new Touch(point);
    m_touches.push_back(touch);
    for (TouchReceiver* tr : m_receievers)
    {
        tr->onTouchBegan(touch);
    }
}

void TouchManager::onTouchMoved(const vec2f& point)
{
    Touch* touch = _resolveTouch(point);
    if (touch && touch->isConsumed())
    {
        touch->getOwner()->onTouchMoved(touch);
    }
}

void TouchManager::onTouchEnded(const vec2f& point)
{
    Touch* touch = _resolveTouch(point, true);
    if (!touch)
        return;
    if(touch->isConsumed())
    {
        touch->getOwner()->onTouchEnded(touch);
    }
    delete touch;
}

void TouchManager::addReceiever(TouchReceiver* r)
{
    auto it = std::find(m_receievers.begin(), m_receievers.end(), r);
    if (it != m_receievers.end())
        return;
    m_receievers.push_back(r);
}

void TouchManager::removeReceiever(TouchReceiver* r)
{
    auto it = std::find(m_receievers.begin(), m_receievers.end(), r);
    if (it == m_receievers.end())
        return;
    m_receievers.erase(it);
}

Touch* TouchManager::_resolveTouch(const vec2f& point, bool erase/* = true*/)
{
    // This will do for win as it has no multitouch
    if (m_touches.empty())
    {
        return nullptr;
    }
    Touch* touch = m_touches.back();
    touch->updateTouch(point);
    if (erase)
        m_touches.pop_back();
    return touch;
}
