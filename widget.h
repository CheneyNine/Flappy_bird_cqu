#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPushButton>
#include <QLabel>
#include "bird.h"
#include "land.h"
#include "pipe.h"
#include "music.h"
#include "skill.h"
#include "background.h"
#include "sqlite.h"
#include <QtGlobal>
#include <QSound>
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget() override;

public slots:
    void gameover();


public:
    void gameover_land();
    void gameing();//readygo
    void game_background_music();
    void game_init();
    void sound_init();
    void in_window(QWidget *tw, int itime);
    void out_window(QWidget *tw, int itime);

private:
    int H=700;
    int W=500;    
    void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent *) override;

    music *m_music;
    Bird *m_bird;
    land *m_land;
    pipe *m_pipe;
    background *m_background;
    skill *m_skill;
    Sqlite *m_sqliteoperator;
    //QSound *startsound;
    void mousePressEvent(QMouseEvent *event) override;
    bool isGameStart;
    bool isGameover;
    bool isChooserole;
    bool isdefending;
    bool isAuto=0;
    bool birdshow=1;
    bool isLogin=0;
    bool hide;
    bool first;
    bool light;
    int gametime;
    QTimer timer_twinkle,timer_twinkle_last;


    Ui::Widget *ui;
};
#endif // WIDGET_H
