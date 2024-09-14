#include "mediaplayer.h"

MediaPlayer::MediaPlayer()
{
    // 初始化音樂播放器
    gameOver = new QMediaPlayer();
    gameOver->setMedia(QUrl("qrc:/new/prefix1/sound/Game Over.mp3"));

    ground = new QMediaPlayer();
    ground->setMedia(QUrl("qrc:/new/prefix1/sound/Ground Theme.mp3"));

    underground = new QMediaPlayer();
    underground->setMedia(QUrl("qrc:/new/prefix1/sound/Underground Theme.mp3"));

    superstar = new QMediaPlayer();
    superstar->setMedia(QUrl("qrc:/new/prefix1/sound/superstar.mp3"));

    levelcomplete = new QMediaPlayer();
    levelcomplete->setMedia(QUrl("qrc:/new/prefix1/sound/Level Complete.mp3"));

    // 初始化音效播放器
    jumpingsmall = new QSoundEffect();
    jumpingsmall->setSource(QUrl("qrc:/new/prefix1/sound/jump-small.wav"));

    jumpingbig = new QSoundEffect();
    jumpingbig->setSource(QUrl("qrc:/new/prefix1/sound/jump-super.wav"));

    powerup = new QSoundEffect();
    powerup->setSource(QUrl("qrc:/new/prefix1/sound/powerup.wav"));

    fireball = new QSoundEffect();
    fireball->setSource(QUrl("qrc:/new/prefix1/sound/fireball.wav"));

    coin = new QSoundEffect();
    coin->setSource(QUrl("qrc:/new/prefix1/sound/coin.wav"));
    pipe = new QSoundEffect();
    pipe->setSource(QUrl("qrc:/new/prefix1/sound/pipe.wav"));

}


void MediaPlayer::playGameOverMusic()
{
    stopGroundMusic();
    stopUndergroundMusic();
    gameOver->play();
}

void MediaPlayer::playGroundMusic()
{
    stopUndergroundMusic();

    ground->play();
}

void MediaPlayer::playUndergroundMusic()
{
    stopGroundMusic();
    underground->play();
}

void MediaPlayer::playSuperstarMusic()
{
    stopGroundMusic();
    stopUndergroundMusic();

    superstar->play();
}

void MediaPlayer::playLevelCompleteMusic()
{
    stopGroundMusic();
    levelcomplete->play();
}

void MediaPlayer::stopSuperstarMusic()
{
    superstar->stop();
}

void MediaPlayer::stopGameOverMusic()
{
    gameOver->stop();
}

void MediaPlayer::stopGroundMusic()
{
    ground->stop();
}

void MediaPlayer::stopUndergroundMusic()
{
    underground->stop();
}

void MediaPlayer::playJumpingSmallSound()
{
    jumpingsmall->play();
}

void MediaPlayer::playJumpingBigSound()
{
    jumpingbig->play();
}

void MediaPlayer::playPowerupSound()
{
    powerup->play();
}

void MediaPlayer::playFireballSound()
{
    fireball->play();
}

void MediaPlayer::playCoinSound()
{
    coin->play();
}
void MediaPlayer::playPipeSound(){
    pipe->play();
}
