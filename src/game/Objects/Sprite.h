#pragma once
#include "GameObject.h"

class Sprite: public GameObject
{
public:
    Sprite(Texture, vec2f textureLeftBottom, vec2f textureUpRight, ShaderProgram);
    Sprite(Texture, vec2f textureLeftBottom, vec2f textureUpRight, ShaderProgram, vec2f position, vec2f size);
    virtual ~Sprite();

    virtual void                    render();
    virtual void                    update(float);
    virtual void                    bindAttributes();

    /*
    virtual void                    setPosition(const vec2f& p);
    virtual void                    setScale(const vec2f& s);
    virtual void                    setRotation(float r);
    virtual void                    adjustPosition(const vec2f& p);
    virtual void                    adjustScale(const vec2f& s);
    virtual void                    adjustRotation(float r);
    */
    virtual GLsizei                 getVertsCount() const;

    virtual bool                    isPointInside(const vec2f& pt);
    virtual const vec2f&            getSize();

    Texture                         getTexture() const;
    ShaderProgram                   getProgram() const;
    DrawMode                        getDrawMode() const;
    
    void                            init(ShaderProgram, Shape*, Texture);
    void                            setShader(ShaderProgram);
    
private:
    void                            _bindAttributes();

private:
    vec2f                           m_size;
    vec2f                           m_origin;
    Texture                         m_texture = 0;
    ShaderProgram                   m_shader = 0;
    DrawMode                        m_mode = GL_TRIANGLE_FAN;
    Shape*                          m_shape = nullptr;

    // Shader attributes and uniforms
    GLuint                          m_attributePosition = 0;
    GLuint                          m_attributeTexturePosition = 0;
    GLuint                          m_uniformTexture = 0;
    GLuint                          m_uniformTransformation = 0;

};

inline Texture Sprite::getTexture() const
{
    return m_texture;
}
inline ShaderProgram Sprite::getProgram() const
{
    return m_shader;
}
inline DrawMode Sprite::getDrawMode() const
{
    return m_mode;
}
