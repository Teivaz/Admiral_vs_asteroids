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

void TouchManager::onTouchBegan(const vec2d& point)
{
    TouchPtr touch = TouchPtr(new Touch(point));
    m_touches.push_back(touch);
    for (TouchReceiver* tr : m_receievers)
    {
        tr->onTouchBegan(touch);
    }
}

void TouchManager::onTouchMoved(const vec2d& position, const vec2d& previousPosition)
{
    TouchPtr touch = _resolveTouch(position, previousPosition);
    if (touch && touch->isConsumed())
    {
        touch->getOwner()->onTouchMoved(touch);
    }
}

void TouchManager::onTouchEnded(const vec2d& position, const vec2d& previousPosition)
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

TouchPtr TouchManager::_resolveTouch(const vec2d& position, const vec2d& previousPosition, bool erase/* = true*/)
{
    // Find touch with position closest to incoming touch prevoius position
    unsigned int touchesStored = m_touches.size();
    if (touchesStored == 0)
    {
        return TouchPtr();
    }
    else if (touchesStored == 1)
    {
        TouchPtr touch = m_touches.back();
        touch->updateTouch(position);
        if (erase)
            m_touches.pop_back();
        return touch;
    }
    else
    {
        TouchPtr touch = m_touches.front();
        double distance = vec2d(touch->currentPoint() - previousPosition).SqLength();
        auto it = m_touches.begin();
        auto end = m_touches.end();
        ++it;
        for (; it != end; ++it)
        {
            double newDistance = vec2d((*it)->currentPoint() - previousPosition).SqLength();
            if (newDistance < distance)
            {
                distance = newDistance;
                touch = *it;
            }
        }
        touch->updateTouch(position);
        if (erase)
        {
            m_touches.erase(std::find(m_touches.begin(), m_touches.end(), touch));
        }
        return touch;
    }
}
