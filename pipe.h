#ifndef PIPE_H
#define PIPE_H

#include <QObject>
#include <QPoint>
#include <QTimer>
#include <QPixmap>
#include <bird.h>

class pipe : public QObject
{
    Q_OBJECT
public:
    explicit pipe(QObject *parent = nullptr);
    void init();
    void run();
    void stop();
    void appear(QPainter& painter);
    void appear_coin(QPainter& painter);
    void get_check(Bird &bird);
    void clear_screen();
    void shanxian();
    void Hit_check(Bird &bird);
    void auto_fly();
    void change_speed_faster();
    void change_speed_slower();
    bool bonustime;
    QTimer timer_auto_test;
    int speed=10;
    void move_y();



signals:
    void gameover();
    void jump();

//public slots:
private:
    const int pipe_w=80,pipe_h=700,pipe_x_space=200;
    QPixmap pipe_up, pipe_down;
    QTimer timer_move;
    QTimer timer_stop_check;
    QTimer timer_add_speed;
    QTimer timer_y_move;
    QPoint position[3], *last;
    bool passpipe;
    bool ischecking;
    QPixmap skin_coin1,skin_coin2;
    int getRandom(int min, int max);
    int bird_x,bird_y;
    int coin_x,coin_y;
    bool coinget[3];
    bool hascoin[3];
    int y_distance;
    int y_chazhi;
    int y_chazhi2;

};

#endif // PIPE_H

