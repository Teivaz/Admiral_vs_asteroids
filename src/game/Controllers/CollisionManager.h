#pragma once
#include "collisions.h"

class Collidable;

class CollisionManager : public Singleton<CollisionManager>
{
    typedef std::map<string, std::vector<vec2f> > MeshMap_t;
	typedef std::list<Collidable*> ObjectList_t;

public:
    CollisionManager();
    ~CollisionManager();

	void							update(float dt);
	const std::vector<vec2f>&       getMesh(const string& name);
	void                            add(Collidable*);
	bool							contains(Collidable*) const;
	void							remove(Collidable*);

private:
	bool							_checkCollission(Collidable*, Collidable*, const vec2f& point);
	const std::vector<vec2f>&		_loadMesh(const string& name);
private:
	MeshMap_t                       m_meshes;
	ObjectList_t					m_objects;

};

