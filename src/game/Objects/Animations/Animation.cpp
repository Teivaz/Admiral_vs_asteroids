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

void Animation::update(double dt)
{
    if (m_pause)
        return;

    m_timePassed += dt;
    if (m_timePassed >= m_frameTime)
    {
        m_timePassed = 0;
        m_currentFrame = _nextFrame();
    }
    if (m_currentFrame == nullptr)
    {
        m_currentFrame = _nextFrame();
    }
}

void Animation::render()
{
    if (m_currentFrame)
    {
		mat3d transform = getTransformation();
		m_currentFrame->setAdditionalTransformation(transform);
        m_currentFrame->render();
    }
}

void Animation::setFps(double fps)
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

void Animation::setPosition(const vec2d& p)
{
	GameObject::setPosition(p);
}
void Animation::setScale(const vec2d& s)
{
	GameObject::setScale(s);
}
void Animation::setRotation(double r)
{
	GameObject::setRotation(r);
}

void Animation::setCamera(CameraPtr cam)
{
    for (Sprite* f : m_keyFrames)
    {
        f->setCamera(cam);
    }
}

void Animation::setFramesPosition(const vec2d& pos)
{
    for (Sprite* f : m_keyFrames)
    {
        f->setPosition(pos);
    }
}
