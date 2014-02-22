#include "Precompiled.h"
#include "CollisionManager.h"
#include "utils/FileUtils.h"
#include "Objects/Physics/PhysicNode.h"

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

void CollisionManager::add(PhysicNode* obj)
{
	if (contains(obj))
	{
		return;
	}
	m_objects.push_back(obj);
}

bool CollisionManager::contains(PhysicNode* obj) const
{
	auto it = std::find(m_objects.begin(), m_objects.end(), obj);
	return it != m_objects.end();
}

void CollisionManager::remove(PhysicNode* obj)
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
		ASSERT(false && "Error collision file format");
	}
	return mesh;
}

void CollisionManager::update(float dt)
{
    for (PhysicNode* a : m_objects)
	{
		if (!a->hasMoved())
		{
			continue;
		}
        for (PhysicNode* b : m_objects)
		{
            if (a == b)
                continue;

            float sqDistance = (a->getPosition() - b->getPosition()).SqLength();
            float maxSqDistance = a->getSqBoundingRadius() + b->getSqBoundingRadius();
            if (sqDistance > maxSqDistance)
				continue;

			vec2f point;
			if (_checkCollission(a, b, point))
			{
				a->onCollided(b, point);
				b->onCollided(a, point);
			}
		}
        a->setColliosionChecked();
	}
}

bool CollisionManager::_checkCollission(PhysicNode* a, PhysicNode* b, const vec2f& point)
{
	vector<vec2f> meshA;
	meshA.reserve(a->getMesh().size());
	for (auto v : a->getMesh())
	{
		vec3f v3(v, 1.0f);
		v3 = a->getTransformation() * v3;
		meshA.push_back(vec2f(v3.x, v3.y));
	}

	vector<vec2f> meshB;
	meshB.reserve(b->getMesh().size());
	for (auto v : b->getMesh())
	{
		vec3f v3(v, 1.0f);
		v3 = b->getTransformation() * v3;
		meshB.push_back(vec2f(v3.x, v3.y));
	}

	vector<vec2f> normals;
	normals.reserve(meshA.size() - 2 + meshB.size() - 2);

	// For each edge
	for (unsigned int i = 1; i < meshA.size() - 1; ++i)
	{
		vec2f norm = meshA[i + 1] - meshA[i];
		norm.SwapElemtns();
		norm.x *= -1.0f;
		norm.Normalize();
		normals.push_back(norm);
	}
	for (unsigned int i = 1; i < meshB.size() - 1; ++i)
	{
		vec2f norm = meshB[i + 1] - meshB[i];
		norm.SwapElemtns();
		norm.x *= -1.0f;
		norm.Normalize();
		normals.push_back(norm);
	}

	bool collided = true;
	for (const vec2f& norm : normals)
	{
		float maxB = norm.Dot(meshB[1]);
		float minB = maxB;
		for (unsigned int i = 2; i < meshB.size() - 1; ++i)
		{
			float dot = norm.Dot(meshB[i]);
			maxB = max(maxB, dot);
			minB = min(minB, dot);
		}
		float maxA = norm.Dot(meshA[1]);
		float minA = maxA;
		for (unsigned int i = 2; i < meshA.size() - 1; ++i)
		{
			float dot = norm.Dot(meshA[i]);
			maxA = max(maxA, dot);
			minA = min(minA, dot);
		}
		bool overlapping = ((minA > minB) & (minA < maxB)) | ((minB > minA) & (minB < maxA));
		collided &= overlapping;
	}
	return collided;
}
