#pragma once

MakeShared(Touch);
class TouchReceiver;

class TouchManager : public Singleton<TouchManager>
{
    typedef std::list<TouchReceiver*> Kinestetics_t;
    typedef std::list<TouchPtr> Touches_t;
public:
    TouchManager();
    ~TouchManager();

    void                onTouchBegan(const vec2d&);
    void                onTouchMoved(const vec2d& position, const vec2d& previousPosition);
    void                onTouchEnded(const vec2d& position, const vec2d& previousPosition);

    void                addReceiever(TouchReceiver*);
    void                removeReceiever(TouchReceiver*);

private:

    TouchPtr            _resolveTouch(const vec2d& position, const vec2d& previousPosition, bool erase = false);

private:
    Kinestetics_t       m_receievers;
    Touches_t           m_touches;
};
