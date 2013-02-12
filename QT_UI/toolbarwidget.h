#ifndef TOOLBARWIDGET_H
#define TOOLBARWIDGET_H

#include <QWidget>
#include <QPushButton>

class ToolBarWidget : public QWidget
{
    Q_OBJECT

    QPushButton* playButton;
    QPushButton* pauseButton;
    QPushButton* stepButton;
    QPushButton* stopButton;

public:
    explicit ToolBarWidget(QWidget *parent = 0);

    QPushButton* getPlayButton();
    QPushButton* getPauseButton();
    QPushButton* getStepButton();
    QPushButton* getStopButton();
    
signals:
    
public slots:

    void playPressed();
    void pausePressed();
    void stepPressed();
    void stopPressed();
    
};

#endif // TOOLBARWIDGET_H
