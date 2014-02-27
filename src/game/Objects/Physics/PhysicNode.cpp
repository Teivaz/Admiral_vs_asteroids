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
#ifdef _DEBUG
    m_debugShader = ShaderManager::GetInstance()->getShader(shaders::k_red);
    m_uniformTransformation = glGetUniformLocation(m_debugShader, "u_transformation");
#endif

    m_impacts.reserve(10);
	SimpleShape* shape = new SimpleShape;
	shape->create(m_collisionShape);
	m_shape.reset(shape);
	CollisionManager::GetInstance()->add(this);
}

PhysicNode::PhysicNode(const string& meshName)
: m_collisionShape(CollisionManager::GetInstance()->getMesh(meshName))
{
#ifdef _DEBUG
	m_debugShader = ShaderManager::GetInstance()->getShader(shaders::k_red);
    m_uniformTransformation = glGetUniformLocation(m_debugShader, "u_transformation");
#endif

    m_impacts.reserve(10);
	SimpleShape* shape = new SimpleShape;
	vec2f offset = - m_collisionShape[0];
	for (vec2f& v : m_collisionShape)
	{
		v += offset;
	}
	shape->create(m_collisionShape);
	m_shape.reset(shape);
    CollisionManager::GetInstance()->add(this);
    for (unsigned int i = 1; i < m_collisionShape.size(); ++i)
    {
        m_squareBoundingRadius = max(m_squareBoundingRadius, (m_collisionShape[0] - m_collisionShape[i]).SqLength());
    }
}

PhysicNode::~PhysicNode()
{
	CollisionManager::GetInstance()->remove(this);
}

void PhysicNode::update(float dt)
{
    _pocessImpacts();
	adjustPosition(getDirection() * getLinearSpeed() * dt / 1000.f);
	adjustRotation(getRotationSpeed() * dt / 1000.0f);
}

void PhysicNode::_pocessImpacts()
{
    vec2f force(getDirection());
    force *= getLinearSpeed();
    float netTorque = getRotationSpeed();
    for (Impact& impact : m_impacts)
    {
        vec2f center = Transform(getTransformation(), getMesh()[0]);

        float torque = impact.momentum.Dot((impact.point - center).GetRightNomal());
        netTorque += torque / getMass();
        force += impact.momentum / getMass();

    }
    PLOG("torque: %f\n", netTorque);
    setRotationSpeed(netTorque);
    setLinearSpeed(force.Normalize());
    if (getLinearSpeed())
        setDirection(force);
    m_impacts.clear();
}

#ifdef _DEBUG
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
#endif

void PhysicNode::_calculateTransformation()
{
    GameObject::_calculateTransformation();
	m_squareBoundingRadius = 0.0f;
    for (vec2f& vertex : m_collisionShape)
    {
        vertex = Transform(getTransformation(), vertex);
		m_squareBoundingRadius = max(m_squareBoundingRadius, (vertex - m_collisionShape[0]).SqLength());
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

void PhysicNode::onCollided(PhysicNode* other, const vec2f& point, const vec2f& momentum)
{
    addImpact(point, momentum);
}

void PhysicNode::addImpact(const vec2f& point, const vec2f& momentum)
{
    m_impacts.push_back(Impact(point, momentum));
}

bool PhysicNode::hasMoved() const
{
	return m_hasMoved;
}

void PhysicNode::setColliosionChecked()
{
    m_hasMoved = false;
}
void PhysicNode::setAdditionalTransformation(const mat3f& mat)
{
    m_additionalTransformation = mat;
    m_transformationIsDirty = true;
    m_hasMoved = true;
}

vec2f PhysicNode::getMomentum(const vec2f& point)
{
    vec2f toPoint(point - Transform(getTransformation(), m_collisionShape[0]));
	toPoint.TurnRight90();
	vec2f rotationPart = toPoint * getRotationSpeed();
	vec2f linearPart = getDirection() * getLinearSpeed();
	vec2f momentum = (linearPart + rotationPart) * getMass();
	return momentum;
}
void PhysicNode::setMass(float mass)
{
	m_mass = mass;
}
float PhysicNode::getMass() const
{
	return m_mass;
}
void PhysicNode::setRotationSpeed(float speed)
{
	m_rotationSpeed = speed;
}
float PhysicNode::getRotationSpeed() const
{
	return m_rotationSpeed;
}
void PhysicNode::setLinearSpeed(float speed)
{
	m_linearSpeed = speed;
}
float PhysicNode::getLinearSpeed() const
{
	return m_linearSpeed;
}
void PhysicNode::setDirection(const vec2f& dir)
{
	m_direction = dir;
	m_direction.Normalize();
}
const vec2f& PhysicNode::getDirection() const
{
	return m_direction;
}
