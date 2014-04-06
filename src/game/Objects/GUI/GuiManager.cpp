#include "Precompiled.h"
#include "GuiManager.h"
#include "utils/FileUtils.h"
#include "Controllers/SpriteManager.h"
#include "Controllers/ShaderManager.h"
#include "Objects/Sprite.h"

#include "BasicWidget.h"
#include "ButtonWidget.h"
#include "SliderWidget.h"
#include "ProgressBarWidget.h"
#include "JoystickWidget.h"

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

vec2d GuiManager::_scaleToScreen(vec2d size)
{
    return vec2d(size.x / static_cast<double>(m_screenSize.x), size.y / static_cast<double>(m_screenSize.y))*2.0;
}

Sprite* GuiManager::_loadSpriteForWidget(const string& spriteName, const Json::Value& widget)
{
    const vec2d anchor(static_cast<double>(widget["anchor"]["x"].asDouble()),
                       static_cast<double>(widget["anchor"]["y"].asDouble()));
    const vec2d scale( static_cast<double>(widget["scale"]["x"].asDouble()),
                       static_cast<double>(widget["scale"]["y"].asDouble()));
    const vec2d offset(static_cast<double>(widget["offset"]["x"].asDouble()), 
                       static_cast<double>(widget["offset"]["y"].asDouble()));
    const string verticalAllign(widget["allign"]["y"].asString());
    const string horizontalAllign(widget["allign"]["x"].asString());

    bool scaleReltiveToScreen = false;
    Json::Value rel = widget["scale_relative_to_screen"];
    if (rel != Json::nullValue)
    {
        scaleReltiveToScreen = rel.asBool();
    }
    
    vec2d size = scaleReltiveToScreen ? m_screenSize : SpriteManager::GetInstance()->getSpriteSize(spriteName);

    vec2d relativeSize = _scaleToScreen(vec2d(scale.x * size.x, scale.y * size.y));
    vec2d relativeOffset = _scaleToScreen(offset);
    vec2d relativePosition;
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
    Sprite* sprite = SpriteManager::GetInstance()->createSprite(spriteName, vec2d(), vec2d(1.0), false, 0);

    sprite->setScale(relativeSize);
    sprite->setPosition(relativePosition - vec2d(relativeSize.x * anchor.x, relativeSize.y * anchor.y) );
    sprite->adjustPosition(relativeOffset);
    return sprite;
}

BasicWidget* GuiManager::_createBasicWidget(const Json::Value& widget)
{
    const string name(widget["name"].asString());
    const string spriteName(widget["sprite"].asString());
    Sprite* sprite = _loadSpriteForWidget(spriteName, widget);
    return new BasicWidget(sprite, name);
}

ButtonWidget* GuiManager::_createButtonWidget(const Json::Value& widget)
{
    const string name(widget["name"].asString());
    const string spriteNameIdle(widget["sprite"].asString());
    Sprite* spriteIdle = _loadSpriteForWidget(spriteNameIdle, widget);
    const string spriteNamePressed(widget["sprite_selected"].asString());
    Sprite* spritePressed = _loadSpriteForWidget(spriteNamePressed, widget);
    return new ButtonWidget(spriteIdle, spritePressed, name);
}

SliderWidget* GuiManager::_createSliderWidget(const Json::Value& widget)
{
    const string name(widget["name"].asString());
    const string spriteName(widget["sprite"].asString());
    Sprite* sprite = _loadSpriteForWidget(spriteName, widget);
    const vec2d travel(static_cast<double>(widget["travel"]["x"].asDouble()),
                       static_cast<double>(widget["travel"]["y"].asDouble()));
    double value = static_cast<double>(widget["default"].asDouble());
    return new SliderWidget(sprite, name, _scaleToScreen(travel), value);
}

ProgressBarWidget* GuiManager::_createProgressBarWidget(const Json::Value& widget)
{
    const string name(widget["name"].asString());
    const string spriteName(widget["sprite"].asString());
    Sprite* sprite = _loadSpriteForWidget(spriteName, widget);
    const string spriteFullName(widget["sprite_full"].asString());
    Sprite* spriteFull = _loadSpriteForWidget(spriteFullName, widget);
    const vec2d offsetFull(static_cast<double>(widget["offset_full"]["x"].asDouble()),
                           static_cast<double>(widget["offset_full"]["y"].asDouble()));
    vec2d relativeOffsetFull = _scaleToScreen(offsetFull);
    spriteFull->adjustPosition(relativeOffsetFull);
    double value = static_cast<double>(widget["value"].asDouble());
    return new ProgressBarWidget(sprite, spriteFull, name, value);
}

JoystickWidget* GuiManager::_createJoystickWidget(const Json::Value& widget)
{
    const string name(widget["name"].asString());
    const string spriteName(widget["sprite"].asString());
    Sprite* sprite = _loadSpriteForWidget(spriteName, widget);
    const vec2d travel(static_cast<double>(widget["travel"]["x"].asDouble()),
        static_cast<double>(widget["travel"]["y"].asDouble()));
    double value = static_cast<double>(widget["default"].asDouble());
    return new JoystickWidget(sprite, sprite, name);
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
        return _createButtonWidget(value);
    }
    else if (type == "SliderWidget")
    {
        return _createSliderWidget(value);
    }
    else if (type == "JoystickWidget")
    {
        return _createJoystickWidget(value);
    }
    else if (type == "ProgressBarWidget")
    {
        return _createProgressBarWidget(value);
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
    rootWidget->setRenderLayer(1000);
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

