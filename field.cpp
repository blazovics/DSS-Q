#include "field.h"
#include "place.h"
#include <set>
#include <list>

using namespace std;

Field::Field()
{

}

Field::~Field(){
    delete[] this->placeArray;
}

Field::Field(unsigned width, unsigned height, float unit, float xOffset, float yOffset){
    this->width = width;
    this->height = height;
    this->unit = unit;
    
    this->offset.x = xOffset;
    this->offset.y = yOffset;

    
    this->placeArray = new Place[width*height];

    float verticalUnit = unit*sqrt(3);
    float halfVerticalUnit = verticalUnit/2;
    float horizontalUnit = unit*1.5;
    
    this->maxOffset.x = verticalUnit*width-1024;
    this->maxOffset.y = horizontalUnit*height+unit/2-600;

    //row index = y
    for(unsigned i=0; i<this->height; i++){
        //column index = x
        for(unsigned j=0; j<this->width; j++){

            if(i%2 && j == this->width-1)
                continue;

            //Setup the coordinates

            float x = j*verticalUnit + (i%2)*halfVerticalUnit;
            float y = i*horizontalUnit;

            std::cout<<i<<" "<<j<<" "<<x<<" "<<y<<std::endl;

            placeArray[i*width+j].setParentField(this);
            placeArray[i*width+j].setUnitDistance(this->unit);
            placeArray[i*width+j].setPosition(Point2i(j,i));
            placeArray[i*width+j].setOnScreenPos(Point2f(x,y));

            //Setup Top neighbors

            if(i>0)
            {
                if(i%2 == 0)
                {
                    if(j>0)
                    {
                        placeArray[i*width+j].setNeighbor(&placeArray[(i-1)*width+j-1],topLeftNeighbor);
                    }
                    if(j<this->width-1)
                    {
                        placeArray[i*width+j].setNeighbor(&placeArray[(i-1)*width+j],topRightNeighbor);
                    }
                }
                else
                {
                    placeArray[i*width+j].setNeighbor(&placeArray[(i-1)*width+j],topLeftNeighbor);

                    placeArray[i*width+j].setNeighbor(&placeArray[(i-1)*width+j+1],topRightNeighbor);
                }
            }

            if(i<this->height-1)
            {    
                if(i%2 == 0)
                {
                    if(j>0)
                    {
                        placeArray[i*width+j].setNeighbor(&placeArray[(i+1)*width+j-1],bottomLeftNeighbor);
                    }
                    if(j<this->width-1)
                    {
                        placeArray[i*width+j].setNeighbor(&placeArray[(i+1)*width+j],bottomRightNeighbor);
                    }
                }
                else
                {
                    placeArray[i*width+j].setNeighbor(&placeArray[(i+1)*width+j],bottomLeftNeighbor);

                    placeArray[i*width+j].setNeighbor(&placeArray[(i+1)*width+j+1],bottomRightNeighbor);
                }
            }

            if(j>0)
            {
                placeArray[i*width+j].setNeighbor(&placeArray[i*width+j-1],leftNeighbor);
            }
            if(j<this->width-2 || (j<this->width-1 && i%2 == 0))
            {
                placeArray[i*width+j].setNeighbor(&placeArray[i*width+j+1],rightNeighbor);
            }
        }
    }
}

unsigned Field::getWidth()
{
    return this->width;
}

unsigned Field::getHeight()
{
    return this->height;
}

unsigned Field::getUnit()
{
    return this->unit;
}

Point2i Field::getOffset()
{
    return this->offset;
}

void Field::setOffset(Point2i offset)
{
    if(offset.x > 0 && offset.x < this->maxOffset.x){
        this->offset.x = offset.x;
    }
    if(offset.y > 0 && offset.y < this->maxOffset.y){
        this->offset.y = offset.y;
    }
}

//Dijkstra
bool Field::getPathBetweenPlaces(Place* startPlace,Place* destPlace, Place*** routePlaces, unsigned& routeLength){

    Entity* destEntity = destPlace->getEntity();
    
    unsigned size = width*height;

    unsigned *distanceArray = (unsigned*)malloc(size*sizeof(unsigned));// new unsigned[size];

    Place** nextPlace = (Place**)malloc(size*sizeof(Place*));

    set<Place*> unsortedPlaces;
    set<Place*>::iterator it;
    pair<set<Place*>::iterator,bool> ret;

    list<Place*> pathPlaces;
    list<Place*>::iterator pathIter;

    for(unsigned i=0; i<this->height; i++)
    {
        for(unsigned j=0; j<this->width; j++)
        {
            if(i%2 && j == this->width-1)
                continue;
            Place* curPlace = &placeArray[i*width+j];
            
            ret = unsortedPlaces.insert(curPlace);
            if(ret.second == false){
                cout<<i<<" "<<j<<endl;
            }
        }
    }

    //init distance Array with MAX_DISTANCE
    for(unsigned i = 0; i < size; i++)
    {
        distanceArray[i] = MAX_DISTANCE;
        nextPlace[i] = NULL;
    }

    //init the startPlace index

    Point2i selfPos = startPlace->getPosition();
    int selfIndex = selfPos.y*width+selfPos.x;
    distanceArray[selfIndex] = 0;
    
    while (unsortedPlaces.size() > 0)
    {
        it = unsortedPlaces.begin();
        Place* nearestPlace = *it;
        for(it = unsortedPlaces.begin(); it!=unsortedPlaces.end(); ++it){
            Point2i canPlacePos = nearestPlace->getPosition();
            unsigned canIndex = canPlacePos.y*width + canPlacePos.x;
            unsigned canDist = distanceArray[canIndex];
            
            Place* curPlace = *it;
            
            Point2i curPlacePos = curPlace->getPosition();
            unsigned curIndex = curPlacePos.y*width + curPlacePos.x;
            unsigned curDist = distanceArray[curIndex];

            if(canDist > curDist){
                nearestPlace = curPlace;
            }
        }
        unsortedPlaces.erase(nearestPlace);

        Point2i nearestPlacePos = nearestPlace->getPosition();
        unsigned nearestIndex = nearestPlacePos.y*width + nearestPlacePos.x;
        unsigned nearestDist = distanceArray[nearestIndex];

        if(nearestDist >= MAX_DISTANCE)
        {
            break;
        }

        char* freeNeighborArray;
        unsigned freeNBCount;
        nearestPlace->getFreeNeighbors(&freeNeighborArray,freeNBCount,destEntity);

        for(unsigned i=0; i<freeNBCount; i++){
            unsigned placeIndex = (unsigned)freeNeighborArray[i];
            Place* tmpPlace = nearestPlace->getNeighbor(placeIndex);
            Point2i pos = tmpPlace->getPosition();
            int index = pos.y*width+pos.x;

            unsigned altDist = distanceArray[nearestIndex] + 1; // 1 is distance
            if(altDist < distanceArray[index])
            {
                distanceArray[index] = altDist;
                nextPlace[index] = nearestPlace;
            }
        }

        delete []freeNeighborArray;
    }

    Point2i nextPosPoint = destPlace->getPosition();
    int nextIndex = nextPosPoint.y*width+nextPosPoint.x;

    Place* place = nextPlace[nextIndex];
    
    while (nextPlace[nextIndex] != NULL)
    {
        Place* place = nextPlace[nextIndex];
        
        pathPlaces.push_front(place);

        Point2i nxtPosPoint = place->getPosition();
        nextIndex = nxtPosPoint.y*width+nxtPosPoint.x;

        //std::cout<<"match "<<nextIndex<<std::endl;
    }

    routeLength = pathPlaces.size();
    *routePlaces = new Place*[routeLength];

    int i=0;

    for(i=0, pathIter = pathPlaces.begin(); pathIter != pathPlaces.end(); ++pathIter, i++)
    {
        (*routePlaces)[i] = *pathIter;
    }

    delete []distanceArray;
    delete []nextPlace;

    return true;
}

#ifdef QT_UI

void Field::setPainter(QPainter *painter){
    this->painter = painter;

    int entityPlace = -1;

    //row
    for(unsigned i=0; i<this->height; i++)
    {
        //column
        for(unsigned j=0; j<this->width; j++)
        {
            if(i%2 && j == this->width-1)
                continue;
            placeArray[i*width+j].setPainter(painter);
            placeArray[i*width+j].setBrush(QBrush(Qt::green));

            if(placeArray[i*width+j].getEntity() != NULL)
            {
                entityPlace = i*width+j;

                if(entityPlace > -1)
                {
                    Place* p = &placeArray[entityPlace];
                    p->setBrush(QBrush(Qt::blue));
                }
            }
        }
    }

}

#endif

void Field::cleanNextEntities()
{
    //row
    for(unsigned i=0; i<this->height; i++)
    {
        //column
        for(unsigned j=0; j<this->width; j++)
        {
            if(i%2 && j == this->width-1)
                continue;
            placeArray[i*width+j].setNextEntity(NULL);
        }
    }
}

unsigned Field::placeCount()
{
    return width*height;
}

Place* Field::getPlaceAtPosition(Point2i pos){
    if(pos.y*width+pos.x < placeCount())
        return &placeArray[pos.y*width+pos.x];
    return NULL;
}

Place* Field::getPlaceForTouchPoint(Point2i tPos){
    float xWidth = sqrt(3)/2*unit;
    
    tPos.x -= xWidth;
    tPos.y -= unit;
    
    Place* selectedPlace = NULL;
    
    for(unsigned i=0; i<this->height; i++)
    {
        //column
        for(unsigned j=0; j<this->width; j++)
        {
            if(i%2 && j == this->width-1)
                continue;
            Point2f pPos = placeArray[i*width+j].getOnScreenPos();
            float distance = sqrt(pow(tPos.x-pPos.x+offset.x,2)+pow(tPos.y-pPos.y+offset.y,2));
            if(distance < unit)
                selectedPlace = &placeArray[i*width+j];
        }
    }
    return selectedPlace;
}

void Field::Draw(float dTime){   

#ifdef QT_UI
    painter->drawRect(this->offset.x,this->offset.y+5,this->width*unit*sqrt(3),this->height*unit*1.5);
#endif

    //row
    for(unsigned i=0; i<this->height; i++)
    {
        //column
        for(unsigned j=0; j<this->width; j++)
        {
            if(i%2 && j == this->width-1)
                continue;
            placeArray[i*width+j].Draw(dTime);
        }
    }
}

