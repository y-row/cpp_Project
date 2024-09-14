#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QMediaPlayer>
#include <QSoundEffect>
class MediaPlayer : public QObject
{
    Q_OBJECT
public:
    MediaPlayer();

    void playGameOverMusic();
    void stopGameOverMusic();   // 用不到

    void playGroundMusic();
    void stopGroundMusic();

    void playUndergroundMusic();
    void stopUndergroundMusic();

    void playSuperstarMusic();
    void stopSuperstarMusic();

    void playLevelCompleteMusic();


    void playJumpingSmallSound(); // 給 small mario
    void playJumpingBigSound();   // 給 big mario
    void playPowerupSound();      // 吃到超級蘑菇
    void playFireballSound();     // 火焰彈
    void playCoinSound();         // 吃金幣
    void playPipeSound();




private:
    QMediaPlayer *gameOver;
    QMediaPlayer *ground;
    QMediaPlayer *underground;
    QMediaPlayer *superstar;
    QMediaPlayer *levelcomplete;

    QSoundEffect *jumpingsmall;
    QSoundEffect *jumpingbig;
    QSoundEffect *powerup;
    QSoundEffect *fireball;
    QSoundEffect *coin;
    QSoundEffect *pipe;


};

#endif // MEDIAPLAYER_H

