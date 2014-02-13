#include "Precompiled.h"
#include "CollisionManager.h"
#include "utils/FileUtils.h"

CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{

}

const std::vector<vec2f>& CollisionManager::getMesh(const string& name)
{
	auto it = m_meshes.find(name);
	if (it == m_meshes.end())
	{
		return _loadMesh(name);
	}
	else
	{
		return it->second;
	}
}

void CollisionManager::add(Collidable* c)
{
	
}

bool CollisionManager::contains(Collidable* c) const
{
	return false;
}

void CollisionManager::remove(Collidable* c)
{

}

const std::vector<vec2f>& CollisionManager::_loadMesh(const string& name)
{
	char* data;
	size_t size;
	FileUtils::LoadFile(name.c_str(), &data, size, FileUtils::app);
	ASSERT(data && "Error opening collision file");
	Json::Reader reader;
	Json::Value root;
	bool result = reader.parse(data, data + size, root, false);
	ASSERT(result && "Error parsing collision file");
	delete[] data;

	std::vector<vec2f>& mesh = m_meshes[name];
	if (root.isArray())
	{
		Json::Value::iterator it = root.begin();
		Json::Value::iterator end = root.end();
		for (; it != end; ++it)
		{
			const Json::Value vertex = *it;
			float x = static_cast<float>(vertex[1u].asDouble());
			float y = -static_cast<float>(vertex[0u].asDouble());
			mesh.push_back(vec2f(x, y));
		}
		ASSERT(mesh.size() > 3 && "Collision mesh should contain at least 3 vertices");
		mesh.push_back(mesh[1]);
	}
	else
	{
		ASSERT(false, "Error collision file format");
	}
	return mesh;
}

void CollisionManager::update(float dt)
{

}
