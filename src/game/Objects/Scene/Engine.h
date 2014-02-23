#pragma once
#include "Objects/GameObject.h"

MakeShared(Ship);
MakeShared(Animation);
MakeShared(Camera);

class Engine : public GameObject
{
public:
    Engine(Ship* ship, const Json::Value& value);
    Engine(Ship* ship, Animation* flame, const vec2f& position);
    ~Engine();

    virtual void                    update(float);
    virtual void                    render();

    virtual void                    setPosition(const vec2f& p);
    virtual void                    setScale(const vec2f& s);
    virtual void                    setRotation(float r);

    virtual void                    setCamera(CameraPtr);

    void                            setPower(float);

private:
//    void                            _load

private:
    Ship*                           m_ship;
    AnimationPtr                    m_flame;
    float                           m_maxPower = 0;
    float                           m_power = 0;
};
