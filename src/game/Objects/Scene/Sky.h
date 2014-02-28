#pragma once
#include "Objects/GameObject.h"

MakeShared(Sprite);

class Sky : public GameObject
{
public:
	Sky();
	~Sky();

	virtual void                    update(float);
	virtual void                    render();

	virtual void                    setPosition(const vec2f& p);
	virtual void                    setScale(const vec2f& s);
	virtual void                    setRotation(float r);
	virtual void					setCamera(CameraPtr);

	void							onCameraMoved(const vec2f& newPosition);

private:

	std::vector<SpritePtr>			m_starsLevel1;
	std::vector<SpritePtr>			m_starsLevel2;
	SpritePtr						m_back;

	float							m_level1Move = 0.9f;
	float							m_level2Move = 0.5f;
};
