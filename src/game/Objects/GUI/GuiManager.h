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
    BasicWidget*            _createBasicWidget(const string& name, Sprite* sprite);
    BasicWidget*            _createBasicWidget(const Json::Value& widget);

    vec2f                   _scaleToScreen(vec2f);

private:
    vec2i                   m_screenSize;
};
