#include "Precompiled.h"
#include "CaptainsBridge.h"
#include "Ship.h"

#include "Controllers/SpriteManager.h"
#include "Objects/Sprite.h"
#include "Controllers/Painter.h"
#include "LaserBeam.h"
#include "Objects/Animations/Animation.h"
#include "Controllers/CollisionManager.h"

CaptainsBridge::CaptainsBridge()
{}

CaptainsBridge::~CaptainsBridge()
{}

void CaptainsBridge::render()
{}

void CaptainsBridge::update(float dt)
{}

void CaptainsBridge::shoot()
{
    m_ship->shoot();
}

void CaptainsBridge::rotate(float speed)
{
    m_ship->setEnginePower(Ship::ELeftFront, -speed);
    m_ship->setEnginePower(Ship::ERightBack, -speed);
    m_ship->setEnginePower(Ship::ELeftBack, speed);
    m_ship->setEnginePower(Ship::ERightFront, speed);
}

void CaptainsBridge::setMainEnginePower(float power)
{
    m_ship->setEnginePower(Ship::EMain, power);
}

void CaptainsBridge::setEnginePower(int engineId, float power)
{
    m_ship->setEnginePower(static_cast<Ship::EEngines>(engineId), power);
}

vec2f CaptainsBridge::getShipMoveDirection() const
{
    return m_ship->getMoveDirection();
}

vec2f CaptainsBridge::getShipRotation() const
{
    return m_ship->getRotation();
}
float CaptainsBridge::getShipRotationSpeed() const
{
    return m_ship->getRadialVelocity();
}
float CaptainsBridge::getShipRotationSpeedDerivative() const
{
    return 0;
}
vec2f CaptainsBridge::getShipMoveSpeedDerivative() const
{
    return 0;
}