#include "Precompiled.h"
#include "PhysicNode.h"
#include "Controllers/ShaderManager.h"
#include "Controllers/Camera.h"
#include "Controllers/CollisionManager.h"
#include "Controllers/ShaderAttributes.h"
#include "Objects/Shape/Shape.h"

PhysicNode::PhysicNode(const vector<vec2f>& mesh)
: m_collisionShape(mesh)
{
    m_debugShader = ShaderManager::GetInstance()->getShader(shaders::k_red);
	m_uniformTransformation = glGetUniformLocation(m_debugShader, "u_transformation");
	SimpleShape* shape = new SimpleShape;
	shape->create(m_collisionShape);
	m_shape.reset(shape);
	CollisionManager::GetInstance()->add(this);
    for (int i = 1; i < m_collisionShape.size(); ++i)
        m_squareBoundingRadius = max(m_squareBoundingRadius, (m_collisionShape[0] - m_collisionShape[i]).SqLength());
}

PhysicNode::PhysicNode(const string& meshName)
: m_collisionShape(CollisionManager::GetInstance()->getMesh(meshName))
{
	m_debugShader = ShaderManager::GetInstance()->getShader(shaders::k_red);
	m_uniformTransformation = glGetUniformLocation(m_debugShader, "u_transformation");
	SimpleShape* shape = new SimpleShape;
	vec2f offset = - m_collisionShape[0];
	for (vec2f& v : m_collisionShape)
	{
		v += offset;
	}
	shape->create(m_collisionShape);
	m_shape.reset(shape);
    CollisionManager::GetInstance()->add(this);
    for (int i = 1; i < m_collisionShape.size(); ++i)
        m_squareBoundingRadius = max(m_squareBoundingRadius, (m_collisionShape[0] - m_collisionShape[i]).SqLength());
}

PhysicNode::~PhysicNode()
{
	CollisionManager::GetInstance()->remove(this);
}

void PhysicNode::update(float dt)
{
	vec2f delta = m_direction * m_speed * dt / 1000.f;
	adjustPosition(delta);
}

void PhysicNode::renderDebug()
{
	GameObject::render();
    glUseProgram(m_debugShader);
	m_shape->bind();
	if (m_camera)
	{
		mat3f transform = m_camera->getTransformationMatrix() * getTransformation();
		glUniformMatrix3fv(m_uniformTransformation, 1, GL_FALSE, &transform.a1);
	}
	else
	{
		glUniformMatrix3fv(m_uniformTransformation, 1, GL_FALSE, &getTransformation().a1);
	}

    glEnableVertexAttribArray(Attributes::VERTEX_COORDINATES);
    glVertexAttribPointer(
		Attributes::VERTEX_COORDINATES,
        2,
        GL_FLOAT,
        GL_FALSE,
        0,
		0);

	glDrawArrays(GL_LINE_LOOP, 0, m_collisionShape.size());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void PhysicNode::_calculateTransformation()
{
    GameObject::_calculateTransformation();
    for (vec2f& vertex : m_collisionShape)
    {
        vec3f v(vertex.x, vertex.y, 0.0f);
        v = m_transformationMatrix * v;
        vertex.x = v.x;
        vertex.y = v.y;
    }
}

void PhysicNode::setPosition(const vec2f& p)
{
	if (p == m_position)
		return;
	m_position = p;
	m_transformationIsDirty = true;
    m_hasMoved = true;
}

void PhysicNode::setScale(const vec2f& s)
{
	if (s == m_scale)
		return;
	m_scale = s;
    m_transformationIsDirty = true;
    m_hasMoved = true;
}

void PhysicNode::setRotation(float r)
{
	if (r == m_rotation)
		return;
	m_rotation = r;
    m_transformationIsDirty = true;
    m_hasMoved = true;
}

const std::vector<vec2f>& PhysicNode::getMesh() const
{
	return m_collisionShape;
}

void PhysicNode::onCollided(PhysicNode* other, vec2f point)
{
}

bool PhysicNode::hasMoved() const
{
	return m_hasMoved;
}

float PhysicNode::getEnergy() const
{
	return getSpeed() * getMass();
}
void PhysicNode::setMass(float mass)
{
	m_mass = mass;
}
float PhysicNode::getMass() const
{
	return m_mass;
}
void PhysicNode::setDirection(const vec2f& dir)
{
	m_direction = dir;
}
const vec2f& PhysicNode::getDirection() const
{
	return m_direction;
}
void PhysicNode::setSpeed(float speed)
{
	m_speed = speed;
}
float PhysicNode::getSpeed() const
{
	return m_speed;
}
void PhysicNode::setColliosionChecked()
{
    m_hasMoved = false;
}
void PhysicNode::setAdditionalTransformation(const mat3f& mat)
{
    m_AdditionalTransformation = mat;
    m_transformationIsDirty = true;
    m_hasMoved = true;
}