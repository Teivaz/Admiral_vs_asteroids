#pragma once
#include "Controllers/TouchReceiver.h"

class Sprite;

class Widget : public TouchReceiver
{
public:
    typedef std::list<Widget*> WidgetList_t;

    enum EAllignX
    {
        ELeft,
        ECenterX,
        ERight
    };
    enum EAllignY
    {
        ETop,
        ECenterY,
        EBottom
    };

    Widget();
    virtual ~Widget();

    virtual void                setPosition(const vec2f&);
    virtual void                setScale(const vec2f&);
    virtual void                render();

    virtual void                onTouchBegan(Touch*);
    virtual void                onTouchMoved(Touch*);
    virtual void                onTouchEnded(Touch*);

    const string&               getName() const;
    void                        addChild(Widget*);
    Widget*                     getParent();
    Widget*                     findChildByName(const string&, bool deep = false);
    void                        removeFromParent(Widget*);

private:
    void                        _setParent(Widget*);

protected:
    WidgetList_t                m_children;
    Widget*                     m_parent = nullptr;
    string                      m_name;
};
