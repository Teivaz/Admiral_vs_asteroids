#pragma once
#include "GameObject.h"

MakeShared(Camera);

class Sprite: public GameObject
{
public:
    Sprite(Texture, vec2d textureLeftBottom, vec2d textureUpRight, ShaderProgram);
    Sprite(Texture, vec2d textureLeftBottom, vec2d textureUpRight, ShaderProgram, vec2d position, vec2d size);
    virtual ~Sprite();

    virtual void                    render();
    virtual void                    update(double);
    virtual void                    bindAttributes();

    /*
    virtual void                    setPosition(const vec2d& p);
    virtual void                    setScale(const vec2d& s);
    virtual void                    setRotation(double r);
    virtual void                    adjustPosition(const vec2d& p);
    virtual void                    adjustScale(const vec2d& s);
    virtual void                    adjustRotation(double r);
    */
    virtual GLsizei                 getVertsCount() const;

    virtual bool                    isPointInside(const vec2d& pt);
    virtual const vec2d&            getSize();

    Texture                         getTexture() const;
    ShaderProgram                   getProgram() const;
    DrawMode                        getDrawMode() const;
    Shape*                          getShape();

    void                            init(ShaderProgram, Shape*, Texture);
    void                            setShader(ShaderProgram);
    
private:
    void                            _bindAttributes();

private:
    vec2d                           m_size;
    vec2d                           m_origin;
    Texture                         m_texture = 0;
    ShaderProgram                   m_shader = 0;
    DrawMode                        m_mode = GL_TRIANGLE_FAN;
    Shape*                          m_shape = nullptr;

    // Shader uniforms
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
inline Shape* Sprite::getShape()
{
    return m_shape;
}
