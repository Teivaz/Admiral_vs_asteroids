#include "Precompiled.h"
#include "Sprite.h"
#include "Controllers/ShaderManager.h"
#include "Shape/Shape.h"

Sprite::Sprite(Texture tex, vec2f lb, vec2f ur, ShaderProgram sp)
{
    m_size = abs(lb - ur);
    m_origin = vec2f(min(lb.x, ur.x), min(lb.y, ur.y));
    std::vector<vec2f> verts(4);
    verts[1] = lb;
    verts[0] = vec2f(lb.x, ur.y);
    verts[3] = ur;
    verts[2] = vec2f(ur.x, lb.y);
    SimpleShape* shape = new SimpleShape(verts);
    init(sp, shape, tex);
}

Sprite::Sprite(Texture tex, vec2f textureLeftBottom, vec2f textureUpRight, ShaderProgram sp, vec2f position, vec2f size)
{
    m_size = size;
    m_origin = position;
    std::vector<vec2f> texVerts(4);
    texVerts[1] = textureLeftBottom;
    texVerts[0] = vec2f(textureLeftBottom.x, textureUpRight.y);
    texVerts[3] = textureUpRight;
    texVerts[2] = vec2f(textureUpRight.x, textureLeftBottom.y);

    std::vector<vec2f> verts(4);
    verts[0] = position;
    verts[1] = vec2f(position.x, position.y + size.y);
    verts[2] = position + size;
    verts[3] = vec2f(position.x + size.x, position.y);
    SeparateShape* shape = new SeparateShape(verts, texVerts);
    init(sp, shape, tex);
}

Sprite::~Sprite()
{
}

bool Sprite::isPointInside(const vec2f& pt)
{
    vec3f lb = vec3f(m_origin.x, m_origin.y, 1);
    vec3f ur = vec3f(m_size.x + m_origin.x, m_size.y + m_origin.y, 1);
    lb = m_transformationMatrix * lb;
    ur = m_transformationMatrix * ur;
    return ((pt.x > lb.x) && (pt.y > lb.y) && (pt.x < ur.x) && (pt.y < ur.y));
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
