#include "Precompiled.h"
#include "Collidable.h"
#include "Controllers/ShaderManager.h"

Collidable::Collidable()
{
    m_debugShader = ShaderManager::GetInstance()->getShader(shaders::k_red);
    m_collisionShape.push_back(0.1);
    m_collisionShape.push_back(vec2f(0.1, -0.1));
    m_collisionShape.push_back(-0.1);
    m_collisionShape.push_back(vec2f(-0.1, 0.1));
    m_indices = new GLshort[4];
    m_indices[0] = 0;
    m_indices[1] = 1;
    m_indices[2] = 2;
    m_indices[3] = 3;
}

Collidable::~Collidable()
{
    delete[] m_indices;
}

void Collidable::renderDebug()
{
    glUseProgram(m_debugShader);
    GLuint verts = 3;// glGetAttribLocation(m_debugShader, "a_position");
    GLuint transformations_uniform = glGetUniformLocation(m_debugShader, "u_transformation");

    //if (transformations_uniform)
   //     glUniformMatrix3fv(transformations_uniform, 1, GL_FALSE, &m_transformationMatrix.a1);

    glEnableVertexAttribArray(verts);
    glVertexAttribPointer(
        verts,
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(vec2f),
        m_collisionShape.data());

    glDrawElements(GL_LINE_LOOP, 4, GL_SHORT, m_indices);

}

bool Collidable::isCollidedWith(Collidable* other)
{
    return false;
}

void Collidable::_calculateTransformation()
{
    GameObject::_calculateTransformation();
    for (vec2f& vertex : m_collisionShape)
    {
        vec3f v(vertex.x, vertex.y, 0.0f);
        v = m_transformationMatrix * v;
//        vertex.x = v.x;
//        vertex.y = v.y;
//        vertex = m_transformationMatrix * vertex;
    }
}
