#ifndef SCENE_H
#define SCENE_H

#include "common.h"
#include <set>

using namespace std;

class Field;
class Entity;
class PlayerEntity;

typedef enum
{
    gameStateUnitAdd,
    gameStateUnitSelect,
    gameStateUnitDestination
}SceneState;

typedef enum
{
    runModeContinous,
    runModeStepping,
    runModePaused
}SceneRunMode;

class Scene
{
    Field* field;
    set<Entity*> entities;
    Entity* playerEntity;
    
    SceneState sceneState;
    Entity* selectedEntity;

    SceneRunMode runMode;

#ifdef QT_UI
    QPainter* painter;
public:
    void setPainter(QPainter *painter);
#endif

public:
    Scene(unsigned fieldWidth, unsigned fieldHeight, unsigned xOffset = 0, unsigned yOffset = 0);
    void addSwarmEntityAtPosition(Point2i point);
    void handleTouchEvent(Point2i touchPoint);

    Field* getField();

    Point2i getOffset();
    void setOffset(Point2i offset);
    
    ~Scene();
    void Step();
    void Draw(float dTime = 0);

    SceneRunMode getRunMode();
    void setRunMode(SceneRunMode runMode);

    void Reset();
};

#endif // SCENE_H
