#pragma once

class Captain;

class CaptainTask
{
public:
    CaptainTask(Captain& cap) : m_captain(cap) {}
    virtual ~CaptainTask() {}
    virtual bool            update(double dt) { return true; }
protected:
    Captain&                m_captain;
};

class CaptainTaskStopRotation : public CaptainTask
{
public:
    CaptainTaskStopRotation(Captain& cap);
    virtual ~CaptainTaskStopRotation();
    virtual bool            update(double dt);
};


class CaptainTaskSetRotation : public CaptainTask
{
public:
    CaptainTaskSetRotation(Captain& cap, const vec2d& direction);
    virtual ~CaptainTaskSetRotation();
    virtual bool            update(double dt);
private:
    vec2d                   m_direction;
};

class CaptainTaskStopShip : public CaptainTask
{
public:
    CaptainTaskStopShip(Captain& cap);
    virtual ~CaptainTaskStopShip();
    virtual bool            update(double dt);
};

class CaptainTaskSetShipMoveDirection : public CaptainTask
{
public:
	CaptainTaskSetShipMoveDirection(Captain& cap, const vec2d& direction, double speed);
	virtual ~CaptainTaskSetShipMoveDirection();
    virtual bool            update(double dt);
private:
    vec2d                   m_direction;
    double                   m_speed;
};
