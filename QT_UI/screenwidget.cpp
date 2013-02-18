#include "screenwidget.h"
#include "../scene.h"
#include "../field.h"
#include "../entity.h"
#include "../place.h"
#include "../targetEntity.h"
#include <QTimer>
#include <QPushButton>
#include <QDebug>
#include <QMouseEvent>

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QTranslator>
#include <QObject>

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

void ScreenWidget::savePressed()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Scene"), "",tr("DSS XML Scene File (*.xml);;All Files (*)"));

    if (fileName.isEmpty())
    {
        return;
    }
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::information(this, tr("Unable to open file"), file.errorString());
            return;
        }

        QTextStream out(&file);

        Field* currentField = this->scene->getField();
        out<<"<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>"<<"\n";
        out<<"<scene>"<<"\n";
        out<<"\t"<<"<field>"<<"\n";
        out<<"\t"<<"\t"<<"<width>"<<currentField->getWidth()<<"</width>"<<"\n";
        out<<"\t"<<"\t"<<"<height>"<<currentField->getHeight()<<"</height>"<<"\n";
        out<<"\t"<<"</field>"<<"\n";

        TargetEntity* currentTarget = this->scene->getTargetEntity();

        out<<"\t"<<"<targetEntity>"<<"\n";

            Point2i pos = currentTarget->getCurrentPlace()->getPosition();

        out<<"\t"<<"\t"<<"<x>"<<pos.x<<"</x>"<<"\n";
        out<<"\t"<<"\t"<<"<y>"<<pos.y<<"</y>"<<"\n";

        out<<"\t"<<"</targetEntity>"<<"\n";

        set<Entity*> currentEntities = this->scene->getEntities();

        set<Entity*>::iterator it;

        out<<"\t"<<"<entities>"<<"\n";
        for ( it=currentEntities.begin() ; it != currentEntities.end(); it++ )
        {
            out<<"\t"<<"\t"<<"<entity>"<<"\n";
            out<<"\t"<<"\t"<<"\t"<<"<type>"<<((Entity*)*it)->getType()<<"</type>"<<"\n";

            Point2i pos = ((Entity*)*it)->getCurrentPlace()->getPosition();

            out<<"\t"<<"\t"<<"\t"<<"<x>"<<pos.x<<"</x>"<<"\n";
            out<<"\t"<<"\t"<<"\t"<<"<y>"<<pos.y<<"</y>"<<"\n";

            out<<"\t"<<"\t"<<"</entity>"<<"\n";

        }
        out<<"\t"<<"</entities>"<<"\n";
        out<<"</scene>";
    }
}

void ScreenWidget::loadPressed()
{

}

void ScreenWidget::setScene(Scene *scene){
    this->scene = scene;
    Field* sceneField = scene->getField();

    unsigned width = 800;
    unsigned height = 600;

    if(sceneField != NULL)
    {
        width = sceneField->getWidth()*sqrt(3)*sceneField->getUnit()+20;
        height = sceneField->getHeight()*1.5*sceneField->getUnit();
    }

    this->setGeometry(0,0,width,height);
}

void ScreenWidget::paintEvent(QPaintEvent * /* event */)
 {
     QPainter painter(this);

     painter.setPen(QPen(QColor(100,100,100)));
     painter.setBrush(brush);

     painter.setRenderHint(QPainter::Antialiasing, true);

     scene->setPainter(&painter);
     scene->Step();
     scene->Draw();
}

void ScreenWidget::updateCaption(){
    this->repaint();
}
