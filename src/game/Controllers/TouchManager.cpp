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
    TouchPtr touch = TouchPtr(new Touch(point));
    m_touches.push_back(touch);
    for (TouchReceiver* tr : m_receievers)
    {
        tr->onTouchBegan(touch);
    }
}

void TouchManager::onTouchMoved(const vec2f& position, const vec2f& previousPosition)
{
    TouchPtr touch = _resolveTouch(position, previousPosition);
    if (touch && touch->isConsumed())
    {
        touch->getOwner()->onTouchMoved(touch);
    }
}

void TouchManager::onTouchEnded(const vec2f& position, const vec2f& previousPosition)
{
    TouchPtr touch = _resolveTouch(position, previousPosition, true);
    if (!touch)
        return;
    if(touch->isConsumed())
    {
        touch->getOwner()->onTouchEnded(touch);
    }
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

TouchPtr TouchManager::_resolveTouch(const vec2f& position, const vec2f& previousPosition, bool erase/* = true*/)
{
#ifdef _WIN321
    // This will do for Windows as it has no multitouch
    if (m_touches.empty())
    {
        return nullptr;
    }
    TouchPtr touch = m_touches.back();
    touch->updateTouch(position);
    if (erase)
        m_touches.pop_back();
    return touch;
#else
    // Find touch with position closest to incoming touch prevoius position
    auto result = m_touches.begin();
    float distance = vec2f((*result)->currentPoint() - previousPosition).SqLength();
    auto it = result;
    auto end = m_touches.end();
    ++it;
    for (; it != end; ++it)
    {
        float newDistance = vec2f((*it)->currentPoint() - previousPosition).SqLength();
        if (newDistance < distance)
        {
            distance = newDistance;
            result = it;
        }
    }
    if (erase)
    {
        m_touches.erase(result);
    }
    return *result;
#endif
}
