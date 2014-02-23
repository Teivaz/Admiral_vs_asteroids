#pragma once

MakeShared(Ship);
class Captain;
class GameObject;

class CaptainsBridge : public has_slots<>
{
    friend Captain;
protected: // Captain only!

    CaptainsBridge();
    virtual ~CaptainsBridge();

    virtual void                    render();
    virtual void                    update(float dt);
    
    // ******************************
    // Captain commands:
    // ******************************

    // Fire all canons!
    void                            shoot();

    // Set propriate maneuver engine power to rotate in desired direction
    // -1 ... +1
    void                            rotate(float speed);
                                    // 0 ... +1
    void                            setMainEnginePower(float power);
    void                            setEnginePower(int engineId, float power);


    // ******************************
    // Captain asks:
    // ******************************

    vec2f                           getShipMoveDirection() const;
    vec2f                           getShipRotation() const;
    float                           getShipRotationSpeed() const;
    float                           getShipRotationSpeedDerivative() const;
    vec2f                           getShipMoveSpeed() const;
    vec2f                           getShipMoveSpeedDerivative() const;
	
private:
    ShipPtr                         m_ship;
};
