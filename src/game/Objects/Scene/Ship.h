#pragma once
#include "Collidable.h"

MakeShared(Sprite);
MakeShared(Animation);

class Ship : public Collidable
{
public:
    Ship();
    virtual ~Ship();

    virtual void                    render();
    virtual void                    update(float dt);

    virtual void                    setPosition(const vec2f& p);
    virtual void                    setScale(const vec2f& s);
    virtual void                    setRotation(float r);

                                    // -1...+1
    void                            setRotationSpeed(float);
    void                            setEnginePower(float);
    void                            shoot();

protected:
    void                            createFire();
    void                            setFireScale(float);

private:
    SpritePtr                       m_ship;
    AnimationPtr                    m_engineFire;
    float                           m_rotationSpeed = 0.0f;
    float                           m_enginePower = 0.0f;
    vec2f                           m_rotationV;
    vec2f                           m_cannonPosition = vec2f(-2.0f, 50.0f);

    float                           m_maxSpeedFwd = 200.0f;
    float                           m_maxSpeedBwd = 100.0f;
};
