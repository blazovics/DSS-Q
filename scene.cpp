#include "scene.h"
#include "field.h"
#include "entity.h"
#include "place.h"
#include "swarmentity.h"
#include "grgentity.h"
#include "playerentity.h"

#ifdef MARMALADE_UI

#include "Mar_entity.h"

#endif

Scene::Scene(unsigned fieldWidth, unsigned fieldHeight, unsigned xOffset, unsigned yOffset)
{
    srand ( time(NULL) );

    this->field = new Field(fieldWidth,fieldHeight,20.0,xOffset,yOffset);

    sceneState = gameStateUnitAdd;
    
    this->playerEntity = new Entity();
    this->playerEntity->setCurrentPlace(field->getPlaceAtPosition(Point2i(3,3)));
    //this->playerEntity->setTargetPlace(field->getPlaceAtPosition(Point2i(17,7)));
/*
    SwarmEntity* swarmEntities[12];

    for(int i=0; i<12; i++){
        swarmEntities[i] = new SwarmEntity();
        swarmEntities[i]->setTargetEntity(playerEntity);
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

*/
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

#ifdef QT_UI

void Scene::setPainter(QPainter *painter){
    this->painter = painter;

    field->setPainter(painter);

    set<Entity*>::iterator it;

    for ( it=entities.begin() ; it != entities.end(); it++ )
    {
        ((Entity*)*it)->setPainter(painter);
    }

    this->playerEntity->setPainter(painter);
}

#endif

Scene::~Scene()
{
    delete field;
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

void Scene::addSwarmEntityAtPosition(Point2i point)
{

    Place* place = this->field->getPlaceForTouchPoint(point);

    if(place->getEntity() != NULL)
        return;

    SwarmEntity* swarmEntity = new SwarmEntity();
    swarmEntity->setTargetEntity(playerEntity);
    this->entities.insert(swarmEntity);

    swarmEntity->setBrush(QBrush(QColor(40,70,34)));

    swarmEntity->setCurrentPlace(place);

}

void Scene::Step()
{


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

    /*
    for ( it=entities.begin() ; it != entities.end(); it++ )
    {
        Place* desiredPlace = ((Entity*)*it)->getDesiredPlace();
        desiredPlace->setNextEntity(((Entity*)*it));
    }

    for ( it=entities.begin() ; it != entities.end(); it++ )
    {
        ((Entity*)*it)->AfterStep();
    }*/

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
#ifdef MARMALADE_UI
    
    // Clear screen
	Iw2DSurfaceClear(0xff000000);
    
	// Draw the games sprite objects
	field->Draw(dTime);
    
	// Show surface
	Iw2DSurfaceShow();

#endif
       
    field->Draw(dTime);

}
