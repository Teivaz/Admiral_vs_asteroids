#include "Precompiled.h"
#include "GameObject.h"
#include "States/State.h"
#include "Controllers/Painter.h"

GameObject::~GameObject()
{
    Painter::GetInstance()->remove(this);
}

void GameObject::init(ShaderProgram sp)
{
    m_shader = sp;
    m_uniformTexture = glGetUniformLocation(sp, "u_texture");
    m_uniformTransformation = glGetUniformLocation(sp, "u_transformation");
    m_attributePosition = glGetAttribLocation(sp, "a_position");
    m_attributeTexturePosition = glGetAttribLocation(sp, "a_texturePosition");
}

void GameObject::render()
{
    if (m_transformationIsDirty)
        _calculateTransformation();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glBindBuffer(GL_ARRAY_BUFFER, getVbo());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, getIbo());
    glUseProgram(getProgram());
    _bindAttributes();
    glDrawArrays(getDrawMode(), 0, getVertsCount());
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
        sizeof(float)* 4,
        (void*)(sizeof(float)* 0));

    glVertexAttribPointer(
        m_attributeTexturePosition,
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(float)* 4,
        (void*)(sizeof(float)* 2));

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

void GameObject::_calculateTransformation()
{
    m_transformationMatrix.SetRotatation(m_rotation);
    mat3f scale;
    scale.SetScale(m_scale);
    m_transformationMatrix = m_transformationMatrix * scale;
    mat3f translate;
    translate.SetTranslation(m_position);
    m_transformationMatrix = m_transformationMatrix * translate;
    m_transformationIsDirty = false;
}
