#include "background.h"
#include <QPainter>
background::background(QObject *parent) : QObject(parent)
{
    skin.load(":/image/bg.png");
    position[0] = 0;
    position[1] = 1048;
    connect(&timer_move, &QTimer::timeout, [=]()
    {
        position[0]--;
        if(position[0]<=-1048){
            position[0] = 1048;
        }
        position[1]--;
        if(position[1]<=-1048){
            position[1] = 1048;
        }
    });
    run();
}

void background::appear(QPainter &painter)
{
    for(int i = 0;i<2;i++)
    {
        painter.drawPixmap(position[i], 0, 1049, 700, skin);
    }
}

void background::run()
{
    timer_move.start(20);
}

void background::stop()
{
    timer_move.stop();
}
