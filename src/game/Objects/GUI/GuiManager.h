#pragma once

class Widget;
class BasicWidget;
class ButtonWidget;
class SliderWidget;
class Sprite;

class GuiManager : public Singleton<GuiManager>
{
public:
    GuiManager();
    ~GuiManager();
    
    void                    setAppSize(int width, int height);

    Widget*                 LoadGui(const string& name);
    Widget*                 createWidget(const Json::Value& root);

protected:
    ButtonWidget*           _createButtonWidget(const Json::Value& widget);
    BasicWidget*            _createBasicWidget(const Json::Value& widget);

    Sprite*                 _loadSpriteForWidget(const string& name, const Json::Value& widget);

    vec2f                   _scaleToScreen(vec2f);

private:
    vec2i                   m_screenSize;
};