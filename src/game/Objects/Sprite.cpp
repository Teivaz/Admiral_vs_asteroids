#include "Precompiled.h"
#include "Sprite.h"
#include "Controllers/ShaderManager.h"
#include "Shape/Shape.h"
#include "Controllers/Camera.h"

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
    m_attributePosition = glGetAttribLocation(shader, "a_position");
    m_attributeTexturePosition = glGetAttribLocation(shader, "a_texturePosition");
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

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    m_shape->bind();
    glUseProgram(getProgram());
    _bindAttributes();
    glDrawArrays(getDrawMode(), 0, m_shape->getCount());
}

void Sprite::_bindAttributes()
{
    glEnableVertexAttribArray(m_attributePosition);
    glEnableVertexAttribArray(m_attributeTexturePosition);

    glVertexAttribPointer(
        m_attributePosition,
        2,
        GL_FLOAT,
        GL_FALSE,
        m_shape->getStride(),
        m_shape->getVertexOffset());

    glVertexAttribPointer(
        m_attributeTexturePosition,
        2,
        GL_FLOAT,
        GL_FALSE,
        m_shape->getStride(),
        m_shape->getTextureOffset());

    if (m_uniformTexture)
        glUniform1i(m_uniformTexture, 0);

    if (m_uniformTransformation)
    {
        if (m_camera)
        {
            mat3f transform = m_camera->getTransformationMatrix() * m_transformationMatrix;
            glUniformMatrix3fv(m_uniformTransformation, 1, GL_FALSE, &transform.a1);
        }
        else
        {
            glUniformMatrix3fv(m_uniformTransformation, 1, GL_FALSE, &m_transformationMatrix.a1);
        }
    }

    bindAttributes();
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

GLsizei Sprite::getVertsCount() const
{
    return m_shape->getCount();
}

const vec2f& Sprite::getSize()
{
    return m_size;
}

void Sprite::setCamera(CameraPtr cam)
{
    m_camera = cam;
}
