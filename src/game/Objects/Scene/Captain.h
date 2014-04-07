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
    virtual void                    update(double dt);
    
    void                            shoot(bool);

    // Set propriate maneuver engine power to rotate in desired direction
    // -1 ... +1
    void                            rotate(double speed);
                                    // 0 ... +1
    void                            setMainEnginePower(double power);
    void                            setEnginePower(int engineId, double power);

    // ------------------------------
    // Tasks
    // ------------------------------

    // Align ship along specified vector.
    // Will start a set of enigne manipulation tasks
    void                            setShipRotation(vec2d direction);

    // Stop ship movement.
    // Align ship backwards, launch engines to compensate enertia
    void                            stopShip();

    // Correct moving direction to match specifed vector and speed
    // Turn ship to compensate enertia in directions not matching desired.
    void                            setShipMoveDirection(vec2d direction, double targetSpeed);

    void                            cancelCurrentTask();
    void                            cancelAllTasks();

    vec2d                           getShipMoveDirection() const;
    vec2d                           setShipRotation() const;
    double                          getShipRotationSpeed() const;
    double                          getShipRotationSpeedDerivative() const;
    vec2d                           getShipMoveSpeed() const;
    vec2d                           getShipMoveSpeedDerivative() const;

	signal1<const vec2d&>			onMoved;

private:
    string                          m_name;
    CaptainsBridgePtr               m_bridge;

    typedef std::list<CaptainTaskPtr> Tasks_t;
    Tasks_t                         m_tasks;
};
