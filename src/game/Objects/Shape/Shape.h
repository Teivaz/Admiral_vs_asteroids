#pragma once

class Shape
{
public:
    Shape();
    virtual ~Shape();
    void*                           getVertexOffset() const;
    void*                           getTextureOffset() const;
    void*                           getNormalsOffset() const;
    GLuint                          getStride() const;

    void                            bind();
    inline GLsizei                  getCount() const
    {
        return m_count;
    }
protected:
    void                            _deleteBuffers();
protected:
    GLsizei                         m_count = 0;
    Vbo                             m_vbo = 0;
    GLuint                          m_stride = sizeof(vec2d);
    GLuint                          m_textureOffset = 0;
    GLuint                          m_vertexOffset = 0;
    GLuint                          m_normalsOffset = 0;
};

class SimpleShape : public Shape
{
public:
    SimpleShape();
    SimpleShape(const std::vector<vec2d>& verts);
    virtual ~SimpleShape();

    void                            create(const std::vector<vec2d>& verts);
};

class SeparateShape : public Shape
{
public:
    SeparateShape();
    SeparateShape(const std::vector<vec2d>& verts, const std::vector<vec2d>& tex);
    virtual ~SeparateShape();

    void                            create(const std::vector<vec2d>& verts, const std::vector<vec2d>& tex);
};

