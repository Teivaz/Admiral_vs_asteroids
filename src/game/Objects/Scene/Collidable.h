#pragma once
#include "../GameObject.h"

class Animation;

class Collidable : virtual public GameObject
{
public:
    Collidable();
    virtual ~Collidable();

    bool isCollidedWith(Collidable* other);

    virtual void renderDebug();

protected:
    virtual void _calculateTransformation();

private:
    // triangle fan
    std::vector<vec2f>  m_collisionShape;
    short*              m_indices = nullptr;

    ShaderProgram       m_debugShader;
};
