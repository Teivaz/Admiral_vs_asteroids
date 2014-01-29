#pragma once

class GameObject;

class Painter : public Singleton<Painter>
{
public:
    Painter(EGLDisplay, EGLSurface);
    ~Painter();

    void                    render();
    void                    add(GameObject*);
    void                    remove(GameObject*);

private:
    void                    _sort();

private:
    typedef std::list<GameObject*> ObjectsMap_t;
    ObjectsMap_t            m_objects;
    bool                    m_needsSorting = false;
    EGLDisplay              m_display = nullptr;
    EGLSurface              m_surface = nullptr;
};
