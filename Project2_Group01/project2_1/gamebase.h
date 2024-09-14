#ifndef GAMEBASE_H
#define GAMEBASE_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QPixmap>
#include <QString>
#include <QLabel>
#include <QPropertyAnimation>
#include <QtWidgets>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QProgressBar>
#include <QPalette>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "runestone.h"
#include "characters.h"
#include "bullet.h"
#include "slime.h"
#include "greenmonster.h"
#include "fireboss.h"
#include "mediaplayer.h"
#include "monster.h"


class GameBase : public QGraphicsView {
    Q_OBJECT
    friend class Characters;
public:
    GameBase(QWidget *parent = nullptr);
    void preparestage();
    void battlestage1();
    void battlestage2();
    void battlestage3();
    void countdown();
    void setting();
    void win();
    void lose();
    void goback();
    void restart();
    void cancel();
    void confirm();
    void showstage1();
    void showstage2();
    void showstage3();
    void showattack(int team, int monster, int damage);
    //team:發動攻擊的角色(從左到右0~5)  monster:共幾隻的第幾個(ex.共3隻第1個, monster = 31) damage:攻擊數值
    void changeplayerhp(qreal a);
    void updategame();
    void stopalign();
    void minusPlayerHP(int damageFromMonster);
    void plusPlayerHP(int heal);
    static void staticplusHP (int heal);
    void weathering();
    void DamageToMonster();
    void monsterAttack();
    void changetonormal();
    void usingSkill(Characters *);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void timerEvent(QTimerEvent *event) override;

private:
    QTimer *timer;
    QPixmap img; // 圖片對象
    QGraphicsPixmapItem* backgroundImage;
    QGraphicsPixmapItem* plateImage;
    QGraphicsPixmapItem* teammembergraphic[6];
    QGraphicsScene *background;
    Runestone *runestone;
    Bullet *bullet[6];

    Characters *characters[6]; //在prepare stage顯示的角色
    Characters *teammember[6];  //隊伍成員

    QLabel *playerscharacters;
    QLabel *characterslist;
    QLabel *gamemission;
    QLabel *youwin;
    QLabel *youlose;
    QLabel *hpremain;
    QLabel *stage1;
    QLabel *stage2;
    QLabel *stage3;
    QLabel *changehplabel;
    //static QLabel *changehp;
    QLabel *cd1;
    QLabel *cd2;
    QLabel *cd3;
    QLabel *combolabel;
    QLabel *damagevalue[6];
    QLabel *skilldescription;

    QPushButton *selectgame;
    QPushButton *button_start;
    QPushButton *set_button;
    QPushButton *surrender;
    QPushButton *gobackbutton;
    QPushButton *restartbutton;
    QPushButton *confirmbutton;
    QPushButton *cancelbutton;

    QProgressBar *playerhpbar;    //玩家血條
    QProgressBar *timerbar;
    QProgressBar *enemyhpbar1;
    QProgressBar *enemyhpbar2;
    QProgressBar *enemyhpbar3;

    QPropertyAnimation *animation;

    bool isDragging;
    QPointF dragStartPos;   // 拖动起始位置
    Runestone* draggingStone; // 被拖動的符石
    QPoint startPos;

//    Runestone* currentRunestone;
    void deleteRune();
    int teamattribute[6];
    bool prepare;
    bool battle1;
    bool battle2;
    bool battle3;
    bool set;
    bool canalign;
    bool aligntimeto15; //true:延長移動符石時間至15秒
    int numteam;    //隊伍成員數量
    int aligntime;  //排珠時間
    int timerID;
    static int hp; //玩家血量
    int originalHP; //玩家血量初始值
    int combo;
    int NCAR[7]; // 消除的對應屬性符石的數量
    int skillactive;    //發動技能的成員編號
    bool gainResistant;
    bool changeFallingProb;// 改變掉落率

    // 修正為以 Monster
    Slime *waterslime;
    Slime *fireslime;
    Slime *earthslime;
    Slime *lightslime;
    Slime *darkslime;

    GreenMonster *greenMonster;

    FireBoss *fireBoss;

    Monster *monsters[3];//放螢幕上的怪物
    int numAlive;
    MediaPlayer *mediaplayer;
    struct runeStack{
        Runestone*rune;
        runeStack *next;
    };
    runeStack *runeStackTop;
    void pushStack(Runestone* node);
    Runestone*popStack();
    void fallingStage();//處理天降

};

#endif // GAMEBASE_H

