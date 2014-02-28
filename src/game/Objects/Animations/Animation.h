#pragma once

#include "../Sprite.h"

MakeShared(Camera);

class Animation : public GameObject
{
public:
    typedef std::vector<Sprite*> KeyFrames_t;

    Animation(const KeyFrames_t& keyFrames);
    Animation();
    virtual ~Animation();

    virtual void                    update(double);
    virtual void                    render();

    void                            setFps(double);
    void                            setLoop(bool);
    void                            setPause(bool);
    void                            addFrame(Sprite* frame);
    
    virtual void                    setPosition(const vec2d& p);
    virtual void                    setScale(const vec2d& s);
    virtual void                    setRotation(double r);

	virtual void                    setCamera(CameraPtr);
    
    void                            setFramesPosition(const vec2d& pos);

private:
    Sprite*                         _nextFrame();

private:
    Sprite*                         m_currentFrame = nullptr;
    KeyFrames_t                     m_keyFrames;
    double                           m_frameTime = 1000.0f/30.0f;
    double                           m_timePassed = 0.0f;
    bool                            m_loop = true;
    bool                            m_pause = false;

    unsigned int                    m_frameNum;
};
