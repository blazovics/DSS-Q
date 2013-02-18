#include "renderobject.h"

RenderObject::RenderObject()
{

}

Point2f RenderObject::getOnScreenPos()
{
    return this->onScreenPos;
}

void RenderObject::setOnScreenPos(Point2f newPos)
{
    this->onScreenPos = newPos;
}

#ifdef QT_UI

void RenderObject::setPainter(QPainter *painter)
{
    this->painter = painter;
}

void RenderObject::setBrush(const QBrush &brush)
{
    this->brush = brush;
}

#endif

void RenderObject::Draw(float dTime)
{

}


