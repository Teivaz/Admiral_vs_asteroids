#include "Precompiled.h"
#include "Shape.h"

Shape::Shape()
{
}

Shape::~Shape()
{
    _deleteBuffers();
}

void Shape::_deleteBuffers()
{
    if (m_vbo)
        glDeleteBuffers(1, &m_vbo);
    m_vbo = 0;
    if (m_ibo)
        glDeleteBuffers(1, &m_ibo);
    m_ibo = 0;
    m_count = 0;
}

void Shape::_createSequentialIbo()
{
    std::vector<GLushort> idx(m_count);
    for (GLushort a = 0; a < m_count; ++a)
        idx[a] = a;
    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)* 4, idx.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
}

void Shape::bind()
{
    ASSERT(m_vbo || m_ibo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
}

//*******************************************************************
// Simple Shape
// Texture coordinates and vertex coordinates are same
//*******************************************************************

SimpleShape::SimpleShape()
{
}

SimpleShape::SimpleShape(const std::vector<vec2f>& verts)
{
    create(verts);
}

SimpleShape::~SimpleShape()
{
}

void SimpleShape::create(const std::vector<vec2f>& verts)
{
    _deleteBuffers();
    m_count = verts.size();
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_count*sizeof(vec2f), verts.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    _createSequentialIbo();
}

GLuint SimpleShape::getStride() const
{
    return static_cast<GLuint>(sizeof(vec2f));
}

void* SimpleShape::getTextureOffset() const
{
    return (void*)(0);
}

void* SimpleShape::getVertexOffset() const
{
    return (void*)(0);
}

//*******************************************************************
// Separate Shape
// Texture coordinates and vertex coordinates are separate
//*******************************************************************

SeparateShape::SeparateShape(const std::vector<vec2f>& verts, const std::vector<vec2f>& tex)
{
    create(verts, tex);
}

void SeparateShape::create(const std::vector<vec2f>& verts, const std::vector<vec2f>& tex)
{
    _deleteBuffers();
    ASSERT(verts.size() == tex.size() && "Should be same size!");
    std::vector<vec2f> data;
    m_count = verts.size();
    data.reserve(m_count * 2);
    for (unsigned int a = 0; a < verts.size(); ++a)
    {
        data.push_back(verts[a]);
        data.push_back(tex[a]);
    }
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_count*sizeof(vec2f)*2, data.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    _createSequentialIbo();
}

SeparateShape::SeparateShape()
{
}

SeparateShape::~SeparateShape()
{
}

GLuint SeparateShape::getStride() const
{
    return static_cast<GLuint>(2*sizeof(vec2f));
}

void* SeparateShape::getTextureOffset() const
{
    return (void*)(sizeof(vec2f));
}

void* SeparateShape::getVertexOffset() const
{
    return (void*)0;
}
