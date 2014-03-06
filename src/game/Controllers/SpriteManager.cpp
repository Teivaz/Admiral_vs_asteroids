#include "Precompiled.h"
#include "SpriteManager.h"
#include "Objects/Sprite.h"
#include "Painter.h"
#include "ShaderManager.h"
#include "utils/FileUtils.h"
#include "TextureManager.h"
#include "Objects/Animations/Animation.h"

SpriteManager::SpriteManager()
{
}

SpriteManager::~SpriteManager()
{
}

Sprite* SpriteManager::createSprite(const string& name, bool autorender/* = true*/, int renderLayer/* = 0*/)
{
    auto it = m_spriteRectMap.find(name);
    if (it == m_spriteRectMap.end())
    {
        ASSERT(false && "Sprite not found in existing atlases");
        return nullptr;
    }
    it->second.lb;
    Sprite* sprite = new Sprite(it->second.tex, it->second.lb, it->second.ur, ShaderManager::GetInstance()->getShader(shaders::k_simple));
    sprite->setRenderLayer(renderLayer);
    if (autorender)
    {
        Painter::GetInstance()->add(sprite);
    }
    return sprite;
}

vec2i SpriteManager::getSpriteSizei(const string& name)
{
    auto it = m_spriteRectMap.find(name);
    if (it == m_spriteRectMap.end())
    {
        ASSERT(false && "Sprite not found in existing atlases");
        return 0;
    }
    return it->second.sizePx;
}

vec2d SpriteManager::getSpriteSize(const string& name)
{
    vec2i sizei = getSpriteSizei(name);
    return vec2d(static_cast<double>(sizei.x), static_cast<double>(sizei.y));
}

Sprite* SpriteManager::createSprite(const string& name, vec2d position, vec2d size, bool autorender/* = true*/, int renderLayer/* = 0*/)
{
    auto it = m_spriteRectMap.find(name);
    if (it == m_spriteRectMap.end())
    {
        ASSERT(false && "Sprite not found in existing atlases");
        return nullptr;
    }
    it->second.lb;
    Sprite* sprite = new Sprite(it->second.tex, it->second.lb, it->second.ur, ShaderManager::GetInstance()->getShader(shaders::k_simple), position, size);
    sprite->setRenderLayer(renderLayer);
    if (autorender)
    {
        Painter::GetInstance()->add(sprite);
    }
    return sprite;
}

void SpriteManager::loadAtlas(const string& name)
{
    char* data;
    size_t size;
    FileUtils::LoadFile(name.c_str(), &data, size, FileUtils::app);
    ASSERT(data && "Error opening atlas description file");
    Json::Reader reader;
    Json::Value root;
    bool result = reader.parse(data, data + size, root, false);
    ASSERT(result && "Error parsing atlas description file");
    delete[] data;
    Json::Value meta = root["meta"];
    Json::Value texName = meta["image"];
    vec2d texSize = vec2d(static_cast<double>(meta["size"]["w"].asInt()), 
                          static_cast<double>(meta["size"]["h"].asInt()));
    Texture tex = TextureManager::GetInstance()->getTexture(texName.asString());
    ASSERT(tex);
    Json::Value frames = root.get("frames", Json::Value(""));
    if (frames.isObject())
    {
        Json::Value::iterator it = frames.begin();
        Json::Value::iterator end = frames.end();
        for (; it != end; ++it)
        {
            const char* spriteName = it.memberName();
            Json::Value frame = (*it).get("frame", Json::nullValue);
            ASSERT(frame != Json::nullValue);
            double x = static_cast<double>(frame["x"].asInt()) / texSize.x;
            double y = static_cast<double>(frame["y"].asInt()) / texSize.y;
            double w = static_cast<double>(frame["w"].asInt()) / texSize.x;
            double h = static_cast<double>(frame["h"].asInt()) / texSize.y;
            m_spriteRectMap[spriteName] = SpriteRect(vec2d(x, y), vec2d(x + w, y + h), tex, vec2i(frame["w"].asInt(), frame["h"].asInt()));
        }        
    }
}

Animation* SpriteManager::createAnimation(const string& name)
{
    auto anim = m_animations.find(name);
    if (anim != m_animations.end())
    {
        return _animationFromFramesData(anim->second);
    }

    char* data;
    size_t size;
    FileUtils::LoadFile(name.c_str(), &data, size, FileUtils::app);
    ASSERT(data && "Error opening animation file");
    Json::Reader reader;
    Json::Value root;
    bool result = reader.parse(data, data + size, root, false);
    ASSERT(result && "Error parsing animation file");

    AnimationData animData;
    animData.fps = static_cast<double>(root["fps"].asDouble());
    Json::Value frames = root["frames"];
    if (frames.isArray())
    {
        Json::Value::iterator it = frames.begin();
        Json::Value::iterator end = frames.end();
        for (; it != end; ++it)
        {
            AnimationFrameData frameData;
            frameData.sprite = (*it)["sprite"].asString();
            frameData.anchor = vec2d(static_cast<double>((*it)["anchor"]["x"].asDouble()),
                                     static_cast<double>((*it)["anchor"]["y"].asDouble()));
            frameData.scale = vec2d(static_cast<double>((*it)["scale"]["x"].asDouble()),
                                    static_cast<double>((*it)["scale"]["y"].asDouble()));
            frameData.offset = vec2d(static_cast<double>((*it)["offset"]["x"].asDouble()),
                                     static_cast<double>((*it)["offset"]["y"].asDouble()));
            frameData.rotation = static_cast<double>((*it)["rotate"].asDouble());
            frameData.rotation = (PI * frameData.rotation) / 180.0f;
            animData.frames.push_back(frameData);
        }
    }

    m_animations[name] = animData;
    return _animationFromFramesData(animData);
}


Animation* SpriteManager::_animationFromFramesData(const AnimationData& data)
{
    Animation::KeyFrames_t frames;
    for (auto frameData : data.frames)
    {
        vec2d size = getSpriteSize(frameData.sprite);
        vec2d anchor(frameData.anchor.x * size.x, frameData.anchor.y * size.y);
        Sprite* frame = createSprite(frameData.sprite, -anchor, size, false, 0);
        frame->setPosition(frameData.offset);
        frame->setRotation(frameData.rotation);
        frame->setScale(frameData.scale);
        frames.push_back(frame);
    }
     Animation* anim = new Animation(frames);
     anim->setFps(data.fps);
     return anim;
}
