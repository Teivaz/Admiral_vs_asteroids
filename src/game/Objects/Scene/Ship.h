#pragma once
#include "Objects/Physics/PhysicNode.h"

MakeShared(Sprite);
MakeShared(Animation);
MakeShared(Engine);

class Ship : public PhysicNode
{
public:

    static Ship*                    create(const string& name);

    Ship(const string& name, const string& collision, Sprite* body);
    virtual ~Ship();

    void                            setLeftFrontEngine(const std::vector<EnginePtr>& eng);
    void                            setRightFrontEngine(const std::vector<EnginePtr>& eng);
    void                            setLeftBackEngine(const std::vector<EnginePtr>& eng);
    void                            setRightBackEngine(const std::vector<EnginePtr>& eng);
    void                            setMainEngine(const std::vector<EnginePtr>& eng);

    virtual void                    render();
    virtual void                    update(float dt);

    virtual void                    setPosition(const vec2f& p);
    virtual void                    setScale(const vec2f& s);
    virtual void                    setRotation(float r);

                                    // -1...+1
    void                            setRotationSpeed(float);
    void                            setEnginePower(float);
	void                            shoot();
    virtual void					onCollided(PhysicNode* other, vec2f point);
	virtual float					getSpeed() const;

protected:
    void                            createFire();
    void                            setFireScale(float);

private:
    string                          m_name;
    SpritePtr                       m_ship;
    AnimationPtr                    m_engineFire;
    float                           m_rotationSpeed = 0.0f;
    float                           m_enginePower = 0.0f;
    vec2f                           m_rotationV;
    vec2f                           m_cannonPosition = vec2f(-2.0f, 80.0f);

    float                           m_maxSpeedFwd = 200.0f;
    float                           m_maxSpeedBwd = 100.0f;

    vector<EnginePtr>               m_leftFrontEngine;
    vector<EnginePtr>               m_rightFrontEngine;
    vector<EnginePtr>               m_leftBackEngine;
    vector<EnginePtr>               m_rightBackEngine;
    vector<EnginePtr>               m_mainEngine;
};
