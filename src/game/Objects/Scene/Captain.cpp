#include "Precompiled.h"
#include "Captain.h"

#include "CaptainsBridge.h"
#include "CaptainTask.h"

Captain::Captain(const string& name, CaptainsBridgePtr bridge)
: m_name(name)
, m_bridge(bridge)
{

}

Captain::~Captain()
{
}

//void Captain::render()
//{}

void Captain::update(float dt)
{
    if (m_tasks.size())
    {
        bool finished = m_tasks.front()->update(dt);
        if (finished)
        {
            m_tasks.pop_front();
        }
    }
}


void Captain::shoot()
{
    m_bridge->shoot();
}

void Captain::rotate(float speed)
{
    m_bridge->rotate(speed);
}

void Captain::setMainEnginePower(float power)
{
    m_bridge->setMainEnginePower(power);
}

void Captain::setEnginePower(int id, float power)
{
    m_bridge->setEnginePower(id, power);
}

void Captain::setShipRotation(vec2f direction)
{
    cancelAllTasks();
    m_tasks.push_back(CaptainTaskPtr(new CaptainTaskSetRotation(*this, direction)));
}

void Captain::stopShip()
{
    cancelAllTasks();
    m_tasks.push_back(CaptainTaskPtr(new CaptainTaskStopShip(*this)));
}

void Captain::setShipMoveDirection(vec2f direction, float targetSpeed)
{
    cancelAllTasks();
    //m_tasks.push_back(CaptainTaskPtr(new CaptainTaskStopShip(*this)));
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

