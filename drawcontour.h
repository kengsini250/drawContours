#ifndef DRAWCONTOUR_H
#define DRAWCONTOUR_H

#include <QWidget>
#include "label.h"
#include <QFileDialog>
#include <QString>

#include "opencv2/opencv.hpp"


QT_BEGIN_NAMESPACE
namespace Ui { class DrawContour; }
QT_END_NAMESPACE

class DrawContour : public QWidget
{
    Q_OBJECT

public:
    DrawContour(QWidget *parent = nullptr);
    ~DrawContour();

private:
    Ui::DrawContour *ui;
    Label *label;
    QString file;
};
#endif // DRAWCONTOUR_H
