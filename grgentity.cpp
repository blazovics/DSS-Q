#include "grgentity.h"
#include "place.h"
#include "field.h"

GRGEntity::GRGEntity() : Entity()
{
    this->targetEntity = NULL;
    this->rotationStartPlace = NULL;
}

int GRGEntity::getType()
{
    return GRG_ENTITY;
}

void GRGEntity::setTargetEntity(Entity* targetEntity)
{
    this->targetEntity = targetEntity;
}

void GRGEntity::Step()
{
    Place* targetPlace = this->targetEntity->getCurrentPlace();
    if(targetPlace == NULL)
        return;

    neighborhoodType nType = same;

    //calculate current distance from the target
    Place::entityDistance(this->currentPlace, targetPlace,this->targetDistance,nType);

    //get neighbors which are closer than me
    char* freePlaceIDArray = NULL;
    unsigned arraySize = 0;
    this->currentPlace->getFreeNeighbors(&freePlaceIDArray,arraySize);

    this->desiredPlace = currentPlace;

    for(unsigned i=0; i<arraySize; i++)
    {
        Place* nFreePlace = this->currentPlace->getNeighbor((unsigned)freePlaceIDArray[i]);
        unsigned nTargetDistance;

        neighborhoodType nfType;

        Place::entityDistance(nFreePlace,this->targetEntity->getCurrentPlace(), nTargetDistance,nfType);

        //interresting Place
        if(nTargetDistance < this->targetDistance)
        {
            //We are on an edge. Mid neighbor
            if(nType < 6)
            {
                continue;
            }

            if(((nfType == l_Neighbor || nfType == l_tl_Neighbor) && (nFreePlace->getNeighbor(topLeftNeighbor) == this->currentPlace))||
               ((nfType == tl_Neighbor || nfType == tl_tr_Neighbor) && (nFreePlace->getNeighbor(topRightNeighbor) == this->currentPlace)) ||
               ((nfType == tr_Neighbor || nfType == tr_r_Neighbor) && (nFreePlace->getNeighbor(rightNeighbor) == this->currentPlace)) ||
               ((nfType == r_Neighbor || nfType == r_br_Neighbor) && (nFreePlace->getNeighbor(bottomRightNeighbor) == this->currentPlace)) ||
               ((nfType == br_Neighbor || nfType == br_bl_Neighbor) && (nFreePlace->getNeighbor(bottomLeftNeighbor) == this->currentPlace)) ||
               ((nfType == bl_Neighbor || nfType == l_bl_Neighbor) && (nFreePlace->getNeighbor(leftNeighbor) == this->currentPlace)))
            {
                this->desiredPlace = nFreePlace;
            }
        }
    }

    //If there is no target, then rotate:
    if(this->desiredPlace == currentPlace)
    {
        //check if there is a rotating entity behind me
        if((nType == l_Neighbor || nType == l_bl_Neighbor))
        {
            Place *blockedPlace = this->currentPlace->getNeighbor(bottomLeftNeighbor);
            if(blockedPlace == NULL || blockedPlace->getEntity() == NULL)
            {
                this->desiredPlace = this->currentPlace->getNeighbor(bottomRightNeighbor);
            }
        }
        else if((nType == bl_Neighbor || nType == br_bl_Neighbor))
        {
            Place *blockedPlace = this->currentPlace->getNeighbor(bottomRightNeighbor);
            if(blockedPlace == NULL || blockedPlace->getEntity() == NULL)
            {
                this->desiredPlace = this->currentPlace->getNeighbor(rightNeighbor);
            }
        }
        else if((nType == br_Neighbor || nType == r_br_Neighbor))
        {
            Place *blockedPlace = this->currentPlace->getNeighbor(rightNeighbor);
            if(blockedPlace == NULL || blockedPlace->getEntity() == NULL)
            {
                this->desiredPlace = this->currentPlace->getNeighbor(topRightNeighbor);
            }
        }
        else if((nType == r_Neighbor || nType == tr_r_Neighbor))
        {
            Place *blockedPlace = this->currentPlace->getNeighbor(topRightNeighbor);
            if(blockedPlace == NULL || blockedPlace->getEntity() == NULL)
            {
                this->desiredPlace = this->currentPlace->getNeighbor(topLeftNeighbor);
            }
        }
        else if((nType == tl_tr_Neighbor || nType == tr_Neighbor))
        {
            Place *blockedPlace = this->currentPlace->getNeighbor(topLeftNeighbor);
            if(blockedPlace == NULL || blockedPlace->getEntity() == NULL)
            {
                this->desiredPlace = this->currentPlace->getNeighbor(leftNeighbor);
            }
        }
        else if((nType == tl_Neighbor || nType == l_tl_Neighbor))
        {
            Place *blockedPlace = this->currentPlace->getNeighbor(leftNeighbor);
            if(blockedPlace == NULL || blockedPlace->getEntity() == NULL)
            {
                this->desiredPlace = this->currentPlace->getNeighbor(bottomLeftNeighbor);
            }
        }

        if(this->desiredPlace != currentPlace && this->desiredPlace->getEntity() != NULL)
        {
            this->desiredPlace = currentPlace;
        }
    }


}

void GRGEntity::AfterStep()
{

}

void GRGEntity::setState(GRGState newState)
{
    switch(newState)
    {
    case greedy:
        this->rotationStartPlace = NULL;
        break;
    case rotation:
        this->rotationStartPlace = this->currentPlace;
        break;
    case stopped:

        break;
    }
}

void GRGEntity::Draw(float dTime)
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

#ifdef QT_UI

    painter->setPen(QPen(QColor(100,100,100)));

    painter->setBrush(this->brush);
    painter->save();
    painter->translate(placePos.x + offset.x , placePos.y + offset.y);

    painter->drawEllipse(QPoint(height,unit),(int)(unit/2),(int)(unit/2));
    painter->restore();

#endif
}
