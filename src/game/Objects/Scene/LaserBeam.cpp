#include "Precompiled.h"
#include "LaserBeam.h"
#include "../Animations/Animation.h"
#include "Controllers/SpriteManager.h"
#include "Controllers/Painter.h"
#include "Controllers/CollisionManager.h"

LaserBeam::LaserBeam(const vec2d& position, double speed, double direction, double lifetime)
: PhysicNode(collisions::k_beam_1)
, m_lifetime(lifetime)
, m_speed(speed)
, m_directionF(direction)
{
    m_animation = SpriteManager::GetInstance()->createAnimation("beam.anim");

    m_directionV = vec2d(cos(m_directionF), sin(m_directionF));
    setRotation(m_directionF + PI/2);
    setPosition(position);
	setMoveDirection(m_directionV);
	setVelocity(speed);

	setMass(1);
}

LaserBeam::~LaserBeam()
{
    delete m_animation;
}

void LaserBeam::setCamera(CameraPtr c)
{
	m_animation->setCamera(c);
	PhysicNode::setCamera(c);
}

void LaserBeam::update(double dt)
{
	PhysicNode::update(dt);
    m_animation->update(dt);
    //adjustPosition(m_directionV * m_speed * dt / 1000.0f);
    m_lifetime -= dt;
	m_toRemove |= m_lifetime < 0;
	if (m_toRemove)
		delete this;
}

void LaserBeam::render()
{
	PhysicNode::render();
    m_animation->render();
}
void LaserBeam::setPosition(const vec2d& p)
{
	PhysicNode::setPosition(p);
    m_animation->setPosition(p);
}
void LaserBeam::setScale(const vec2d& s)
{
	PhysicNode::setScale(s);
    m_animation->setScale(s);
}
void LaserBeam::setRotation(double r)
{
    PhysicNode::setRotation(r);
    m_animation->setRotation(r);
}

void LaserBeam::create(const vec2d& position, double speed, double direction, double lifetime)
{
    LaserBeam* l = new LaserBeam(position, speed, direction, lifetime);
    l->setRenderLayer(100);
	l->setCamera(Painter::GetInstance()->getSceneCamera());
    Painter::GetInstance()->add(l);
}

void LaserBeam::onCollided(PhysicNode* other, const vec2d& point, const vec2d& momentum)
{
    PhysicNode::onCollided(other, point, momentum);
	m_toRemove = true;
}
