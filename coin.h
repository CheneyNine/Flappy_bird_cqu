#ifndef COIN_H
#define COIN_H

#include <QObject>
#include <QPoint>
#include <QTimer>
#include <QPixmap>
#include <bird.h>
#include <pipe.h>

class coin : public QObject
{
    Q_OBJECT
public:
    explicit coin(QObject *parent = nullptr);


    void set_speed(pipe &pipe){speed=pipe.speed;}
    void init();

private:
    int speed;

    QTimer timer_move;
    QPoint position[3], *last;




};

#endif // COIN_H
