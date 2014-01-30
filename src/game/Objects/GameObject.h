#pragma once

class State;
class Shader;

class GameObject : public has_slots<>
{
public:
    virtual ~GameObject();
    virtual void                    render();
    virtual void                    update(float) = 0;
    virtual void                    bindAttributes() = 0;

    //******************************************************
    inline Texture                  getTexture() const
    {
        return m_texture;
    }
    inline ShaderProgram            getProgram() const
    {
        return m_shader;
    }
    inline Vbo                      getVbo() const
    {
        return m_vbo;
    }
    inline Ibo                      getIbo() const
    {
        return m_ibo;
    }
    inline DrawMode                 getDrawMode() const
    {
        return m_mode;
    }
    inline GLsizei                  getVertsCount() const
    {
        return m_vertsCount;
    }
    //******************************************************

    inline const vec2f&             getPosition() const
    {
        return m_position;
    }
    inline const vec2f&             getScale() const
    {
        return m_scale;
    }
    inline float                    getRotation() const
    {
        return m_rotation;
    }
    inline void                     setPosition(const vec2f& p)
    {
        m_position = p;
    }
    inline void                     setScale(const vec2f& s)
    {
        m_scale = s;
    }
    inline void                     setRotation(float r)
    {
        m_rotation = r;
    }
    inline void                     adjustPosition(const vec2f& p)
    {
        m_position += p;
    }
    inline void                     adjustScale(const vec2f& s)
    {
        m_scale += s;
    }
    inline void                     adjustRotation(float r)
    {
        m_rotation += r;
    }
    //******************************************************
protected:
    Texture                         m_texture = 0;
    ShaderProgram                   m_shader = 0;
    Vbo                             m_vbo = 0;
    Ibo                             m_ibo = 0;
    DrawMode                        m_mode = GL_TRIANGLE_FAN;
    GLsizei                         m_vertsCount = 0;

    vec2f                           m_position = 0.0f;
    vec2f                           m_scale = 1.0f;
    float                           m_rotation = 0.0f;
};
