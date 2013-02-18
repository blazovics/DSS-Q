#include "swarmentity.h"
#include "place.h"
#include "field.h"

SwarmEntity::SwarmEntity() : Entity()
{
    this->targetEntity = NULL;
    this->targetDistance = 0;
}

int SwarmEntity::getType()
{
    return SWARM_ENTITY;
}

void SwarmEntity::setTargetEntity(Entity* targetEntity)
{
    this->targetEntity = targetEntity;
}

void SwarmEntity::Step()
{
    if(this->targetEntity == NULL)
    {
        //In order to keep the entity in a given place
        this->desiredPlace = this->currentPlace;
        return;

        //choose a neighbor
        unsigned freeNbSize = 0;
        char* neighbors = NULL;

        currentPlace->getFreeNextNeighbors(&neighbors,freeNbSize);

        //genrate random number
        if (freeNbSize > 0){
            int randomNumber = rand();
            unsigned index = randomNumber % freeNbSize;
            unsigned newID = neighbors[index];
            Place* newPlace = currentPlace->getNeighbor(newID);

            //Point2i p = newPlace->getPosition();
            //std::cout<<"possible places: "<<freeNbSize<<" randomNum: "<<randomNumber<<" index: "<<index<<" new place: "<<newID<<" "<<p.x<<" "<<p.y<<endl;

            this->desiredPlace = newPlace;
            newPlace->setNextEntity(this);
            delete [] neighbors;
        }

        this->desiredPlace = this->currentPlace;
        return;
    }

    if(this->targetEntity->getCurrentPlace() == NULL)
    {
        this->desiredPlace = this->currentPlace;
        return;
    }

    neighborhoodType nType = same;

    Place::entityDistance(this->currentPlace,this->targetEntity->getCurrentPlace(),this->targetDistance, nType);

    if(nType == same)
    {
        this->desiredPlace = this->currentPlace;
        return;
    }

    headingDir = this->calculateHeadingDirection();

    neighborType nextNeighbor;

    //circulation only

    if(nType < 6)
    {
        neighborType lookAtN = (neighborType)nType;

        if(headingDir == rightHeading)
        {
             if(lookAtN == leftNeighbor)
             {
                 nextNeighbor = bottomLeftNeighbor;
            }
             else
             {
                 nextNeighbor = (neighborType)((int)nType-1);
             }
        }
        else
        {
            if(lookAtN == bottomLeftNeighbor)
            {
                nextNeighbor = leftNeighbor;
            }
            else
            {
                nextNeighbor = (neighborType)((int)nType+1);
            }
        }
    }

    else if(nType > 6)
    {
        if(headingDir == rightHeading)
        {
            if(nType == l_tl_Neighbor)
            {
                if(currentPlace->getNeighbor(rightNeighbor)->getEntity() == NULL)
                {
                    nextNeighbor = bottomRightNeighbor;
                }
                else
                {
                    nextNeighbor = topRightNeighbor;
                }
            }
            else if(nType == tl_tr_Neighbor)
            {
                if(currentPlace->getNeighbor(bottomRightNeighbor)->getEntity() == NULL)
                {
                    nextNeighbor = bottomLeftNeighbor;
                }
                else
                {
                    nextNeighbor = rightNeighbor;
                }
            }
            else if(nType == tr_r_Neighbor)
            {
                if(currentPlace->getNeighbor(bottomLeftNeighbor)->getEntity() == NULL)
                {
                    nextNeighbor = leftNeighbor;
                }
                else
                {
                    nextNeighbor = bottomRightNeighbor;
                }
            }
            else if(nType == r_br_Neighbor)
            {
                if(currentPlace->getNeighbor(leftNeighbor)->getEntity() == NULL)
                {
                    nextNeighbor = topLeftNeighbor;
                }
                else
                {
                    nextNeighbor = bottomLeftNeighbor;
                }
            }
            else if(nType == br_bl_Neighbor)
            {
                if(currentPlace->getNeighbor(topLeftNeighbor)->getEntity() == NULL)
                {
                    nextNeighbor = topRightNeighbor;
                }
                else
                {
                    nextNeighbor = leftNeighbor;
                }
            }
            else if(nType == l_bl_Neighbor)
            {
                if(currentPlace->getNeighbor(topRightNeighbor)->getEntity() == NULL)
                {
                    nextNeighbor = rightNeighbor;
                }
                else
                {
                    nextNeighbor = topLeftNeighbor;
                }
            }
        }
        else
        {   
            if(nType == l_tl_Neighbor)
            {
                if(currentPlace->getNeighbor(bottomRightNeighbor)->getEntity() == NULL)
                {
                    nextNeighbor = rightNeighbor;
                }
                else
                {
                    nextNeighbor = bottomLeftNeighbor;
                }
            }
            else if(nType == tl_tr_Neighbor)
            {
                if(currentPlace->getNeighbor(bottomLeftNeighbor)->getEntity() == NULL)
                {
                    nextNeighbor = bottomRightNeighbor;
                }
                else
                {
                    nextNeighbor = leftNeighbor;
                }
            }
            else if(nType == tr_r_Neighbor)
            {
                if(currentPlace->getNeighbor(leftNeighbor)->getEntity() == NULL)
                {
                    nextNeighbor = bottomLeftNeighbor;
                }
                else
                {
                    nextNeighbor = topLeftNeighbor;
                }
            }
            else if(nType == r_br_Neighbor)
            {
                if(currentPlace->getNeighbor(topLeftNeighbor)->getEntity() == NULL)
                {
                    nextNeighbor = leftNeighbor;
                }
                else
                {
                    nextNeighbor = topRightNeighbor;
                }
            }
            else if(nType == br_bl_Neighbor)
            {
                if(currentPlace->getNeighbor(topRightNeighbor)->getEntity() == NULL)
                {
                    nextNeighbor = topLeftNeighbor;
                }
                else
                {
                    nextNeighbor = rightNeighbor;
                }
            }
            else if(nType == l_bl_Neighbor)
            {
                if(currentPlace->getNeighbor(rightNeighbor)->getEntity() == NULL)
                {
                    nextNeighbor = topRightNeighbor;
                }
                else
                {
                    nextNeighbor = bottomRightNeighbor;
                }
            }
        }
    }

    Place* nextPlace = this->currentPlace->getNeighbor(nextNeighbor);

    this->desiredPlace = nextPlace;
}

void SwarmEntity::AfterStep()
{

    if(this->targetEntity == NULL)
    {
        this->desiredPlace = this->currentPlace;
        return;
    }

    if(this->targetEntity->getCurrentPlace() == NULL)
    {
        this->desiredPlace = this->currentPlace;
        return;
    }

    neighborhoodType nType = same;

    Place::entityDistance(this->currentPlace,this->targetEntity->getCurrentPlace(),this->targetDistance, nType);

    unsigned desiredTargetDistance;

    neighborhoodType desiredTargetNType;

    Place::entityDistance(this->desiredPlace,this->targetEntity->getCurrentPlace(),desiredTargetDistance, desiredTargetNType);

    if(this->currentPlace == this->desiredPlace)
        std::cout<<"CRITICAL ERROR!"<<std::endl;

    if(desiredTargetDistance < this->targetDistance || targetDistance == 1)
    {
        return;
    }

    if(this->desiredPlace != NULL && this->desiredPlace->getNextEntity() == this)
    {
        this->desiredPlace->setNextEntity(NULL);
    }

    if(nType == same)
    {
        this->desiredPlace = this->currentPlace;
        return;
    }

    headingDir = this->calculateHeadingDirection();

    neighborType nextNeighbor;

    //for the edge test
    neighborhoodType nfType;
    unsigned dist;

    if(headingDir == rightHeading)
    {

        /*
        if(lookAtN == leftNeighbor)
        {
            nextNeighbor = bottomLeftNeighbor;
        }
        else
        {
            nextNeighbor = (neighborType)((int)nType-1);
        }*/

        if(nType == l_Neighbor)
        {
            if(currentPlace->getNeighbor(rightNeighbor)->getNextEntity() == NULL)
            {
                nextNeighbor = rightNeighbor;
            }
            else
            {
                nextNeighbor = (neighborType)((int)nType-1);
            }
        }
        else if(nType == tl_Neighbor)
        {
            if(currentPlace->getNeighbor(bottomRightNeighbor)->getNextEntity() == NULL)
            {
                nextNeighbor = bottomRightNeighbor;
            }
            else
            {
                nextNeighbor = (neighborType)((int)nType-1);
            }
        }
        else if(nType == tr_Neighbor)
        {
            if(currentPlace->getNeighbor(bottomLeftNeighbor)->getNextEntity() == NULL)
            {
                nextNeighbor = bottomLeftNeighbor;
            }
            else
            {
                nextNeighbor = (neighborType)((int)nType-1);
            }
        }
        else if(nType == r_Neighbor)
        {
            if(currentPlace->getNeighbor(leftNeighbor)->getNextEntity() == NULL)
            {
                nextNeighbor = leftNeighbor;
            }
            else
            {
                nextNeighbor = bottomLeftNeighbor;
            }
        }
        else if(nType == br_Neighbor)
        {
            if(currentPlace->getNeighbor(topLeftNeighbor)->getNextEntity() == NULL)
            {
                nextNeighbor = topLeftNeighbor;
            }
            else
            {
                nextNeighbor = (neighborType)((int)nType-1);
            }
        }
        else if(nType == bl_Neighbor)
        {
            if(currentPlace->getNeighbor(topRightNeighbor)->getNextEntity() == NULL)
            {
                nextNeighbor = topRightNeighbor;
            }
            else
            {
                nextNeighbor = (neighborType)((int)nType-1);
            }
        }

        else if(nType == l_tl_Neighbor)
        {
            if(currentPlace->getNeighbor(rightNeighbor)->getNextEntity() == NULL)
            {
                Place::entityDistance(currentPlace->getNeighbor(rightNeighbor),this->targetEntity->getCurrentPlace(),dist,nfType);

                if(nfType < 6)
                {
                    nextNeighbor = topRightNeighbor;
                }
                else
                {
                    nextNeighbor = rightNeighbor;
                }
            }
            else
            {
                nextNeighbor = topRightNeighbor;
            }
        }
        else if(nType == tl_tr_Neighbor)
        {
            if(currentPlace->getNeighbor(bottomRightNeighbor)->getNextEntity() == NULL)
            {
                Place::entityDistance(currentPlace->getNeighbor(bottomRightNeighbor),this->targetEntity->getCurrentPlace(),dist,nfType);

                if(nfType < 6)
                {
                    nextNeighbor = rightNeighbor;
                }
                else
                {
                    nextNeighbor = bottomRightNeighbor;
                }
            }
            else
            {
                nextNeighbor = rightNeighbor;
            }
        }
        else if(nType == tr_r_Neighbor)
        {
            if(currentPlace->getNeighbor(bottomLeftNeighbor)->getNextEntity() == NULL)
            {
                Place::entityDistance(currentPlace->getNeighbor(bottomLeftNeighbor),this->targetEntity->getCurrentPlace(),dist,nfType);

                if(nfType < 6)
                {
                    nextNeighbor = bottomRightNeighbor;
                }
                else
                {
                    nextNeighbor = bottomLeftNeighbor;
                }
            }
            else
            {
                nextNeighbor = bottomRightNeighbor;
            }
        }
        else if(nType == r_br_Neighbor)
        {
            if(currentPlace->getNeighbor(leftNeighbor)->getNextEntity() == NULL)
            {
                Place::entityDistance(currentPlace->getNeighbor(leftNeighbor),this->targetEntity->getCurrentPlace(),dist,nfType);

                if(nfType < 6)
                {
                    nextNeighbor = bottomLeftNeighbor;
                }
                else
                {
                    nextNeighbor = leftNeighbor;
                }
            }
            else
            {
                nextNeighbor = bottomLeftNeighbor;
            }
        }
        else if(nType == br_bl_Neighbor)
        {
            if(currentPlace->getNeighbor(topLeftNeighbor)->getNextEntity() == NULL)
            {
                Place::entityDistance(currentPlace->getNeighbor(topLeftNeighbor),this->targetEntity->getCurrentPlace(),dist,nfType);

                if(nfType < 6)
                {
                    nextNeighbor = leftNeighbor;
                }
                else
                {
                    nextNeighbor = topLeftNeighbor;
                }
            }
            else
            {
                nextNeighbor = leftNeighbor;
            }
        }
        else if(nType == l_bl_Neighbor)
        {
            if(currentPlace->getNeighbor(topRightNeighbor)->getNextEntity() == NULL)
            {
                Place::entityDistance(currentPlace->getNeighbor(topRightNeighbor),this->targetEntity->getCurrentPlace(),dist,nfType);

                if(nfType < 6)
                {
                    nextNeighbor = topLeftNeighbor;
                }
                else
                {
                    nextNeighbor = topRightNeighbor;
                }
            }
            else
            {
                nextNeighbor = topLeftNeighbor;
            }
        }
        else{
            std::cout <<"Critical Error"<<std::endl;
        }
    }
    else
    {
        if(nType == l_Neighbor)
        {
            if(currentPlace->getNeighbor(rightNeighbor)->getNextEntity() == NULL)
            {
                nextNeighbor = rightNeighbor;
            }
            else
            {
                nextNeighbor = (neighborType)((int)nType+1);
            }
        }
        else if(nType == tl_Neighbor)
        {
            if(currentPlace->getNeighbor(bottomRightNeighbor)->getNextEntity() == NULL)
            {
                nextNeighbor = bottomRightNeighbor;
            }
            else
            {
                nextNeighbor = (neighborType)((int)nType+1);
            }
        }
        else if(nType == tr_Neighbor)
        {
            if(currentPlace->getNeighbor(bottomLeftNeighbor)->getNextEntity() == NULL)
            {
                nextNeighbor = bottomLeftNeighbor;
            }
            else
            {
                nextNeighbor = leftNeighbor;
            }
        }
        else if(nType == r_Neighbor)
        {
            if(currentPlace->getNeighbor(leftNeighbor)->getNextEntity() == NULL)
            {
                nextNeighbor = leftNeighbor;
            }
            else
            {
                nextNeighbor = (neighborType)((int)nType+1);
            }
        }
        else if(nType == br_Neighbor)
        {
            if(currentPlace->getNeighbor(topLeftNeighbor)->getNextEntity() == NULL)
            {
                nextNeighbor = topLeftNeighbor;
            }
            else
            {
                nextNeighbor = (neighborType)((int)nType+1);
            }
        }
        else if(nType == bl_Neighbor)
        {
            if(currentPlace->getNeighbor(topRightNeighbor)->getNextEntity() == NULL)
            {
                nextNeighbor = topRightNeighbor;
            }
            else
            {
                nextNeighbor = (neighborType)((int)nType+1);
            }
        }
        else if(nType == l_tl_Neighbor)
        {
            if(currentPlace->getNeighbor(bottomRightNeighbor)->getNextEntity() == NULL)
            {
                Place::entityDistance(currentPlace->getNeighbor(bottomRightNeighbor),this->targetEntity->getCurrentPlace(),dist,nfType);

                if(nfType < 6)
                {
                    nextNeighbor = bottomLeftNeighbor;
                }
                else
                {
                    nextNeighbor = bottomRightNeighbor;
                }
            }
            else
            {
                nextNeighbor = bottomLeftNeighbor;
            }
        }
        else if(nType == tl_tr_Neighbor)
        {
            if(currentPlace->getNeighbor(bottomLeftNeighbor)->getNextEntity() == NULL)
            {
                Place::entityDistance(currentPlace->getNeighbor(bottomLeftNeighbor),this->targetEntity->getCurrentPlace(),dist,nfType);

                if(nfType < 6)
                {
                    nextNeighbor = leftNeighbor;
                }
                else
                {
                    nextNeighbor = bottomLeftNeighbor;
                }
            }
            else
            {
                nextNeighbor = leftNeighbor;
            }
        }
        else if(nType == tr_r_Neighbor)
        {
            if(currentPlace->getNeighbor(leftNeighbor)->getNextEntity() == NULL)
            {
                Place::entityDistance(currentPlace->getNeighbor(leftNeighbor),this->targetEntity->getCurrentPlace(),dist,nfType);

                if(nfType < 6)
                {
                    nextNeighbor = topLeftNeighbor;
                }
                else
                {
                    nextNeighbor = leftNeighbor;
                }
            }
            else
            {
                nextNeighbor = topLeftNeighbor;
            }
        }
        else if(nType == r_br_Neighbor)
        {
            if(currentPlace->getNeighbor(topLeftNeighbor)->getNextEntity() == NULL)
            {
                Place::entityDistance(currentPlace->getNeighbor(topLeftNeighbor),this->targetEntity->getCurrentPlace(),dist,nfType);

                if(nfType < 6)
                {
                    nextNeighbor = topRightNeighbor;
                }
                else
                {
                    nextNeighbor = topLeftNeighbor;
                }
            }
            else
            {
                nextNeighbor = topRightNeighbor;
            }
        }
        else if(nType == br_bl_Neighbor)
        {
            if(currentPlace->getNeighbor(topRightNeighbor)->getNextEntity() == NULL)
            {
                Place::entityDistance(currentPlace->getNeighbor(topRightNeighbor),this->targetEntity->getCurrentPlace(),dist,nfType);

                if(nfType < 6)
                {
                    nextNeighbor = rightNeighbor;
                }
                else
                {
                    nextNeighbor = topRightNeighbor;
                }
            }
            else
            {
                nextNeighbor = rightNeighbor;
            }
        }
        else if(nType == l_bl_Neighbor)
        {
            if(currentPlace->getNeighbor(rightNeighbor)->getNextEntity() == NULL)
            {
                Place::entityDistance(currentPlace->getNeighbor(rightNeighbor),this->targetEntity->getCurrentPlace(),dist,nfType);

                if(nfType < 6)
                {
                    nextNeighbor = bottomRightNeighbor;
                }
                else
                {
                    nextNeighbor = rightNeighbor;
                }
            }
            else
            {
                nextNeighbor = bottomRightNeighbor;
            }
        }
        else{
            std::cout <<"Critical Error"<<std::endl;
        }
    }

    Place* nextPlace = this->currentPlace->getNeighbor(nextNeighbor);

    this->desiredPlace = nextPlace;

    if(nextPlace->getNextEntity() != NULL && nextPlace->getEntity() != this)
    {
        std::cout<<"Critical Error!"<<std::endl;
    }

    if(nextPlace == this->currentPlace)
    {
        std::cout<<"Critical Placement Error!"<<std::endl;
    }

    nextPlace->setNextEntity(this);
}


headingDirection SwarmEntity::calculateHeadingDirection()
{
    if(this->targetDistance % 2 == 0)
    {
        return leftHeading;
    }
    else{
        return rightHeading;
    }
}

void SwarmEntity::Draw(float dTime)
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
