#include "place.h"
#include "field.h"
#include "entity.h"

Place::Place():RenderObject()
{
    for(int i = 0; i < 6; i++){
        this->neighbors[i] = NULL;
    }
    this->entity = NULL;
    this->nextEntity = NULL;
}

void Place::setNeighbor(Place* neighbor,  neighborType type)
{
    this->neighbors[type] = neighbor;
}

Place* Place::getNeighbor(unsigned neighborID){
    return this->neighbors[neighborID];
}


Place* Place::getNeighbor(neighborType type){
    return this->neighbors[type];
}

void Place::setPosition(Point2i position)
{
    this->position.x = position.x;
    this->position.y = position.y;
}

Point2i Place::getPosition(){
    return this->position;
}

void Place::setUnitDistance(unsigned unit)
{
    this->unit = unit;
}

unsigned Place::getUnitDistance()
{
    return  this->unit;
}

void Place::setParentField(Field* field)
{
    this->parentField = field;
}

Field* Place::getParentField()
{
    return this->parentField;
}

void Place::setEntity(Entity* entity)
{
    this->entity = entity;
}

Entity* Place::getEntity()
{
    return this->entity;
}

void Place::setNextEntity(Entity* entity)
{
    this->nextEntity = entity;
}

Entity* Place::getNextEntity()
{
    return this->nextEntity;
}

void Place::serialize(ostream &os)
{

}

void Place::getFreeNeighbors(char ** neighborIDArray, unsigned& size)
{
    getFreeNeighbors(neighborIDArray, size, NULL);
}

void Place::getFreeNeighbors(char** neighborIDArray, unsigned& size, Entity* ignorableEntity)
{
    size = 0;
    *neighborIDArray = NULL;
    char tempArray[6];
    
    for(unsigned i=0; i < 6; i++)
    {
        if(this->neighbors[i] != NULL)
        {
            if(this->neighbors[i]->entity == NULL || this->neighbors[i]->entity == ignorableEntity)
            {
                tempArray[size] = (char)i;
                size++;
            }
        }
    }
    if(size > 0)
    {
        char* array = NULL;
        array = (char*)malloc(size*sizeof(char));
        for(unsigned i = 0; i < size; i++)
        {
            array[i] = tempArray[i];
        }
        *neighborIDArray = array;
    }
}

void Place::getFreeNextNeighbors(char ** neighborIDArray, unsigned& size)
{
    size = 0;
    *neighborIDArray = NULL;
    char tempArray[6];

    for(unsigned i=0; i < 6; i++)
    {
        if(this->neighbors[i] != NULL)
        {
            if(this->neighbors[i]->nextEntity == NULL)
            {
                tempArray[size] = (char)i;
                size++;
            }
        }
    }
    if(size > 0)
    {
        char* array = NULL;
        array = (char*)malloc(size*sizeof(char));
        for(unsigned i = 0; i < size; i++)
        {
            array[i] = tempArray[i];
        }
        *neighborIDArray = array;
    }
}

void Place::entityDistance(Place* firstPlace, Place* secondPlace, unsigned& distance, neighborhoodType& nType)
{
    Point2i firstPos = firstPlace->getPosition();
    Point2i secondPos = secondPlace->getPosition();

    int leftSegmenter_x;
    int rightSegmenter_x;

    nType = same;

    int f_l_a = (int)ceil(firstPos.y/2.0);
    int s_l_a = (int)ceil(secondPos.y/2.0);

    int f_r_a = (int)ceil((firstPos.y+1)/2.0);
    int s_r_a = (int)ceil((secondPos.y+1)/2.0);

    if(firstPos.y>=secondPos.y)
    {
        leftSegmenter_x = secondPos.x + (s_l_a-f_l_a);
        rightSegmenter_x = secondPos.x + (f_r_a-s_r_a);
    }
    else
    {
        rightSegmenter_x = secondPos.x + (s_l_a-f_l_a);
        leftSegmenter_x = secondPos.x + (f_r_a-s_r_a);
    }

    //row
    if(firstPos.y == secondPos.y)
    {
        if(firstPos.x < secondPos.x)
            nType = l_Neighbor;
        else if(firstPos.x > secondPos.x)
            nType = r_Neighbor;
    }
    //top
    else if(firstPos.y < secondPos.y)
    {
        if(leftSegmenter_x > firstPos.x)
        {
            nType = l_tl_Neighbor;
        }
        else if (leftSegmenter_x == firstPos.x)
        {
            nType = tl_Neighbor;
        }
        else if (firstPos.x > leftSegmenter_x && rightSegmenter_x > firstPos.x){
            nType = tl_tr_Neighbor;
        }
        else if (rightSegmenter_x == firstPos.x)
        {
            nType = tr_Neighbor;
        }
        else
        {
            nType = tr_r_Neighbor;
        }
    }
    else
    {
        if(leftSegmenter_x > firstPos.x)
        {
            nType = l_bl_Neighbor;
        }
        else if (leftSegmenter_x == firstPos.x)
        {
            nType = bl_Neighbor;
        }
        else if (firstPos.x > leftSegmenter_x && rightSegmenter_x > firstPos.x){
            nType = br_bl_Neighbor;
        }
        else if (rightSegmenter_x == firstPos.x)
        {
            nType = br_Neighbor;
        }
        else
        {
            nType = r_br_Neighbor;
        }
    }

    int x_dist = secondPos.x - firstPos.x;
    int y_dist = secondPos.y - firstPos.y;

    int cell2x = secondPos.x;
    int dy = abs(firstPos.y - secondPos.y);
    //
    // If dy is odd, then reflect the x coordinate about the starting cell, do a similar
    // reflection if dy is even.
    if (firstPos.y % 2 == 0 && secondPos.x < firstPos.x && dy % 2 == 1)
    {
        cell2x = firstPos.x + (firstPos.x - secondPos.x) - 1;
    }
    else if (firstPos.y % 2 == 1 && secondPos.x > firstPos.x && dy % 2 == 1)
    {
        cell2x = firstPos.x - (secondPos.x - firstPos.x) + 1;
    }

    int dx = abs(firstPos.x - cell2x);

    if (dx < dy/2)
    {
        distance = dy;
    }
    else
    {
        distance = dy + dx - floor(dy/2.0f);
    }
}

void Place::Draw(float dTime){

    //float unit = 40;
    float width = sqrt(3)/2*unit;
    Point2i offset = this->parentField->getOffset();
    
#ifdef QT_UI

    static const QPoint center(width,unit);

    static const QPoint points[6] = {
        QPoint(width, 0),
        QPoint(2*width, unit/2),
        QPoint(2*width, unit/2+unit),
        QPoint(width, 2*unit),
        QPoint(0, unit/2+unit),
        QPoint(0, unit/2)
    };

    static const QPoint points2[6] = {
        QPoint(1.5*width,unit/4),
        QPoint(2*width,unit),
        QPoint(1.5*width,unit+unit/2+unit/4),
        QPoint(0.5*width,unit+unit/2+unit/4),
        QPoint(0,unit),
        QPoint(0.5*width,unit/4),
    };

    painter->setBrush(this->brush);
    painter->save();
    painter->translate(this->onScreenPos.x+offset.x, this->onScreenPos.y+offset.y);

    for(unsigned i=0; i<6; i++){

        painter->drawLine(points2[i],center);
    }

    painter->restore();
#endif
    
    if(this->entity != NULL){
        this->entity->Draw(dTime);
    }

}
