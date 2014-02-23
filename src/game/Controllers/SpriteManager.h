#pragma once
#include "sprites.h"

class Sprite;
class Animation;

class SpriteManager : public Singleton<SpriteManager>
{
    struct SpriteRect
    {
        SpriteRect(){};
        SpriteRect(vec2f _lb, vec2f _ur, Texture _tex, vec2i originalSize)
            : lb(_lb), ur(_ur), tex(_tex), sizePx(originalSize)
        {};
        vec2f lb;
        vec2f ur;
        Texture tex;
        vec2i sizePx;
    };

    struct AnimationFrameData
    {
        string sprite;
        vec2f anchor;
        vec2f scale;
        vec2f offset;
        float rotation = 0;
    };

    struct AnimationData
    {
        float fps = 30;
        vector<AnimationFrameData> frames;
    };

    typedef std::map<string, AnimationData> AnimationMap_t;
    typedef std::map<string, SpriteRect> SpriteRectMap_t;

public:
    SpriteManager();
    ~SpriteManager();

    vec2i                   getSpriteSizei(const string& name);
    vec2f                   getSpriteSize(const string& name);
    Sprite*                 createSprite(const string& name, bool autorender = true, int renderLayer = 0);
    Sprite*                 createSprite(const string& name, vec2f position, vec2f size, bool autorender = true, int renderLayer = 0);
    void                    loadAtlas(const string& name);

    Animation*              createAnimation(const string& name);

private:
    SpriteRect&             _getSpriteRect(const string& name);
    Animation*              _animationFromFramesData(const AnimationData& data);

private:
    SpriteRectMap_t         m_spriteRectMap;
    AnimationMap_t          m_animations;
};
