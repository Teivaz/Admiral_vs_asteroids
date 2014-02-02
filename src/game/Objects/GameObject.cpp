#include "Precompiled.h"
#include "GameObject.h"
#include "States/State.h"
#include "Controllers/Painter.h"
#include "Shape/Shape.h"

GameObject::~GameObject()
{
    Painter::GetInstance()->remove(this);
    delete m_shape;
}

void GameObject::init(ShaderProgram shader, Shape* shape, Texture tex)
{
    if (m_shape)
        delete m_shape;
    m_shape = shape;
    setShader(shader);
    m_texture = tex;
}

void GameObject::setShader(ShaderProgram shader)
{
    m_shader = shader;
    m_uniformTexture = glGetUniformLocation(shader, "u_texture");
    m_uniformTransformation = glGetUniformLocation(shader, "u_transformation");
    m_attributePosition = glGetAttribLocation(shader, "a_position");
    m_attributeTexturePosition = glGetAttribLocation(shader, "a_texturePosition");
}

void GameObject::setRenderLayer(int layer)
{
    m_renderLayer = layer;
    if (Painter::GetInstance()->contains(this))
    {
        Painter::GetInstance()->requestSort();
    }
}

void GameObject::render()
{
    if (m_transformationIsDirty)
        _calculateTransformation();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    m_shape->bind();
    glUseProgram(getProgram());
    _bindAttributes();
    glDrawArrays(getDrawMode(), 0, m_shape->getCount());
}

void GameObject::_bindAttributes()
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
        glUniformMatrix3fv(m_uniformTransformation, 1, GL_FALSE, &m_transformationMatrix.a1);

    bindAttributes();
}

void GameObject::setPosition(const vec2f& p)
{
    if (p == m_position)
        return;
    m_position = p;
    m_transformationIsDirty = true;
}
void GameObject::setScale(const vec2f& s)
{
    if (s == m_scale)
        return;
    m_scale = s;
    m_transformationIsDirty = true;
}
void GameObject::setRotation(float r)
{
    if (r == m_rotation)
        return;
    m_rotation = r;
    m_transformationIsDirty = true;
}
void GameObject::adjustPosition(const vec2f& p)
{
    setPosition(p + getPosition());
}
void GameObject::adjustScale(const vec2f& s)
{
    setScale(s + getScale());
}
void GameObject::adjustRotation(float r)
{
    setRotation(r + getRotation());
}

GLsizei GameObject::getVertsCount() const
{
    return m_shape->getCount();
}

void GameObject::_calculateTransformation()
{
    m_transformationMatrix.SetScale(m_scale);
    mat3f rot;
    rot.SetRotatation(m_rotation);
    m_transformationMatrix = m_transformationMatrix * rot;
    mat3f translate;
    translate.SetTranslation(m_position);
    m_transformationMatrix = m_transformationMatrix * translate;
    m_transformationIsDirty = false;
}
