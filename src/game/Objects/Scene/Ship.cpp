#include "Precompiled.h"
#include "Ship.h"
#include "Controllers/SpriteManager.h"
#include "Objects/Sprite.h"
#include "Controllers/Painter.h"
#include "LaserBeam.h"
#include "Objects/Animations/Animation.h"
#include "Controllers/CollisionManager.h"

Ship::Ship()
: Collidable(collisions::k_she)
{
    vec2f shipSize = SpriteManager::GetInstance()->getSpriteSize(sprites::k_she);
    m_ship = SpritePtr(SpriteManager::GetInstance()->createSprite(sprites::k_she, -shipSize / 2, shipSize, false, 0));
    m_ship->setCamera(Painter::GetInstance()->getSceneCamera());
    createFire();
    setFireScale(0);
}

Ship::~Ship()
{
}

void Ship::render()
{
	GameObject::render();
    m_engineFire->render();
    m_ship->render();
}

void Ship::update(float dt)
{
    float step = dt / 1000.0f;
    adjustRotation(m_rotationSpeed * step);
    adjustPosition(m_rotationV * m_enginePower * step);
    m_engineFire->update(dt);
}

void Ship::setPosition(const vec2f& p)
{
	Collidable::setPosition(p);
    m_ship->setPosition(p);
    m_engineFire->setPosition(p);
}

void Ship::setScale(const vec2f& s)
{
	Collidable::setScale(s);
    m_ship->setScale(s);
    m_engineFire->setScale(s);
}

void Ship::setRotation(float r)
{
	Collidable::setRotation(r);
    m_rotationV = vec2f(cos(m_rotation + PI / 2), sin(m_rotation + PI / 2));
    m_ship->setRotation(r);
    m_engineFire->setRotation(r);
}

void Ship::setRotationSpeed(float s)
{
    m_rotationSpeed = s;
}

void Ship::setEnginePower(float p)
{
    if (p > 0)
    {
        m_enginePower = p * m_maxSpeedFwd;
        setFireScale(p);
    }
    else
    {
        m_enginePower = p * m_maxSpeedBwd;
        setFireScale(0.0f);
    }
}

void Ship::shoot()
{
    if (m_transformationIsDirty)
    {
        _calculateTransformation();
    }
    vec3f beamPos3 = m_transformationMatrix * vec3f(m_cannonPosition, 1.0f);
    vec2f beamPos(beamPos3.x, beamPos3.y);
    LaserBeam::create(beamPos, 400.0f, m_rotation + PI / 2, 1000.0f);
}

void Ship::createFire()
{
    m_engineFire.reset(new Animation);
    vec2f flameSize = SpriteManager::GetInstance()->getSpriteSize(sprites::k_flame);
    vec2f sizes[5] = { flameSize, flameSize, flameSize, flameSize, flameSize };
    sizes[0].y *= 1.0f;
    sizes[1].y *= 0.9f;
    sizes[2].y *= 0.8f;
    sizes[3].y *= 0.85f;
    sizes[4].y *= 0.9f;
    vec2f pos[5] = { sizes[0]/2, sizes[1]/2, sizes[2]/2, sizes[3]/2, sizes[4]/2 };
    pos[0].y *= 2.0f;
    pos[1].y *= 2.0f;
    pos[2].y *= 2.0f;
    pos[3].y *= 2.0f;
    pos[4].y *= 2.0f;
    Sprite* s = SpriteManager::GetInstance()->createSprite(sprites::k_flame, -pos[0], sizes[0], false, 0);
    m_engineFire->addFrame(s);
    s = SpriteManager::GetInstance()->createSprite(sprites::k_flame, -pos[1], sizes[1], false, 0);
    m_engineFire->addFrame(s);
    s = SpriteManager::GetInstance()->createSprite(sprites::k_flame, -pos[2], sizes[2], false, 0);
    m_engineFire->addFrame(s);
    s = SpriteManager::GetInstance()->createSprite(sprites::k_flame, -pos[3], sizes[3], false, 0);
    m_engineFire->addFrame(s);
    s = SpriteManager::GetInstance()->createSprite(sprites::k_flame, -pos[4], sizes[4], false, 0);
    m_engineFire->addFrame(s);

    m_engineFire->setFps(20);
    m_engineFire->setCamera(Painter::GetInstance()->getSceneCamera());
}

void Ship::setFireScale(float s)
{
    m_engineFire->setScale(vec2f(1.0f + 0.1*s, s));
}
