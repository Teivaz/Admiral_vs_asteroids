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
    m_count = 0;
}

void Shape::bind()
{
    ASSERT(m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
}

void* Shape::getVertexOffset() const
{
    return (void*)m_vertexOffset;
}

void* Shape::getTextureOffset() const
{
    return (void*)m_textureOffset;
}

void* Shape::getNormalsOffset() const
{
    return (void*)m_normalsOffset;
}

GLuint Shape::getStride() const
{
    return m_stride;
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
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    m_normalsOffset = 0;
    m_textureOffset = 0;
    m_vertexOffset = 0;
    m_stride = static_cast<GLuint>(sizeof(vec2f));
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
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    m_normalsOffset = 0;
    m_textureOffset = sizeof(vec2f);
    m_vertexOffset = 0;
    m_stride = static_cast<GLuint>(2 * sizeof(vec2f));
}

SeparateShape::SeparateShape()
{
}

SeparateShape::~SeparateShape()
{
}
