#include "widget.h"
#include "ui_widget.h"
#include <QPixmap>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QGraphicsOpacityEffect>
#include <QSound>
#include <QSoundEffect>
#include <QPushButton>
#include <QTime>
#include <windows.h>
#include <synchapi.h>
#include <QPropertyAnimation>
#include <QKeyEvent>
#include <QPainter>
#include <QtDebug>
#include <QKeyEvent>
#include "QLabel"
#include "QMovie"

#define back_sound ":/music/game_background_music.wav"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置游戏窗口大小
    resize(W,H);
    setWindowTitle("林间探秘");
    setMaximumSize(500, 700);
    setMinimumSize(500, 700);
    m_bird = new Bird(this);
    m_music = new music();
    m_land = new land(this);
    m_pipe = new pipe(this);
    m_background = new background(this);
    m_skill = new skill(this);
    m_sqliteoperator = new Sqlite();
    game_init();
    ui->lb_name->show();
    ui->lb_start->show();
    ui->lb_score->show();
    isLogin=0;
    gametime=1;
    ui->lineEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->lineEdit->setAlignment(Qt::AlignCenter);
    ui->lb_enter->show();
    game_background_music();
    connect(m_pipe, &pipe::gameover, this, &Widget::gameover);
    connect(m_pipe,&pipe::jump,m_bird,&Bird::jump);
    //connect(m_bird,&Bird::light_end,this,&Widget::light_end);
    connect(&timer_twinkle, &QTimer::timeout, [=]()
    {
        if(birdshow)birdshow=0;
        else {
            birdshow=1;
        }

        qDebug()<<"birdshow=0;"<<endl;
    });
    connect(&timer_twinkle_last, &QTimer::timeout, [=]()
    {
        timer_twinkle.stop();
        qDebug()<<"timer_twinkle.stop"<<endl;
    });

}

Widget::~Widget()
{
    delete ui;
}
//游戏初始化
void Widget::game_init()
{

    ui->lb_name->hide();
    ui->lb_start->hide();
    ui->lb_start->setGeometry(101,351,104,58);
    ui->lb_score->hide();
    ui->lb_over->hide();
    ui->lb_choose->hide();
    m_bird->init();
    m_pipe->init();
    m_skill->init();
    m_land->run();
    m_background->run();
    isChooserole=0;
    isGameStart=0;
    isdefending=0;
    birdshow=1;
    light=0;

    timer_twinkle.stop();
    hide=0;
    isAuto=0;
    isGameover=0;
    first=0;


}

void Widget::paintEvent(QPaintEvent *)
{
    //画背景
    QPainter painter(this);
    m_background->appear(painter);
    //画管道
    m_pipe->appear(painter);
    //画土地
    m_land->appear(painter);
    //技能标志
    if(isGameStart){
        m_skill->appear(painter);
    }
    if(m_bird->light){
        m_bird->light_appear(painter);
    }
//    if(m_bird->huanchong){
//        m_bird->huanchong_appear(painter);
//    }

    //画分数
    if(isGameover&&!isChooserole){
        m_bird->appear_score_table(painter);
    }
    if(first&&!isChooserole)m_bird->appear_score(painter);

    //画小鸟
    if(isChooserole){
        m_bird->appear_all(painter);
    }else{
        if(birdshow)m_bird->appear(painter);
        if(isdefending){m_bird->defence_appear(painter);}
    }
    //碰撞检测
    m_pipe->Hit_check(*m_bird);
    if(m_bird->defended_time==1){
        timer_twinkle.start(100);
        timer_twinkle_last.start(2000);
        hide=1;
        m_bird->defended_time=0;
    }
    if(m_bird->getposition().y()+60>650) gameover_land();
    m_pipe->get_check(*m_bird);
    update();
}

void Widget::gameover()
{
    if(isGameStart){
        ui->lb_over->show();
        ui->lb_start->show();
        ui->lb_score->show();
        m_sqliteoperator->InsertData(gametime,ui->lineEdit->text(),m_bird->score);
        gametime++;
        QSound::play(":/sound/over.wav");//音效
    }
    isGameover=1;
    isGameStart=0;
    m_pipe->stop();
    m_pipe->timer_auto_test.stop();
    m_land->stop();
    m_background->stop();
    m_bird->hit();
    m_bird->bestscore=m_sqliteoperator->bestscore();
    //qDebug()<<m_bird->bestscore<<endl;

}



void Widget::gameover_land()
{
    if(isGameStart){
        ui->lb_over->show();
        ui->lb_start->show();
        ui->lb_score->show();
        m_sqliteoperator->InsertData(gametime,ui->lineEdit->text(),m_bird->score);
        gametime++;
        QSound::play(":/sound/over.wav");//音效
    }
    isGameover=1;
    isGameStart=0;
    m_pipe->stop();
    m_land->stop();
    m_background->stop();
    m_bird->hit_land();
    m_bird->bestscore=m_sqliteoperator->bestscore();
}

void Widget::game_background_music()
{
    m_music->run();
}
//根据鼠标的点击做出判断
void Widget::mousePressEvent(QMouseEvent *event)
{
    if(isGameStart)
    {
        m_bird->jump();
    }
    if(!isLogin){
        if(event->x() > 178 && event->x() < 337 && event->y() >457 && event->y() < 506){
            isLogin=1;
            ui->lb_enter->hide();
            ui->lineEdit->setEnabled(false);
            ui->lineEdit->hide();
            QSound::play(":/sound/select.wav");//音效
        }
    }
    if(isLogin){
        if(!isGameStart){
            if(
                event->x() > ui->lb_start->x() &&
                event->x() < ui->lb_start->x()+ui->lb_start->width()&&
                event->y() > ui->lb_start->y()&&
                event->y() < ui->lb_start->y()+ui->lb_start->height())
            {
                //当点击开始按钮后开始游戏
                qDebug()<<"StartInterface::lb_start::mousePressEvent"<<endl;
                game_init();
                isGameStart=1;
                first=1;
                QSound::play(":/sound/start.wav");//音效
                if(m_bird->skin_choose==1){
                    m_bird->get_defence();
                    isdefending=1;
                    qDebug()<<"get_defence"<<endl;
                }
                if(m_bird->skin_choose==2){
                    m_pipe->change_speed_faster();
                    m_bird->fly_quicker();
                    qDebug()<<"狂暴"<<endl;
                }
                if(m_bird->skin_choose==4){
                    m_pipe->change_speed_slower();
                    m_bird->fly_slower();
                    m_skill->magic_bird();
                    m_pipe->move_y();
                    qDebug()<<"冰冻"<<endl;
                }
                if(m_bird->skin_choose==3){
                    m_pipe->bonustime=1;
                }
                m_pipe->run();
                m_bird->start();
            }
            if(
                event->x()>ui->lb_score->x()&&
                event->x()<ui->lb_score->x()+ui->lb_score->width()&&
                event->y()>ui->lb_score->y()&&
                event->y()<ui->lb_score->y()+ui->lb_score->height())
            {
                qDebug()<<"StartInterface::lb_score::mousePressEvent  "<<!isGameStart<<endl;
                isChooserole=1;
                ui->lb_name->hide();
                ui->lb_start->hide();
                ui->lb_score->hide();
                ui->lb_over->hide();
                ui->lb_choose->show();
                ui->lb_start->setGeometry(199,500,104,58);
                ui->lb_start->show();

            }
        }
        if(isChooserole&&!isGameStart){
    }

        if(event->y()>=220&&event->y()<=280){
            if(event->x()>=40&&event->x()<=100){
                m_bird->skin_choose=0;
                QSound::play(":/sound/select.wav");//音效
            }
            if(event->x()>=130&&event->x()<=190){
                m_bird->skin_choose=1;
                QSound::play(":/sound/select.wav");//音效
            }
            if(event->x()>=220&&event->x()<=280){
                m_bird->skin_choose=2;
                QSound::play(":/sound/select.wav");//音效
            }
            if(event->x()>=310&&event->x()<=370){
                m_bird->skin_choose=3;
                QSound::play(":/sound/select.wav");//音效
            }
            if(event->x()>=400&&event->x()<=460){
                m_bird->skin_choose=4;
                QSound::play(":/sound/select.wav");//音效
            }
            qDebug()<<m_bird->skin_choose<<endl;
        }
    }

}
//根据按键做出响应
void Widget::keyPressEvent(QKeyEvent *e)
{
   if(isGameStart&&!isAuto){
       switch (e->key())
      {
      case Qt::Key_E :
          if(!m_skill->shanxian_used){
              m_skill->use_skill_shanxian();
              m_bird->huanchong=1;
              m_pipe->shanxian();
              m_bird->get_defence();
              isdefending=1;
              m_bird->jump();
              m_bird->score++;
              QSound::play(":/sound/shanxian.wav");//音效
          }
           break;
      case Qt::Key_W :
          if(!m_skill->qingping_used){
              m_skill->use_skill_qingping();
              m_pipe->clear_screen();
              m_bird->score+=2;
              m_bird->light=1;
              QSound::play(":/sound/zhansha.wav");//音效
          }
           break;
      case Qt::Key_A : m_pipe->auto_fly();isAuto=1; break;

      }
   }
   if(isGameStart){
       switch (e->key())
      {
        case Qt::Key_G : gameover(); break;
        //case Qt::Key_C : m_sqliteoperator->QueryAllData(); break;
      }
   }

}
