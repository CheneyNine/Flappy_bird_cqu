#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QObject>
#include <QPoint>
#include <QTimer>
#include <QPixmap>

class background : public QObject
{

public:
    explicit background(QObject *parent = nullptr);
    void appear(QPainter& painter);
    void run();
    void stop();

private:
    QPixmap skin;
    QTimer timer_move;
    int position[2];

};

#endif // BACKGROUND_H
