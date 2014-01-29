#pragma once
#include "GameObject.h"

class Sprite: public GameObject
{
public:
    Sprite(Texture, vec2f lb, vec2f ur);
    virtual ~Sprite();
    virtual void                    update(float);
    virtual void                    render();
    virtual void                    bindAttributes();

private:

};
