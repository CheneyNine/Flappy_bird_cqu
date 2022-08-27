#ifndef BGMUSIC_H
#define BGMUSIC_H

#include <QThread>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class music : public QThread
{
    Q_OBJECT

public:
    music();
    void run() override;

    QMediaPlayer* player;
    QMediaPlaylist* playerList;
    void initStatus(QMediaPlayer::MediaStatus status); // 槽函数 监听QMediaPlayer::mediaStatusChanged信号
};

#endif // BGMUSIC_H

