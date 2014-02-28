#include "Precompiled.h"
#include "Cannon.h"
#include "LaserBeam.h"

Cannon::Cannon(const Json::Value& value)
{
    vec2d position;
    Json::ReadVector(value["position"], position);
    setPosition(position);
    m_speed = static_cast<double>(value["speed"].asDouble());
    m_lifetime = static_cast<double>(value["lifetime"].asDouble());
    m_damage = static_cast<double>(value["damage"].asDouble());
    double rotation = static_cast<double>(value["rotation"].asDouble());
    m_additionalRotation = rotation / 180.0f * PI;
    setRotation(rotation);
}

Cannon::Cannon(const vec2d& position, double rotation, double bulletSpeed, double bulletDamage, double bulletLifetime)
    : m_speed(bulletSpeed)
    , m_lifetime(bulletLifetime)
    , m_damage(bulletDamage)
    , m_additionalRotation(rotation)
{
    setPosition(position);
}


Cannon::~Cannon()
{}

void Cannon::update(double dt)
{
}

void Cannon::shoot()
{
    if (m_transformationIsDirty)
    {
        _calculateTransformation();
    }
    vec2d beamPos = Transform(getTransformation(), vec2d());

    LaserBeam::create(beamPos, m_speed, getRotation() + m_additionalRotation, m_lifetime);
}
