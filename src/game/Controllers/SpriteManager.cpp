#include "Precompiled.h"
#include "SpriteManager.h"
#include "Objects/Sprite.h"
#include "Painter.h"
#include "ShaderManager.h"
#include "utils/FileUtils.h"
#include "TextureManager.h"

SpriteManager::SpriteManager()
{
}

SpriteManager::~SpriteManager()
{
}

Sprite* SpriteManager::createSprite(const string& name, bool autorender/* = true*/)
{
    auto it = m_spriteRectMap.find(name);
    if (it == m_spriteRectMap.end())
    {
        ASSERT(false && "Sprite not found in existing atlases");
        return nullptr;
    }
    it->second.lb;
    Sprite* sprite = new Sprite(it->second.tex, it->second.lb, it->second.ur, ShaderManager::GetInstance()->getShader(shaders::k_simple));
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
    ASSERT(data && "Error opening shader file");
    Json::Reader reader;
    Json::Value root;
    bool result = reader.parse(data, data + size, root, false);
    ASSERT(result && "Error parsing shader file");
    delete[] data;
    Json::Value meta = root.get("meta", Json::Value(""));
    Json::Value texName = meta.get("image", Json::Value(""));
    vec2f texSize = vec2f(meta["size"]["w"].asInt(), meta["size"]["h"].asInt());
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
            float x = static_cast<float>(frame["x"].asInt()) / texSize.x;
            float y = static_cast<float>(frame["y"].asInt()) / texSize.y;
            float w = static_cast<float>(frame["w"].asInt()) / texSize.x;
            float h = static_cast<float>(frame["h"].asInt()) / texSize.y;
            m_spriteRectMap[spriteName] = SpriteRect(vec2f(x,1.0f-y), vec2f(x+w,1.0f-y-h), tex);
        }        
    }
}
