#pragma once
#include "Objects/GameObject.h"

MakeShared(Ship);
MakeShared(Animation);
MakeShared(Camera);

class Engine : public GameObject
{
public:
    Engine(Ship* ship, const Json::Value& value);
    Engine(Ship* ship, Animation* flame, const vec2d& position);
    ~Engine();

    virtual void                    update(double);
    virtual void                    render();

    virtual void                    setPosition(const vec2d& p);
    virtual void                    setScale(const vec2d& s);
    virtual void                    setRotation(double r);

    virtual void                    setCamera(CameraPtr);

    void                            setPower(double);

private:
	void                            _calculateTransformation();

private:
    Ship*                           m_ship;
    AnimationPtr                    m_flame;
    double                           m_maxPower = 0;
    double                           m_power = 0;
    vec2d                           m_direction = vec2d(1.0f, 0.0f);
};
