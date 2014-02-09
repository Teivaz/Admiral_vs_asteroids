#pragma once
#include "Collidable.h"

MakeShared(Sprite);

class Ship : public Collidable
{
public:
    Ship();
    virtual ~Ship();

    virtual void    render();
    virtual void    update(float dt);

protected:

private:
    SpritePtr       m_ship;

};
