#include "entity.h"
#include "place.h"
#include "logger.h"
#include "field.h"

#include <cmath>

float Entity::aspect = sqrt(3)/2;

Entity::Entity()
{
    this->currentPlace = NULL;
    this->desiredPlace = NULL;

    this->animating = false;

    this->stepCount = 0;
}

Entity::~Entity()
{

}

void Entity::Step()
{
    this->desiredPlace = this->currentPlace;
}

unsigned Entity::getStepCount()
{
    return this->stepCount;
}

void Entity::setStepCount(unsigned stepCount)
{
    this->stepCount = stepCount;
}

void Entity::increaseStepCount()
{
    this->stepCount++;
}

void Entity::AfterStep()
{
    this->desiredPlace = this->currentPlace;
}

void Entity::setCurrentPlace(Place* place, bool forced)
{
    if(place->getEntity() != NULL && forced == false){
        Logger::log("Placement error - Entity tired to occupy a non empty place.");
    }
    else{
        //if we would like to place the entity onto the same place
        if(this->currentPlace != NULL  && this->currentPlace == place)
        {
            //std::cout<<"Placement error"<<std::endl;
            return;
        }
        
        //if somebody have already placed himself on the current place which we will leave
        //ONLY IN FORCED MODE
        if(this->currentPlace != NULL && this->currentPlace->getEntity() == this){
            this->currentPlace->setEntity(NULL);
        }
        
        if(this->currentPlace != NULL){
            PrepareForAnimation(this->currentPlace,place);
        }
        this->currentPlace = place;
        place->setEntity(this);
    }
}

Place* Entity::getCurrentPlace()
{
    return this->currentPlace;
}

Place* Entity::getDesiredPlace()
{
    return this->desiredPlace;
}

bool Entity::getAnimating()
{
    return this->animating;
}

void Entity::PrepareForAnimation(Place *previousPlace, Place *nextPlace)
{
    this->animationPosition = previousPlace->getOnScreenPos();
    animating = true;
}

void Entity::Animate()
{
    if(animating)
    {
        Point2f destinationPosition = currentPlace->getOnScreenPos();
        float xDiff = animationPosition.x - destinationPosition.x;
        float yDiff = animationPosition.y - destinationPosition.y;
        
        float norm = sqrt((xDiff*xDiff) + (yDiff*yDiff));

        float xNorm = xDiff/norm;
        float yNorm = yDiff/norm;

        float unit = this->currentPlace->getParentField()->getUnit();
        
        static float step = unit/4.0f;

        /*
        static float halfStepX = step/2;
        static float halfStepY = halfStepX/aspect;
        */

        float halfStepX = abs(xNorm*step);
        float halfStepY = abs(yNorm*step);

        bool isOnX = false;
        bool isOnY = false;
        
        if(abs(xDiff) > step)
        {
            (xDiff < 0)? animationPosition.x += halfStepX : animationPosition.x -= halfStepX;
        }
        else
        {
            isOnX = true;
            animationPosition.x = destinationPosition.x;
        }

        if(abs(yDiff) > step)
        {
            (yDiff < 0) ? animationPosition.y += halfStepY : animationPosition.y -= halfStepY;
        }
        else
        {
            isOnY = true;
            animationPosition.y = destinationPosition.y;
        }
        if(isOnX && isOnY)
            animating = false;
        
    }
}

void Entity::Draw(float dTime)
{

    if(this->currentPlace == NULL)
        return;

    float unit = this->currentPlace->getParentField()->getUnit();
    float height = sqrt(3)/2*unit;

    Point2f placePos = this->currentPlace->getOnScreenPos();
    Point2i offset = this->currentPlace->getParentField()->getOffset();

#ifdef QT_UI

    painter->setPen(QPen(QColor(100,100,100)));

    painter->setBrush(this->brush);
    painter->save();
    painter->translate(placePos.x + offset.x, placePos.y + offset.y);

    painter->drawEllipse(QPoint(height,unit),(int)(unit/2),(int)(unit/2));
    painter->restore();

#endif

}


