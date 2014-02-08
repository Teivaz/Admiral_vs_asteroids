#pragma once

#include "../Sprite.h"

class Animation : public GameObject
{
public:
    typedef std::vector<Sprite*> KeyFrames_t;

    Animation(const KeyFrames_t& keyFrames);
    Animation();
    virtual ~Animation();

    virtual void                    update(float);
    virtual void                    render();

    void                            setFps(float);
    void                            setLoop(bool);
    void                            setPause(bool);
    void                            addFrame(Sprite* frame);
    
    virtual void                    setPosition(const vec2f& p);
    virtual void                    setScale(const vec2f& s);
    virtual void                    setRotation(float r);
    virtual void                    adjustPosition(const vec2f& p);
    virtual void                    adjustScale(const vec2f& s);
    virtual void                    adjustRotation(float r);
    
private:
    Sprite*                         _nextFrame();

private:
    Sprite*                         m_currentFrame = nullptr;
    KeyFrames_t                     m_keyFrames;
    float                           m_frameTime = 1000.0f/30.0f;
    float                           m_timePassed = 0.0f;
    bool                            m_loop = true;
    bool                            m_pause = false;

    unsigned int                    m_frameNum;
};
