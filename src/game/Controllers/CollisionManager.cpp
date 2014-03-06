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

const std::vector<vec2d>& CollisionManager::getMesh(const string& name)
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

const std::vector<vec2d>& CollisionManager::_loadMesh(const string& name)
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

	std::vector<vec2d>& mesh = m_meshes[name];
	if (root.isArray())
	{
		Json::Value::iterator it = root.begin();
		Json::Value::iterator end = root.end();
		for (; it != end; ++it)
		{
			const Json::Value vertex = *it;
			double x = static_cast<double>(vertex[1u].asDouble());
			double y = -static_cast<double>(vertex[0u].asDouble());
			mesh.push_back(vec2d(x, y));
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

void CollisionManager::update(double dt)
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

            double sqDistance = (a->getPosition() - b->getPosition()).SqLength();
            double maxSqDistance = a->getSqBoundingRadius() + b->getSqBoundingRadius();
            if (sqDistance > maxSqDistance)
				continue;

			vec2d point;
			if (_checkCollission(a, b, point))
			{
				vec2d momentumA = a->getMomentum(point);
				vec2d momentumB = b->getMomentum(point);
                vec2d pointA(momentumA);
                vec2d pointB(momentumB);
                if (!(pointA == vec2d()))
                    pointA.Normalize();
                if (!(pointB == vec2d()))
                    pointB.Normalize();
                vec2d plane = (pointA - pointB) / 2.0f;
                vec2d normA = plane.Dot(momentumA);
                vec2d normB = plane.Dot(momentumB);
                momentumA = momentumA - normA + normB;
                momentumB = momentumB - normB + normA;
				a->onCollided(b, point, momentumA);
				b->onCollided(a, point, momentumB);
			}
		}
        a->setColliosionChecked();
	}
}

bool CollisionManager::_checkCollission(PhysicNode* a, PhysicNode* b, vec2d& point)
{
	vector<vec2d> meshA;
	meshA.reserve(a->getMesh().size());
	for (auto v : a->getMesh())
	{
		meshA.push_back(Transform(a->getTransformation(), v));
	}

	vector<vec2d> meshB;
	meshB.reserve(b->getMesh().size());
	for (auto v : b->getMesh())
	{
		meshB.push_back(Transform(b->getTransformation(), v));
	}

	vector<vec2d> normals;
	normals.reserve(meshA.size() - 2 + meshB.size() - 2);

	// For each edge
	for (unsigned int i = 1; i < meshA.size() - 1; ++i)
	{
		vec2d norm = meshA[i + 1] - meshA[i];
		norm = norm.GetRightNomal();
		normals.push_back(norm);
	}
	for (unsigned int i = 1; i < meshB.size() - 1; ++i)
	{
		vec2d norm = meshB[i + 1] - meshB[i];
		norm = norm.GetRightNomal();
		normals.push_back(norm);
	}

	bool collided = true;
	for (const vec2d& norm : normals)
	{
		double maxB = norm.Dot(meshB[1]);
		double minB = maxB;
		for (unsigned int i = 2; i < meshB.size() - 1; ++i)
		{
			double dot = norm.Dot(meshB[i]);
			maxB = max(maxB, dot);
			minB = min(minB, dot);
		}
		double maxA = norm.Dot(meshA[1]);
		double minA = maxA;
		for (unsigned int i = 2; i < meshA.size() - 1; ++i)
		{
			double dot = norm.Dot(meshA[i]);
			maxA = max(maxA, dot);
			minA = min(minA, dot);
		}
		bool overlapping = ((minA > minB) && (minA < maxB)) || ((minB > minA) && (minB < maxA));
		collided &= overlapping;
	}
    if (collided)
    {
        point = meshA[0] + meshB[0];
        point = point / 2.0f;
    }

	return collided;
}
