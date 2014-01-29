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
protected:
    Texture                         m_texture = 0;
    ShaderProgram                   m_shader = 0;
    Vbo                             m_vbo = 0;
    Ibo                             m_ibo = 0;
    DrawMode                        m_mode = GL_TRIANGLE_FAN;
    GLsizei                         m_vertsCount = 0;
};
