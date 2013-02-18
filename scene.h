#ifndef SCENE_H
#define SCENE_H

#include "common.h"
#include <set>

using namespace std;

class Field;
class Entity;
class TargetEntity;

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
    TargetEntity* targetEntity;

    Entity* selectedEntity;

    SceneRunMode runMode;

#ifdef QT_UI
    QPainter* painter;
public:
    void setPainter(QPainter *painter);
#endif

public:
    Scene();
    Scene(unsigned fieldWidth, unsigned fieldHeight, unsigned xOffset = 0, unsigned yOffset = 0);

    void setField(unsigned fieldWidth, unsigned fieldHeight, unsigned xOffset = 0, unsigned yOffset = 0);

    void addEntityAtPosition(int type, Point2i point);

    void addSwarmEntityAtPosition(Point2i point);

    void handleTouchEvent(Point2i touchPoint);

    set<Entity*> getEntities();
    TargetEntity* getTargetEntity();

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
