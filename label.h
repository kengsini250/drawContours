#ifndef LABEL_H
#define LABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPoint>
#include <QMap>
#include <QList>
#include <QImage>
#include <QWheelEvent>

class Label : public QLabel
{
    Q_OBJECT
public:
    Label(QWidget *parent=nullptr);

    QMap<int, QList<QPoint>> contours;
    QImage img;

public slots:
    void clear();

private:
    bool isLeftPressed = false;
    bool isRightPressed = false;
    QPoint curr,temp;
    qreal ZoomValue = 1.0;  //鼠标缩放值
    qreal ZoomValueTemp = 1.0;

    QPoint oldpos,temppos,newpos;
    int px=0,py=0;

    int count = 0;
    QList<QPoint> points,points_temp;
protected:
    void mousePressEvent(QMouseEvent*e)override;
    void mouseMoveEvent(QMouseEvent*e)override;
    void mouseReleaseEvent(QMouseEvent*e)override;
    void wheelEvent(QWheelEvent* event) override;      
    void paintEvent(QPaintEvent*e)override;
};

#endif // LABEL_H
