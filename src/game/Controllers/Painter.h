#pragma once

class GameObject;

class Painter : public Singleton<Painter>
{
public:
    Painter();
    ~Painter();

    void                    render();
    void                    add(GameObject*);
    void                    remove(GameObject*);
    void                    requestSort();
    bool                    contains(GameObject*) const;

private:
    void                    _sort();

private:
    typedef std::list<GameObject*> ObjectsMap_t;
    ObjectsMap_t            m_objects;
    bool                    m_needsSorting = false;
};
