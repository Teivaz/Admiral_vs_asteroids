#include "Precompiled.h"
#include "Engine.h"
#include "Ship.h"
#include "Objects/Animations/Animation.h"
#include "Controllers/SpriteManager.h"

Engine::Engine(Ship* ship, const Json::Value& value)
: m_ship(ship)
, m_power(0.0f)
{
    m_flame.reset(SpriteManager::GetInstance()->createAnimation(value["animation"].asString()));

    vec2f position;
    Json::ReadVector(value["position"], position);
    m_flame->setPosition(position);

    m_maxPower = static_cast<float>(value["power"].asDouble());

    float rotation = static_cast<float>(value["rotation"].asDouble());
    rotation = rotation / 180.0f * PI;
    m_flame->setRotation(rotation);
}

Engine::Engine(Ship* ship, Animation* flame,  const vec2f& pos)
: m_ship(ship)
, m_flame(flame)
{
    m_flame->setFramesPosition(pos);
    setPosition(pos);
}

Engine::~Engine()
{

}

void Engine::setCamera(CameraPtr cam)
{
    GameObject::setCamera(cam);
    m_flame->setCamera(cam);
}

void Engine::render()
{
    m_flame->setAdditionalTransformation(getTransformation());
    m_flame->render();
}

void Engine::update(float dt)
{
    m_flame->update(dt);
    if (m_power > 0)
    {
        vec3f point3(m_flame->getPosition(), 0.0f);
        point3 = m_flame->getTransformation() * point3;
        vec2f point(point3.x, point3.y);
        vec2f rotation(cos(m_flame->getRotation()), sin(m_flame->getRotation()));
        m_ship->addImpact(point, rotation * m_power * m_maxPower * dt / 1000.0f);
    }
}

void Engine::setPosition(const vec2f& pos)
{
    GameObject::setPosition(pos);
}

void Engine::setRotation(float rot)
{
    GameObject::setRotation(rot);
}

void Engine::setScale(const vec2f& scale)
{
    GameObject::setScale(scale);
}
void Engine::setPower(float p)
{
    vec2f scale = m_flame->getScale();
    scale.x = clamp(p);
    m_flame->setScale(scale);
    m_power = clamp(p);
}
