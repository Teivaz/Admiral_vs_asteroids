#include "Precompiled.h"
#include "Sky.h"
#include "Objects/Sprite.h"
#include "Controllers/SpriteManager.h"
#include "Controllers/Painter.h"

Sky::Sky()
{
	for (int a = 0; a < 50; ++a)
	{
		float x = static_cast<float>(rand() % 10000 - 5000);
		float y = static_cast<float>(rand() % 10000 - 5000);
		vec2f pos(x, y);
		vec2f size = SpriteManager::GetInstance()->getSpriteSize(sprites::k_star_flare_penta);
		Sprite* s = SpriteManager::GetInstance()->createSprite(sprites::k_star_flare_penta, pos, size, false, 0);
		s->setScale(0.1f);
		m_starsLevel1.push_back(SpritePtr(s));
	}

	for (int a = 0; a < 50; ++a)
	{
		float x = static_cast<float>(rand() % 10000 - 5000);
		float y = static_cast<float>(rand() % 10000 - 5000);
		vec2f pos(x, y);
		vec2f size = SpriteManager::GetInstance()->getSpriteSize(sprites::k_star_flare_penta);
		Sprite* s = SpriteManager::GetInstance()->createSprite(sprites::k_star_flare_penta, pos, size, false, 0);
		s->setScale(0.1f);
		m_starsLevel2.push_back(SpritePtr(s));
	}

	m_back.reset(SpriteManager::GetInstance()->createSprite(sprites::k_stars_back, -1, 2, false, -100));

	Sky::setCamera(Painter::GetInstance()->getSceneCamera());
}

Sky::~Sky()
{}

void Sky::setCamera(CameraPtr cam)
{
	GameObject::setCamera(cam);
	for (auto star : m_starsLevel1)
	{
		star->setCamera(cam);
	}
	for (auto star : m_starsLevel2)
	{
		star->setCamera(cam);
	}
}

void Sky::update(float dt)
{
	GameObject::update(dt);
}

void Sky::render()
{
	m_back->render();
	for (auto star : m_starsLevel2)
	{
		star->render();
	}
	for (auto star : m_starsLevel1)
	{
		star->render();
	}
}

void Sky::setPosition(const vec2f& p)
{
//	GameObject::setPosition(p);
}

void Sky::setScale(const vec2f& s)
{
//	GameObject::setScale(s);
}

void Sky::setRotation(float r)
{
//	GameObject::setRotation(r);
}

void Sky::onCameraMoved(const vec2f& newCameraPosition)
{
	mat3f transform;
	transform.SetTranslation(newCameraPosition * m_level1Move);
	for (auto star : m_starsLevel1)
	{
		star->setAdditionalTransformation(transform);
	}
	transform.SetTranslation(newCameraPosition * m_level2Move);
	for (auto star : m_starsLevel2)
	{
		star->setAdditionalTransformation(transform);
	}
}
