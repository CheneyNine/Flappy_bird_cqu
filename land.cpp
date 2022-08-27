#include "land.h"
#include <QPainter>
land::land(QObject *parent) : QObject(parent)
{
    skin.load(":/image/ground.png");
    position[0] = 0;
    position[1] = 500;
    connect(&timer_move, &QTimer::timeout, [=]()
    {
        position[0]--;
        if(position[0]<=-500){
            position[0] = 500;
        }
        position[1]--;
        if(position[1]<=-500){
            position[1] = 500;
        }
    });
    run();
}

void land::appear(QPainter &painter)
{
    for(int i = 0;i<2;i++)
    {
        painter.drawPixmap(position[i], 600, 500, 100, skin);
    }
}

void land::run()
{
    timer_move.start(10);
}

void land::stop()
{
    timer_move.stop();
}
