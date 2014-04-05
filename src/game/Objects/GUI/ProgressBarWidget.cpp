#include "Precompiled.h"
#include "ProgressBarWidget.h"
#include "../Sprite.h"
#include "Controllers/Touch.h"
#include "Objects/Shape/Shape.h"
#include "Controllers/ShaderManager.h"

ProgressBarWidget::ProgressBarWidget(Sprite* back, Sprite* full, const string& name, double value)
: m_spriteBack(back)
, m_spriteFull(full)
, m_value(value)
{
    ShaderProgram cropped = ShaderManager::GetInstance()->getShader(shaders::k_cropped);
    m_spriteFull->setShader(cropped);
    m_name = name;
}

ProgressBarWidget::~ProgressBarWidget()
{
    delete m_spriteBack;
    delete m_spriteFull;
}

void ProgressBarWidget::setPosition(const vec2d& p)
{
    m_spriteBack->setPosition(p);
    m_spriteFull->setPosition(p);
    Widget::setPosition(p);
}

void ProgressBarWidget::setScale(const vec2d& s)
{
    m_spriteBack->setScale(s);
    m_spriteFull->setScale(s);
    Widget::setScale(s);
}

void ProgressBarWidget::render()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_spriteFull->getTexture());
    m_spriteFull->getShape()->bind();    
    glUseProgram(m_spriteFull->getProgram());
    GLuint value = glGetUniformLocation(m_spriteFull->getProgram(), "u_value");
    glUniform1f(value, static_cast<float>(m_value));
    m_spriteFull->bindAttributes();
    glDrawArrays(m_spriteFull->getDrawMode(), 0, m_spriteFull->getShape()->getCount());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    m_spriteBack->render();
    Widget::render();
}

bool ProgressBarWidget::_isPointInside(const vec2d& pt)
{
    return m_spriteBack->isPointInside(pt);
}
