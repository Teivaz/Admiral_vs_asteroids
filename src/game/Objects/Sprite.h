#pragma once
#include "GameObject.h"

class Sprite: public GameObject
{
public:
    Sprite(Texture, vec2f lb, vec2f ur, ShaderProgram);
    virtual ~Sprite();
    virtual void                    update(float);
    virtual void                    render();
    virtual void                    bindAttributes();

    inline const vec2f&             getSize()
    {
        return m_size;
    }

private:
    vec2f                           m_size;
};
