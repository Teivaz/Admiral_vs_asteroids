#pragma once

class GameObject;

class State
{
public:
    virtual ~State() {};

    virtual void                update(double dt) = 0;
    virtual void                render() = 0;
    virtual void                onEnter() = 0;
    virtual void                onFinish() = 0;
    virtual void                pause(bool) = 0;
    virtual bool                isFinished() const = 0;
};
