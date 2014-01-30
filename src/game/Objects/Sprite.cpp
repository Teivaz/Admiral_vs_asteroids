#include "Precompiled.h"
#include "Sprite.h"
#include "Controllers/ShaderManager.h"

Sprite::Sprite(Texture tex, vec2f lb, vec2f ur, ShaderProgram sp)
{
    m_texture = tex;
    m_vertsCount = 4;
    m_shader = sp;

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

}

Sprite::Sprite(Texture tex, vec2f lb, vec2f ur)
{
    m_texture = tex;
    m_vertsCount = 4;
    m_shader = ShaderManager::GetInstance()->getShader("colorblend_shader.json");

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
    auto u = glGetUniformLocation(m_shader, "u_texture");
    glUniform1i(u, 0);

    auto vPosAttribute = glGetAttribLocation(m_shader, "a_position");
    auto vTexPosAttribute = glGetAttribLocation(m_shader, "a_texturePosition");
    glEnableVertexAttribArray(vPosAttribute);
    glEnableVertexAttribArray(vTexPosAttribute);

    auto col = glGetUniformLocation(m_shader, "u_blendColor");
    if(col)
        glUniform3f(col, 1.0f, 0.2f, 0.2f);


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
