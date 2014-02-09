#pragma once
#include "sprites.h"

class Sprite;

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

public:
    SpriteManager();
    ~SpriteManager();

    vec2i                   getSpriteSizei(const string& name);
    vec2f                   getSpriteSize(const string& name);
    Sprite*                 createSprite(const string& name, bool autorender = true, int renderLayer = 0);
    Sprite*                 createSprite(const string& name, vec2f position, vec2f size, bool autorender = true, int renderLayer = 0);
    void                    loadAtlas(const string& name);

private:
    SpriteRect&             _getSpriteRect(const string& name);

private:
    typedef std::map<string, SpriteRect> SpriteRectMap_t;
    SpriteRectMap_t         m_spriteRectMap;
};
