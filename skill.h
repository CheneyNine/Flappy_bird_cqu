#ifndef SKILL_H
#define SKILL_H

#include <QObject>
#include <QPoint>
#include <QTimer>
#include <QPixmap>

class skill : public QObject
{
    Q_OBJECT
public:
    explicit skill(QObject *parent = nullptr);
    void init();
    void appear(QPainter& painter);
    void shanxian_stop();
    void qingping_stop();
    void skin_shanxian_change();
    void skin_qingping_change();
    void use_skill_shanxian();
    void use_skill_qingping();
    bool shanxian_used;
    bool qingping_used;
    void magic_bird();



private:
    QTimer timer_cd_shanxian,timer_cd_qingping,timer_shanxian_change,timer_qingping_change;
    QPixmap skin_skill_off[2][30];
    QPixmap skin_skill_on[2];
    QPixmap skin_key[2];
    QPixmap *skin_qingping_current;
    QPixmap *skin_shanxian_current;
    int shanxian_count;
    int qingping_count;
    int shanxian_cd;
    int qingping_cd;



signals:

public slots:
};

#endif // SKILL_H
