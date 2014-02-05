#include "Precompiled.h"
#include "Painter.h"
#include "Objects/GameObject.h"

Painter::Painter()
{
}

Painter::~Painter()
{
}

void Painter::remove(GameObject* obj)
{
    auto it = std::find(m_objects.begin(), m_objects.end(), obj);
    if (it != m_objects.end())
    {
        m_objects.erase(it);
    }
}

void Painter::add(GameObject* obj)
{
    if (contains(obj))
    {
        return;
    }
    m_objects.push_back(obj);
    requestSort();
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
    m_objects.sort(GameObject::less);
    m_needsSorting = false;
}

void Painter::requestSort()
{
    m_needsSorting = true;
}

bool Painter::contains(GameObject* obj) const
{
    auto it = std::find(m_objects.begin(), m_objects.end(), obj);
    return it != m_objects.end();
}

void Painter::update(float dt)
{
    // Game object can delete itself in update so this is needed to prevent iterator invalidation

    auto it = m_objects.begin(), end = m_objects.end();
    while (it != end)
    {
        auto object = *it;
        ++it;
        object->update(dt);
    }
}