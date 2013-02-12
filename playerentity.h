//
//  playerentity.h
//  swarm
//
//  Created by Laszlo Blazovics on 1/16/13.
//
//

#ifndef PLAYERENTITY_H
#define PLAYERENTITY_H

#include <iostream>

#include "entity.h"

class PlayerEntity : public Entity
{
    Place* targetPlace;
    Place* destinationPlace;
    
    bool selfWander();
    bool moveTowardsTheTarget();
    
public:
    PlayerEntity();
    void setTargetPlace(Place* targetPlace);
    void Step();
    void Draw(float dTime);
};

#endif /* defined(__swarm__File__) */
