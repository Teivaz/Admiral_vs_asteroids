#pragma once
#include "GameObject.h"

class Sprite: public GameObject
{
public:
    Sprite(Texture, vec2f textureLeftBottom, vec2f textureUpRight, ShaderProgram);
    Sprite(Texture, vec2f textureLeftBottom, vec2f textureUpRight, ShaderProgram, vec2f position, vec2f size);
    virtual ~Sprite();
    virtual void                    update(float);
    virtual void                    render();
    virtual void                    bindAttributes();

    inline const vec2f&             getSize()
    {
        return m_size;
    }

    bool isPointInside(const vec2f& pt);

private:
    vec2f                           m_size;
    vec2f                           m_origin;
};
