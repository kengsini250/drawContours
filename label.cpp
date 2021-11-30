#include "label.h"

Label::Label(QWidget *p):QLabel(p)
{}

void Label::clear()
{
    points.clear();
    contours.clear();
    count = 0;
}

void Label::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        isLeftPressed = true;
        curr.setX(e->pos().x()/ZoomValue-oldpos.x()/ZoomValue);
        curr.setY(e->pos().y()/ZoomValue-oldpos.y()/ZoomValue);
        temp.setX(e->pos().x()/ZoomValue-oldpos.x()/ZoomValue);
        temp.setY(e->pos().y()/ZoomValue-oldpos.y()/ZoomValue);
    }
    if(e->button() == Qt::RightButton)
    {
        isRightPressed = true;
        temppos = e->pos();
    }
}

void Label::mouseMoveEvent(QMouseEvent *e)
{
    if(isLeftPressed)
    {
        temp.setX(e->pos().x()/ZoomValue-oldpos.x()/ZoomValue);
        temp.setY(e->pos().y()/ZoomValue-oldpos.y()/ZoomValue);
        points.push_back(temp);
    }
    if(isRightPressed)
    {
        newpos = e->pos();
        int dx = newpos.x()-temppos.x();
        int dy = newpos.y()-temppos.y();
        oldpos.setX(oldpos.x()+dx);
        oldpos.setY(oldpos.y()+dy);
        temppos = newpos;
    }
}

void Label::mouseReleaseEvent(QMouseEvent *e)
{
    if (isLeftPressed) { 
        isLeftPressed = false; 
        if (!points.isEmpty()) {
            contours.insert(count++, points);
            points.clear();
        }
    }
    if(isRightPressed)
    {
        isRightPressed = false;
        if(e->pos() == temppos)
        {
        }
        else
        {
            int dx = newpos.x() - temppos.x();
            int dy = newpos.y() - temppos.y();
            oldpos.setX(oldpos.x() + dx);
            oldpos.setY(oldpos.y() + dy);
            temppos = newpos;

            for (int i = 0; i < points.size(); i++) {
                points[i].setX(points[i].x() + dx);
                points[i].setY(points[i].y() + dy);
            }
        }
    }
}

void Label::wheelEvent(QWheelEvent* event)
{
    float d = 0.05f;
    float min = 0.2f;

    QPoint value = event->angleDelta();

    if (value.y() > 0)  //放大
    {
        ZoomValue += d;
    }
    else            //缩小
    {
        ZoomValue -= d;

        if (ZoomValue <= min)
        {
            ZoomValue = min;
        }
    }
}

void Label::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    QPen pen;
    pen.setWidth(3);
    pen.setColor(QColor(255,0,0));
    pen.setStyle(Qt::SolidLine);
    p.setPen(pen);

    p.scale(ZoomValue,ZoomValue);
    p.drawPixmap(oldpos.x()/ZoomValue,oldpos.y()/ZoomValue, img.width(), img.height(), QPixmap::fromImage(img));

    if(isLeftPressed){
        for (int i = 0; i < points.size(); i++) {
            p.drawPoint(points[i].x() + oldpos.x() / ZoomValue, points[i].y() + oldpos.y() / ZoomValue);
        }
    }

    for(int j=0;j<contours.size();j++){
        auto ccc = contours[j];
        for (int i = 0; i < ccc.size(); i++) {
            p.drawPoint(ccc[i].x() + oldpos.x() / ZoomValue, ccc[i].y() + oldpos.y() / ZoomValue);
        }
    }

    update();
}
