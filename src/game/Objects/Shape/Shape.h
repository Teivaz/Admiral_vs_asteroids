#pragma once

class Shape
{
public:
    Shape();
    virtual ~Shape();
    virtual void*                   getVertexOffset() const = 0;
    virtual void*                   getTextureOffset() const = 0;
    virtual GLuint                  getStride() const = 0;

    void                            bind();
    inline GLsizei                  getCount() const
    {
        return m_count;
    }
protected:
    void                            _deleteBuffers();
    void                            _createSequentialIbo();
protected:
    GLsizei                         m_count = 0;
    Ibo                             m_ibo = 0;
    Vbo                             m_vbo = 0;
};

class SimpleShape : public Shape
{
public:
    SimpleShape();
    SimpleShape(const std::vector<vec2f>& verts);
    virtual ~SimpleShape();

    void                            create(const std::vector<vec2f>& verts);
    virtual void*                   getVertexOffset() const;
    virtual void*                   getTextureOffset() const;
    virtual GLuint                  getStride() const;
};

class SeparateShape : public Shape
{
    SeparateShape();
    SeparateShape(const std::vector<vec2f>& verts, const std::vector<vec2f>& tex);
    virtual ~SeparateShape();

    void                            create(const std::vector<vec2f>& verts, const std::vector<vec2f>& tex);
    virtual void*                   getVertexOffset() const;
    virtual void*                   getTextureOffset() const;
    virtual GLuint                  getStride() const;
};

