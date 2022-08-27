#include "skill.h"
#include <QPainter>
#include <QtDebug>
skill::skill(QObject *parent) : QObject(parent)
{
    for(int i = 0;i < 2;i++)
    {
        for(int j = 0;j < 30; j++){
            int x=i+1;
            skin_skill_off[i][j].load(QString(":/image/skill_%1/skill_%2_%3.png").arg(x).arg(i).arg(j));
        }
        skin_skill_on[i].load(QString(":/image/skill_%1.png").arg(i));
    }
    skin_key[0].load(QString(":/image/e.png"));
    skin_key[1].load(QString(":/image/w.png"));

    connect(&timer_qingping_change, &QTimer::timeout, this, &skill::skin_qingping_change);
    connect(&timer_shanxian_change, &QTimer::timeout, this, &skill::skin_shanxian_change);
    connect(&timer_cd_shanxian, &QTimer::timeout, [=]()
    {
       shanxian_used=0;
       timer_cd_shanxian.stop();
       timer_shanxian_change.stop();
       skin_shanxian_current=&skin_skill_on[0];
       shanxian_count=0;
    });
    connect(&timer_cd_qingping, &QTimer::timeout, [=]()
    {
        qingping_used=0;
        timer_cd_qingping.stop();
        timer_qingping_change.stop();
        skin_qingping_current=&skin_skill_on[1];
        qingping_count=0;
    });
}

void skill::init()
{
    shanxian_stop();
    qingping_stop();
    skin_shanxian_current=&skin_skill_on[0];
    skin_qingping_current=&skin_skill_on[1];
    shanxian_used=0;
    qingping_used=0;
    shanxian_count=0;
    qingping_count=0;
    qingping_cd=6000;
    shanxian_cd=3000;


}

void skill::appear(QPainter &painter)
{
    painter.drawPixmap(50, 600, 60, 60,*skin_shanxian_current);
    painter.drawPixmap(130, 600, 60, 60,*skin_qingping_current);
    painter.drawPixmap(50+40, 600+40, 20, 20,skin_key[0]);
    painter.drawPixmap(130+40, 600+40, 20, 20,skin_key[1]);


}

void skill::shanxian_stop()
{
    timer_cd_shanxian.stop();
    timer_shanxian_change.stop();
}

void skill::qingping_stop()
{
    timer_cd_shanxian.stop();
    timer_qingping_change.stop();
}

void skill::skin_shanxian_change()
{

    skin_shanxian_current = &skin_skill_off[0][shanxian_count];
    shanxian_count++;
    if(shanxian_count==30){
        shanxian_count=0;
    }
}

void skill::skin_qingping_change()
{

    skin_qingping_current = &skin_skill_off[1][qingping_count];
    qingping_count++;
    if(qingping_count==30){
        qingping_count=0;
    }
}

void skill::use_skill_shanxian()
{
    shanxian_used=1;
    timer_shanxian_change.start(shanxian_cd/30);
    timer_cd_shanxian.start(shanxian_cd);
}

void skill::use_skill_qingping()
{
    qingping_used=1;
    timer_qingping_change.start(qingping_cd/30);
    timer_cd_qingping.start(qingping_cd);
}

void skill::magic_bird()
{
    shanxian_cd=300;
    qingping_cd=600;
    qDebug()<<"change";

}

