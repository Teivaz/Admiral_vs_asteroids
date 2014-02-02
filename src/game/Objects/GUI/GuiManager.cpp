#include "Precompiled.h"
#include "GuiManager.h"
#include "utils/FileUtils.h"
#include "Controllers/SpriteManager.h"
#include "Controllers/ShaderManager.h"
#include "Objects/Sprite.h"

#include "BasicWidget.h"
#include "ButtonWidget.h"
#include "SliderWidget.h"

GuiManager::GuiManager()
{

}

GuiManager::~GuiManager()
{

}

void GuiManager::setAppSize(int width, int height)
{
    m_screenSize = vec2i(width, height);
}

vec2f GuiManager::_scaleToScreen(vec2f size)
{
    return vec2f(size.x / static_cast<float>(m_screenSize.x), size.y / static_cast<float>(m_screenSize.y))*2.0;
}

BasicWidget* GuiManager::_createBasicWidget(const Json::Value& widget)
{
    const vec2f anchor(widget["anchor"]["x"].asDouble(), widget["anchor"]["y"].asDouble());
    const vec2f scale(widget["scale"]["x"].asDouble(), widget["scale"]["y"].asDouble());
    const vec2f offset(widget["offset"]["x"].asDouble(), widget["offset"]["y"].asDouble());
    const string name(widget["name"].asString());
    const string spriteName(widget["sprite"].asString());
    const string verticalAllign(widget["allign"]["y"].asString());
    const string horizontalAllign(widget["allign"]["x"].asString());
    
    vec2i originalSize = SpriteManager::GetInstance()->getSpriteSize(spriteName);
    vec2f relativeSize = _scaleToScreen(vec2f(scale.x * originalSize.x, scale.y * originalSize.y));
    vec2f relativeOffset = _scaleToScreen(offset);
    vec2f relativePosition;
    if (verticalAllign == "top")
    {
        relativePosition.y = 1.0f;
    }
    else if (verticalAllign == "center")
    {
        relativePosition.y = 0.0f;
    }
    else if (verticalAllign == "bottom")
    {
        relativePosition.y = -1.0f;
    }
    else
    {
        ASSERT(false && "Wrong allign mode");
    }

    if (horizontalAllign == "left")
    {
        relativePosition.x = -1.0f;
    }
    else if (horizontalAllign == "center")
    {
        relativePosition.x = 0.0f;
    }
    else if (horizontalAllign == "right")
    {
        relativePosition.x = 1.0f;
    }
    else
    {
        ASSERT(false && "Wrong allign mode");
    }

    Sprite* sprite = SpriteManager::GetInstance()->createSprite(spriteName, -vec2f(relativeSize.x*anchor.x, relativeSize.y*anchor.y), relativeSize, false, 0);
    sprite->setPosition(relativePosition);
    sprite->adjustPosition(relativeOffset);
    return new BasicWidget(sprite, name);
}

BasicWidget* GuiManager::_createBasicWidget(const string& name, Sprite* sprite)
{
    return nullptr;
}

Widget* GuiManager::createWidget(const Json::Value& value)
{
    const string type(value.get("type","").asString());
    if (type == "BasicWidget")
    {
        return _createBasicWidget(value);
    }
    else if (type == "ButtonWidget")
    {
        return nullptr;
    }
    else if (type == "SliderWidget")
    {
        return nullptr;
    }
    else
    {
        ASSERT(false && "Widget is not implemented.");
        return nullptr;
    }
}

Widget* GuiManager::LoadGui(const string& name)
{
    Widget* rootWidget = new Widget;
    char* data;
    size_t size;
    FileUtils::LoadFile(name.c_str(), &data, size, FileUtils::app);
    ASSERT(data && "Error opening GUI file");
    Json::Reader reader;
    Json::Value root;
    bool result = reader.parse(data, data + size, root, false);
    ASSERT(result && "Error parsing GUI file");
    delete[] data;

    if (root.isArray())
    {
        Json::Value::iterator it = root.begin();
        Json::Value::iterator end = root.end();
        for (; it != end; ++it)
        {
            Widget* w = createWidget(*it);
            if (w)
                rootWidget->addChild(w);
        }
    }
    return rootWidget;
}

