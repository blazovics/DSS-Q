#ifndef GRGENTITY_H
#define GRGENTITY_H

#include "entity.h"

typedef enum
{
    greedy = 0,
    rotation = 1,
    rotationStopped = 2,
    stopped = 3
}GRGState;

class GRGEntity : public Entity
{
    unsigned targetDistance;
    Entity* targetEntity;

    GRGState state;
    Place* rotationStartPlace;


public:
    GRGEntity();
    void setTargetEntity(Entity* targetEntity);
    void Step();
    void AfterStep();
    void Draw(float dTime);
    int getType();

    void setState(GRGState newState);
};

#endif // GRGENTITY_H
