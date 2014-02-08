#pragma once

class Touch;
class TouchReceiver;

class TouchManager : public Singleton<TouchManager>
{
    typedef std::list<TouchReceiver*> Kinestetics_t;
    typedef std::list<Touch*> Touches_t;
public:
    TouchManager();
    ~TouchManager();

    void                onTouchBegan(const vec2f&);
    void                onTouchMoved(const vec2f& position, const vec2f& previousPosition);
    void                onTouchEnded(const vec2f& position, const vec2f& previousPosition);

    void                addReceiever(TouchReceiver*);
    void                removeReceiever(TouchReceiver*);

private:

    Touch*              _resolveTouch(const vec2f& position, const vec2f& previousPosition, bool erase = false);

private:
    Kinestetics_t       m_receievers;
    Touches_t           m_touches;
};
