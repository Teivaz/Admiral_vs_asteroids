#pragma once
#include "../GameObject.h"

MakeShared(Shape);

class PhysicNode : virtual public GameObject
{
    struct Impact
    {
        Impact(const vec2f& _point, const vec2f& _momentum) : point(_point), momentum(_momentum) {}
        vec2f point;
        vec2f momentum;
    };

public:
    PhysicNode(const vector<vec2f>& mesh);
    PhysicNode(const string& meshName);
    virtual ~PhysicNode();

    // GameObject
//    virtual void                    render();
    virtual void                    update(float);
#ifdef _DEBUG
    virtual void                    renderDebug();
#endif
    virtual void                    setPosition(const vec2f& p);
    virtual void                    setScale(const vec2f& s);
    virtual void                    setRotation(float r);
    virtual void					setAdditionalTransformation(const mat3f&);
//    virtual const vec2f&            getPosition() const;
//    virtual const vec2f&            getScale() const;
//    virtual float                   getRotation() const;
    
    //Physics
    virtual void					onCollided(PhysicNode* other, const vec2f& point, const vec2f& momentum);
    
    const std::vector<vec2f>&		getMesh() const;
    bool							hasMoved() const;
    
    virtual void					setMass(float mass);
    virtual float					getMass() const;
	virtual void					setRotationSpeed(float speed);
	virtual float					getRotationSpeed() const;
	virtual void					setLinearSpeed(float speed);
	virtual float					getLinearSpeed() const;
	virtual void 					setDirection(const vec2f& dir);
	virtual const vec2f&			getDirection() const;
    
    void                            setColliosionChecked();
    float                           getSqBoundingRadius() const 
    { 
        return m_squareBoundingRadius * getScale().SqLength();
    }

	vec2f                           getMomentum(const vec2f& momentum);
    void                            addImpact(const vec2f& point, const vec2f& momentum);

protected:
    virtual void					_calculateTransformation();

    void                            _pocessImpacts();
protected:
    // triangle fan
    vector<vec2f>					m_collisionShape;
	GLuint							m_uniformTransformation;
    ShaderProgram					m_debugShader;
	ShapePtr						m_shape;

	bool							m_hasMoved = true;
	float							m_mass = 1.0f;
	float							m_linearSpeed = 0.0f;
	float							m_rotationSpeed = 0.0f;
	vec2f							m_direction;
    float                           m_squareBoundingRadius = 0.0f;
    vector<Impact>                  m_impacts;
};
