#pragma once

class GameObject;

class Camera
{
public:
    Camera() {}
    ~Camera() {}

    void                    setViewSize(const vec2f&);
    void                    setPosition(const vec2f&);
    const mat3f&            getTransformationMatrix();

private:
    void                    _updateTransformation();

private:
    mat3f                   m_transformation;
    bool                    m_isDirty = false;
    vec2f                   m_view;
    vec2f                   m_position;
};

inline void Camera::setViewSize(const vec2f& v)
{
    m_view = v;
    m_isDirty = true;
}

inline void Camera::setPosition(const vec2f& p)
{
    m_position = p;
    m_isDirty = true;
}

inline void Camera::_updateTransformation()
{
    m_isDirty = false;
    m_transformation.SetIdentity();
    mat3f tmpMat;
    tmpMat.SetTranslation(-m_position);
    m_transformation = tmpMat * m_transformation;
    tmpMat.SetScale(1.0f / m_view);
    m_transformation = tmpMat * m_transformation;
}

inline const mat3f& Camera::getTransformationMatrix()
{
    if (m_isDirty)
    {
        _updateTransformation();
    }
    return m_transformation;
}