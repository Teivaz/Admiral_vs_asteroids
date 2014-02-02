#include "Precompiled.h"
#include "Sprite.h"
#include "Controllers/ShaderManager.h"
#include "Shape/Shape.h"

Sprite::Sprite(Texture tex, vec2f lb, vec2f ur, ShaderProgram sp)
{
    m_size = vec2f(abs(lb.x - ur.x), abs(lb.y - ur.y));
    m_texture = tex;
    std::vector<vec2f> verts(4);
    verts[0] = lb;
    verts[1] = vec2f(lb.x, ur.y);
    verts[2] = ur;
    verts[3] = vec2f(ur.x, lb.y);
    SimpleShape* shape = new SimpleShape(verts);
    init(sp, shape);
}

Sprite::~Sprite()
{
}

void Sprite::render()
{
    GameObject::render();
}

void Sprite::update(float dt)
{
    
}

void Sprite::bindAttributes()
{
    auto col = glGetUniformLocation(m_shader, "u_blendColor");
    if(col)
        glUniform3f(col, 1.0f, 0.2f, 0.2f);
}
