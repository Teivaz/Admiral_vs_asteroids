#include "Precompiled.h"
#include "CaptainTask.h"

#include "Captain.h"

CaptainTaskStopRotation::CaptainTaskStopRotation(Captain& cap)
: CaptainTask(cap)
{}

CaptainTaskStopRotation::~CaptainTaskStopRotation()
{}

bool CaptainTaskStopRotation::update(float dt)
{
    m_captain;
    return false;
}

CaptainTaskSetRotation::CaptainTaskSetRotation(Captain& cap, const vec2f& direction)
: CaptainTask(cap)
, m_direction(direction)
{}

CaptainTaskSetRotation::~CaptainTaskSetRotation()
{}

bool CaptainTaskSetRotation::update(float dt)
{
    m_captain;
    return false;
}

CaptainTaskStopShip::CaptainTaskStopShip(Captain& cap)
: CaptainTask(cap)
{}

CaptainTaskStopShip::~CaptainTaskStopShip()
{}

bool CaptainTaskStopShip::update(float dt)
{
    m_captain;
    return false;
}

setShipMoveDirection::setShipMoveDirection(Captain& cap, const vec2f& direction, float speed)
: CaptainTask(cap)
, m_direction(direction)
, m_speed(speed)
{}

setShipMoveDirection::~setShipMoveDirection()
{}

bool setShipMoveDirection::update(float dt)
{
    m_captain;
    return false;
}
