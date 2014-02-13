#include "Precompiled.h"
#include "Collidable.h"
#include "Controllers/ShaderManager.h"
#include "Controllers/Camera.h"
#include "Controllers/CollisionManager.h"
#include "Controllers/ShaderAttributes.h"
#include "Objects/Shape/Shape.h"

Collidable::Collidable(const vector<vec2f>& mesh)
: m_collisionShape(mesh)
{
    m_debugShader = ShaderManager::GetInstance()->getShader(shaders::k_red);
	m_uniformTransformation = glGetUniformLocation(m_debugShader, "u_transformation");
	SimpleShape* shape = new SimpleShape;
	shape->create(m_collisionShape);
	m_shape.reset(shape);
}

Collidable::Collidable(const string& meshName)
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
}

Collidable::~Collidable()
{
	CollisionManager::GetInstance()->remove(this);
}

void Collidable::renderDebug()
{
	GameObject::render();
    glUseProgram(m_debugShader);
	m_shape->bind();
	if (m_camera)
	{
		mat3f transform = m_camera->getTransformationMatrix() * m_transformationMatrix;
		glUniformMatrix3fv(m_uniformTransformation, 1, GL_FALSE, &transform.a1);
	}
	else
	{
		glUniformMatrix3fv(m_uniformTransformation, 1, GL_FALSE, &m_transformationMatrix.a1);
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
	//glDrawArrays(GL_TRIANGLE_FAN, 0, m_collisionShape.size());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Collidable::_calculateTransformation()
{
    GameObject::_calculateTransformation();
    for (vec2f& vertex : m_collisionShape)
    {
        vec3f v(vertex.x, vertex.y, 0.0f);
        v = m_transformationMatrix * v;
        vertex.x = v.x;
        vertex.y = v.y;
        //vertex = m_transformationMatrix * vertex;
    }
}

void Collidable::setPosition(const vec2f& p)
{
	if (p == m_position)
		return;
	m_position = p;
	m_transformationIsDirty = true;
}

void Collidable::setScale(const vec2f& s)
{
	if (s == m_scale)
		return;
	m_scale = s;
	m_transformationIsDirty = true;
}

void Collidable::setRotation(float r)
{
	if (r == m_rotation)
		return;
	m_rotation = r;
	m_transformationIsDirty = true;
}

const std::vector<vec2f>& Collidable::getMesh() const
{
	return m_collisionShape;
}

void Collidable::onCollided(Collidable* other, vec2f point)
{

}
