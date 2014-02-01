#include "Precompiled.h"
#include "Sprite.h"
#include "Controllers/ShaderManager.h"

Sprite::Sprite(Texture tex, vec2f lb, vec2f ur, ShaderProgram sp)
{
    m_texture = tex;
    m_vertsCount = 4;

    GLushort idx[] = { 0, 1, 2, 3 };

    // pos         texture
    float verts[] = { -1.0f, -1.0f, lb.x, lb.y,
        -1.0f, 1.0f, lb.x, ur.y,
        1.0f, 1.0f, ur.x, ur.y,
        1.0f, -1.0f, ur.x, lb.y
    };

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)* 4, idx, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

    init(sp);
}

Sprite::Sprite(Texture tex, vec2f lb, vec2f ur)
{
    m_texture = tex;
    m_vertsCount = 4;
    init(ShaderManager::GetInstance()->getShader(shaders::k_softLight));

    GLushort idx[] = { 0, 1, 2, 3 };

                    // pos         texture
    float verts[] = {-1.0f, -1.0f, lb.x, lb.y,
                     -1.0f, +1.0f, lb.x, ur.y,
                     +1.0f, +1.0f, ur.x, ur.y,
                     +1.0f, -1.0f, ur.x, lb.y
                    };

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)* 4, idx, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
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
