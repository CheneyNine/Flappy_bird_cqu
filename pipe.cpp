#include "pipe.h"
#include "land.h"
#include <QPainter>
#include <QTime>
#include <QDebug>
#include <QSound>
pipe::pipe(QObject *parent) : QObject(parent)
{
    pipe_up.load(":/image/pipe_up.png");
    pipe_down.load(":/image/pipe_down.png");
    skin_coin1.load(":/image/medal_2.png");

    init();
    connect(&timer_move, &QTimer::timeout, [=]()
    {
        timer_move.start(speed);
        passpipe = 1;
        for(int i=0;i<3;i++){
            position[i].setX(position[i].x()-1);
            //管道出框之后对管道的位置进行重新的移动
            if(position[i].x()+pipe_w<0){
                position[i].setX(last->x()+pipe_w+pipe_x_space);
                position[i].setY(getRandom(100-700, 700-100-150-700-100));//getRandom(-600, -400)

                last = &position[i];
                coinget[i]=0;
                hascoin[i]=0;
            }
        }
        if(y_distance>-350)y_chazhi=-1;
        if(y_distance<-600)y_chazhi=1;
        position[1].setY(y_distance);

    });
    connect(&timer_stop_check, &QTimer::timeout, [=]()
    {
        ischecking=1;
        qDebug()<<"check continue"<<endl;
    });
    connect(&timer_y_move, &QTimer::timeout, [=]()
    {
        y_distance+=y_chazhi;


    });
    connect(&timer_auto_test, &QTimer::timeout, [=]()
    {
        for (int i=0;i<3;i++) {
            int pipe_x = position[i].x();
            int pipe_y = position[i].y();
                //在判定区域下
            if(bird_x+60<pipe_x&&bird_x+230>pipe_x){
                if(bird_y+60>=pipe_y+850)emit jump();
            }
            if(bird_x+60>=pipe_x&&bird_x+60<pipe_x+120){
                if(bird_y+60>=pipe_y+700+130)emit jump();
            }

            //qDebug()<<"Auto"<<endl;
        }
    });
    connect(&timer_add_speed, &QTimer::timeout, [=]()
    {
        if(speed==5){
            speed=5;
        }
        if(speed>5){
            speed--;
            qDebug()<<"add speed"<<speed<<endl;
        }

    });

}
void pipe::init()
{
    stop();
    for(int i = 0;i<3;i++)
    {
        position[i].setX(500+i*(pipe_w+pipe_x_space));
        position[i].setY(getRandom(100-700, 700-100-150-700-100));//getRandom(-600, -350)
    }
    last = &position[2];
    passpipe = 0;
    ischecking=1;
    timer_stop_check.stop();
    timer_auto_test.stop();
    timer_add_speed.stop();
    timer_y_move.stop();
    speed=10;
    y_distance=-350;
    y_chazhi=1;
    y_chazhi2=0;
    bonustime=0;
    for (int i =0 ;i<3;i++) {
        coinget[i]=0;
        hascoin[i]=0;
    }
}

void pipe::run()
{
    timer_move.start(speed);
    timer_add_speed.start(4000);
    qDebug()<<speed<<endl;
}

void pipe::stop()
{
    timer_move.stop();
}

void pipe::appear(QPainter &painter)
{
    for(int i = 0;i<3;i++)
    {
        painter.drawPixmap(position[i].x(), position[i].y(), pipe_w, pipe_h, pipe_down);
        painter.drawPixmap(position[i].x(), position[i].y()+pipe_h+150, pipe_w, pipe_h, pipe_up);
        int x=(-position[i].y())%4;
        coin_x=position[i].x()+19;
        coin_y= position[i].y()+pipe_h+53;
        if(bonustime){
            if(!coinget[i]){
                if(x==1){
                    hascoin[i]=1;
                    painter.drawPixmap(coin_x,coin_y, 44, 44, skin_coin1);
                    }
             }
        }
    }
}

void pipe::get_check(Bird &bird)
{
    bird_x = bird.getposition().x();
    bird_y = bird.getposition().y();

    for(int i = 0;i<3;i++)
    {
        coin_x=position[i].x()+19;
        coin_y= position[i].y()+pipe_h+53;
        if((bird_x+60>coin_x && bird_x<coin_x+44 && bird_y<coin_y+44 && bird_y>coin_y)
            ||(bird_x+60>coin_x && bird_x<coin_x+44 && bird_y+60>coin_y&&bird_y+60<coin_y+44))
        {
            coinget[i]=1;
            if(hascoin[i]){
                QSound::play(":/sound/coin.wav");//音效
                bird.score_add();
                bird.score_add();
                qDebug()<<"get coin"<<i<<endl;
                hascoin[i]=0;
            }
        }
    }
}

void pipe::clear_screen()
{
    for(int i = 0;i<3;i++)
    {
        position[i].setX(500+i*(pipe_w+pipe_x_space));
        position[i].setY(getRandom(100-700, 700-100-150-700-100));
    }
    last = &position[2];
}

void pipe::shanxian()
{
    for(int i = 0;i<3;i++)
    {
        position[i].setX(200+i*(pipe_w+pipe_x_space));
    }
    last = &position[2];
}

void pipe::Hit_check(Bird &bird)
{
    bird_x = bird.getposition().x();
    bird_y = bird.getposition().y();
    int a = 20;

    if(ischecking){
        for(int i = 0;i<3;i++)
        {
            int pipe_x = position[i].x();
            int pipe_y = position[i].y();
            //鸟的左上角点加上60在柱子左上角点的右边，且尚未飞过这个柱子；鸟的纵坐标在管道上或管道下，返回真
            if(bird_x+60-a>pipe_x && bird_x<pipe_x+pipe_w-a && (bird_y<pipe_y+pipe_h-a || bird_y+60-a>pipe_y+pipe_h+150))
            {
                if(bird.defend_time==0)emit gameover();
                else {
                    bird.defend_time--;
                    bird.defended_time=1;
                    QSound::play(":/sound/defence_over.wav");//音效
                    timer_stop_check.start(2000);
                    ischecking=0;
                    bird.score_add();
                    passpipe = 0;
                    qDebug()<<"hit stop check"<<endl;
                    //qDebug()<<bird.defended_time<<endl;
                }

            }
            else if(bird_x==pipe_x+pipe_w)//刚好通过了柱子
            {
                if(passpipe)
                {
                    bird.score_add();
                    //qDebug()<<QString("addscore:%1").arg(bird.getScore())<<endl;
                    passpipe = 0;
                }
            }
        }

    }

}


void pipe::auto_fly()
{
    timer_auto_test.start(50);

}

void pipe::change_speed_faster()
{
   speed=5;
   qDebug()<<"faster"<<endl;
}

void pipe::change_speed_slower()
{
    speed=15;
    qDebug()<<"slower"<<endl;
}

void pipe::move_y()
{
    timer_y_move.start(10);
}

int pipe::getRandom(int min, int max)
{
    //static QTime t = QTime::currentTime();
    static int n = 0;
    //QTime T = QTime::currentTime();
    //int i = T.msecsTo(t);
    qsrand(n+=20);
    if(n>100) n = 0;
    int num = -(qrand()%(-min));
    if(num > max) return getRandom(min, max);
    else return num;

}

