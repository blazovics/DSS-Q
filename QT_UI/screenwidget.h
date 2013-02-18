#ifndef SCREENWIDGET_H
#define SCREENWIDGET_H

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <QPainter>

#include <QPushButton>

class Scene;

class ScreenWidget : public QWidget
{

private:
    Q_OBJECT
    QPen pen;
    QBrush brush;
    QPixmap pixmap;

    QPushButton* playButton;
    QPushButton* pauseButton;
    QPushButton* stepButton;
    QPushButton* stopButton;

    Scene* scene;

protected:
    void mouseReleaseEvent ( QMouseEvent * e );

public:
    explicit ScreenWidget(QWidget *parent = 0);
    void setScene(Scene* scene);
    
signals:
    
public slots:
    void updateCaption();

    void playPressed();
    void pausePressed();
    void stepPressed();
    void stopPressed();
    void savePressed();
    void loadPressed();
    
private:
    void paintEvent(QPaintEvent *event);
};

#endif // SCREENWIDGET_H
