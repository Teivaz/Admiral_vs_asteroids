#include "Precompiled.h"
#include "CaptainTask.h"

#include "Captain.h"

CaptainTaskStopRotation::CaptainTaskStopRotation(Captain& cap)
: CaptainTask(cap)
{}

CaptainTaskStopRotation::~CaptainTaskStopRotation()
{}

bool CaptainTaskStopRotation::update(double dt)
{
    m_captain;
    return false;
}

CaptainTaskSetRotation::CaptainTaskSetRotation(Captain& cap, const vec2d& direction)
: CaptainTask(cap)
, m_direction(direction)
{}

CaptainTaskSetRotation::~CaptainTaskSetRotation()
{}

bool CaptainTaskSetRotation::update(double dt)
{
    m_captain;
    return false;
}

CaptainTaskStopShip::CaptainTaskStopShip(Captain& cap)
: CaptainTask(cap)
{}

CaptainTaskStopShip::~CaptainTaskStopShip()
{}

bool CaptainTaskStopShip::update(double dt)
{
    m_captain;
    return false;
}

CaptainTaskSetShipMoveDirection::CaptainTaskSetShipMoveDirection(Captain& cap, const vec2d& direction, double speed)
: CaptainTask(cap)
, m_direction(direction)
, m_speed(speed)
{}

CaptainTaskSetShipMoveDirection::~CaptainTaskSetShipMoveDirection()
{}

bool CaptainTaskSetShipMoveDirection::update(double dt)
{
    m_captain;
    return false;
}
