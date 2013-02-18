#include "toolbarwidget.h"
#include <QHBoxLayout>

ToolBarWidget::ToolBarWidget(QWidget *parent) :
    QWidget(parent)
{
    this->playButton = new QPushButton("&Play", this);

    this->pauseButton = new QPushButton("&Pause", this);

    this->stepButton = new QPushButton("&Step", this);

    this->stopButton = new QPushButton("&Stop", this);

    this->saveButton = new QPushButton("&Save", this);

    this->loadButton = new QPushButton("&Load", this);

    QHBoxLayout *hbox = new QHBoxLayout(this);

    hbox->addWidget(this->playButton);
    hbox->addWidget(this->pauseButton);
    hbox->addWidget(this->stepButton);
    hbox->addWidget(this->stopButton);
    hbox->addWidget(this->saveButton);
    hbox->addWidget(this->loadButton);

    QObject::connect(this->playButton, SIGNAL(released()), this, SLOT(playPressed()));
    QObject::connect(this->pauseButton, SIGNAL(released()), this, SLOT(pausePressed()));
    QObject::connect(this->stepButton, SIGNAL(released()), this, SLOT(stepPressed()));
    QObject::connect(this->stopButton, SIGNAL(released()), this, SLOT(stopPressed()));
    QObject::connect(this->saveButton, SIGNAL(released()), this, SLOT(savePressed()));
    QObject::connect(this->loadButton, SIGNAL(released()), this, SLOT(loadPressed()));

    this->playButton->setEnabled(true);
    this->pauseButton->setEnabled(false);
    this->stopButton->setEnabled(false);
    this->stepButton->setEnabled(true);

    this->saveButton->setEnabled(true);
    this->loadButton->setEnabled(true);

    this->setLayout(hbox);
}

void ToolBarWidget::playPressed()
{
    this->playButton->setEnabled(false);
    this->pauseButton->setEnabled(true);
    this->stopButton->setEnabled(true);
    this->stepButton->setEnabled(false);

    this->saveButton->setEnabled(false);
    this->loadButton->setEnabled(false);
}

void ToolBarWidget::pausePressed()
{
    this->playButton->setEnabled(true);
    this->pauseButton->setEnabled(false);
    this->stopButton->setEnabled(true);
    this->stepButton->setEnabled(true);

    this->saveButton->setEnabled(true);
    this->loadButton->setEnabled(true);
}

void ToolBarWidget::stepPressed()
{
    this->playButton->setEnabled(true);
    this->pauseButton->setEnabled(false);
    this->stopButton->setEnabled(true);
    this->stepButton->setEnabled(true);

    this->saveButton->setEnabled(false);
    this->loadButton->setEnabled(false);
}

void ToolBarWidget::stopPressed()
{
    this->playButton->setEnabled(true);
    this->pauseButton->setEnabled(false);
    this->stopButton->setEnabled(false);
    this->stepButton->setEnabled(true);

    this->saveButton->setEnabled(false);
    this->loadButton->setEnabled(false);
}

void ToolBarWidget::savePressed()
{

}

void ToolBarWidget::loadPressed()
{

}

QPushButton* ToolBarWidget::getPlayButton()
{
    return this->playButton;
}

QPushButton* ToolBarWidget::getPauseButton()
{
    return this->pauseButton;
}

QPushButton* ToolBarWidget::getStepButton()
{
    return this->stepButton;
}

QPushButton* ToolBarWidget::getStopButton()
{
    return this->stopButton;
}

QPushButton* ToolBarWidget::getSaveButton()
{
    return this->saveButton;
}

QPushButton* ToolBarWidget::getLoadButton()
{
    return this->loadButton;
}

