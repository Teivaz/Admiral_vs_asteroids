#pragma once

class GameObject;

class Camera
{
public:
    Camera() {}
    ~Camera() {}

    void                    setViewSize(const vec2d&);
    void                    setPosition(const vec2d&);
    const mat3d&            getTransformationMatrix();

private:
    void                    _updateTransformation();

private:
    mat3d                   m_transformation;
    bool                    m_isDirty = false;
    vec2d                   m_view;
    vec2d                   m_position;
};

inline void Camera::setViewSize(const vec2d& v)
{
    m_view = v;
    m_isDirty = true;
}

inline void Camera::setPosition(const vec2d& p)
{
    m_position = p;
    m_isDirty = true;
}

inline void Camera::_updateTransformation()
{
    m_isDirty = false;
    m_transformation.SetIdentity();
    mat3d tmpMat;
    tmpMat.SetTranslation(-m_position);
    m_transformation = tmpMat * m_transformation;
    tmpMat.SetScale(1.0 / m_view);
    m_transformation = tmpMat * m_transformation;
}

inline const mat3d& Camera::getTransformationMatrix()
{
    if (m_isDirty)
    {
        _updateTransformation();
    }
    return m_transformation;
}