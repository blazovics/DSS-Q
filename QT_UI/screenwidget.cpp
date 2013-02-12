#include "screenwidget.h"
#include "../scene.h"
#include "../field.h"
#include <QTimer>
#include <QPushButton>
#include <QDebug>
#include <QMouseEvent>


ScreenWidget::ScreenWidget(QWidget *parent) :
    QWidget(parent)
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateCaption()));
    timer->start(100);

}

void ScreenWidget::mouseReleaseEvent ( QMouseEvent * e )
{
    // check if cursor not moved since click beginning
    /*if ((m_mouseClick) && (e->pos() == m_lastPoint))
    {
        // do something: for example emit Click signal
        emit mouseClickEvent;
    }*/

    QPoint point = e->pos();
    qDebug()<<"x:"<<point.x()<<" y:"<<point.y();

    Point2i pos;
    pos.x = point.x()-10;
    pos.y = point.y()-15;

    if(this->scene->getRunMode()==runModePaused)
    {
        this->scene->addSwarmEntityAtPosition(pos);
    }
}

void ScreenWidget::playPressed()
{
    this->scene->setRunMode(runModeContinous);
}

void ScreenWidget::pausePressed()
{
    this->scene->setRunMode(runModePaused);
}

void ScreenWidget::stepPressed()
{
    this->scene->setRunMode(runModeStepping);
}

void ScreenWidget::stopPressed()
{
    this->scene->setRunMode(runModePaused);
}

void ScreenWidget::setScene(Scene *scene){
    this->scene = scene;

    Field* sceneField = scene->getField();

    unsigned width = sceneField->getWidth()*sqrt(3)*sceneField->getUnit()+20;
    unsigned height = sceneField->getHeight()*1.5*sceneField->getUnit();

    this->setGeometry(0,0,width,height);
}

void ScreenWidget::paintEvent(QPaintEvent * /* event */)
 {

    /*
     QRect rect(10, 20, 80, 60);

     QPainterPath path;
     path.moveTo(20, 80);
     path.lineTo(20, 30);
     path.cubicTo(80, 0, 50, 50, 80, 80);

     int startAngle = 20 * 16;
     int arcLength = 120 * 16;
*/
     QPainter painter(this);

     painter.setPen(QPen(QColor(100,100,100)));
     painter.setBrush(brush);

     painter.setRenderHint(QPainter::Antialiasing, true);

     scene->setPainter(&painter);
     scene->Step();
     scene->Draw();

     /*
     for (int x = 0; x < width(); x += 100) {
         for (int y = 0; y < height(); y += 100) {
             painter.save();
             painter.translate(x, y);

             painter.translate(50, 50);
             painter.rotate(60.0);
             painter.scale(0.6, 0.9);
             painter.translate(-50, -50);

             painter.drawPolygon(points, 4);
             painter.restore();
         }
     }*/

/*
     painter.setRenderHint(QPainter::Antialiasing, false);
     painter.setPen(palette().dark().color());
     painter.setBrush(Qt::NoBrush);
     painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
*/
}

void ScreenWidget::updateCaption(){
    this->repaint();
}
