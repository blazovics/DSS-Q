#include "common.h"

#include "scene.h"

#ifdef QT_UI

#include <QtGui/QApplication>
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

    Scene scene(25,15,10,10);

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

    gridlayout->addWidget(&toolbarWidget,0,1);

    QScrollArea *const scroll(new QScrollArea);
    scroll->setWidget(&screenWidget);

    gridlayout->addWidget(scroll,1,1);

    window->setCentralWidget(centralWidget);

    window->show();

    //sreenWidget.show();

    return app.exec();
}

#endif

#ifdef MARMALADE_UI

#include "s3e.h"
#include "Iw2D.h"
#include "IwResManager.h"

#include "Mar_input.h"

// Main entry point for the application
int main()
{
    // Initialise Marmalade 2D graphics system
    Iw2DInit();
    
	// Initialise the resource manager
	IwResManagerInit();
    
    IwGetResManager()->LoadGroup("Level1.group");
    
	// initialise the input system
	g_Input.Init();
    
	// Initialise the game object
    Scene scene(29,15);
    
    CTouch previousTouch;
    Point2i localOffset;
    previousTouch.id = -1;
    
    uint64 LastFrameTime = 0;
    float interval = 0;
    
	// Main Loop
	while (!s3eDeviceCheckQuitRequest())	// Exit main loop if device quit request received
	{
        
		// Update input system
		g_Input.Update();
        
        if(g_Input.getTouchCount() > 0)
        {
            
            CTouch* currentTouch = g_Input.getTouch(0);
            
            if(previousTouch.id != -1)
            {
                if(previousTouch.id == currentTouch->id)
                {
                    Point2i offset = scene.getOffset();
                    
                    offset.x +=  previousTouch.x - currentTouch->x;
                    offset.y +=  previousTouch.y - currentTouch->y;
                    
                    localOffset.x += previousTouch.x - currentTouch->x;
                    localOffset.y += previousTouch.y - currentTouch->y;
                    
                    std::cout<<"x: "<<offset.x<<"y: "<<offset.y<<std::endl;
                    
                    scene.setOffset(offset);
                }
            }
            
            previousTouch = *currentTouch;
            
            //
        }
        else
        {
            if(previousTouch.id != -1)
            {
                if(localOffset.x<2 && localOffset.y<2)
                {
                  scene.handleTouchEvent(Point2i(previousTouch.x, previousTouch.y));
                }
                localOffset.x = 0;
                localOffset.y = 0;
                previousTouch.id = -1;
            }
        }
        
		// If back button is pressed then exit the main loop
		
        //if (g_Input.isKeyDown(s3eKeyAbsBSK))
		//	break;
        
        float dt = (float)(s3eTimerGetMs() - LastFrameTime) / 16.67f;
        interval += dt;
        if (dt < 1.0)
            dt = 1.0f;
        if (dt > 6.0f)
            dt = 6.0f;
        LastFrameTime = s3eTimerGetMs();
        
        if(interval > 30.0){
            interval = 0;
            // Update the game
            scene.Step();
        }
        
		// Draw the game
		scene.Draw(dt);
        
		// Yield to the operating system
		s3eDeviceYield(0);
	}
    
	// Shut down the input system
	
    //g_Input.Release();
    
	// Shut down the resource manager
	IwResManagerTerminate();
    
	// Shut down Marmalade 2D graphics system
	Iw2DTerminate();
    
    return 0;
}

#endif
