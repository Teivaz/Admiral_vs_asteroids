#pragma once

class GameObject : public has_slots<>
{
    virtual ~GameObject();
    virtual void                    update(float) = 0;
    virtual void                    render() = 0;
    //virtual void
};
