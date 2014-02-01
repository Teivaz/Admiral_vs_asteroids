#pragma once

class State;
class Shader;

class GameObject : public has_slots<>
{
public:
    void init(ShaderProgram); 
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
    void                            setPosition(const vec2f& p);
    void                            setScale(const vec2f& s);
    void                            setRotation(float r);
    void                            adjustPosition(const vec2f& p);
    void                            adjustScale(const vec2f& s);
    void                            adjustRotation(float r);
    //******************************************************

private:
    void                            _bindAttributes();
    void                            _calculateTransformation();

    bool                            m_transformationIsDirty = true;

protected:
    Texture                         m_texture = 0;
    ShaderProgram                   m_shader = 0;
    Vbo                             m_vbo = 0;
    Ibo                             m_ibo = 0;
    DrawMode                        m_mode = GL_TRIANGLE_FAN;
    GLsizei                         m_vertsCount = 0;

    // Shader attributes and uniforms
    GLuint                          m_attributePosition = 0;
    GLuint                          m_attributeTexturePosition = 0;
    GLuint                          m_uniformTexture = 0;
    GLuint                          m_uniformTransformation = 0;



    vec2f                           m_position = 0.0f;
    vec2f                           m_scale = 1.0f;
    float                           m_rotation = 0.0f;
    mat3f                           m_transformationMatrix;
};
