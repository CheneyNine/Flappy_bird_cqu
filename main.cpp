#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qputenv("QT_SCALE_FACTOR", "1.8");
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
