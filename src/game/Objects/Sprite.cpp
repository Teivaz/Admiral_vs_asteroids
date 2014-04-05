#include "Precompiled.h"
#include "Sprite.h"
#include "Controllers/ShaderManager.h"
#include "Shape/Shape.h"
#include "Controllers/Camera.h"
#include "Controllers/ShaderAttributes.h"

Sprite::Sprite(Texture tex, vec2d lb, vec2d ur, ShaderProgram sp)
{
    m_size = abs(lb - ur);
    m_origin = vec2d(min(lb.x, ur.x), min(lb.y, ur.y));
    std::vector<vec2d> verts(4);
    verts[1] = lb;
    verts[0] = vec2d(lb.x, ur.y);
    verts[3] = ur;
    verts[2] = vec2d(ur.x, lb.y);
    SimpleShape* shape = new SimpleShape(verts);
    init(sp, shape, tex);
}

Sprite::Sprite(Texture tex, vec2d textureLeftBottom, vec2d textureUpRight, ShaderProgram sp, vec2d position, vec2d size)
{
    m_size = size;
    m_origin = position;
    std::vector<vec2d> texVerts(4);
    texVerts[1] = textureLeftBottom;
    texVerts[0] = vec2d(textureLeftBottom.x, textureUpRight.y);
    texVerts[3] = textureUpRight;
    texVerts[2] = vec2d(textureUpRight.x, textureLeftBottom.y);

    std::vector<vec2d> verts(4);
    verts[0] = position;
    verts[1] = vec2d(position.x, position.y + size.y);
    verts[2] = position + size;
    verts[3] = vec2d(position.x + size.x, position.y);
    SeparateShape* shape = new SeparateShape(verts, texVerts);
    init(sp, shape, tex);
}

Sprite::~Sprite()
{
    delete m_shape;
}

void Sprite::init(ShaderProgram shader, Shape* shape, Texture tex)
{
    if (m_shape)
        delete m_shape;
    m_shape = shape;
    setShader(shader);
    m_texture = tex;
}

void Sprite::setShader(ShaderProgram shader)
{
    m_shader = shader;
    m_uniformTexture = glGetUniformLocation(shader, "u_texture");
    m_uniformTransformation = glGetUniformLocation(shader, "u_transformation");
}

bool Sprite::isPointInside(const vec2d& pt)
{
    vec2d lb = m_origin;
    vec2d ur = m_size + m_origin;
    lb = Transform(m_transformationMatrix, lb);
    ur = Transform(m_transformationMatrix, ur);
    return ((pt.x > lb.x) && (pt.y > lb.y) && (pt.x < ur.x) && (pt.y < ur.y));
}

void Sprite::render()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    m_shape->bind();
    glUseProgram(getProgram());
    _bindAttributes();
    glDrawArrays(getDrawMode(), 0, m_shape->getCount());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Sprite::_bindAttributes()
{
    glEnableVertexAttribArray(Attributes::VERTEX_COORDINATES);

    glVertexAttribPointer(
        Attributes::VERTEX_COORDINATES,
        2,
        GL_FLOAT,
        GL_FALSE,
        m_shape->getStride(),
        m_shape->getVertexOffset());

    glEnableVertexAttribArray(Attributes::TEXTURE_COORDINATES);
    glVertexAttribPointer(
        Attributes::TEXTURE_COORDINATES,
        2,
        GL_FLOAT,
        GL_FALSE,
        m_shape->getStride(),
        m_shape->getTextureOffset());

    if (m_uniformTexture)
        glUniform1i(m_uniformTexture, 0);


    if (m_camera)
    {
		mat3f transform = m_camera->getTransformationMatrix() * getTransformation();
        glUniformMatrix3fv(m_uniformTransformation, 1, GL_FALSE, &transform.a1);
    }
    else
    {
        mat3f transform = getTransformation();
        glUniformMatrix3fv(m_uniformTransformation, 1, GL_FALSE, &transform.a1);
    }
}

void Sprite::update(double dt)
{    
}

void Sprite::bindAttributes()
{
    _bindAttributes();
}

GLsizei Sprite::getVertsCount() const
{
    return m_shape->getCount();
}

const vec2d& Sprite::getSize()
{
    return m_size;
}
