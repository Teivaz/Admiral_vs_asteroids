#pragma once
#include "sprites.h"

class Sprite;

class SpriteManager : public Singleton<SpriteManager>
{
    struct SpriteRect
    {
        SpriteRect()
        :lb(0), ur(0), tex(0)
        {};
        SpriteRect(vec2f _lb, vec2f _ur, Texture _tex)
        : lb(_lb), ur(_ur), tex(_tex)
        {};
        vec2f lb;
        vec2f ur;
        Texture tex;
    };

public:
    SpriteManager();
    ~SpriteManager();

    Sprite*                 createSprite(const string& name, bool autorender = true);
    void                    loadAtlas(const string& name);

private:
    SpriteRect&             _getSpriteRect(const string& name);

private:
    typedef std::map<string, SpriteRect> SpriteRectMap_t;
    SpriteRectMap_t         m_spriteRectMap;
};
