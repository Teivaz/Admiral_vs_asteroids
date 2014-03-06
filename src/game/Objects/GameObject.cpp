#include "Precompiled.h"
#include "GameObject.h"
#include "States/State.h"
#include "Controllers/Painter.h"
#include "Shape/Shape.h"

GameObject::GameObject()
{
	m_additionalTransformation.SetIdentity();
}

GameObject::~GameObject()
{
	if (m_painter)
	{
		m_painter->remove(this);
	}
}

void GameObject::setRenderLayer(int layer)
{
    m_renderLayer = layer;
    if (m_painter && m_painter->contains(this))
    {
        m_painter->requestSort();
    }
}

void GameObject::render()
{
}

void GameObject::setPosition(const vec2d& p)
{
    if (p == m_position)
        return;
    m_position = p;
    m_transformationIsDirty = true;
}

void GameObject::setScale(const vec2d& s)
{
    if (s == m_scale)
        return;
    m_scale = s;
    m_transformationIsDirty = true;
}

void GameObject::setRotation(double r)
{
    if (r == m_rotation)
        return;
    m_rotation = r;
    m_transformationIsDirty = true;
}

void GameObject::adjustPosition(const vec2d& p)
{
    setPosition(p + getPosition());
}

void GameObject::adjustScale(const vec2d& s)
{
    setScale(s + getScale());
}

void GameObject::adjustRotation(double r)
{
    setRotation(r + getRotation());
}

void GameObject::_calculateTransformation()
{
    m_transformationMatrix.SetScale(m_scale);
    mat3d rot;
    rot.SetRotatation(m_rotation);
    mat3d translate;
    translate.SetTranslation(m_position);
    m_transformationMatrix = rot * m_transformationMatrix;
    m_transformationMatrix = translate * m_transformationMatrix;
	m_transformationMatrix = m_additionalTransformation * m_transformationMatrix;
    m_transformationIsDirty = false;
}

const vec2d& GameObject::getPosition() const
{
    return m_position;
}

const vec2d& GameObject::getScale() const
{
    return m_scale;
}

double GameObject::getRotation() const
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

const mat3d& GameObject::getTransformation()
{
	if (m_transformationIsDirty)
	{
		_calculateTransformation();
	}
	return m_transformationMatrix;
}

void GameObject::setAdditionalTransformation(const mat3d& mat)
{
	if (mat == m_additionalTransformation)
		return;
	m_additionalTransformation = mat;
	m_transformationIsDirty = true;
}

void GameObject::setPainter(Painter* p)
{
	if (m_painter)
		m_painter->remove(this);
	m_painter = p;
}
