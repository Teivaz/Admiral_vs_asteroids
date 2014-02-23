#include "Precompiled.h"
#include "Ship.h"
#include "Controllers/SpriteManager.h"
#include "Objects/Sprite.h"
#include "Controllers/Painter.h"
#include "LaserBeam.h"
#include "Objects/Animations/Animation.h"
#include "Controllers/CollisionManager.h"
#include "utils/FileUtils.h"
#include "Engine.h"

Ship* Ship::create(const string& name)
{
    char* data;
    size_t size;
    FileUtils::LoadFile(name.c_str(), &data, size, FileUtils::app);
    ASSERT(data && "Error opening animation file");
    Json::Reader reader;
    Json::Value root;
    bool result = reader.parse(data, data + size, root, false);
    ASSERT(result && "Error parsing animation file");
    delete[] data;
    const Json::Value cannons = root["cannons"];

    Ship* ship;

    const Json::Value body = root["body"];
    {
        string sprite = body["sprite"].asString();
        vec2f position;
        Json::ReadVector(body["position"], position);
        vec2f scale;
        Json::ReadVector(body["scale"], scale);
        float rotation = static_cast<float>(body["rotation"].asDouble());
        rotation = (rotation / 180.0f) * PI;
        string collision = body["collision"].asString();
        float mass = static_cast<float>(body["mass"].asDouble());

        vec2f shipSize = SpriteManager::GetInstance()->getSpriteSize(sprite);
        Sprite* bodySprite = SpriteManager::GetInstance()->createSprite(sprite, -shipSize / 2, shipSize, false, 0);
        bodySprite->setScale(scale);
        bodySprite->setRotation(rotation);
        bodySprite->setPosition(position);
        ship = new Ship(name, collision, bodySprite);
        ship->setMass(mass);
    }
    
    const Json::Value engines = root["engines"];
    {
        {
            vector<EnginePtr> leftFrontEngine;
            Json::Value::iterator it = engines["left_front"].begin();
            Json::Value::iterator end = engines["left_front"].end();
            for (; it != end; ++it)
            {
                EnginePtr e(new Engine(ship, *it));
                e->setCamera(Painter::GetInstance()->getSceneCamera());
                leftFrontEngine.push_back(e);
            }
            ship->setLeftFrontEngine(leftFrontEngine);

        }
        {
            vector<EnginePtr> rightFrontEngine;
            Json::Value::iterator it = engines["right_front"].begin();
            Json::Value::iterator end = engines["right_front"].end();
            for (; it != end; ++it)
            {
                EnginePtr e(new Engine(ship, *it));
                e->setCamera(Painter::GetInstance()->getSceneCamera());
                rightFrontEngine.push_back(e);
            }
            ship->setRightFrontEngine(rightFrontEngine);
        }
        {
            vector<EnginePtr> leftBackEngine;
            Json::Value::iterator it = engines["left_back"].begin();
            Json::Value::iterator end = engines["left_back"].end();
            for (; it != end; ++it)
            {
                EnginePtr e(new Engine(ship, *it));
                e->setCamera(Painter::GetInstance()->getSceneCamera());
                leftBackEngine.push_back(e);
            }
            ship->setLeftBackEngine(leftBackEngine);
        }
        {
            vector<EnginePtr> rightBackEngine;
            Json::Value::iterator it = engines["right_back"].begin();
            Json::Value::iterator end = engines["right_back"].end();
            for (; it != end; ++it)
            {
                EnginePtr e(new Engine(ship, *it));
                e->setCamera(Painter::GetInstance()->getSceneCamera());
                rightBackEngine.push_back(e);
            }
            ship->setRightBackEngine(rightBackEngine);
        }
        {
            vector<EnginePtr> mainEngine;
            Json::Value::iterator it = engines["main"].begin();
            Json::Value::iterator end = engines["main"].end();
            for (; it != end; ++it)
            {
                EnginePtr e(new Engine(ship, *it));
                e->setCamera(Painter::GetInstance()->getSceneCamera());
                mainEngine.push_back(e);
            }
            ship->setMainEngine(mainEngine);
        }
    }

    return ship;
}

Ship::Ship(const string& name, const string& collision, Sprite* body)
: PhysicNode(collision)
, m_name(name)
, m_ship(SpritePtr(body))
{
    m_ship->setCamera(Painter::GetInstance()->getSceneCamera());
    createFire();
    setFireScale(0);
	setDirection(vec2f(0.0f, 1.0f));
}

Ship::~Ship()
{
}

void Ship::render()
{
    m_ship->setAdditionalTransformation(getTransformation());
    m_ship->render();
    m_engineFire->render();
    for (auto e : m_leftFrontEngine)
        e->render();
    for (auto e : m_rightFrontEngine)
        e->render();
    for (auto e : m_leftBackEngine)
        e->render();
    for (auto e : m_rightBackEngine)
        e->render();
    for (auto e : m_mainEngine)
        e->render();
}

void Ship::update(float dt)
{
    PhysicNode::update(dt);
    float step = dt / 1000.0f;
    adjustRotation(m_rotationSpeed * step);
    adjustPosition(m_rotationV * m_enginePower * step);

    for (auto e : m_leftFrontEngine)
        e->update(dt);
    for (auto e : m_rightFrontEngine)
        e->update(dt);
    for (auto e : m_leftBackEngine)
        e->update(dt);
    for (auto e : m_rightBackEngine)
        e->update(dt);
    for (auto e : m_mainEngine)
        e->update(dt);
}

void Ship::setPosition(const vec2f& p)
{
    PhysicNode::setPosition(p);
    for (auto e : m_leftFrontEngine)
        e->setPosition(p);
    for (auto e : m_rightFrontEngine)
        e->setPosition(p);
    for (auto e : m_leftBackEngine)
        e->setPosition(p);
    for (auto e : m_rightBackEngine)
        e->setPosition(p);
    for (auto e : m_mainEngine)
        e->setPosition(p);
}

void Ship::setScale(const vec2f& s)
{
    PhysicNode::setScale(s);
    for (auto e : m_leftFrontEngine)
        e->setScale(s);
    for (auto e : m_rightFrontEngine)
        e->setScale(s);
    for (auto e : m_leftBackEngine)
        e->setScale(s);
    for (auto e : m_rightBackEngine)
        e->setScale(s);
    for (auto e : m_mainEngine)
        e->setScale(s);
}

void Ship::setRotation(float r)
{
    PhysicNode::setRotation(r);
    m_rotationV = vec2f(cos(m_rotation + PI / 2), sin(m_rotation + PI / 2));
    for (auto e : m_leftFrontEngine)
        e->setRotation(r);
    for (auto e : m_rightFrontEngine)
        e->setRotation(r);
    for (auto e : m_leftBackEngine)
        e->setRotation(r);
    for (auto e : m_rightBackEngine)
        e->setRotation(r);
    for (auto e : m_mainEngine)
        e->setRotation(r);
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
    vec3f beamPos3 = getTransformation() * vec3f(m_cannonPosition, 1.0f);
    vec2f beamPos(beamPos3.x, beamPos3.y);
    LaserBeam::create(beamPos, 0.0f, m_rotation + PI / 2, 10000.0f);
}

void Ship::createFire()
{
    m_engineFire.reset(SpriteManager::GetInstance()->createAnimation("jet_small.anim"));
    m_engineFire->setFramesPosition(vec2f(0.0, -50));

    m_engineFire->setCamera(Painter::GetInstance()->getSceneCamera());
}

void Ship::setFireScale(float s)
{
    //m_engineFire->setScale(vec2f(1.0f + 0.1f*s, s));
}

void Ship::onCollided(PhysicNode* other, vec2f point)
{
	vec2f dir = m_position - other->getPosition();
	dir.Normalize();
	vec2f resultVector = dir * other->getEnergy() + getDirection() * getEnergy();
	setSpeed(resultVector.Normalize() / (2.0f * getMass()));
	setDirection(resultVector);
}

float Ship::getSpeed() const
{
	return m_enginePower * getMass();
}

void Ship::setLeftFrontEngine(const std::vector<EnginePtr>& eng)
{
    m_leftFrontEngine = eng;
}

void Ship::setRightFrontEngine(const std::vector<EnginePtr>& eng)
{
    m_rightFrontEngine = eng;
}
void Ship::setLeftBackEngine(const std::vector<EnginePtr>& eng)
{
    m_leftBackEngine = eng;
}
void Ship::setRightBackEngine(const std::vector<EnginePtr>& eng)
{
    m_rightBackEngine = eng;
}
void Ship::setMainEngine(const std::vector<EnginePtr>& eng)
{
    m_mainEngine = eng;
}
