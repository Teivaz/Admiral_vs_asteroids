#pragma once

MakeShared(Touch);

class TouchReceiver
{
public:
    TouchReceiver(){};
    virtual ~TouchReceiver();

    virtual void            onTouchBegan(TouchPtr){};
    virtual void            onTouchMoved(TouchPtr){};
    virtual void            onTouchEnded(TouchPtr){};
};
