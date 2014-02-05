#include "Precompiled.h"
#include "LaserBeam.h"
#include "../Animations/Animation.h"
#include "Controllers/SpriteManager.h"
#include "Controllers/Painter.h"

LaserBeam::LaserBeam(const vec2f& position, float speed, float direction, float lifetime)
: m_lifetime(lifetime)
, m_speed(speed)
, m_directionF(direction)
{
    float scale = 300.0f;
    m_animation = new Animation();
    vec2i size_ = SpriteManager::GetInstance()->getSpriteSize(sprites::k_beam_1);
    vec2f size = vec2f(size_.x, size_.y) / scale;
    Sprite* s = SpriteManager::GetInstance()->createSprite(sprites::k_beam_1, size/2, size, false);
    m_animation->addFrame(s);
    size_ = SpriteManager::GetInstance()->getSpriteSize(sprites::k_beam_2);
    size = vec2f(size_.x, size_.y) / scale;
    Sprite* s1 = SpriteManager::GetInstance()->createSprite(sprites::k_beam_2, size / 2, size, false);
    m_animation->addFrame(s1);
    size_ = SpriteManager::GetInstance()->getSpriteSize(sprites::k_beam_3);
    size = vec2f(size_.x, size_.y) / scale;
    Sprite* s2 = SpriteManager::GetInstance()->createSprite(sprites::k_beam_3, size / 2, size, false);
    m_animation->addFrame(s2);
    size_ = SpriteManager::GetInstance()->getSpriteSize(sprites::k_beam_2);
    size = vec2f(size_.x, size_.y) / scale;
    s1 = SpriteManager::GetInstance()->createSprite(sprites::k_beam_2, size / 2, size, false);
    m_animation->addFrame(s1);
    m_animation->setFps(20);

    m_directionV = vec2f(cos(m_directionF), sin(m_directionF));
    setRotation(m_directionF + PI/2);
}

LaserBeam::~LaserBeam()
{
    delete m_animation;
}

void LaserBeam::update(float dt)
{
    m_animation->update(dt);
    m_position += m_directionV * m_speed;
    setPosition(m_position);
    m_lifetime -= dt;
    if (m_lifetime < 0)
        delete this;
}

void LaserBeam::render()
{
    m_animation->render();
}
void LaserBeam::setPosition(const vec2f& p)
{
    m_animation->setPosition(p);
}
void LaserBeam::setScale(const vec2f& s)
{
    m_animation->setScale(s);
}
void LaserBeam::setRotation(float r)
{
    m_animation->setRotation(r);
}

void LaserBeam::create(const vec2f& position, float speed, float direction, float lifetime)
{
    LaserBeam* l = new LaserBeam(position, speed, direction, lifetime);
    Painter::GetInstance()->add(l);
}
