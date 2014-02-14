#include "Precompiled.h"
#include "GameObject.h"
#include "States/State.h"
#include "Controllers/Painter.h"
#include "Shape/Shape.h"

GameObject::~GameObject()
{
    Painter::GetInstance()->remove(this);
}

void GameObject::setRenderLayer(int layer)
{
    m_renderLayer = layer;
    if (Painter::GetInstance()->contains(this))
    {
        Painter::GetInstance()->requestSort();
    }
}

void GameObject::render()
{
    if (m_transformationIsDirty)
    {
        _calculateTransformation();
    }
}

void GameObject::setPosition(const vec2f& p)
{
    if (p == m_position)
        return;
    m_position = p;
    m_transformationIsDirty = true;
}

void GameObject::setScale(const vec2f& s)
{
    if (s == m_scale)
        return;
    m_scale = s;
    m_transformationIsDirty = true;
}

void GameObject::setRotation(float r)
{
    if (r == m_rotation)
        return;
    m_rotation = r;
    m_transformationIsDirty = true;
}

void GameObject::adjustPosition(const vec2f& p)
{
    setPosition(p + getPosition());
}

void GameObject::adjustScale(const vec2f& s)
{
    setScale(s + getScale());
}

void GameObject::adjustRotation(float r)
{
    setRotation(r + getRotation());
}

void GameObject::_calculateTransformation()
{
    m_transformationMatrix.SetScale(m_scale);
    mat3f rot;
    rot.SetRotatation(m_rotation);
    mat3f translate;
    translate.SetTranslation(m_position);
    m_transformationMatrix = rot * m_transformationMatrix;
    m_transformationMatrix = translate * m_transformationMatrix;
    m_transformationIsDirty = false;
}

const vec2f& GameObject::getPosition() const
{
    return m_position;
}

const vec2f& GameObject::getScale() const
{
    return m_scale;
}

float GameObject::getRotation() const
{
    return m_rotation;
}

void GameObject::renderDebug()
{

}

void GameObject::setCamera(CameraPtr cam)
{
	m_camera = cam;
}

const mat3f& GameObject::getTransformation()
{
	if (m_transformationIsDirty)
	{
		_calculateTransformation();
	}
	return m_transformationMatrix;
}
