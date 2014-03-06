#pragma once

MakeShared(Ship);
class Captain;
class GameObject;

class CaptainsBridge : public has_slots<>
{
    friend Captain;

public:
    virtual ~CaptainsBridge();

protected: // Captain only!

    CaptainsBridge(const string& shipName);

    virtual void                    render();
    virtual void                    update(double dt);
    
    // ******************************
    // Captain commands:
    // ******************************

    // Fire all canons!
    void                            shoot();

    // Set propriate maneuver engine power to rotate in desired direction
    // -1 ... +1
    void                            rotate(double speed);
                                    // 0 ... +1
    void                            setMainEnginePower(double power);
    void                            setEnginePower(int engineId, double power);


    // ******************************
    // Captain asks:
    // ******************************

    vec2d                           getShipMoveDirection() const;
    vec2d                           getShipRotation() const;
    double                           getShipRotationSpeed() const;
    double                           getShipRotationSpeedDerivative() const;
	double                           getShipMoveSpeed() const;
	double                           getShipMoveSpeedDerivative() const;
	vec2d                           GetShipPosition() const;
	
private:
    ShipPtr                         m_ship;
};
