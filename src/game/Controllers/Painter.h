#pragma once

class GameObject;
MakeShared(Camera);

class Painter : public Singleton<Painter>
{
public:
    Painter();
    ~Painter();

    void                    render();
    void                    update(float);
    void                    init(int width, int height);
    void                    add(GameObject*);
    void                    remove(GameObject*);
    void                    requestSort();
    bool                    contains(GameObject*) const;
    CameraPtr               getSceneCamera() const;

private:
    void                    _sort();

private:
    typedef std::list<GameObject*> ObjectsMap_t;
    ObjectsMap_t            m_objects;
    bool                    m_needsSorting = false;
    CameraPtr               m_sceneCamera;
    vec2f                   m_screen;
};
