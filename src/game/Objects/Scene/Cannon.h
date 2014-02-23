#pragma once
#include "Objects/GameObject.h"

class Ship;
class Animation;
MakeShared(Camera);

class Cannon : public GameObject
{
public:
    Cannon(const Json::Value& value);
    Cannon(const vec2f& position, float rotation, float bulletSpeed, float bulletDamage, float bulletLifetime);
    ~Cannon();

    virtual void                    update(float);
    
    void                            shoot();

private:
    float                           m_additionalRotation = 0;
    float                           m_speed = 0;
    float                           m_lifetime = 0;
    float                           m_damage = 0;
};
