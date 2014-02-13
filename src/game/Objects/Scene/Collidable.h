#pragma once
#include "../GameObject.h"

MakeShared(Shape);

class Collidable : virtual public GameObject
{
public:
	Collidable(const vector<vec2f>& mesh);
	Collidable(const string& meshName);
	virtual ~Collidable();
	
	virtual void					renderDebug();
	virtual void                    setPosition(const vec2f& p);
	virtual void                    setScale(const vec2f& s);
	virtual void                    setRotation(float r);

	virtual void					onCollided(Collidable* other, vec2f point);

	const std::vector<vec2f>&		getMesh() const;

protected:
    virtual void					_calculateTransformation();

private:
    // triangle fan
    vector<vec2f>					m_collisionShape;
	GLuint							m_uniformTransformation;
    ShaderProgram					m_debugShader;
	ShapePtr						m_shape;

	bool							m_hasMoved = true;
	float							m_mass = 1.0f;
	float							m_speed = 0.0f;
	vec2f							m_direction;
};
