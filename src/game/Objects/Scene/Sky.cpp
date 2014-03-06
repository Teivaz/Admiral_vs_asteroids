#include "Precompiled.h"
#include "Sky.h"
#include "Objects/Sprite.h"
#include "Controllers/SpriteManager.h"
#include "Controllers/Painter.h"

Sky::Sky()
{
	for (int a = 0; a < 50; ++a)
	{
		double x = static_cast<double>(rand() % 1000 - 500);
		double y = static_cast<double>(rand() % 1000 - 500);
		vec2d pos(x, y);
		vec2d size = SpriteManager::GetInstance()->getSpriteSize(sprites::k_star_flare_penta);
        Sprite* s = SpriteManager::GetInstance()->createSprite(sprites::k_star_flare_penta, -size / 2, size, false, 0);
        s->setScale(0.05f);
        s->setPosition(pos);
		m_starsLevel1.push_back(SpritePtr(s));
	}

	for (int a = 0; a < 50; ++a)
	{
		double x = static_cast<double>(rand() % 1000 - 500);
		double y = static_cast<double>(rand() % 1000 - 500);
		vec2d pos(x, y);
		vec2d size = SpriteManager::GetInstance()->getSpriteSize(sprites::k_star_flare_penta);
		Sprite* s = SpriteManager::GetInstance()->createSprite(sprites::k_star_flare_penta, -size / 2, size, false, 0);
		s->setScale(0.06f);
        s->setPosition(pos);
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

void Sky::update(double dt)
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

void Sky::setPosition(const vec2d& p)
{
//	GameObject::setPosition(p);
}

void Sky::setScale(const vec2d& s)
{
//	GameObject::setScale(s);
}

void Sky::setRotation(double r)
{
//	GameObject::setRotation(r);
}

void Sky::onCameraMoved(const vec2d& newCameraPosition)
{
	mat3d transform;
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
