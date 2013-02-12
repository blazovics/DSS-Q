#ifndef ENTITY_H
#define ENTITY_H

#include "common.h"
#include "renderobject.h"

class Place;

class Entity : public RenderObject
{

protected:

    Place* currentPlace;
    Place* desiredPlace;
    
    //for moving animation only
    bool animating;
    Point2f animationPosition;
    
    static float aspect;

public:
    Entity();
    ~Entity();
    
    void setCurrentPlace(Place* place, bool forced = false);
    
    Place* getCurrentPlace();

    Place* getDesiredPlace();
    
    bool getAnimating();

    virtual void Draw(float dTime);
    virtual void Step();
    virtual void AfterStep();
    virtual void Animate();
    virtual void PrepareForAnimation(Place* previousPlace, Place* nextPlace);
};

#endif // ENTITY_H
