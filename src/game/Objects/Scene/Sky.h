#pragma once
#include "Objects/GameObject.h"

MakeShared(Sprite);

class Sky : public GameObject
{
public:
	Sky();
	~Sky();

	virtual void                    update(double);
	virtual void                    render();

	virtual void                    setPosition(const vec2d& p);
	virtual void                    setScale(const vec2d& s);
	virtual void                    setRotation(double r);
	virtual void					setCamera(CameraPtr);

	void							onCameraMoved(const vec2d& newPosition);

private:

	std::vector<SpritePtr>			m_starsLevel1;
	std::vector<SpritePtr>			m_starsLevel2;
	SpritePtr						m_back;

	double							m_level1Move = 0.9f;
	double							m_level2Move = 0.5f;
};
