#include "bird.h"
#include <QPainter>
#include <QDebug>
#include <QSound>
Bird::Bird(QObject *parent) : QObject(parent)
{
    for(int i = 0;i < 5;i++)
    {
        for(int j = 0;j < 3;j++)
        {
            skin[i][j].load(QString(":/image/bird%1_%2.png").arg(i).arg(j));
        }
    }
    for(int i = 0;i < 5;i++)
    {
        skin_choose_effect[i].load(QString(":/image/bird%1_choose.png").arg(i));
    }
    for(int i = 0;i < 5;i++)
    {
        skin_choose_info[i].load(QString(":/image/info_%1.png").arg(i));
    }
    for(int i = 0;i < 9;i++)
    {
        skin_defence[i].load(QString(":/image/defence_%1.png").arg(i));
    }
    for(int i = 0;i < 10;i++)
    {
        for(int j = 0;j < 10;j++)
        {
            skin_score[i][j].load(QString(":/image/num%1.png").arg(j));
        }
    }
    for(int i = 0;i < 5;i++)
    {
        skin_light[i].load(QString(":/image/light%1.png").arg(i));
    }
    for(int i = 0;i < 5;i++)
    {
        skin_huanchong[i].load(QString(":/image/huanchong%1.png").arg(i));
    }
    skin_socre_table.load(QString(":/image/info_score.png"));
    skin_score_shi=skin_score[0][0];
    skin_score_current = &skin_score[0][0];
    skin_choose = 0;
    skin_current = &skin[0][0];
    skin_light_current=&skin_light[0];
    skin_defence_current = &skin_defence[0];
    skin_huanchong_current= &skin_huanchong[0];
    init();
    connect(&timer_fly, &QTimer::timeout, this, &Bird::fly);
    connect(&timer_drop, &QTimer::timeout, this, &Bird::drop);
    connect(&timer_defence_effect_change, &QTimer::timeout, this, &Bird::defence_change);
    connect(&timer_light, &QTimer::timeout, [=]()
    {
        static int i = 0;
        skin_light_current = &skin_light[i];
        i++;
        if(i==5){
            light = 0;
            timer_light.stop();
            i=0;
            draw=1;
            qDebug()<<"draw finish"<<endl;
        }
    });
    connect(&timer_huanchong, &QTimer::timeout, [=]()
    {
        static int i = 0;
        skin_huanchong_current = &skin_huanchong[i];
        i++;
        if(i==5){
            huanchong = 0;
            timer_huanchong.stop();
            i=0;
            draw1=1;
            qDebug()<<"draw1 finish"<<endl;
        }
    });
}

void Bird::init()
{
    position = QPoint((500-60)/2, (700-60)/2-100);
    bird_angle = 0.0;
    fly_speed = 60;
    dropSpeed = 0;
    gravity = 3;
    fail = 0;
    score = 0;
    timer_fly.start(fly_speed);
    timer_drop.stop();
    timer_defence_effect_change.stop();
    if(skin_choose==1)defence_start();
    skin_current = &skin[skin_choose][0];
    defend_time=0;
    jump_height=18;
    defended_time=0;
    bird_angle_speed=3.0;
    bird_angle_speed_a=1;
    skin_score_shi=skin_score[0][0];
    skin_score_current = &skin_score[0][0];
    timer_light.stop();
    light=0;
    timer_huanchong.stop();
    huanchong=0;
    draw=1;

}
void Bird::appear(QPainter& painter)
{

    //先移动到画面中心点，再旋转一定角度，再移动回左上角进行绘图
    painter.translate(position.x()+30, position.y()+30);
    painter.rotate(bird_angle);
    painter.translate(-position.x()-30, -position.y()-30);
    painter.drawPixmap(position.x(), position.y(), bird_w, bird_h,*skin_current);

}
void Bird::defence_appear(QPainter& painter)
{
    if(defend_time!=0)painter.drawPixmap(position.x(), position.y(), bird_w, bird_h,*skin_defence_current);
}
void Bird::light_appear(QPainter& painter)
{
    if(draw){
        timer_light.start(50);
        draw=0;
    }

    painter.drawPixmap(0, position.y()-320, 500, 700,*skin_light_current);
    qDebug()<<"draw"<<endl;
}
void Bird::huanchong_appear(QPainter& painter)
{
    if(draw1){
        timer_huanchong.start(50);
        draw1=0;
        qDebug()<<"draw1111111"<<endl;
    }
    painter.drawPixmap(position.x()-30, position.y()-30, 120, 120,*skin_huanchong_current);

}
void Bird::appear_all(QPainter &painter)
{
    int x=40;
    for(int i=0;i<5;i++){
        skin_current = &skin[i][0];
        painter.drawPixmap(x, (700-60)/2-100, bird_w, bird_h,*skin_current);
        x+=90;
    }
    skin_choose_effect_current = &skin_choose_effect[skin_choose];
    painter.drawPixmap(40+90*skin_choose, (700-60)/2-100, bird_w, bird_h,*skin_choose_effect_current);
    skin_choose_info_current = &skin_choose_info[skin_choose];
    painter.drawPixmap(100, 300, 300, 150,*skin_choose_info_current);

}

void Bird::appear_score(QPainter &painter)
{
    int ge=score%10;
    int shi=score/10;
    static int a=0,b=0;
    int ge_x=238;
    skin_score_current=&skin_score[shi][ge];
    skin_score_shi= skin_score[0][shi];
    if(fail){
        a=71;b=188;
        int best_ge = bestscore%10;
        int best_shi= bestscore/10;
        skin_bestscore_shi=skin_score[0][best_shi];
        skin_bestscore_ge= skin_score[best_shi][best_ge];
        int c=0;
        if(best_shi!=0){
            painter.drawPixmap(296, 281, 24, 36,skin_bestscore_shi);
            c=13;
        }else{
            c=0;
        }
        painter.drawPixmap(309+c, 281, 24, 36,skin_bestscore_ge);


    }else{
        a=0;
        b=0;
    }
    if(score>9){
        ge_x=251;
        painter.drawPixmap(225+a, 50+b, 24, 36,skin_score_shi);
    }
    painter.drawPixmap(ge_x+a, 50+b, 24, 36,*skin_score_current);
    if(score==99)score=0;



}

void Bird::appear_score_table(QPainter &painter)
{
    painter.drawPixmap(100,195, 300, 150,skin_socre_table);
}
void Bird::move(int x, int y)
{
    position.setX(x);
    position.setY(y);
}
void Bird::jump()
{
    //move(0,10);
    //qDebug()<<"jump"<<endl;
    int x=3;
    bird_angle=-25;
    dropSpeed=-jump_height;
    if(skin_choose==2||skin_choose==4)x=0;
    bird_angle_speed=x;
    QSound::play(":/sound/jump_2.wav");//音效

}
void Bird::hit()
{
    if(!fail)jump();
    timer_fly.stop();
    fail=1;
}
void Bird::hit_land()
{
    timer_fly.stop();
    fail=1;
}
void Bird::score_add()
{
    score++;
}
void Bird::start()
{
    timer_drop.start(50);
}
void Bird::get_defence()
{
    defend_time=1;
    QSound::play(":/sound/get_defence.wav");//音效
}
void Bird::fly_quicker()
{
    fly_speed=30;
    gravity=5;
    jump_height=30;
    bird_angle_speed=0;
    bird_angle_speed_a=1;

}
void Bird::fly_slower()
{
    fly_speed=80;
    gravity=5;
    jump_height=25;
    bird_angle_speed=0;
    bird_angle_speed_a=1;
}
void Bird::defence_change()
{
    static int i = 0;
    skin_defence_current = &skin_defence[i];
    i++;
    if(i==9){
        i=0;
    }
}
void Bird::defence_start()
{
    timer_defence_effect_change.start(100);
}
void Bird::fly()
{
    // !!使用静态变量在反复的时候不改变i与a的值
    static int i = 1;
    static int a=-1;
    if(i==2){
        a*=-1;
    }else if(i==0){
        a*=-1;
    }
    skin_current = &skin[skin_choose][i];
    i+=a;
 }
void Bird::drop()
{

    bird_angle_speed+=bird_angle_speed_a;
    bird_angle+=bird_angle_speed;
    if(bird_angle>=90.0) {
        bird_angle = 90.0;
    }
    dropSpeed += gravity;    
    position.setY(position.y()+(dropSpeed));

    if(fail)
    {
        if(position.y()+60>=650)
        {
            position.setY(650-60+10);
            bird_angle = 90.0;
            timer_drop.stop();
            timer_fly.stop();
        }
    }
}





