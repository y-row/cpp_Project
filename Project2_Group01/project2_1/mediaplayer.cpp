#include "mediaplayer.h"

MediaPlayer::MediaPlayer() {
    // 初始化音樂播放器
    mission1 = new QMediaPlayer();
    mission1->setMedia(QUrl("qrc:/new/prefix1/dataset/music/BGM mission1.mp3"));
    connect(mission1, &QMediaPlayer::mediaStatusChanged, this, &MediaPlayer::onMission1StatusChanged);

    boss = new QMediaPlayer();
    boss->setMedia(QUrl("qrc:/new/prefix1/dataset/music/BGM Boss.mp3"));
    connect(boss, &QMediaPlayer::mediaStatusChanged, this, &MediaPlayer::onBossStatusChanged);

    characterselect = new QMediaPlayer();
    characterselect->setMedia(QUrl("qrc:/new/prefix1/dataset/music/BGM characterselect.mp3"));
    connect(characterselect, &QMediaPlayer::mediaStatusChanged, this, &MediaPlayer::onCharacterSelectStatusChanged);

    moverunestone = new QSoundEffect();
    moverunestone->setSource(QUrl("qrc:/new/prefix1/dataset/music/moverunestone.wav"));

    ability = new QSoundEffect();
    ability->setSource(QUrl("qrc:/new/prefix1/dataset/music/ability.wav"));

    victory = new QMediaPlayer();
    victory->setMedia(QUrl("qrc:/new/prefix1/dataset/music/victory.mp3"));
}

void MediaPlayer::playMission1Music() {
    mission1->play();
}

void MediaPlayer::stopMission1Music() {
    mission1->stop();
}

void MediaPlayer::playBossMusic() {
    boss->play();
}

void MediaPlayer::stopBossMusic() {
    boss->stop();
}

void MediaPlayer::playCharacterSelectMusic() {
    characterselect->play();
}

void MediaPlayer::stopCharacterSelectMusic() {
    characterselect->stop();
}

void MediaPlayer::playVictory() {
    victory->play();
}

void MediaPlayer::playMoveRunestone() {
    moverunestone->play();
}

void MediaPlayer::playAbility() {
    ability->play();
}






void MediaPlayer::onMission1StatusChanged(QMediaPlayer::MediaStatus status) {
    if (status == QMediaPlayer::EndOfMedia) {
        mission1->play();
    }
}

void MediaPlayer::onBossStatusChanged(QMediaPlayer::MediaStatus status) {
    if (status == QMediaPlayer::EndOfMedia) {
        boss->play();
    }
}

void MediaPlayer::onCharacterSelectStatusChanged(QMediaPlayer::MediaStatus status) {
    if (status == QMediaPlayer::EndOfMedia) {
        characterselect->play();
    }
}
