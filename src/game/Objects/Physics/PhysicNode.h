#pragma once
#include "../GameObject.h"

MakeShared(Shape);

class PhysicNode : virtual public GameObject
{
public:
    PhysicNode(const vector<vec2f>& mesh);
    PhysicNode(const string& meshName);
    virtual ~PhysicNode();
    
    virtual void                    renderDebug();
    virtual void                    setPosition(const vec2f& p);
    virtual void                    setScale(const vec2f& s);
    virtual void                    setRotation(float r);
    virtual void                    setAdditionalTransformation(const mat3f&);
    virtual void                    update(float dt);
    
    virtual void					onCollided(PhysicNode* other, vec2f point);
    
    const std::vector<vec2f>&		getMesh() const;
    bool							hasMoved() const;
    
    virtual void					setMass(float mass);
    virtual float					getMass() const;
    virtual void					setDirection(const vec2f& dir);
    virtual const vec2f&			getDirection() const;
    virtual void					setSpeed(float speed);
    virtual float					getSpeed() const;
    
    void                            setColliosionChecked();
    virtual float					getEnergy() const;
    float                           getSqBoundingRadius() const 
    { 
        return m_squareBoundingRadius * getScale().SqLength();
    }

protected:
    virtual void					_calculateTransformation();

protected:
    // triangle fan
    vector<vec2f>					m_collisionShape;
	GLuint							m_uniformTransformation;
    ShaderProgram					m_debugShader;
	ShapePtr						m_shape;

	bool							m_hasMoved = true;
	float							m_mass = 1.0f;
	float							m_speed = 0.0f;
	vec2f							m_direction;
    float                           m_squareBoundingRadius = 0.0f;
};
