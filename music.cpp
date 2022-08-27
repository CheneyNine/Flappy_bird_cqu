#include "music.h"

music::music()
{
    playerList = new QMediaPlaylist();
    player = new QMediaPlayer();
    playerList->addMedia(QUrl("qrc:/music/game_background_music.wav"));
    playerList->addMedia(QUrl("qrc:/music/game_background_music.wav")); // 方法一、保证有两个音频（可以相同）被添加
    playerList->setPlaybackMode(QMediaPlaylist::Loop);
    playerList->setCurrentIndex(0);
    player->setPlaylist(playerList);
    player->setVolume(100);
    //  connect(player, &QMediaPlayer::mediaStatusChanged,this,&music::initStatus);// 方法二 槽函数 监听QMediaPlayer::mediaStatusChanged信号   进行连接
}

void music::run() {
     player->play();
}

void music::initStatus(QMediaPlayer::MediaStatus status){
    if(status == QMediaPlayer::EndOfMedia)
      {
           //player->setPosition(0);
          // player->play();
      }
}

