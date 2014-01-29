#include "Precompiled.h"
#include "Sprite.h"
#include "Controllers/ShaderManager.h"

Sprite::Sprite(Texture tex, vec2f lb, vec2f ur)
{
    m_texture = tex;
    m_vertsCount = 4;
    m_shader = ShaderManager::GetInstance()->getShader(shaders::k_simple_shader);

    GLushort idx[] = { 0, 1, 2, 3 };

                    // pos         texture
    float verts[] = {-1.0f, -1.0f, lb.x, lb.y,
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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)*4, idx, GL_STATIC_DRAW);
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
    auto u = glGetUniformLocation(m_shader, "uv_texture");
    glUniform1i(u, 0);

    auto vPosAttribute = glGetAttribLocation(m_shader, "vPos");
    auto vTexPosAttribute = glGetAttribLocation(m_shader, "vTexPos");
    glEnableVertexAttribArray(vPosAttribute);
    glEnableVertexAttribArray(vTexPosAttribute);
    glVertexAttribPointer(
        vPosAttribute,
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(float)*4,
        0);
    glVertexAttribPointer(
        vTexPosAttribute,
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(float)* 4,
        (void*)(sizeof(float)* 2));
}
