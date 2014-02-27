#include "Precompiled.h"
#include "Ship.h"
#include "Controllers/SpriteManager.h"
#include "Objects/Sprite.h"
#include "Controllers/Painter.h"
#include "LaserBeam.h"
#include "Objects/Animations/Animation.h"
#include "Controllers/CollisionManager.h"
#include "utils/FileUtils.h"
#include "Cannon.h"
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

    const Json::Value cannons = root["cannons"];
    {
        vector<CannonPtr> cannonsVec;
        Json::Value::iterator it = cannons.begin();
        Json::Value::iterator end = cannons.end();
        for (; it != end; ++it)
        {
            cannonsVec.push_back(CannonPtr(new Cannon(*it)));
        }
        ship->setCannons(cannonsVec);
    }

    return ship;
}

Ship::Ship(const string& name, const string& collision, Sprite* body)
: PhysicNode(collision)
, m_name(name)
, m_ship(SpritePtr(body))
{
    m_ship->setCamera(Painter::GetInstance()->getSceneCamera());
	setMoveDirection(vec2f(0.0f, 1.0f));
}

Ship::~Ship()
{
}

void Ship::render()
{
    m_ship->setAdditionalTransformation(getTransformation());
    m_ship->render();
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

    for (auto c : m_cannons)
    {
        c->setAdditionalTransformation(getTransformation());
        c->update(dt);
    }

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

    for (auto c : m_cannons)
        c->setRotation(r);

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

void Ship::setRotationEnginesSpeed(float speed)
{
    setEnginePower(Ship::ELeftFront, speed);
    setEnginePower(Ship::ERightBack, speed);
    setEnginePower(Ship::ELeftBack, -speed);
    setEnginePower(Ship::ERightFront, -speed);
//    m_rotationSpeed += 0.01f*speed;
}

void Ship::setEnginePower(EEngines engine, float p)
{
    switch (engine)
    {
    case EMain:
        for (auto e : m_mainEngine)
            e->setPower(p);
        break;
    case ELeftBack:
        for (auto e : m_leftBackEngine)
            e->setPower(p);
        break;
    case ELeftFront:
        for (auto e : m_leftFrontEngine)
            e->setPower(p);
        break;
    case ERightBack:
        for (auto e : m_rightBackEngine)
            e->setPower(p);
        break;
    case ERightFront:
        for (auto e : m_rightFrontEngine)
            e->setPower(p);
        break;        
    }
}

void Ship::shoot()
{
    for (auto c : m_cannons)
        c->shoot();
}

void Ship::onCollided(PhysicNode* other, const vec2f& point, const vec2f& momentum)
{
    PhysicNode::onCollided(other, point, momentum);
	//vec2f dir = m_position - other->getPosition();
	//dir.Normalize();
	//vec2f resultVector = dir * getMass() + getDirection() * getMass();
	//setLinearSpeed(resultVector.Normalize() / (2.0f * getMass()));
	//setDirection(resultVector);
}

float Ship::getSpeed() const
{
	return getMass();
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
void Ship::setCannons(const std::vector<CannonPtr>& cannons)
{
    m_cannons = cannons;
}
