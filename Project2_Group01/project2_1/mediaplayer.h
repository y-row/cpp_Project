#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QMediaPlayer>
#include <QSoundEffect>

class MediaPlayer : public QObject
{
    Q_OBJECT
public:
    MediaPlayer();

    // music
    void playMission1Music();
    void stopMission1Music();

    void playBossMusic();
    void stopBossMusic();

    void playCharacterSelectMusic();
    void stopCharacterSelectMusic();

    // sound effect
    void playMoveRunestone();
    void playVictory();
    void playAbility();

private slots:
    void onMission1StatusChanged(QMediaPlayer::MediaStatus status);
    void onBossStatusChanged(QMediaPlayer::MediaStatus status);
    void onCharacterSelectStatusChanged(QMediaPlayer::MediaStatus status);



private:
    QMediaPlayer *characterselect;
    QMediaPlayer *mission1;
    QMediaPlayer *boss;
    QMediaPlayer *victory;

    QSoundEffect *moverunestone;
    QSoundEffect *ability;


};

#endif // MEDIAPLAYER_H

