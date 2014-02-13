#include "Precompiled.h"
#include "CollisionManager.h"
#include "utils/FileUtils.h"
#include "Objects/Scene/Collidable.h"

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

void CollisionManager::add(Collidable* obj)
{
	if (contains(obj))
	{
		return;
	}
	m_objects.push_back(obj);
}

bool CollisionManager::contains(Collidable* obj) const
{
	auto it = std::find(m_objects.begin(), m_objects.end(), obj);
	return it != m_objects.end();
}

void CollisionManager::remove(Collidable* obj)
{
	auto it = std::find(m_objects.begin(), m_objects.end(), obj);
	if (it != m_objects.end())
	{
		m_objects.erase(it);
	}
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
	for (Collidable* a : m_objects)
	{
		if (!a->hasMoved())
		{
			continue;
		}
		for (Collidable* b : m_objects)
		{
			if (a == b)
			{
				continue;
			}
			vec2f point;
			if (_checkCollission(a, b, point))
			{
				a->onCollided(b, point);
				b->onCollided(a, point);
			}
		}
	}
}

bool CollisionManager::_checkCollission(Collidable* a, Collidable* b, const vec2f& point)
{
	bool collided = false;
	const vector<vec2f>& meshA = a->getMesh();
	const vector<vec2f>& meshB = b->getMesh();
	for (int i = 1; i < meshA.size() - 1; ++i)
	{
		vec2f norm = meshA[i + 1] - meshA[i];
		norm.SwapElemtns();
		norm.Normalize();
	}
	for (int i = 1; i < meshB.size() - 1; ++i)
	{
		vec2f norm = meshB[i + 1] - meshB[i];
		norm.SwapElemtns();
		norm.Normalize();
	}
	return false;
}
