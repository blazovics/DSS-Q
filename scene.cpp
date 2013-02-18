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

 TargetEntity* Scene::getTargetEntity()
 {
     return this->targetEntity;
 }

 void Scene::setField(unsigned fieldWidth, unsigned fieldHeight, unsigned xOffset, unsigned yOffset)
 {
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

    this->targetEntity->setPainter(painter);
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
    Place* place = this->field->getPlaceForTouchPoint(point);

    if(place->getEntity() != NULL)
        return;

    Entity* newEntity = NULL;

    switch(type)
    {
    case SWARM_ENTITY:
        newEntity = new SwarmEntity();
        ((SwarmEntity*)newEntity)->setTargetEntity(targetEntity);
        break;
    case GRG_ENTITY:
        newEntity = new GRGEntity();
        ((GRGEntity*)newEntity)->setTargetEntity(targetEntity);
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
