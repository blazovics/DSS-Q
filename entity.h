#ifndef ENTITY_H
#define ENTITY_H

#include "common.h"
#include "renderobject.h"

using namespace std;

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

    unsigned stepCount;

public:
    Entity();
    ~Entity();
    
    void setCurrentPlace(Place* place, bool forced = false);
    
    Place* getCurrentPlace();

    Place* getDesiredPlace();
    
    bool getAnimating();

    unsigned getStepCount();
    void setStepCount(unsigned stepCount);
    void increaseStepCount();

    virtual void Draw(float dTime);
    virtual void Step();
    virtual void AfterStep();
    virtual void Animate();
    virtual void PrepareForAnimation(Place* previousPlace, Place* nextPlace);
    virtual int getType() = 0;
};

#endif // ENTITY_H
