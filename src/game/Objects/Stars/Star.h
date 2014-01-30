#pragma once
#include "Objects/GameObject.h"

class Star : public GameObject
{
public:
    enum EStarColor
    {
        EWhiteStar = 0,
        ERedStar,
        EBlueStar,
        EYellowStar,

        ETotal
    };

    static const vec3f s_colors[ETotal];

    Star();
    ~Star();

    void SetColor(EStarColor);
    void SetColor(::vec3f);

private:
    vec3f m_color = 0;
};

const vec3f Star::s_colors[Star::ETotal] =
{
    {1.0f, 1.0f, 1.0f},   // EWhiteStar
    {1.0f, 0.2f, 0.2f},   // ERedStar
    {0.2f, 0.4f, 0.8f},   // EBlueStar
    {1.0f, 1.0f, 0.4f}    // EYellowStar
};
