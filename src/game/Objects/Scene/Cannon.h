#pragma once
#include "Objects/GameObject.h"

class Ship;
class Animation;
MakeShared(Camera);

class Cannon : public GameObject
{
public:
    Cannon(const Json::Value& value);
    Cannon(const vec2d& position, double rotation, double bulletSpeed, double bulletDamage, double bulletLifetime);
    ~Cannon();

    virtual void                    update(double);
    
    void                            shoot();

private:
    double                           m_additionalRotation = 0;
    double                           m_speed = 0;
    double                           m_lifetime = 0;
    double                           m_damage = 0;
};
