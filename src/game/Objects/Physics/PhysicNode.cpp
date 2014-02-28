#include "Precompiled.h"
#include "PhysicNode.h"
#include "Controllers/ShaderManager.h"
#include "Controllers/Camera.h"
#include "Controllers/CollisionManager.h"
#include "Controllers/ShaderAttributes.h"
#include "Objects/Shape/Shape.h"

PhysicNode::PhysicNode(const vector<vec2d>& mesh)
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
	vec2d offset = - m_collisionShape[0];
	for (vec2d& v : m_collisionShape)
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

void PhysicNode::update(double dt)
{
    _pocessImpacts();
    adjustPosition(getMoveDirection() * getVelocity() * dt / 1000.f);
    adjustRotation(getRadialVelocity() * dt / 1000.0f);
    if (dt > 0)
    {
        double deltaRadialVelocity = getRadialVelocity() - m_prevRadialVelocity;
        m_radialVelocityDerivative = deltaRadialVelocity / dt;
        m_prevRadialVelocity = getRadialVelocity();

        double deltaLinearVelocity = getVelocity() - m_prevLinearVelocity;
        m_linearVelocityDerivative = deltaLinearVelocity / dt;
        m_prevLinearVelocity = getVelocity();
    }

}

void PhysicNode::_pocessImpacts()
{
    vec2d force(getMoveDirection() * getVelocity());
    double netTorque = getRadialVelocity();
    for (Impact& impact : m_impacts)
    {
        vec2d center = Transform(getTransformation(), getMesh()[0]);
        double torque = impact.momentum.Dot((impact.point - center).GetLeftNormal());
        netTorque += torque / (getMass() * 2 * PI);
		vec2d normal = (impact.point - center);
		normal.Normalize();
		force += normal * impact.momentum.Dot(normal) / getMass();
    }
    setRadialVelocity(netTorque);
    setVelocity(force.Normalize());
    if (getVelocity())
        setMoveDirection(force);
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
        mat3f transform = getTransformation();
        glUniformMatrix3fv(m_uniformTransformation, 1, GL_FALSE, &transform.a1);
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
    for (vec2d vertex : m_collisionShape)
    {
        vertex = Transform(getTransformation(), vertex);
		m_squareBoundingRadius = max(m_squareBoundingRadius, (vertex - m_collisionShape[0]).SqLength());
    }
}

void PhysicNode::setPosition(const vec2d& p)
{
	if (p == m_position)
		return;
	m_position = p;
	m_transformationIsDirty = true;
    m_hasMoved = true;
}

void PhysicNode::setScale(const vec2d& s)
{
	if (s == m_scale)
		return;
	m_scale = s;
    m_transformationIsDirty = true;
    m_hasMoved = true;
}

void PhysicNode::setRotation(double r)
{
	if (r == m_rotation)
		return;
	m_rotation = r;
    m_transformationIsDirty = true;
    m_hasMoved = true;
}

const std::vector<vec2d>& PhysicNode::getMesh() const
{
	return m_collisionShape;
}

void PhysicNode::onCollided(PhysicNode* other, const vec2d& point, const vec2d& momentum)
{
    addImpact(point, momentum);
}

void PhysicNode::addImpact(const vec2d& point, const vec2d& momentum)
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
void PhysicNode::setAdditionalTransformation(const mat3d& mat)
{
    m_additionalTransformation = mat;
    m_transformationIsDirty = true;
    m_hasMoved = true;
}

vec2d PhysicNode::getMomentum(const vec2d& point)
{
    vec2d toPoint(point - Transform(getTransformation(), m_collisionShape[0]));
	toPoint.TurnRight90();
	vec2d rotationPart = toPoint * getRadialVelocity();
	vec2d linearPart = getMoveDirection() * getVelocity();
	vec2d momentum = (linearPart + rotationPart) * getMass();
	return momentum;
}
void PhysicNode::setMass(double mass)
{
	m_mass = mass;
}
double PhysicNode::getMass() const
{
	return m_mass;
}
void PhysicNode::setRadialVelocity(double speed)
{
	m_radialVelocity = speed;
}
double PhysicNode::getRadialVelocity() const
{
	return m_radialVelocity;
}
void PhysicNode::setVelocity(double speed)
{
	m_linearVelocity = speed;
}
double PhysicNode::getVelocity() const
{
	return m_linearVelocity;
}
void PhysicNode::setMoveDirection(const vec2d& dir)
{
	m_moveDirection = dir;
	m_moveDirection.Normalize();
}
const vec2d& PhysicNode::getMoveDirection() const
{
	return m_moveDirection;
}

double PhysicNode::getRadialVelocityDerivative() const
{
    return m_linearVelocityDerivative;
}

double PhysicNode::getVelocityDerivative() const
{
    return m_radialVelocityDerivative;
}
