#include "Precompiled.h"
#include "CaptainsBridge.h"
#include "Ship.h"

#include "Controllers/SpriteManager.h"
#include "Objects/Sprite.h"
#include "Controllers/Painter.h"
#include "LaserBeam.h"
#include "Objects/Animations/Animation.h"
#include "Controllers/CollisionManager.h"

CaptainsBridge::CaptainsBridge(const string& shipName)
: m_ship(ShipPtr(Ship::create(shipName)))
{
    Painter::GetInstance()->add(m_ship.get());
}

CaptainsBridge::~CaptainsBridge()
{}

void CaptainsBridge::render()
{}

void CaptainsBridge::update(double dt)
{}

void CaptainsBridge::shoot()
{
    m_ship->shoot();
}

void CaptainsBridge::rotate(double speed)
{
    m_ship->setEnginePower(Ship::ELeftFront, -speed);
    m_ship->setEnginePower(Ship::ERightFront, speed);
    m_ship->setEnginePower(Ship::ERightBack, -speed);
    m_ship->setEnginePower(Ship::ELeftBack, speed);
}

void CaptainsBridge::setMainEnginePower(double power)
{
    m_ship->setEnginePower(Ship::EMain, power);
    m_ship->setEnginePower(Ship::ERightBack, power);
    m_ship->setEnginePower(Ship::ELeftBack, power);
}

void CaptainsBridge::setEnginePower(int engineId, double power)
{
    m_ship->setEnginePower(static_cast<Ship::EEngines>(engineId), power);
}

vec2d CaptainsBridge::getShipMoveDirection() const
{
    return m_ship->getMoveDirection();
}

vec2d CaptainsBridge::getShipRotation() const
{
    return m_ship->getRotation();
}
double CaptainsBridge::getShipRotationSpeed() const
{
    return m_ship->getRadialVelocity();
}
double CaptainsBridge::getShipRotationSpeedDerivative() const
{
    return m_ship->getRadialVelocityDerivative();
}
double CaptainsBridge::getShipMoveSpeedDerivative() const
{
	return m_ship->getVelocityDerivative();
}

double CaptainsBridge::getShipMoveSpeed() const
{
	return m_ship->getVelocity();
}
vec2d CaptainsBridge::GetShipPosition() const
{
    return m_ship->getPosition();//getTransformation().GetTranslationPart();
}
