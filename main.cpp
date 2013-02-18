#include "common.h"

#include "scene.h"

//#include <QtGui/QApplication>
#include <QApplication>
#include <QMainWindow>
#include "qmlapplicationviewer.h"
#include "QT_UI/screenwidget.h"
#include "QT_UI/toolbarwidget.h"

#include <QHBoxLayout>
#include <QGridLayout>
#include <QtGui>
#include <QObject>

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow *window = new QMainWindow();

    //Scene scene(25,15,10,10);
    Scene scene;

    ScreenWidget screenWidget;
    screenWidget.setScene(&scene);

    QWidget *centralWidget = new QWidget(window);
    QGridLayout *gridlayout = new QGridLayout();

    centralWidget->setLayout(gridlayout);

    ToolBarWidget toolbarWidget;

    toolbarWidget.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    QObject::connect(toolbarWidget.getPlayButton(), SIGNAL(released()), &screenWidget, SLOT(playPressed()));
    QObject::connect(toolbarWidget.getPauseButton(), SIGNAL(released()), &screenWidget, SLOT(pausePressed()));
    QObject::connect(toolbarWidget.getStepButton(), SIGNAL(released()), &screenWidget, SLOT(stepPressed()));
    QObject::connect(toolbarWidget.getStopButton(), SIGNAL(released()), &screenWidget, SLOT(stopPressed()));

    QObject::connect(toolbarWidget.getSaveButton(), SIGNAL(released()), &screenWidget, SLOT(savePressed()));
    QObject::connect(toolbarWidget.getLoadButton(), SIGNAL(released()), &screenWidget, SLOT(loadPressed()));

    gridlayout->addWidget(&toolbarWidget,0,1);

    QScrollArea *const scroll(new QScrollArea);
    scroll->setWidget(&screenWidget);

    gridlayout->addWidget(scroll,1,1);

    window->setCentralWidget(centralWidget);

    window->show();

    //sreenWidget.show();

    return app.exec();
}
