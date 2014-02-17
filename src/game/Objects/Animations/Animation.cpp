#include "Precompiled.h"
#include "Animation.h"

Animation::Animation(const KeyFrames_t& keyFrames)
: m_keyFrames(keyFrames)
{
}

Animation::Animation()
{
}

Animation::~Animation()
{
    for (Sprite* f : m_keyFrames)
    {
        delete f;
    }
}

void Animation::update(float dt)
{
    if (m_pause)
        return;

    m_timePassed += dt;
    if (m_timePassed >= m_frameTime)
    {
        m_timePassed = 0;
        m_currentFrame = _nextFrame();
    }
}

void Animation::render()
{
    if (m_currentFrame)
    {
		mat3f transform = getTransformation();
		transform = transform * m_currentFrame->getTransformation();
		m_currentFrame->setTransformation(transform);
        m_currentFrame->render();
    }
}

void Animation::setFps(float fps)
{
    m_frameTime = 1000.0f / fps;
}

void Animation::setLoop(bool v)
{
    m_loop = v;
}

void Animation::setPause(bool v)
{
    m_pause = v;
}

Sprite* Animation::_nextFrame()
{
    if (m_keyFrames.empty())
        return nullptr;

    if (m_currentFrame == nullptr)
    {
        m_frameNum = 0;
        return m_keyFrames[0];
    }
    ++m_frameNum;
    if (m_frameNum >= m_keyFrames.size())
        m_frameNum = 0;
    return m_keyFrames[m_frameNum];
}

void Animation::addFrame(Sprite* s)
{
    m_keyFrames.push_back(s);
}

void Animation::setPosition(const vec2f& p)
{
	GameObject::setPosition(p);
    for (Sprite* s : m_keyFrames)
    {
        //s->setPosition(p);
    }
}
void Animation::setScale(const vec2f& s)
{
	GameObject::setScale(s);
    for (Sprite* sp : m_keyFrames)
    {
        //sp->setScale(s);
    }
}
void Animation::setRotation(float r)
{
	GameObject::setRotation(r);
    for (Sprite* s : m_keyFrames)
    {
        //s->setRotation(r);
    }
}

void Animation::setCamera(CameraPtr cam)
{
    for (Sprite* f : m_keyFrames)
    {
        f->setCamera(cam);
    }
}
