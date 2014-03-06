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
    virtual void                    update(double dt);
    virtual void                    setCamera(CameraPtr);

    virtual void                    setPosition(const vec2d& p);
    virtual void                    setScale(const vec2d& s);
    virtual void                    setRotation(double r);

                                    // -1...+1
    void                            setRotationEnginesSpeed(double);
    void                            setEnginePower(EEngines, double);
	void                            shoot();
    virtual void					onCollided(PhysicNode* other, const vec2d& point, const vec2d& momentum);
	virtual double					getSpeed() const;

protected:

private:
    string                          m_name;
    SpritePtr                       m_ship;

    double                           m_rotationSpeed = 0.0f;
    vec2d                           m_rotationV;

    vector<EnginePtr>               m_leftFrontEngine;
    vector<EnginePtr>               m_rightFrontEngine;
    vector<EnginePtr>               m_leftBackEngine;
    vector<EnginePtr>               m_rightBackEngine;
    vector<EnginePtr>               m_mainEngine;

    vector<CannonPtr>               m_cannons;
};
