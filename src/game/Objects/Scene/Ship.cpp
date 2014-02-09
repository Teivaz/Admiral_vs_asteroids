#include "Precompiled.h"
#include "Ship.h"
#include "Controllers/SpriteManager.h"
#

Ship::Ship()
{
    vec2f shipSize = SpriteManager::GetInstance()->getSpriteSize(sprites::k_she);
//    SpriteManager::GetInstance()->createSprite(sprites::k_she, )
}

Ship::~Ship()
{
}

void Ship::render()
{

}

void Ship::update(float dt)
{

}

