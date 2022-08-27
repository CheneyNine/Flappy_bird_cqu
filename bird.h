#ifndef BIRD_H
#define BIRD_H

#include <QObject>
#include <QPoint>
#include <QTimer>
#include <QPixmap>

class Bird:public QObject
{

public:
    explicit Bird(QObject *parent = nullptr);
    void init();
    void appear(QPainter& painter);
    void appear_all(QPainter& painter);
    void appear_score(QPainter& painter);
    void appear_score_table(QPainter& painter);
    void move(int x,int y);

    void hit();
    void hit_land();
    void score_add();
    void start();
    void get_defence();
    void fly_quicker();
    void fly_slower();
    void defence_change();
    void defence_start();
    void defence_appear(QPainter& painter);
    QPoint getposition()const {return position;}
    QPoint position;
    int skin_choose;
    int defend_time=0;
    int defended_time=0;
    int jump_height;
    bool fail;
    bool light;
    bool huanchong;
    int score;
    int bestscore;
    void light_appear(QPainter& painter);
    void huanchong_appear(QPainter& painter);

public slots:
    void fly();
    void drop();
    void jump();



private:

    int bird_h=60,bird_w=60;
    int bird_jumpheight=50;
    QPixmap skin[5][3];
    QPixmap *skin_current;
    QPixmap skin_choose_effect[5];
    QPixmap *skin_choose_effect_current;
    QPixmap skin_choose_info[5];
    QPixmap *skin_choose_info_current;
    QPixmap skin_defence[9];
    QPixmap *skin_defence_current;
    QPixmap skin_score[10][10];
    QPixmap skin_score_shi;
    QPixmap *skin_score_current;
    QPixmap skin_bestscore_shi,skin_bestscore_ge;
    QPixmap skin_socre_table;
    QPixmap skin_light[5];
    QPixmap *skin_light_current;
    QPixmap skin_huanchong[5];
    QPixmap *skin_huanchong_current;
    double bird_angle;
    double bird_angle_speed;
    double bird_angle_speed_a;
    int dropSpeed, gravity,fly_speed;
    QTimer timer_light,timer_huanchong;
    bool draw,draw1;
    QTimer timer_fly,timer_drop,timer_defence_effect_change;
};

#endif // BIRD_H
