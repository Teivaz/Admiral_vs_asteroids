#pragma once

class TouchReceiver;

class Touch
{
public:
    Touch(const vec2d& pos)
        : m_startPosition(pos)
        , m_currentPostion(pos)
    {}
    ~Touch(){};

    Touch& operator=(const Touch& t)
    {
        m_startPosition = t.m_startPosition;
        m_currentPostion = t.m_currentPostion;
        m_owner = nullptr;
        PLOG("Touch is copied!\n");
        return *this;
    }

    const vec2d&    startPoint() const
    {
        return m_startPosition;
    }
    const vec2d&    currentPoint() const
    {
        return m_currentPostion;
    }
    bool            isConsumed() const
    {
        return m_owner != nullptr;
    }
    vec2d           getDelta()
    {
        return m_currentPostion - m_startPosition;
    }
    void            consume(TouchReceiver* r)
    {
        m_owner = r;
    }
    void            releaseParent()
    {
        m_owner = nullptr;
    }
    TouchReceiver*  getOwner()
    {
        return m_owner;
    }
    void            updateTouch(const vec2d& position)
    {
        m_currentPostion = position;
    }
private:
    vec2d           m_startPosition;
    vec2d           m_currentPostion;
    TouchReceiver*  m_owner = nullptr;
};
