#include "scene.h"
#include "field.h"
#include "entity.h"
#include "place.h"
#include "targetentity.h"
#include "swarmentity.h"
#include "grgentity.h"
#include "playerentity.h"

Scene::Scene()
{
    srand ( time(NULL) );

    this->field = NULL;
    this->targetEntity = NULL;

    this->runMode = runModePaused;
}

Scene::Scene(unsigned fieldWidth, unsigned fieldHeight, unsigned xOffset, unsigned yOffset)
{
    srand ( time(NULL) );

    this->field = new Field(fieldWidth,fieldHeight,20.0,xOffset,yOffset);

    this->targetEntity = new TargetEntity();
    this->targetEntity->setCurrentPlace(field->getPlaceAtPosition(Point2i(3,3)));

    SwarmEntity* swarmEntities[12];

    for(int i=0; i<12; i++){
        swarmEntities[i] = new SwarmEntity();
        swarmEntities[i]->setTargetEntity(targetEntity);
        entities.insert(swarmEntities[i]);

        swarmEntities[i]->setBrush(QBrush(QColor(40,30*i,34)));
    }

    swarmEntities[0]->setCurrentPlace(field->getPlaceAtPosition(Point2i(3,2)));

    swarmEntities[1]->setCurrentPlace(field->getPlaceAtPosition(Point2i(4,2)));
    swarmEntities[2]->setCurrentPlace(field->getPlaceAtPosition(Point2i(2,3)));
    swarmEntities[3]->setCurrentPlace(field->getPlaceAtPosition(Point2i(4,4)));
    swarmEntities[4]->setCurrentPlace(field->getPlaceAtPosition(Point2i(3,4)));
    swarmEntities[5]->setCurrentPlace(field->getPlaceAtPosition(Point2i(5,4)));
    swarmEntities[6]->setCurrentPlace(field->getPlaceAtPosition(Point2i(7,3)));
    swarmEntities[7]->setCurrentPlace(field->getPlaceAtPosition(Point2i(10,4)));

    swarmEntities[8]->setCurrentPlace(field->getPlaceAtPosition(Point2i(13,5)));
    swarmEntities[9]->setCurrentPlace(field->getPlaceAtPosition(Point2i(1,4)));
    swarmEntities[10]->setCurrentPlace(field->getPlaceAtPosition(Point2i(2,8)));
    swarmEntities[11]->setCurrentPlace(field->getPlaceAtPosition(Point2i(25,7)));

/*
    GRGEntity* grgEntities[12];

    for(int i=0; i<12; i++){
        grgEntities[i] = new GRGEntity();
        grgEntities[i]->setTargetEntity(playerEntity);
        entities.insert(grgEntities[i]);

        grgEntities[i]->setBrush(QBrush(QColor(40,30*i,34)));
    }

    grgEntities[0]->setCurrentPlace(field->getPlaceAtPosition(Point2i(3,2)));

    grgEntities[1]->setCurrentPlace(field->getPlaceAtPosition(Point2i(4,2)));
    grgEntities[2]->setCurrentPlace(field->getPlaceAtPosition(Point2i(2,3)));
    grgEntities[3]->setCurrentPlace(field->getPlaceAtPosition(Point2i(4,4)));
    grgEntities[4]->setCurrentPlace(field->getPlaceAtPosition(Point2i(3,4)));
    grgEntities[5]->setCurrentPlace(field->getPlaceAtPosition(Point2i(5,4)));
    grgEntities[6]->setCurrentPlace(field->getPlaceAtPosition(Point2i(7,3)));
    grgEntities[7]->setCurrentPlace(field->getPlaceAtPosition(Point2i(10,4)));

    grgEntities[8]->setCurrentPlace(field->getPlaceAtPosition(Point2i(13,5)));
    grgEntities[9]->setCurrentPlace(field->getPlaceAtPosition(Point2i(1,4)));
    grgEntities[10]->setCurrentPlace(field->getPlaceAtPosition(Point2i(2,8)));
    grgEntities[11]->setCurrentPlace(field->getPlaceAtPosition(Point2i(25,7)));
    */

    this->runMode = runModePaused;
}

void Scene::startMeasure()
{
    this->stepCount = 0;
}

void Scene::setRunMode(SceneRunMode runMode)
{
    this->runMode = runMode;
}

 SceneRunMode Scene::getRunMode()
 {
     return this->runMode;
 }

 set<Entity*> Scene::getEntities()
 {
     return this->entities;
 }

 void Scene::setTargetEntity(TargetEntity* targetEntity, Point2i pos)
 {
     if(targetEntity == NULL)
     {
         return;
     }

     if(this->targetEntity != NULL)
     {
        delete this->targetEntity;
     }

     this->targetEntity = targetEntity;
     this->targetEntity->setCurrentPlace(field->getPlaceAtPosition(pos));

#ifdef QT_UI
     if(this->targetEntity != NULL)
     {
         targetEntity->setPainter(painter);
     }
#endif

 }

 TargetEntity* Scene::getTargetEntity()
 {
     return this->targetEntity;
 }

 void Scene::addField(unsigned fieldWidth, unsigned fieldHeight, unsigned xOffset, unsigned yOffset)
 {
     set<Entity*>::iterator it;

     for ( it=entities.begin() ; it != entities.end(); it++ )
     {
         delete ((Entity*)*it);
     }
     entities.clear();

     if(this->field != NULL)
     {
        delete this->field;
     }
     this->field = new Field(fieldWidth,fieldHeight,20.0,xOffset,yOffset);

#ifdef QT_UI
     if(field != NULL)
     {
         field->setPainter(painter);
     }
#endif

 }

#ifdef QT_UI

void Scene::setPainter(QPainter *painter){
    this->painter = painter;

    if(field != NULL)
    {
        field->setPainter(painter);
    }

    set<Entity*>::iterator it;

    for ( it=entities.begin() ; it != entities.end(); it++ )
    {
        ((Entity*)*it)->setPainter(painter);
    }

    if(this->targetEntity != NULL)
    {
        this->targetEntity->setPainter(painter);
    }
}

#endif

Scene::~Scene()
{
    delete field;
    set<Entity*>::iterator it;

    delete targetEntity;

    for ( it=entities.begin() ; it != entities.end(); it++ )
    {
        delete ((Entity*)*it);
    }
}

Field *Scene::getField()
{
    return this->field;
}

Point2i Scene::getOffset()
{
    return this->field->getOffset();
}

void Scene::setOffset(Point2i offset)
{
    this->field->setOffset(offset);
}

void Scene::handleTouchEvent(Point2i touchPoint)
{

}

void Scene::addEntityAtPosition(int type, Point2i point)
{
    Place* place = this->field->getPlaceAtPosition(point);

    if(place->getEntity() != NULL)
        return;

    Entity* newEntity = NULL;

    switch(type)
    {
    case SWARM_ENTITY:
        newEntity = new SwarmEntity();
        ((SwarmEntity*)newEntity)->setTargetEntity(targetEntity);
#ifdef QT_UI
        newEntity->setBrush(QBrush(QColor(255,70,34)));
#endif
        break;
    case GRG_ENTITY:
        newEntity = new GRGEntity();
        ((GRGEntity*)newEntity)->setTargetEntity(targetEntity);
#ifdef QT_UI
        newEntity->setBrush(QBrush(QColor(255,70,34)));
#endif
        break;
    case TARGET_ENTITY:
        newEntity = new TargetEntity();
#ifdef QT_UI
        newEntity->setBrush(QBrush(QColor(255,70,34)));
#endif
        break;
    }

    if(newEntity != NULL)
    {
        this->entities.insert(newEntity);
        newEntity->setCurrentPlace(place);
    }
}

void Scene::addSwarmEntityAtPosition(Point2i point)
{

    Place* place = this->field->getPlaceForTouchPoint(point);

    if(place->getEntity() != NULL)
        return;

    SwarmEntity* swarmEntity = new SwarmEntity();
    swarmEntity->setTargetEntity(targetEntity);
    this->entities.insert(swarmEntity);

    swarmEntity->setBrush(QBrush(QColor(40,70,34)));

    swarmEntity->setCurrentPlace(place);

}

void Scene::Step()
{
    if(this->field == NULL)
        return;

    set<Entity*>::iterator it;

    bool isAnimating = false;

    for ( it=entities.begin() ; it != entities.end(); it++ )
    {
        Entity* p = (Entity*)*it;
        if(p->getAnimating())
            isAnimating = true;
    }
    if(isAnimating || (this->runMode != runModeContinous && this->runMode != runModeStepping))
        return;

    //check stop condition
    unsigned *trajectoryFillCount = new unsigned[entities.size()];

    for(unsigned i=0; i<entities.size(); i++)
        trajectoryFillCount[i] = 0;

    for ( it=entities.begin() ; it != entities.end(); it++ )
    {
        Entity* p = (Entity*)*it;
        Place* entityPlace = p->getCurrentPlace();
        Place* targetPlace = this->targetEntity->getCurrentPlace();

        neighborhoodType nType = same;
        unsigned distance = -1;

        Place::entityDistance(entityPlace,targetPlace,distance,nType);

        if(distance < 1)
        {
            cout<<"Error"<<endl;
        }

        trajectoryFillCount[distance-1]++;
    }

    for(unsigned i=0; i<entities.size(); i++)
    {
        cout<<trajectoryFillCount[i]<<" ";
    }
    cout<<endl;

    for(unsigned i=0; i<entities.size(); i++)
    {
        if(trajectoryFillCount[i] < i*6+6)
        {
            int outerEntities = 0;
            for(int j=i+1; j<entities.size(); j++)
            {
                outerEntities += trajectoryFillCount[j];
            }
            if(outerEntities == 0)
            {
                //caclucalte statistics

                cout<<"Step Circle Count: "<<stepCount<<endl;

                unsigned overallStepCount;

                cout<<"Entitiy step count: ";
                for ( it=entities.begin() ; it != entities.end(); it++ )
                {
                    unsigned entityStepCount = ((Entity*)*it)->getStepCount();
                    overallStepCount += entityStepCount;
                    cout<<entityStepCount<<" ";
                }
                cout<<endl;

                cout<<"Overall step count: "<<overallStepCount<<endl;

                cout<<"Average step count: "<<overallStepCount/entities.size()<<endl;

                return;
            }
            else
            {
                break;
            }

        }

    }

    //increase step count
    this->stepCount++;

    delete trajectoryFillCount;

    //Move the others

    this->field->cleanNextEntities();

    for ( it=entities.begin() ; it != entities.end(); it++ )
    {
        ((Entity*)*it)->Step();
    }

    for ( it=entities.begin() ; it != entities.end(); it++ )
    {
        Place* desiredPlace = ((Entity*)*it)->getDesiredPlace();
        desiredPlace->setNextEntity(((Entity*)*it));
    }

    for ( it=entities.begin() ; it != entities.end(); it++ )
    {
        ((Entity*)*it)->AfterStep();
    }

    for ( it=entities.begin() ; it != entities.end(); it++ )
    {
        Place* desiredPlace = ((Entity*)*it)->getDesiredPlace();
        desiredPlace->setNextEntity(((Entity*)*it));

        //Probe
        Place* currentPlace = ((Entity*)*it)->getCurrentPlace();
        if(currentPlace != desiredPlace)
            ((Entity*)*it)->increaseStepCount();

        ((Entity*)*it)->setCurrentPlace(desiredPlace,true);
        desiredPlace->setNextEntity(NULL);
    }

    if(this->runMode == runModeStepping)
        this->runMode = runModePaused;
}

void Scene::Draw(float dTime)
{
    if(field != NULL)
    {
        field->Draw(dTime);
    }
}
