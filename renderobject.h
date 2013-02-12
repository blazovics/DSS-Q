#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include "common.h"

#ifdef MARMALADE_UI

#include "s3e.h"
#include "Iw2D.h"

#endif

class RenderObject
{
public:
    RenderObject();
protected:
    Point2f onScreenPos;

public:
    Point2f getOnScreenPos();
    void setOnScreenPos(Point2f newPos);
    virtual void Draw(float dTime);

#ifdef QT_UI
protected:
    QBrush brush;
    QPainter *painter;
public:
    void setPainter(QPainter *painter);
    void setBrush(const QBrush &brush);
#endif

};

#endif // RENDEROBJECT_H
