#pragma once

class Captain;

class CaptainTask
{
public:
    CaptainTask(Captain& cap) : m_captain(cap) {}
    virtual ~CaptainTask() {}
    virtual bool            update(float dt) { return true; }
protected:
    Captain&                m_captain;
};

class CaptainTaskStopRotation : public CaptainTask
{
public:
    CaptainTaskStopRotation(Captain& cap);
    virtual ~CaptainTaskStopRotation();
    virtual bool            update(float dt);
};


class CaptainTaskSetRotation : public CaptainTask
{
public:
    CaptainTaskSetRotation(Captain& cap, const vec2f& direction);
    virtual ~CaptainTaskSetRotation();
    virtual bool            update(float dt);
private:
    vec2f                   m_direction;
};

class CaptainTaskStopShip : public CaptainTask
{
public:
    CaptainTaskStopShip(Captain& cap);
    virtual ~CaptainTaskStopShip();
    virtual bool            update(float dt);
};

class CaptainTaskSetShipMoveDirection : public CaptainTask
{
public:
	CaptainTaskSetShipMoveDirection(Captain& cap, const vec2f& direction, float speed);
	virtual ~CaptainTaskSetShipMoveDirection();
    virtual bool            update(float dt);
private:
    vec2f                   m_direction;
    float                   m_speed;
};
