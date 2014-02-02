#pragma once

class State;
class Shader;
class Shape;

class GameObject : public has_slots<>
{
public:
    void init(ShaderProgram, Shape*);
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
    inline DrawMode                 getDrawMode() const
    {
        return m_mode;
    }

    GLsizei                         getVertsCount() const;

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

    // sort purpose

    inline bool operator <(const GameObject& obj) const
    {
        return m_renderLayer < obj.m_renderLayer;
    }

    void setRenderLayer(int layer);

private:
    void                            _bindAttributes();
    void                            _calculateTransformation();

    bool                            m_transformationIsDirty = true;

protected:
    Texture                         m_texture = 0;
    ShaderProgram                   m_shader = 0;
    DrawMode                        m_mode = GL_TRIANGLE_FAN;
    Shape*                          m_shape = nullptr;

    // Shader attributes and uniforms
    GLuint                          m_attributePosition = 0;
    GLuint                          m_attributeTexturePosition = 0;
    GLuint                          m_uniformTexture = 0;
    GLuint                          m_uniformTransformation = 0;
    
    vec2f                           m_position = 0.0f;
    vec2f                           m_scale = 1.0f;
    float                           m_rotation = 0.0f;
    mat3f                           m_transformationMatrix;

    int                             m_renderLayer = 0;
};
