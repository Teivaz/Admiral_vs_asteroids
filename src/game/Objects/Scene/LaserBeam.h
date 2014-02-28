#pragma once
#include "../GameObject.h"
#include "Objects/Physics/PhysicNode.h"

class Animation;

class LaserBeam : public PhysicNode
{
public:
    static void create(const vec2d& position, double speed, double direction, double lifetime);
    LaserBeam(const vec2d& position, double speed, double direction, double lifetime);
    virtual ~LaserBeam();


    virtual void                    update(double);
    virtual void                    render();
    
    virtual void                    setPosition(const vec2d& p);
    virtual void                    setScale(const vec2d& s);
	virtual void                    setRotation(double r);
	virtual void                    setCamera(CameraPtr);
    virtual void					onCollided(PhysicNode* other, const vec2d& point, const vec2d& momentum);

private:
    double                           m_lifetime = 0;
    double                           m_speed = 1.0f;
    vec2d                           m_directionV;
    double                           m_directionF;
	Animation*                      m_animation = nullptr;

	bool							m_toRemove = false;
};
