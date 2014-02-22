#pragma once
#include "../GameObject.h"
#include "Objects/Physics/PhysicNode.h"

class Animation;

class LaserBeam : public PhysicNode
{
public:
    static void create(const vec2f& position, float speed, float direction, float lifetime);
    LaserBeam(const vec2f& position, float speed, float direction, float lifetime);
    virtual ~LaserBeam();


    virtual void                    update(float);
    virtual void                    render();
    
    virtual void                    setPosition(const vec2f& p);
    virtual void                    setScale(const vec2f& s);
	virtual void                    setRotation(float r);
	virtual void                    setCamera(CameraPtr);
    virtual void					onCollided(PhysicNode* other, vec2f point);

private:
    float                           m_lifetime = 0;
    float                           m_speed = 1.0f;
    vec2f                           m_directionV;
    float                           m_directionF;
	Animation*                      m_animation = nullptr;

	bool							m_toRemove = false;
};
