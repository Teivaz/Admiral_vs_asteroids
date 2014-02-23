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
    // m_ship->setEnginePower(ELeftFront, -speed);
    // m_ship->setEnginePower(ERightBack, -speed);
    // m_ship->setEnginePower(ELeftBack, speed);
    // m_ship->setEnginePower(ERightFront, speed);
}

void CaptainsBridge::setMainEnginePower(float power)
{
    // m_ship->setEnginePower(EMain, power);
}

void CaptainsBridge::setEnginePower(int engineId, float power)
{
    // m_ship->setEnginePower(engineId, power);
}

//vec2f CaptainsBridge::getShipMoveDirection() const
//{
//    return m_ship->getMoveDirection();
//}
//vec2f CaptainsBridge::setShipRotation() const;
//float CaptainsBridge::getShipRotationSpeed() const;
//float CaptainsBridge::getShipRotationSpeedDerivative() const;
//vec2f CaptainsBridge::getShipMoveSpeed() const;
//vec2f CaptainsBridge::getShipMoveSpeedDerivative() const;