#include "Precompiled.h"
#include "Painter.h"
#include "Objects/GameObject.h"

Painter::Painter(EGLDisplay display, EGLSurface surface)
: m_display(display)
, m_surface(surface)
{

}

Painter::~Painter()
{

}

void Painter::remove(GameObject* o)
{
    auto it = std::find(m_objects.begin(), m_objects.end(), o);
    if (it != m_objects.end())
    {
        m_objects.erase(it);
    }
}

void Painter::add(GameObject* o)
{
    auto it = std::find(m_objects.begin(), m_objects.end(), o);
    if (it != m_objects.end())
    {
        return;
    }
    m_objects.push_back(o);
    m_needsSorting = true;
}

void Painter::render()
{
    if (m_needsSorting)
    {
        _sort();
    }
    for (GameObject* o : m_objects)
    {
        o->render();
    }
}

void Painter::_sort()
{
    //std::
    m_needsSorting = false;
}
