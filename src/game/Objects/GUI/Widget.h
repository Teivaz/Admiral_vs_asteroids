#pragma once
#include "Controllers/TouchReceiver.h"
#include "Objects/GameObject.h"

class Sprite;

class Widget : public TouchReceiver, public GameObject
{
public:
    typedef std::list<Widget*> WidgetList_t;

    Widget();
    virtual ~Widget();

    virtual void                setPosition(const vec2d&);
    virtual void                setScale(const vec2d&);
    virtual void                render();

    virtual void                onTouchBegan(TouchPtr);
    virtual void                onTouchMoved(TouchPtr);
    virtual void                onTouchEnded(TouchPtr);

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
