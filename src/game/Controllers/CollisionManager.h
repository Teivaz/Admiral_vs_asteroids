#pragma once
#include "collisions.h"

class PhysicNode;

class CollisionManager : public Singleton<CollisionManager>
{
    typedef std::map<string, std::vector<vec2d> > MeshMap_t;
    typedef std::list<PhysicNode*> ObjectList_t;

public:
    CollisionManager();
    ~CollisionManager();

	void							update(double dt);
	const std::vector<vec2d>&       getMesh(const string& name);
    void                            add(PhysicNode*);
    bool							contains(PhysicNode*) const;
    void							remove(PhysicNode*);

private:
	bool							_checkCollission(PhysicNode*, PhysicNode*, vec2d& point);
	const std::vector<vec2d>&		_loadMesh(const string& name);
private:
	MeshMap_t                       m_meshes;
	ObjectList_t					m_objects;

};

