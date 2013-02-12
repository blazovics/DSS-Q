//
//  File.cpp
//  swarm
//
//  Created by Laszlo Blazovics on 1/16/13.
//
//

#include "playerentity.h"
#include "place.h"
#include "field.h"

PlayerEntity::PlayerEntity() : Entity()
{
    this->targetPlace = NULL;
    this->destinationPlace = NULL;
}

void PlayerEntity::setTargetPlace(Place *targetPlace)
{
    if(targetPlace == NULL || this->currentPlace == NULL)
        return;
    
    this->targetPlace = targetPlace;
    
    Place** routePlaces = NULL;
    unsigned routeLength = 0;
    
    Field* currentField = this->targetPlace->getParentField();
    currentField->getPathBetweenPlaces(this->currentPlace, targetPlace, &routePlaces, routeLength);
    
    if(routeLength == 0)
    {
        //TODO: Unable to go there!
        return;
    }
    
    this->desiredPlace = routePlaces[0];
    
    free(routePlaces);
}

bool PlayerEntity::selfWander()
{
    //choose a neighbor
    unsigned freeNbSize = 0;
    char* neighbors = NULL;
    
    this->currentPlace->getFreeNeighbors(&neighbors,freeNbSize);
    
    //genrate random number
    if (freeNbSize > 0){
        int randomNumber = rand();
        unsigned index = randomNumber % freeNbSize;
        unsigned newID = neighbors[index];
        Place* newPlace = currentPlace->getNeighbor(newID);
        
        Point2i p = newPlace->getPosition();
        std::cout<<"possible places: "<<freeNbSize<<" randomNum: "<<randomNumber<<" index: "<<index<<" new place: "<<newID<<" "<<p.x<<" "<<p.y<<std::endl;
        
        this->desiredPlace = newPlace;
        delete [] neighbors;
        return true;
    }
    return false;
}

bool PlayerEntity::moveTowardsTheTarget()
{
    if(this->targetPlace == NULL)
        return false;
    
    Place** routePlaces = NULL;
    unsigned routeLength = 0;
    
    Field* currentField = this->targetPlace->getParentField();
    currentField->getPathBetweenPlaces(this->currentPlace, targetPlace, &routePlaces, routeLength);
    
    if(routeLength == 0)
    {
        //TODO: Failed
        return false;
    }
    
    if(routeLength < 2)
    {
        this->desiredPlace = routePlaces[0];
        //TODO: Reached
        return false;
    }
    else
    {
        this->desiredPlace = routePlaces[1];
    }
    
    free(routePlaces);
    return true;
}


void PlayerEntity::Step()
{
    if(!moveTowardsTheTarget())
    {
        if(!selfWander())
        {
            //TODO: GAME OVER
        }
    }
}


void PlayerEntity::Draw(float dTime)
{
    Animate();
    if(this->currentPlace == NULL)
        return;
    
    float unit = this->currentPlace->getParentField()->getUnit();
    float height = sqrt(3)/2*unit;
    
    Point2f placePos;
    
    if(animating)
    {
        placePos = this->animationPosition;
    }
    else
    {
        placePos = this->currentPlace->getOnScreenPos();
    }
    
    Point2i offset = this->currentPlace->getParentField()->getOffset();
    
    
#ifdef MARMALADE_UI
    CIwSVec2 Position(placePos.x-offset.x, placePos.y-offset.y);
    
    // Build the transform
	// Set the rotation transform
	Transform.SetRot(0);
	// Scale the transform
	Transform.ScaleRot(IW_GEOM_ONE);
	// Translate the transform
	Transform.SetTrans(Position);
	// Set this transform as the active transform for Iw2D
	Iw2DSetTransformMatrix(Transform);
    
    Iw2DSetColour(0xff00ffff); // Set red
    
    Iw2DFillArc(CIwSVec2(height, unit), CIwSVec2((unit/2), (unit/2)), 0, IW_ANGLE_2PI);
    
#endif
}