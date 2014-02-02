#pragma once

class Touch;

class TouchReceiver
{
public:
    TouchReceiver(){};
    virtual ~TouchReceiver();

    virtual void            onTouchBegan(Touch*){};
    virtual void            onTouchMoved(Touch*){};
    virtual void            onTouchEnded(Touch*){};
};
