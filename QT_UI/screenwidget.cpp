#include "screenwidget.h"
#include "../scene.h"
#include "../field.h"
#include "../entity.h"
#include "../place.h"
#include "../targetentity.h"
#include "../grgentity.h"
#include "../swarmentity.h"
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
#include <QtXml/QDomDocument>
#include <QtXml/QtXml>

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
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load Scene"), "",tr("DSS XML Scene File (*.xml);;All Files (*)"));

    if (fileName.isEmpty())
    {
        return;
    }
    else
    {
        QDomDocument doc("loadedscene");
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return;
        }

        if (!doc.setContent(&file))
        {
            file.close();
            return;
        }
        file.close();

        QDomElement scene = doc.documentElement();

        qDebug()<<scene.text();

        QDomNode field=scene.firstChildElement("field");
        if (field.isElement())
        {
            this->scene->addField(field.firstChildElement("width").text().toUInt(),field.firstChildElement("height").text().toUInt());
        }
        QDomNode targetEntity = scene.firstChildElement("targetEntity");
        if (targetEntity.isElement())
        {

            TargetEntity* newTargetEntity = new TargetEntity();
            Point2i targetPos(targetEntity.firstChildElement("x").text().toInt(),targetEntity.firstChildElement("y").text().toInt());
            this->scene->setTargetEntity(newTargetEntity,targetPos);
        }
        QDomNode entities = scene.firstChildElement("entities");
        if (entities.isElement())
        {
            QDomNodeList entityList =entities.toElement().elementsByTagName("entity");

            for(int i=0;i<entityList.count();i++)
            {
                QDomElement entity = entityList.at(i).toElement();

                int type = entity.firstChildElement("type").text().toInt();
                Point2i entityPos(entity.firstChildElement("x").text().toInt(),entity.firstChildElement("y").text().toInt());

                this->scene->addEntityAtPosition(type,entityPos);
            }
        }
/*
            for(int i=0;i<fieldList.count();i++)
            {
                QDomElement field = fieldList.at(i).toElement();

                qDebug()<<field.attribute("width");
                qDebug()<<field.attribute("height");


                QDomNodeList lll=e1.elementsByTagName("a");
                qDebug(QString::number(lll.count()).toAscii());

                for(int j=0;j<lll.count();j++)
                {
                    QDomElement e2 = lll.at(j).toElement();
                    qDebug(e2.tagName().toAscii()+" "+e2.attribute("ITEM").toAscii());
                    QDomNodeList llll=e2.elementsByTagName("b");
                    for(int k=0;k<llll.count();k++)
                    {
                        QDomElement e3 = llll.at(k).toElement();
                        qDebug(e3.tagName().toAscii()+" "+e3.text().toAscii());
                    }
                }

            }
            */
    }
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
