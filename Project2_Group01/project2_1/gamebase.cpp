#include "gamebase.h"

int GameBase::hp = 2000;

GameBase::GameBase(QWidget *parent)
    : QGraphicsView(parent), draggingStone(nullptr), isDragging(false), originalHP(hp) {
    srand(time(0));
    for(int i=0;i<7;i++){
        NCAR[i]=0;
    }

    aligntimeto15 = false;
    /*創造背景圖片*/
    QPixmap pixmap(":/new/prefix1/dataset/backgroundimage.png");
    backgroundImage = new QGraphicsPixmapItem(pixmap.scaled(540, 480));
    timer = new QTimer(this);
    timer -> start(25);
    background = new QGraphicsScene(0, 0, 540, 960, this);
    setFixedSize(540,960);
    background -> setBackgroundBrush(img);
    setScene(background);
    aligntime = 0;
    timerID = startTimer(500);  // 0.5 sec clock

    mediaplayer = new MediaPlayer();
    enemyhpbar1 = new QProgressBar(this);
    enemyhpbar1 -> hide();
    enemyhpbar1 -> setTextVisible(false);

    enemyhpbar2 = new QProgressBar(this);
    enemyhpbar2 -> hide();
    enemyhpbar2 -> setTextVisible(false);

    enemyhpbar3 = new QProgressBar(this);
    enemyhpbar3 -> hide();
    enemyhpbar3 -> setTextVisible(false);
    // 創建 QFont 並設定字體大小
    QFont font;
    cd1 = new QLabel(this);
    font.setPointSize(15);
    cd1 -> hide();
    cd1 -> setFont(font);

    cd2 = new QLabel(this);
    cd2 -> hide();
    cd2 -> setFont(font);

    cd3 = new QLabel(this);
    cd3 -> hide();
    cd3 -> setFont(font);

    playerscharacters = new QLabel("Player's Characters:", this);
    playerscharacters -> setGeometry(20, 20, 350, 30); // 设置位置和大小
    font.setPointSize(20); // 設定字體大小為 20 點
    playerscharacters -> setFont(font);

    characterslist = new QLabel("Characters list:", this);
    characterslist -> setGeometry(20, 250, 300, 30); // 设置位置和大小
    characterslist -> setFont(font);

    gamemission = new QLabel("Game Mission:", this);
    gamemission -> setGeometry(20, 550, 300, 30); // 设置位置和大小
    gamemission -> setFont(font);

    selectgame = new QPushButton(this);
    selectgame -> move(20, 600);
    selectgame -> setFixedSize(500, 40);
    selectgame -> setText("1");
    selectgame -> setFont(font);

    button_start = new QPushButton(this);
    button_start -> move(20, 880);
    button_start -> setFixedSize(500, 80);
    button_start -> setText("Start");
    font.setPointSize(25);
    button_start -> setFont(font);
    button_start -> setStyleSheet("color: white; background-color: rgba(30, 144, 255, 150);");
    connect(button_start, &QPushButton::clicked, this, &GameBase::showstage1);

    surrender = new QPushButton("Surrender", this);
    surrender -> hide();
    surrender -> setStyleSheet("color: white; background-color: rgba(0, 0, 0, 255);");
    surrender -> setFont(font);
    surrender -> move(100, 250);
    surrender -> setFixedSize(350, 50);
    connect(surrender, &QPushButton::clicked, this, &GameBase::lose);

    gobackbutton = new QPushButton("Go Back", this);
    gobackbutton -> hide();
    gobackbutton -> move(100, 350);
    gobackbutton -> setFixedSize(350, 50);
    gobackbutton -> setFont(font);
    gobackbutton -> setStyleSheet("color: white; background-color: rgba(30, 144, 255, 150);");
    connect(gobackbutton, &QPushButton::clicked, this, &GameBase::goback);

    restartbutton = new QPushButton("Restart", this);
    restartbutton -> hide();
    restartbutton -> move(100, 300);
    restartbutton -> setFixedSize(340, 50);
    restartbutton -> setFont(font);
    restartbutton -> setStyleSheet("color: white; background-color: rgba(30, 144, 255, 150);");
    connect(restartbutton, &QPushButton::clicked, this, &GameBase::restart);

    youwin = new QLabel("You Win!", this);
    font.setPointSize(40);
    youwin -> setStyleSheet("color: black; background-color: white;");
    youwin -> hide();
    youwin -> setGeometry(150, 200, 300, 50); // 设置位置和大小
    youwin -> setFont(font);

    youlose = new QLabel("You Lose!", this);
    youlose -> setStyleSheet("color: black; background-color: white;");
    youlose -> hide();
    youlose -> setGeometry(150, 200, 250, 50); // 设置位置和大小
    youlose -> setFont(font);

    playerhpbar = new QProgressBar(this);
    playerhpbar -> setGeometry(10, 465, 520, 30);
    playerhpbar -> hide();
    playerhpbar -> setTextVisible(false);
    playerhpbar -> setStyleSheet("QProgressBar::chunk { background-color: rgba(219,112,147, 150); } QProgressBar { background-color: white; }");
    // 設定 hpbar 的範圍
    playerhpbar -> setRange(0, originalHP);
    playerhpbar -> setValue(originalHP);
    connect(timer, &QTimer::timeout, this, [=]() {
        // 更新 hpbar 的值
        playerhpbar -> setValue(hp);
        QString hpString = QString::number(hp);
        hpremain->setText(hpString + "/2000");
    });

    timerbar = new QProgressBar(this);
    timerbar -> hide();
    timerbar->setGeometry(10, 465, 520, 30);
    timerbar->setRange(0, 100);
    timerbar->setValue(100);
    timerbar->setTextVisible(false);

    QString hpString = QString::number(hp);
    hpremain = new QLabel(hpString + "/2000", this);
    hpremain -> hide();
    hpremain -> setGeometry(350, 465, 180, 30); // 设置位置和大小
    font.setPointSize(25);
    hpremain -> setFont(font);

    set_button = new QPushButton(this);
    set_button -> hide();
    set_button -> setStyleSheet("background-color: rgba(30, 144, 255, 150);");
    set_button -> setText("setting");
    font.setPointSize(12);
    set_button -> setFont(font);
    set_button -> move(450, 0);
    set_button -> setFixedSize(90, 20);
    connect(set_button, &QPushButton::clicked, this, &GameBase::setting);

    changehplabel = new QLabel(this);
    changehplabel -> hide();
    changehplabel -> setGeometry(240, 465, 200, 30); // 设置位置和大小
    font.setPointSize(30);
    changehplabel -> setFont(font);

    stage1 = new QLabel("Battle 01/03", this);
    font.setPointSize(40);
    stage1 -> hide();
    stage1 -> setGeometry(150, 200, 330, 50); // 设置位置和大小
    stage1 -> setFont(font);

    stage2 = new QLabel("Battle 02/03", this);
    stage2 -> hide();
    stage2 -> setGeometry(150, 200, 330, 50); // 设置位置和大小
    stage2 -> setFont(font);

    stage3 = new QLabel("Battle 03/03", this);
    stage3 -> hide();
    stage3 -> setGeometry(150, 200, 330, 50); // 设置位置和大小
    stage3 -> setFont(font);

    combolabel = new QLabel("Combo", this);
    combolabel -> setStyleSheet("color: white; background-color: black;");
    combolabel -> hide();
    combolabel -> setGeometry(200, 850, 400, 60); // 设置位置和大小
    combolabel -> setFont(font);

    font.setPointSize(25);
    confirmbutton = new QPushButton("Confirm", this);
    confirmbutton -> hide();
    confirmbutton -> setStyleSheet("background-color: rgba(30, 144, 255, 150);");
    confirmbutton -> move(80, 400);
    confirmbutton -> setFixedSize(150, 50);
    confirmbutton -> setFont(font);
    connect(confirmbutton, &QPushButton::clicked, this, &GameBase::confirm);

    cancelbutton = new QPushButton("Cancel", this);
    cancelbutton -> hide();
    cancelbutton -> setStyleSheet("background-color: rgba(30, 144, 255, 150);");
    cancelbutton -> move(280, 400);
    cancelbutton -> setFixedSize(150, 50);
    cancelbutton -> setFont(font);
    connect(cancelbutton, &QPushButton::clicked, this, &GameBase::cancel);

    skilldescription = new QLabel(this);
    skilldescription -> setStyleSheet("color: black; background-color: white;");
    skilldescription -> hide();
    skilldescription -> setGeometry(80, 200, 600, 75); // 设置位置和大小
    font.setPointSize(20);
    skilldescription -> setFont(font);

    preparestage();
}

void GameBase::preparestage(){
    prepare = true;
    battle1 = false;
    battle2 = false;
    battle3 = false;
    gainResistant=false;
    changeFallingProb=false;
    numteam = 0;
    hp = 2000;
    combo=0;
    skillactive = 0;
    playerscharacters -> show();
    characterslist -> show();
    for(int i = 1;i < 6;i++){ //畫面上顯示的
        characters[i] = new Characters(-45 + 90 * i, 300, i);
        background -> addItem(characters[i]);
    }
    gamemission -> show();
    selectgame -> show();
    button_start -> show();

    waterslime = new Slime(50, 110, water);
    fireslime = new Slime(220, 110, fire);
    earthslime = new Slime(390, 110, earth);
    lightslime = new Slime(50, 110, light);
    greenMonster = new GreenMonster(220, 110);
    darkslime = new Slime(390, 110, dark);
    fireBoss = new FireBoss(140,70);
    mediaplayer->playCharacterSelectMusic();
    QFont font;
    font.setPointSize(15);
    for(int i = 0;i < 6;i++){
        damagevalue[i] = new QLabel(this);
        damagevalue[i] -> setGeometry(40 + 90 * i, 400, 50, 50); // 设置位置和大小
        damagevalue[i] -> hide();
        damagevalue[i] -> setFont(font);
        bullet[i] = new Bullet(90 * i + 45, 400);
        bullet[i] -> show();
        teammember[i] = nullptr;
    }
}

void GameBase::showstage1(){ //顯示stage 1/3的字樣
    if(numteam==0)return;
    for(int i=1;i<6;i++){ //把畫面上顯示的obj都移除
           background->removeItem(characters[i]);
           delete(characters[i]);
           characters[i]=nullptr;
    }
    for(int i=0;i<numteam;i++){
        background->removeItem(teammember[i]);
        delete(teammember[i]);
        teammember[i]=nullptr;
    }
    background->clear();

    button_start -> hide();
    selectgame -> hide();
    characterslist -> hide();
    playerscharacters -> hide();
    gamemission -> hide();
    stage1 -> show();
    canalign = false;

    QTimer::singleShot(1000, this, [=]() {
            stage1 -> hide();
            battlestage1();
        });
}

void GameBase::battlestage1(){ //第一關
    background->addItem(backgroundImage);
    prepare = false;
    battle1 = true;
    battle2 = false;
    battle3 = false;
    canalign = true;
    set_button -> show();
    playerhpbar -> show();
    hpremain -> show();

    mediaplayer->stopCharacterSelectMusic();
    mediaplayer->playMission1Music();

    //加入怪物
    monsters[0] = waterslime;
    monsters[1] = fireslime;
    monsters[2] = earthslime;
    numAlive = 3;
    background->addItem(waterslime);
    background->addItem(fireslime);
    background->addItem(earthslime);

    enemyhpbar1 -> setGeometry(40, 250, 128, 10);
    enemyhpbar1 -> show();
    enemyhpbar1 -> setRange(0, 100);
    enemyhpbar1 -> setValue(100);
    enemyhpbar1 -> setStyleSheet("QProgressBar::chunk { background-color: blue; } QProgressBar { background-color: white; }");

    cd1 -> setGeometry(20, 110, 100, 20); // 设置位置和大小
    cd1 -> show();

    enemyhpbar2 -> setGeometry(210, 250, 128, 10);
    enemyhpbar2 -> show();
    enemyhpbar2 -> setRange(0, 100);
    enemyhpbar2 -> setValue(100);
    enemyhpbar2 -> setStyleSheet("QProgressBar::chunk { background-color: red; } QProgressBar { background-color: white; }");

    cd2 -> setGeometry(190, 110, 100, 20); // 设置位置和大小
    cd2 -> show();

    enemyhpbar3 -> setGeometry(380, 250, 128, 10);
    enemyhpbar3 -> show();
    enemyhpbar3 -> setRange(0, 100);
    enemyhpbar3 -> setValue(100);
    enemyhpbar3 -> setStyleSheet("QProgressBar::chunk { background-color: green; } QProgressBar { background-color: white; }");

    cd3 -> setGeometry(360, 110, 100, 20); // 设置位置和大小
    cd3 -> show();

    /*放置浮石*/
    srand(time(NULL));
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 5; j++){
            int a = rand() % 6 + 1;
            Runestone::attributemap[i][j] = a;
        }
    }
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 5; j++){
            Runestone *runestone = new Runestone(90*i,870-90*j,Runestone::attributemap[i][j]);
            Runestone::rune[i][j]=runestone;  //存入map
            runestone->coordinate[0]=i;
            runestone->coordinate[1]=j;
            background -> addItem(runestone);
        }
    }

    for(int i = 0; i < numteam; i++){
       Characters *characters = new Characters(90*i, 370, teamattribute[i]);
       teammember[i]=characters;
       background -> addItem(characters);
       switch(teamattribute[i]){
       case water:
           damagevalue[i] -> setStyleSheet("color: blue;");
           break;
       case fire:
           damagevalue[i] -> setStyleSheet("color: red;");
           break;
       case earth:
           damagevalue[i] -> setStyleSheet("color: green;");
           break;
       case light:
           damagevalue[i] -> setStyleSheet("color: rgba(204, 204, 0, 200);");
           break;
       case dark:
           damagevalue[i] -> setStyleSheet("color: purple;");
           break;
       default:
           damagevalue[i] -> setStyleSheet("color: black;");
           break;
       }
    }
    connect(timer, &QTimer::timeout, this, &GameBase::updategame);
}

void GameBase::showstage2(){
    stage2 -> show();
    canalign = false;
    QTimer::singleShot(1000, this, [=]() {
            stage2 -> hide();
            battlestage2();
        });
}

void GameBase::battlestage2(){
    numAlive=3;
    prepare = false;
    battle1 = false;
    battle2 = true;
    canalign = true;

    background -> addItem(lightslime);
    background -> addItem(darkslime);
    background -> addItem(greenMonster);
    monsters[0]=lightslime;
    monsters[1]=greenMonster;
    monsters[2]=darkslime;


    enemyhpbar1 -> setGeometry(40, 250, 128, 10);
    enemyhpbar1 -> show();
    enemyhpbar1 -> setRange(0, 100);
    enemyhpbar1 -> setValue(100);
    enemyhpbar1 -> setStyleSheet("QProgressBar::chunk { background-color: yellow; } QProgressBar { background-color: white; }");

    cd1 -> show();

    enemyhpbar2 -> setGeometry(210, 250, 128, 10);
    enemyhpbar2 -> show();
    enemyhpbar2 -> setRange(0, 300);
    enemyhpbar2 -> setValue(300);
    enemyhpbar2 -> setStyleSheet("QProgressBar::chunk { background-color: green; } QProgressBar { background-color: white; }");

    cd2 -> show();

    enemyhpbar3 -> setGeometry(380, 250, 128, 10);
    enemyhpbar3 -> show();
    enemyhpbar3 -> setRange(0, 100);
    enemyhpbar3 -> setValue(100);
    enemyhpbar3 -> setStyleSheet("QProgressBar::chunk { background-color: purple; } QProgressBar { background-color: white; }");
    cd3 -> show();
    connect(timer, &QTimer::timeout, this, &GameBase::updategame);
    weathering();
}

void GameBase::showstage3(){
    changetonormal();
    stage3 -> show();
    canalign = false;
    QTimer::singleShot(1000, this, [=]() {
            stage3 -> hide();
            battlestage3();
        });
}

void GameBase::battlestage3(){
    numAlive=1;
    mediaplayer->stopMission1Music();
    mediaplayer->playBossMusic();
    battle2 = false;
    battle3 = true;
    canalign = true;

    background -> addItem(fireBoss);
    monsters[0] = fireBoss;

    enemyhpbar1 -> setGeometry(140, 330, 256, 10);
    enemyhpbar1 -> show();
    enemyhpbar1 -> setRange(0, 700);
    enemyhpbar1 -> setValue(700);
    enemyhpbar1 -> setStyleSheet("QProgressBar::chunk { background-color: red; } QProgressBar { background-color: white; }");

    cd1 -> setGeometry(120, 110, 100, 20); // 设置位置和大小
    cd1 -> show();
    connect(timer, &QTimer::timeout, this, &GameBase::updategame);
}


/*******************************
*戰鬥相關的邏輯
*mousePressEvent:選角、判斷轉珠開始
*mouseMoveEvent: 轉珠邏輯
*mouseReleaseEvent、countdown:停止轉珠的判斷
*stopalign:進入消除state
*(1)將拖曳的珠放到正確位置
*(2)將新的map放到int attributemap之中
*(3)依橫向、直向mark三連以上的珠
*
*
*
*************/
void GameBase::mousePressEvent(QMouseEvent* event){
    if(event -> button() == Qt::LeftButton){
        //在prepare stage選角色
        if(prepare and numteam < 6){
            if(event -> pos().y() <= 390 and event -> pos().y() >= 300){  //y:300~390
                if(event -> pos().x() > 45 and event -> pos().x() < 135 ){  //45~135
                    teamattribute[numteam] = water;
                    Characters *characters = new Characters(90 * numteam , 70, 1);
                    background -> addItem(characters);
                    teammember[numteam]=characters;
                    numteam++;
                }
                else if(event -> pos().x() > 135 and event -> pos().x() < 225 ){  //135~225
                    teamattribute[numteam] = fire;
                    Characters *characters = new Characters(90 * numteam , 70, 2);
                    background -> addItem(characters);
                    teammember[numteam]=characters;
                    numteam++;
                }
                else if(event -> pos().x() > 225 and event -> pos().x() < 315 ){  //225~315
                    teamattribute[numteam] = earth;
                    Characters *characters = new Characters(90 * numteam , 70, 3);
                    background -> addItem(characters);
                    teammember[numteam]=characters;
                    numteam++;
                }
                else if(event -> pos().x() > 315 and event -> pos().x() < 405 ){  //315~405
                    teamattribute[numteam] = light;
                    Characters *characters = new Characters(90 * numteam , 70, 4);
                    background -> addItem(characters);
                    teammember[numteam]=characters;
                    numteam++;
                }
                else if(event -> pos().x() > 405 and event -> pos().x() < 495 ){  //405~495
                    teamattribute[numteam] = dark;
                    Characters *characters = new Characters(90 * numteam , 70, 5);
                    background -> addItem(characters);
                    teammember[numteam]=characters;
                    numteam++;
                }
            }
        }
    }

    // 對著角色圖示按下右鍵，使用技能
    if(event -> button() == Qt::RightButton and canalign){
        QPointF scenePos = mapToScene(event->pos());
        for (int i = 0; i < numteam; ++i) {
            if (teammember[i]->collidesWithItem(background->itemAt(scenePos, QTransform()))) {
//                qDebug() << "teammber" << i << "was clicked.";
                canalign = false;
                if (teammember[i]->cd == 0) {
                    //usingSkill(teammember[i]);
                    skillactive = i;
                    confirmbutton -> show();
                    confirmbutton ->raise();
                    cancelbutton -> show();
                    cancelbutton ->raise();
                    skilldescription -> show();
                    skilldescription ->raise();
                    switch(teammember[i] -> getskill()){
                    case changeAttribute:
                        skilldescription -> setText("將火符石轉成水符石");
                        skilldescription -> setGeometry(120, 200, 300, 30);
                        break;
                    case aligntime15:
                        skilldescription -> setText("延長移動符石時間至15秒");
                        skilldescription -> setGeometry(70, 200, 400, 30);
                        break;
                    case resistant:
                        skilldescription -> setText("下次敵人攻擊傷害-20%");
                        skilldescription -> setGeometry(130, 200, 300, 30);
                        break;
                    case fireFall:
                        skilldescription -> setText("下次天降火浮石機率提升");
                        skilldescription -> setGeometry(70, 200, 400, 30);
                        break;
                    case changetonormalstone:
                        skilldescription -> setText("將場上的符石變回原始模樣");
                        skilldescription -> setGeometry(70, 200, 400, 30);
                        break;
                    }
                }
                else{
                    qDebug() << "teammeber" << i << "skill not ready";
                    cancelbutton -> show();
                    skilldescription -> show();
                    QString cdval = QString::number(teammember[i] -> cd);
                    QString originalcdval = QString::number(teammember[i] -> originalCD);
                    skilldescription -> setText("CD:" + cdval + "/" + originalcdval);
                    skilldescription -> setGeometry(200, 200, 100, 30);
                }



                qDebug() << "teammeber" << i << "cd =" << teammember[i]->cd;
                qDebug() << "teammeberattribute" << teammember[i]->attributeType;
                break;
            }
        }
        return;
    }


    if (event->button() == Qt::LeftButton && (battle1 || battle2 || battle3) and canalign and !set) {
        // 檢查是否點擊到符石
        QList<QGraphicsItem*> items = background->items(event->pos());
        foreach(QGraphicsItem* item, items) {
            if (Runestone* runestone = qgraphicsitem_cast<Runestone*>(item)) {
                draggingStone = runestone; // 記錄當前被拖動的符石
                dragStartPos = event->pos(); // 記錄拖動起始位置
                return;
            }
        }
    }
}


//技能
void GameBase::confirm(){
    confirmbutton -> hide();
    cancelbutton -> hide();
    skilldescription -> hide();
    canalign = true;
    mediaplayer->playAbility();
    switch(teammember[skillactive] -> getskill()){
    case changeAttribute:
        for(int i = 0; i < 6; i++){
            for(int j = 0; j < 5; j++){
                if(Runestone::attributemap[i][j] == fire){
                    Runestone::attributemap[i][j] = water;
                    Runestone::rune[i][j] -> changeType(water);
                    if(Runestone::rune[i][j] -> getburn()){
                        Runestone::rune[i][j] -> burning();
                    }
                    else if(Runestone::rune[i][j] -> getweather()){
                        Runestone::rune[i][j] -> weathered();
                    }
                    else{
                        Runestone::rune[i][j] -> normal();
                    }
                }
            }
        }
        break;
    case aligntime15:
        aligntimeto15 = true;
        break;
    case resistant:
        gainResistant=true;
        break;
    case fireFall:
        changeFallingProb=true;
        break;
    case changetonormalstone:
        for(int i = 0; i < 6; i++){
            for(int j = 0; j < 5; j++){
                Runestone::rune[i][j] -> normal();
            }
        }
        break;
    default:    { //直傷
        if (monsters[0] != NULL && monsters[0]->getHP() > 0) {
            monsters[0]->Damaged(100);
            showattack(skillactive, battle3 ? 11 : 31, 100);
            if (monsters[0]->getHP() <= 0) {
                background->removeItem(monsters[0]);
                delete(monsters[0]);
                monsters[0]=nullptr;
                numAlive--;
            }
        }
        QTimer::singleShot(300, this, [=]() {
            if (monsters[1] != NULL && monsters[1]->getHP() > 0) {
                monsters[1]->Damaged(100);
                showattack(skillactive, 32, 100);
                if (monsters[1]->getHP() <= 1) {
                    background->removeItem(monsters[1]);
                    delete(monsters[1]);
                    monsters[1]=nullptr;
                    numAlive--;
                }
            }
        });
        QTimer::singleShot(600, this, [=]() {
            if (monsters[2] != NULL && monsters[2]->getHP() > 0) {
                monsters[2]->Damaged(100);
                showattack(skillactive, 33, 100);
                if (monsters[2]->getHP() <= 0) {
                    background->removeItem(monsters[2]);
                    delete(monsters[2]);
                    monsters[2]=nullptr;
                    numAlive--;
                }
            }
            canalign = true;
        });

        break;
        }
    }
    teammember[skillactive] -> cd = teammember[skillactive] -> originalCD;
}

void GameBase::mouseMoveEvent(QMouseEvent* event) {
    // 轉珠
    if (draggingStone) {
        // 計算拖動距離
        qreal dx = event->pos().x() - dragStartPos.x();
        qreal dy = event->pos().y() - dragStartPos.y();

        // 移動拖動中的符石
        draggingStone->moveBy(dx, dy);

        // 更新拖動起始位置
        dragStartPos = event->pos();


        // 檢查是否與其他符石碰撞
        QList<QGraphicsItem*> collidingItems = draggingStone->collidingItems();
        foreach(QGraphicsItem* item, collidingItems) {
            Runestone* collidingStone = qgraphicsitem_cast<Runestone*>(item);
            // 移動被碰撞的符石
            mediaplayer->playMoveRunestone();
            if(aligntime == 0 and canalign){
                countdown();
                aligntime = (aligntimeto15 ? 30 : 20);
            }
            /*將新的座標標記*/
            int dx=draggingStone->coordinate[0]-collidingStone->coordinate[0];
            int dy=draggingStone->coordinate[1]-collidingStone->coordinate[1];
            if(dx&&dy){//代表兩個都有改變
                continue;//不可以斜向移動
            }
            Runestone::swap(collidingStone, draggingStone);
            qreal reverseX = collidingStone->pos().x() + 90*dx;
            qreal reverseY = collidingStone->pos().y() - 90*dy;
            collidingStone->setPos(reverseX, reverseY);

            if(collidingStone -> getweather() or draggingStone -> getweather()){
                changeplayerhp(-100);
                collidingStone -> normal();
                draggingStone -> normal();
                aligntime = 0;
            }

            if(collidingStone -> getburn()){
                changeplayerhp(-30);
            }

            if(battle3){
                collidingStone -> burning();
            }
        }
    }
}

//只還原燃燒符石，在battle3使用
void GameBase::changetonormal(){
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 5; j++){
            if(Runestone::rune[i][j] -> getburn()){
                Runestone::rune[i][j] -> normal();
            }
        }
    }
}

void GameBase::mouseReleaseEvent(QMouseEvent* event){
    if(event -> button() == Qt::LeftButton){
        if((battle1 or battle2 or battle3) and aligntime != 0){
            aligntime = 0;
        }
    }
}

void GameBase::countdown(){
    if(aligntimeto15){
        timerbar->setRange(0, 150);
        timerbar -> setValue(150);
    }
    else{
        timerbar->setRange(0, 100);
        timerbar->setValue(100);
    }
    timerbar -> show();
    // 創建一個 QTimer
    QTimer *timer1 = new QTimer(this);

    // 設定 QTimer 的時間間隔（毫秒）
    int interval = 100; // 0.1 秒
    timer1->setInterval(interval);

    // 連接 QTimer 的 timeout 信號到槽函數
    connect(timer1, &QTimer::timeout, this, [=]() {
        // 更新 timerbar 的值，使其減少
        int currentValue = timerbar->value();
        timerbar->setValue(currentValue - 1);

        // 檢查 timerbar 是否已經達到最小值，如果是則停止計時器
        if (currentValue <= timerbar->minimum() or aligntime == 0) {
            stopalign();
            timer1 -> stop();
            timerbar -> hide();
        }
    });

    // 啟動 QTimer，使 timerbar 開始隨時間減少
    timer1->start();
    canalign = false;
}

void GameBase::stopalign(){//停止拖動的判斷邏輯
    timerbar -> hide();
    // 檢查是否在戰鬥中且存在被拖動的符石
    if (draggingStone) {
        // 計算符石的最終位置
        qreal finalX = round(draggingStone->pos().x() / 90) * 90;
        qreal finalY = round(draggingStone->pos().y() / 90) * 90;

        // 設置符石的最終位置
        draggingStone->setPos(finalX, finalY);

        // 清除拖動狀態
        draggingStone = nullptr;
    }

    if(hp > 0){ //還活著才執行消除符石 -> 碰到火焰或是風化導致死亡就不執行消除只執行停止移動
        QString combovalue = QString::number(combo);
        /*把要消除的內容標記*/
        int tmpType;
        /*直排*/
        for(int i=0;i<6;i++){
            tmpType=Runestone::attributemap[i][0]; //從第一個開始
            int inLine=1;
            for(int j=1;j<5;j++){
                if(Runestone::rune[i][j]->attributeType==tmpType){
                    inLine++;
                    if(inLine>=3){
                        Runestone::rune[i][j]->isMarking=true;
                        Runestone::rune[i][j-1]->isMarking=true;
                        Runestone::rune[i][j-2]->isMarking=true;
                    }
                }else{
                    inLine=1;
                    tmpType=Runestone::attributemap[i][j];
                }
            }
        }
        /*橫排*/
        for(int j=0;j<5;j++){
            tmpType=Runestone::attributemap[0][j]; //從第一個開始
            int inLine=1;
            for(int i=1;i<6;i++){
                if(Runestone::rune[i][j]->attributeType==tmpType){
                    inLine++;
                    if(inLine>=3){
                        Runestone::rune[i][j]->isMarking=true;
                        Runestone::rune[i-1][j]->isMarking=true;
                        Runestone::rune[i-2][j]->isMarking=true;
                    }
                }else{
                    inLine=1;
                    tmpType=Runestone::attributemap[i][j];
                }
            }
        }

        for(int i=0;i<6;i++){
            for(int j=0;j<5;j++){
                if(Runestone::rune[i][j]==nullptr)continue;
                if(Runestone::rune[i][j]->isMarking){
                    runeStackTop=(runeStack*)calloc(1,sizeof(runeStack));
                    runeStackTop->rune=Runestone::rune[i][j];
                    deleteRune();
                    combo++;
                    update();
                    combovalue = QString::number(combo);
                    combolabel -> setText(combovalue + " Combo!!");
                    /*新增LABEL顯示combo數與加成*/
                    QCoreApplication::processEvents();
                    QThread::msleep(200);
                }
            }
        }
        /*呼叫天降的函數*/
        fallingStage();
    }
}

void GameBase::deleteRune(){
    Runestone *tmp;
    int x,y;
    if(runeStackTop==nullptr)return;
    tmp=popStack(); //將stack先拿出來
    x=tmp->coordinate[0];
    y=tmp->coordinate[1];
    switch(x){
    case 5:
        if(Runestone::rune[x-1][y]){//沒被消除
           if(Runestone::rune[x-1][y]->attributeType==tmp->attributeType && Runestone::rune[x-1][y]->isMarking ){
               pushStack(Runestone::rune[x-1][y]);
               //放入stack的符石就不用再檢驗
               Runestone::rune[x-1][y]->isMarking=false;
           }
        }
    break;
    case 0:
        if(Runestone::rune[x+1][y]){//沒被消除
           if(Runestone::rune[x+1][y]->attributeType==tmp->attributeType && Runestone::rune[x+1][y]->isMarking ){
               Runestone::rune[x+1][y]->isMarking=false;
               pushStack(Runestone::rune[x+1][y]);
           }
        }
    break;
    default:
        if(Runestone::rune[x+1][y]){//沒被消除
           if(Runestone::rune[x+1][y]->attributeType==tmp->attributeType && Runestone::rune[x+1][y]->isMarking ){
               pushStack(Runestone::rune[x+1][y]);
               Runestone::rune[x+1][y]->isMarking=false;
           }
        }
        if(Runestone::rune[x-1][y]){//沒被消除
           if(Runestone::rune[x-1][y]->attributeType==tmp->attributeType && Runestone::rune[x-1][y]->isMarking ){
               pushStack(Runestone::rune[x-1][y]);
               Runestone::rune[x-1][y]->isMarking=false;
           }
        }
        break;
    }

    /*檢查橫排的消除*/
    switch(y){
    case 4:
        if(Runestone::rune[x][y-1]){//沒被消除
           if(Runestone::rune[x][y-1]->attributeType==tmp->attributeType && Runestone::rune[x][y-1]->isMarking ){
               pushStack(Runestone::rune[x][y-1]);
               //放入stack的符石就不用再檢驗
               Runestone::rune[x][y-1]->isMarking=false;
           }
        }
    break;
    case 0:
        if(Runestone::rune[x][y+1]){//沒被消除
           if(Runestone::rune[x][y+1]->attributeType==tmp->attributeType && Runestone::rune[x][y+1]->isMarking ){
               Runestone::rune[x][y+1]->isMarking=false;
               pushStack(Runestone::rune[x][y+1]);
           }
        }
    break;
    default:
        if(Runestone::rune[x][y+1]){//沒被消除
           if(Runestone::rune[x][y+1]->attributeType==tmp->attributeType && Runestone::rune[x][y+1]->isMarking ){
               pushStack(Runestone::rune[x][y+1]);
               Runestone::rune[x][y+1]->isMarking=false;
           }
        }
        if(Runestone::rune[x][y-1]){//沒被消除
           if(Runestone::rune[x][y-1]->attributeType==tmp->attributeType && Runestone::rune[x][y-1]->isMarking ){
               pushStack(Runestone::rune[x][y-1]);
               Runestone::rune[x][y-1]->isMarking=false;
           }
        }
    }


     /*將符石移除*/
    NCAR[tmp->attributeType]++;
    delete tmp;
    if(runeStackTop==nullptr){
        return;
    }
    else{
        deleteRune();//持續呼叫直到stack為空
    }

}

void GameBase::pushStack(Runestone* node){
    runeStack *newNode=(runeStack*)calloc(1,sizeof(runeStack));
    newNode->rune=node;

    if(runeStackTop==nullptr){
        runeStackTop=newNode;
    }
    else{
        newNode->next=runeStackTop;
        runeStackTop=newNode;
    }
}

Runestone*GameBase::popStack(){
    if(runeStackTop==nullptr)return nullptr;
    runeStack *tmp=runeStackTop;
    Runestone *node=runeStackTop->rune;
    runeStackTop=runeStackTop->next;
    free(tmp);
    return node;
}

void GameBase::fallingStage(){
    bool isChange=false;
    bool needAlign=false;
    for(int k=0;k<5;k++){
        isChange=false;
        for(int j=1;j<5;j++){
            for(int i=0;i<6;i++){
                if(Runestone::rune[i][j-1]==nullptr){ //第i排的j下面為空，將它往下移動一格
                    isChange=true;
                    needAlign=true;
                    if(Runestone::rune[i][j]){
                       Runestone::rune[i][j]->coordinate[1]--;//rune自己的座標往下移動一格
                       qreal reverseX = Runestone::rune[i][j]->pos().x() ;//x不動
                       qreal reverseY = Runestone::rune[i][j]->pos().y() + 90; //y往下掉90
                       Runestone::rune[i][j]->setPos(reverseX, reverseY);

                       //整個map的座標下移一格
                       Runestone::rune[i][j-1]=Runestone::rune[i][j];
                       Runestone::attributemap[i][j-1]=Runestone::rune[i][j]->attributeType;
                       Runestone::rune[i][j]=nullptr;//原本的位置設為null
                       Runestone::attributemap[i][j]=null;
                    }
                }
            }
        }
        /*在最上層的位置新增新符石*/
        for(int i=0;i<6;i++){
            if(Runestone::rune[i][4]==nullptr){
                needAlign=true;
                int seed=0;
                if(changeFallingProb){
                    seed=rand() % 10;
                    switch(seed){
                        case 6:
                        case 7:
                        case 8:
                        case 9:
                            seed=fire;
                        break;
                        default:
                            seed++;
                        break;
                    }
                }
                else{
                    seed=rand() % 6 + 1;
                }
                Runestone::attributemap[i][4]=seed;
                Runestone *newRuneStone = new Runestone(90*i,870-90*4,Runestone::attributemap[i][4]);
                Runestone::rune[i][4]=newRuneStone;
                newRuneStone->coordinate[0]=i;
                newRuneStone->coordinate[1]=4;
                background -> addItem(newRuneStone);
            }
        }
        if(!isChange){
            break;//停止天降
        }
        /*新增LABEL顯示combo數與加成*/
        QCoreApplication::processEvents();
        QThread::msleep(100);
    }

    if(needAlign){
        stopalign();//如果盤面有改動，就呼叫計算combo的函數
    }
    else{//結束天降stage
        canalign=true;
        changeFallingProb=false;
        DamageToMonster();
        //plusPlayerHP(combo * NCAR[heart] * 5);//回血改道dmgTomonster
        QTimer::singleShot(1200, this, [=]() {
                monsterAttack();
                for (int i = 0; i < 7;i++)
                    NCAR[i] = 0;
                combo = 0;
        });

        // 玩家角色CD 減一
        if(combo != 0){ //有消除符石CD才減1
            for (int i = 0; i < numteam; ++i) {
                teammember[i]->minusOneCD();
            }
        }


    }
}

void GameBase::timerEvent(QTimerEvent *event){
    if(event -> timerId() == timerID and timerID != 0){
        aligntime = (aligntime == 0)? 0 : aligntime - 1;
    }
}

void GameBase::showattack(int team, int monster, int damage){  //攻擊動畫
    QString damageval = QString::number(damage);
    damagevalue[team] -> setText(damageval);
    damagevalue[team] -> show();
    bullet[team] -> show();
    qreal monsterX;
    const int animationtime = 300;

    switch(monster){
    case 11:
        monsterX = 270;
        break;
    case 31:
        monsterX = 60;
        break;
    case 32:
        monsterX = 270;
        break;
    case 33:
        monsterX = 460;
        break;
    }

    background -> addItem(bullet[team]);
    bullet[team] -> setPosition((90 * team + 45) / 2 , 200);
    damagevalue[team] -> move((team / 3 ? monsterX - 20 : monsterX + 20) ,120 - 25 * team);
    animation = new QPropertyAnimation(bullet[team], "pos");
    animation -> setDuration(animationtime);
    QPointF endPos = bullet[team] -> pos() + QPointF(monsterX - (90 * team + 45), -250);
    animation -> setEndValue(endPos);
    animation -> setEasingCurve(QEasingCurve::Linear);

    QTimer::singleShot(animationtime, this, [=]() {
        background -> removeItem(bullet[team]);
        QTimer::singleShot(animationtime * 2, this, [=]() {
            for(int i = 0;i < numteam;i++){
               damagevalue[i] -> hide();
            }
        });
    });

    animation -> start(QAbstractAnimation::DeleteWhenStopped);
}
void GameBase::changeplayerhp(qreal a){
    hp += a;
    if(hp > 2000){
        hp = 2000;
    }

    if(hp <= 0){
        aligntime = 0;
        hp = 0;
        lose();
    }

    //顯示hp變化
    QString changevalue = QString::number(a);
        if (a > 0) {
            changehplabel -> show();
            changehplabel -> setText("+" + changevalue);
            changehplabel -> setStyleSheet("color: green");
        }
        else if(a < 0){
            changehplabel -> show();
            changehplabel -> setText(changevalue);
            changehplabel -> setStyleSheet("color: red");
        }

    QTimer::singleShot(1000, this, [=]() {
            changehplabel -> hide();
    });
}


void GameBase::DamageToMonster(){
    canalign = false;
    float damage = 0;
    int attrteam = 0;
    int attrMonster = 0;

    std::srand(std::time(nullptr));

    for (int i = 0; i < numteam;i++) {//每個人對一個怪物攻擊
        if(numAlive<=0)break;
        attrteam = teamattribute[i];
        /*選擇一個怪物攻擊*/
        int AttackID ;
        Monster* target;
        while(1){
            AttackID = std::rand() % 3;
            if(monsters[AttackID]!=nullptr){
                target = monsters[AttackID];
                break;
            }
        }
        attrMonster = target->getAttribute();
        /*qDebug() << "teammember" << i;
        qDebug() << "teammember Attribute" << teamattribute[i];
        qDebug() << "combo" << combo;
        qDebug() << "NCAR[teamattribute[teammember]]" << NCAR[teamattribute[i]];
        qDebug() << "Monster Attribute" << attrMonster;*/
        // Damage 計算
        switch (attrMonster) {
            case water:
                switch (attrteam){
                    case water:
                        damage = combo * NCAR[water] * 1;
                        break;
                    case fire:
                        damage = combo * NCAR[fire] * 0.5;
                        break;
                    case earth:
                        damage = combo * NCAR[earth] * 2;
                    break;
                    case light:
                        damage = combo * NCAR[light] * 1;
                        break;
                    case dark:
                        damage = combo * NCAR[dark] * 1;
                    break;
                    default:
                        damage = 0;
                        break;
                }
                break;
            case fire:
                switch (attrteam){
                    case water:
                        damage = combo * NCAR[water] * 2;
                        break;
                    case fire:
                        damage = combo * NCAR[fire] * 1;
                        break;
                    case earth:
                        damage = combo * NCAR[earth] * 0.5;
                        break;
                    case light:
                        damage = combo * NCAR[light] * 1;
                        break;
                    case dark:
                        damage = combo * NCAR[dark] * 1;
                        break;
                    default:
                        damage = 0;
                        break;
                }
                break;
            case earth:
                switch (attrteam){
                    case water:
                        damage = combo * NCAR[water] * 1;
                        break;
                    case fire:
                        damage = combo * NCAR[fire] * 2;
                        break;
                    case earth:
                        damage = combo * NCAR[earth] * 1;
                        break;
                    case light:
                        damage = combo * NCAR[light] * 1;
                        break;
                    case dark:
                        damage = combo * NCAR[dark] * 0.5;
                       break;
                    default:
                        damage = 0;
                        break;
                }
                break;
            case light:
                switch (attrteam){
                    case water:
                        damage = combo * NCAR[water] * 1;
                        break;
                    case fire:
                        damage = combo * NCAR[fire] * 1;
                        break;
                    case earth:
                        damage = combo * NCAR[earth] * 1;
                        break;
                    case light:
                        damage = combo * NCAR[light] * 1;
                        break;
                    case dark:
                        damage = combo * NCAR[dark] * 2;
                        break;
                    default:
                        damage = 0;
                        break;
                }
                break;
            case dark:
                switch (attrteam){
                    case water:
                        damage = combo * NCAR[water] * 1;
                        break;
                    case fire:
                        damage = combo * NCAR[fire] * 1;
                        break;
                    case earth:
                        damage = combo * NCAR[earth] * 1;
                        break;
                    case light:
                        damage = combo * NCAR[light] * 2;
                        break;
                    case dark:
                        damage = combo * NCAR[dark] * 1;
                        break;
                    default:
                        damage = 0;
                        break;
                }
                break;
            default:
                damage = 0;
                break;
        }

        damage = round(damage);

        if(monsters[AttackID]!=nullptr and damage != 0){
            if(battle3){
                showattack(i, 11, damage);
            }
            else{
                showattack(i, 31 + AttackID, damage);
            }
        }

        bool isDead=target->Damaged(damage);
        if(isDead){ //刪除該怪物
            background->removeItem(monsters[AttackID]);
            delete(monsters[AttackID]);
            monsters[AttackID]=nullptr;
            numAlive--;
        }
    }

    changeplayerhp(combo * NCAR[heart] * 5); //回血
}

// 怪物攻擊
void GameBase::monsterAttack(){
    canalign = false;
    int attack = 0;
    for(int i=0;i<3;i++){
        if(monsters[i]!=nullptr){
            monsters[i]->CDminusOne();
            if(monsters[i]->getCD())continue;
            attack-=monsters[i]->getAttackPower();
            monsters[i]->resetCD();
        }
    }
    if(battle2)weathering();
    if(battle3){
        changetonormal();
    }

    if(gainResistant and attack!=0){
        attack *=0.8;
        gainResistant=false;
    }
    changeplayerhp(attack);
    aligntimeto15 = false;
    canalign = true;
}

void GameBase::updategame(){
    //顯示combo數量
    if(combo == 0){
        combolabel -> hide();
    }
    else{
        combolabel -> show();
    }

    //判斷怪物的cd以及是否能進入下一關
    QString cdString;
    if(monsters[0]){
        enemyhpbar1 -> setValue(monsters[0] -> getHP());
        cdString = QString::number(monsters[0] -> getCD());
        cd1 -> setText("CD " + cdString);
    }
    else{
        enemyhpbar1 -> hide();
        cd1 -> hide();
    }

    if(monsters[1]){
        enemyhpbar2 -> setValue(monsters[1] -> getHP());
        cdString = QString::number(monsters[1] -> getCD());
        cd2 -> setText("CD " + cdString);
    }
    else{
        enemyhpbar2 -> hide();
        cd2 -> hide();
    }


    if(monsters[2]){
        enemyhpbar3 -> setValue(monsters[2] -> getHP());
        cdString = QString::number(monsters[2] -> getCD());
        cd3 -> setText("CD " + cdString);
    }
    else{
        enemyhpbar3 -> hide();
        cd3 -> hide();
    }

    if(monsters[0]==nullptr and monsters[1]==nullptr and monsters[2]==nullptr){//三隻都死掉
        disconnect(timer, &QTimer::timeout, this, &GameBase::updategame);
        QTimer::singleShot(1000, this, [=]() {
            if(battle1){
                showstage2();
            }
            else if(battle2){
                //win();
                showstage3();
            }
        });
    }

    if(battle3 and monsters[0]==nullptr){
        QTimer::singleShot(1000, this, [=]() {
            win();
        });
    }
}


/*其他遊戲狀態*/

void GameBase::goback(){
    surrender -> hide();
    gobackbutton -> hide();
    canalign = true;
    set = false;
}

void GameBase::cancel(){
    confirmbutton -> hide();
    cancelbutton -> hide();
    skilldescription -> hide();
    canalign = true;
}

void GameBase::restart(){
    mediaplayer->stopBossMusic();
    mediaplayer->stopMission1Music();
    youwin -> hide();
    youlose -> hide();
    restartbutton -> hide();
    /*重設怪物*/
    for(int i=0;i<3;i++){
        if(monsters[i]!=nullptr){
            background->removeItem(monsters[i]);
            delete(monsters[i]);
            monsters[i]=nullptr;
        }
    }
    numAlive=0;

    //重設attrmap
    for(int i=0;i<6;i++){
        for(int j=0;j<5;j++){
            Runestone::attributemap[i][j]=null;
            if(Runestone::rune[i][j]){
                background->removeItem(Runestone::rune[i][j]);
                delete(Runestone::rune[i][j]);
            }
            Runestone::rune[i][j]=nullptr;
        }
    }

    //重設team
    for(int i=0;i<6;i++){
        if(teammember[i]!=nullptr){
            background->removeItem(teammember[i]);
            delete(teammember[i]);
            teammember[i]=nullptr;
        }
    }
    numteam=0;
    for(int i=0;i<6;i++){
        delete(damagevalue[i]);
        delete(bullet[i]);
        damagevalue[i]=nullptr;
        bullet[i]=nullptr;
    }
    playerhpbar -> hide();
    hpremain -> hide();
    set_button -> hide();
    enemyhpbar1 -> hide();
    enemyhpbar2 -> hide();
    enemyhpbar3 -> hide();
    cd1 -> hide();
    cd2 -> hide();
    cd3 -> hide();
    background->removeItem(backgroundImage);
    background->clear();
    preparestage();
    set = false;
}

void GameBase::setting(){
    canalign = false;
    set = true;
    surrender -> show();
    gobackbutton -> show();
}

void GameBase::win(){
    combolabel -> hide();
    youwin -> show();
    restartbutton -> show();
    canalign = false;
    set_button -> hide();
    mediaplayer->playVictory();
}

void GameBase::lose(){
    surrender -> hide();
    gobackbutton -> hide();
    youlose -> show();
    restartbutton -> show();
    canalign = false;
}

void GameBase::minusPlayerHP(int damageFromMonster){
    hp -= damageFromMonster;
    if (hp <= 0)
        hp = 0;

}

void GameBase::plusPlayerHP(int heal) {
    hp += heal;
    if (hp >= originalHP)
        hp = originalHP;
}

void GameBase::staticplusHP(int heal) {
    hp += heal;
    if (hp >= 2000)
        hp = 2000;
}

void GameBase::weathering(){
    /*風化浮石設定*/
    if(battle2 and monsters[1] != nullptr){
        int x = 0, y = 0;
        for(int i = 0;i < 2;i++){
            x = rand() % 6;
            y = rand() % 5;
            Runestone::rune[x][y] -> weathered();
        }
    }
}
