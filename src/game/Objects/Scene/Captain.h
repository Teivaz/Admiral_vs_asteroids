#pragma once
#include "Controllers/TouchReceiver.h"

MakeShared(CaptainsBridge);
MakeShared(CaptainTask);

class Captain : public TouchReceiver, public has_slots<>
{
public:

    Captain(const string& captainName, const string& shipName);
    virtual ~Captain();

//    virtual void                    render();
    virtual void                    update(float dt);
    
    void                            shoot(bool);

    // Set propriate maneuver engine power to rotate in desired direction
    // -1 ... +1
    void                            rotate(float speed);
                                    // 0 ... +1
    void                            setMainEnginePower(float power);
    void                            setEnginePower(int engineId, float power);

    // ------------------------------
    // Tasks
    // ------------------------------

    // Align ship along specified vector.
    // Will start a set of enigne manipulation tasks
    void                            setShipRotation(vec2f direction);

    // Stop ship movement.
    // Align ship backwards, launch engines to compensate enertia
    void                            stopShip();

    // Correct moving direction to match specifed vector and speed
    // Turn ship to compensate enertia in directions not matching desired.
    void                            setShipMoveDirection(vec2f direction, float targetSpeed);

    void                            cancelCurrentTask();
    void                            cancelAllTasks();

    vec2f                           getShipMoveDirection() const;
    vec2f                           setShipRotation() const;
    float                           getShipRotationSpeed() const;
    float                           getShipRotationSpeedDerivative() const;
    vec2f                           getShipMoveSpeed() const;
    vec2f                           getShipMoveSpeedDerivative() const;

	signal1<const vec2f&>			onMoved;

private:
    string                          m_name;
    CaptainsBridgePtr               m_bridge;

    typedef std::list<CaptainTaskPtr> Tasks_t;
    Tasks_t                         m_tasks;
};
