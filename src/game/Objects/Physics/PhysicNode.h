#pragma once
#include "../GameObject.h"

MakeShared(Shape);

class PhysicNode : virtual public GameObject
{
    struct Impact
    {
        Impact(const vec2d& _point, const vec2d& _momentum) : point(_point), momentum(_momentum) {}
        vec2d point;
        vec2d momentum;
    };

public:
    PhysicNode(const vector<vec2d>& mesh);
    PhysicNode(const string& meshName);
    virtual ~PhysicNode();

    // GameObject
//    virtual void                    render();
    virtual void                    update(double);
#ifdef _DEBUG
    virtual void                    renderDebug();
#endif
    virtual void                    setPosition(const vec2d& p);
    virtual void                    setScale(const vec2d& s);
    virtual void                    setRotation(double r);
    virtual void					setAdditionalTransformation(const mat3d&);

    //Physics
    virtual void					onCollided(PhysicNode* other, const vec2d& point, const vec2d& momentum);
    
    const std::vector<vec2d>&		getMesh() const;
    bool							hasMoved() const;
    
    virtual void					setMass(double mass);
    virtual double					getMass() const;
    virtual void					setRadialVelocity(double value);
    virtual double					getRadialVelocity() const;
    virtual double                   getRadialVelocityDerivative() const;
    virtual void					setVelocity(double value);
    virtual double					getVelocity() const;
    virtual double                   getVelocityDerivative() const;
    virtual void 					setMoveDirection(const vec2d& dir);
    virtual const vec2d&			getMoveDirection() const;
    
    void                            setColliosionChecked();
    double                           getSqBoundingRadius() const { return m_squareBoundingRadius; }

	vec2d                           getMomentum(const vec2d& momentum);
    void                            addImpact(const vec2d& point, const vec2d& momentum);

protected:
    virtual void					_calculateTransformation();

    void                            _pocessImpacts();
protected:
    // triangle fan
    vector<vec2d>					m_collisionShape;
	GLuint							m_uniformTransformation;
    ShaderProgram					m_debugShader;
	ShapePtr						m_shape;

	bool							m_hasMoved = true;
	double							m_mass = 1.0f;
	double							m_linearVelocity = 0.0f;
    double                          m_prevLinearVelocity = 0.0f;
	double							m_radialVelocity = 0.0f;
    double                          m_prevRadialVelocity = 0.0f;
	vec2d							m_moveDirection;
    double                          m_squareBoundingRadius = 0.0f;
    vector<Impact>                  m_impacts;
    double                          m_linearVelocityDerivative = 0.0f;
    double                          m_radialVelocityDerivative = 0.0f;
};
