#include "Precompiled.h"
#include "GameObject.h"
#include "States/State.h"
#include "Controllers/Painter.h"

GameObject::~GameObject()
{
    Painter::GetInstance()->remove(this);
}

void GameObject::render()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glBindBuffer(GL_ARRAY_BUFFER, getVbo());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, getIbo());
    glUseProgram(getProgram());
    bindAttributes();
    glDrawArrays(getDrawMode(), 0, getVertsCount());
}
