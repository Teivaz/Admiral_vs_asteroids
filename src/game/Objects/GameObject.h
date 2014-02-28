#pragma once

class State;
class Shader;
class Shape;
class Painter;
MakeShared(Camera);

class GameObject : public has_slots<>
{
public:
	GameObject();
    virtual ~GameObject();
    virtual void                    render();
    virtual void                    update(double){};

    virtual void                    renderDebug();

    virtual void                    setPosition(const vec2d& p);
    virtual void                    setScale(const vec2d& s);
    virtual void                    setRotation(double r);
    virtual void					setAdditionalTransformation(const mat3d&);
    virtual void                    adjustPosition(const vec2d& p);
    virtual void                    adjustScale(const vec2d& s);
    virtual void                    adjustRotation(double r);
    virtual const vec2d&            getPosition() const;
    virtual const vec2d&            getScale() const;
    virtual double                   getRotation() const;

    void                            setRenderLayer(int layer);
	int                             getRenderLayer(){ return m_renderLayer; }
	virtual void                    setCamera(CameraPtr);
	const mat3d&					getTransformation();
	void							setPainter(Painter*);

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
	Painter*						m_painter = nullptr;
    bool                            m_transformationIsDirty = true;
    vec2d                           m_position = 0.0f;
    vec2d                           m_scale = 1.0f;
    double                           m_rotation = 0.0f;
	mat3d                           m_additionalTransformation;
	mat3d                           m_transformationMatrix;
    int                             m_renderLayer = 0;
};
