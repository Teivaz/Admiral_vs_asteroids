#include "Precompiled.h"
#include "Captain.h"

#include "CaptainsBridge.h"
#include "CaptainTask.h"

Captain::Captain(const string& captainName, const string& shipName)
: m_name(captainName)
{
    m_bridge.reset(new CaptainsBridge(shipName));
}

Captain::~Captain()
{
}

//void Captain::render()
//{}

void Captain::update(double dt)
{
    if (m_tasks.size())
    {
        bool finished = m_tasks.front()->update(dt);
        if (finished)
        {
            m_tasks.pop_front();
        }
    }
	if (m_bridge->getShipMoveSpeed() != 0)
	{
		onMoved(m_bridge->GetShipPosition());
	}
}


void Captain::shoot(bool yes)
{
    if (yes)
        m_bridge->shoot();
}

void Captain::rotate(double speed)
{
    m_bridge->rotate(speed);
}

void Captain::setMainEnginePower(double power)
{
    m_bridge->setMainEnginePower(power);
}

void Captain::setEnginePower(int id, double power)
{
    m_bridge->setEnginePower(id, power);
}

void Captain::setShipRotation(vec2d direction)
{
    cancelAllTasks();
    m_tasks.push_back(CaptainTaskPtr(new CaptainTaskSetRotation(*this, direction)));
}

void Captain::stopShip()
{
    cancelAllTasks();
    m_tasks.push_back(CaptainTaskPtr(new CaptainTaskStopShip(*this)));
}

void Captain::setShipMoveDirection(vec2d direction, double targetSpeed)
{
    cancelAllTasks();
	m_tasks.push_back(CaptainTaskPtr(new CaptainTaskSetShipMoveDirection(*this, direction, targetSpeed)));
}

void Captain::cancelAllTasks()
{
    m_tasks.clear();
}

void Captain::cancelCurrentTask()
{
    if (m_tasks.size() > 0)
        m_tasks.pop_front();
}

vec2d Captain::getShipMoveSpeed() const
{
    return m_bridge->getShipMoveDirection() * m_bridge->getShipMoveSpeed();
}

double Captain::getShipRotationSpeed() const
{
    return m_bridge->getShipRotationSpeed();
}
