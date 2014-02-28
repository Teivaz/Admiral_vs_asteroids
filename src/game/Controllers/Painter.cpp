#include "Precompiled.h"
#include "Painter.h"
#include "Objects/GameObject.h"
#include "Camera.h"

Painter::Painter()
{
    m_sceneCamera.reset(new Camera);
}

Painter::~Painter()
{
    auto it = m_objects.begin(), end = m_objects.end();
    while (it != end)
    {
        auto object = *it;
        ++it;
        object->setPainter(nullptr);
    }
}

void Painter::init(int width, int height)
{
    m_screen.x = static_cast<float>(width);
    m_screen.y = static_cast<float>(height);
    // Screen size divided by 2
    m_sceneCamera->setViewSize(m_screen/2);
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
	obj->setPainter(this);
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
#ifdef _DEBUG
        o->renderDebug();
#endif
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

CameraPtr Painter::getSceneCamera() const
{
    return m_sceneCamera;
}

void Painter::setSceneCameraPosition(const vec2f& position)
{
	m_sceneCamera->setPosition(position);
	onCameraMoved(position);
}
