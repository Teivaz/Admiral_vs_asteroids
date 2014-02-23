#include "Precompiled.h"
#include "Cannon.h"
#include "LaserBeam.h"

Cannon::Cannon(const Json::Value& value)
{
    vec2f position;
    Json::ReadVector(value["position"], position);
    setPosition(position);
    m_speed = static_cast<float>(value["speed"].asDouble());
    m_lifetime = static_cast<float>(value["lifetime"].asDouble());
    m_damage = static_cast<float>(value["damage"].asDouble());
    float rotation = static_cast<float>(value["rotation"].asDouble());
    m_additionalRotation = rotation / 180.0f * PI;
    setRotation(rotation);
}

Cannon::Cannon(const vec2f& position, float rotation, float bulletSpeed, float bulletDamage, float bulletLifetime)
    : m_speed(bulletSpeed)
    , m_lifetime(bulletLifetime)
    , m_damage(bulletDamage)
    , m_additionalRotation(rotation)
{
    setPosition(position);
}


Cannon::~Cannon()
{}

void Cannon::update(float dt)
{
}

void Cannon::shoot()
{
    if (m_transformationIsDirty)
    {
        _calculateTransformation();
    }
    vec3f beamPos3 = getTransformation() * vec3f(0.0f, 0.0f, 1.0f);
    vec2f beamPos(beamPos3.x, beamPos3.y);

    LaserBeam::create(beamPos, m_speed, getRotation() + m_additionalRotation, m_lifetime);
}
