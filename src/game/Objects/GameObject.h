#pragma once

class State;
class Shader;
class Shape;
MakeShared(Camera);

class GameObject //: public has_slots<>
{
public:
    virtual ~GameObject();
    virtual void                    render();
    virtual void                    update(float){};

    virtual void                    renderDebug();

    virtual void                    setPosition(const vec2f& p);
    virtual void                    setScale(const vec2f& s);
    virtual void                    setRotation(float r);
    virtual void                    adjustPosition(const vec2f& p);
    virtual void                    adjustScale(const vec2f& s);
    virtual void                    adjustRotation(float r);
    virtual const vec2f&            getPosition() const;
    virtual const vec2f&            getScale() const;
    virtual float                   getRotation() const;

    void                            setRenderLayer(int layer);
	int                             getRenderLayer(){ return m_renderLayer; }
	virtual void                    setCamera(CameraPtr);

    //******************************************************
    // sort purpose
    static bool less(GameObject* obj1, GameObject* obj2)
    {
        return obj1->getRenderLayer() < obj2->getRenderLayer();
    }
    //******************************************************

protected:
    virtual void                    _calculateTransformation();

protected:    
	CameraPtr						m_camera;
    bool                            m_transformationIsDirty = true;
    vec2f                           m_position = 0.0f;
    vec2f                           m_scale = 1.0f;
    float                           m_rotation = 0.0f;
    mat3f                           m_transformationMatrix;
    int                             m_renderLayer = 0;
};
