#ifndef LAND_H
#define LAND_H

#include <QObject>
#include <QPoint>
#include <QTimer>
#include <QPixmap>

class land : public QObject
{

public:
    explicit land(QObject *parent = nullptr);
    void appear(QPainter& painter);
    void run();
    void stop();

private:
    QPixmap skin;
    QTimer timer_move;
    int position[2];

};

#endif // LAND_H
