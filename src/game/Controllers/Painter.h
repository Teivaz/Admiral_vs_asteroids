#pragma once

class GameObject;
MakeShared(Camera);

class Painter : public Singleton<Painter>, public has_slots<>
{
public:
    Painter();
    ~Painter();

    void                    render();
    void                    update(double);
    void                    init(int width, int height);
    void                    add(GameObject*);
    void                    remove(GameObject*);
    void                    requestSort();
    bool                    contains(GameObject*) const;
    CameraPtr               getSceneCamera() const;
	void					setSceneCameraPosition(const vec2d& position);


	signal1<const vec2d&>	onCameraMoved;

private:
    void                    _sort();

private:
    typedef std::list<GameObject*> ObjectsMap_t;
    ObjectsMap_t            m_objects;
    bool                    m_needsSorting = false;
    CameraPtr               m_sceneCamera;
    vec2d                   m_screen;
};
