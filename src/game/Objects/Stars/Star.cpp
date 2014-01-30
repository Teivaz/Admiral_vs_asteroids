#include "Precompiled.h"
#include "Star.h"

Star::Star()
{

}

Star::~Star()
{

}

void Star::SetColor(EStarColor c)
{
    m_color = s_colors[c];
}

void Star::SetColor(::vec3f c)
{
    m_color = c;
}
