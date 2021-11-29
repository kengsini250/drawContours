#include "drawcontour.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DrawContour w;
    w.show();
    return a.exec();
}
