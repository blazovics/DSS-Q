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
    QPushButton* startButton;
    QPushButton* stopButton;
    QPushButton* saveButton;
    QPushButton* loadButton;

public:
    explicit ToolBarWidget(QWidget *parent = 0);

    QPushButton* getPlayButton();
    QPushButton* getPauseButton();
    QPushButton* getStepButton();
    QPushButton* getStartButton();
    QPushButton* getStopButton();
    QPushButton* getSaveButton();
    QPushButton* getLoadButton();
    
signals:
    
public slots:

    void playPressed();
    void pausePressed();
    void stepPressed();
    void startPressed();
    void stopPressed();
    void savePressed();
    void loadPressed();
    
};

#endif // TOOLBARWIDGET_H
