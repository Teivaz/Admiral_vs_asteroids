#pragma once
#include "Objects/Physics/PhysicNode.h"

MakeShared(Sprite);
MakeShared(Animation);
MakeShared(Engine);
MakeShared(Cannon);

class Ship : public PhysicNode
{
public:

    enum EEngines
    {
        EMain,
        ELeftFront,
        ERightBack,
        ELeftBack,
        ERightFront
    };


    static Ship*                    create(const string& name);

    Ship(const string& name, const string& collision, Sprite* body);
    virtual ~Ship();

    void                            setLeftFrontEngine(const std::vector<EnginePtr>& eng);
    void                            setRightFrontEngine(const std::vector<EnginePtr>& eng);
    void                            setLeftBackEngine(const std::vector<EnginePtr>& eng);
    void                            setRightBackEngine(const std::vector<EnginePtr>& eng);
    void                            setMainEngine(const std::vector<EnginePtr>& eng);

    void                            setCannons(const std::vector<CannonPtr>& cannons);

    virtual void                    render();
    virtual void                    update(float dt);

    virtual void                    setPosition(const vec2f& p);
    virtual void                    setScale(const vec2f& s);
    virtual void                    setRotation(float r);

                                    // -1...+1
    void                            setRotationEnginesSpeed(float);
    void                            setEnginePower(EEngines, float);
	void                            shoot();
    virtual void					onCollided(PhysicNode* other, const vec2f& point, const vec2f& momentum);
	virtual float					getSpeed() const;

protected:

private:
    string                          m_name;
    SpritePtr                       m_ship;

    float                           m_rotationSpeed = 0.0f;
    vec2f                           m_rotationV;

    vector<EnginePtr>               m_leftFrontEngine;
    vector<EnginePtr>               m_rightFrontEngine;
    vector<EnginePtr>               m_leftBackEngine;
    vector<EnginePtr>               m_rightBackEngine;
    vector<EnginePtr>               m_mainEngine;

    vector<CannonPtr>               m_cannons;
};
