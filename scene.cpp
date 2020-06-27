#include "scene.h"
#include <QMediaPlayer>
#include"card.h"

static const int TowerCost = 300;

Scene::Scene(QWidget *parent) : QLabel(parent)
  , m_waves(0)
  , m_gameEnded(false)
  , m_gameWin(false)
  , m_playerHp(15)
  , m_playerGold(10000)
{
    this->setMouseTracking(true);
    this->grabKeyboard();
}

Scene::~Scene()
{
    if (!(this->MoneyFront == nullptr)) delete this->MoneyFront;
    if (!(this->MoneyBar == nullptr)) delete this->MoneyBar;
    if (!(this->moneybar == nullptr))delete this->moneybar;
    if (!(this->MoneyLabel == nullptr)) delete this->MoneyLabel;
    if (!(this->moneylabel == nullptr)) delete this->moneylabel;

    if (!(this->LifeFront == nullptr))delete this->LifeFront;
    if (!(this->LifeBar == nullptr)) delete this->LifeBar;
    if (!(this->lifebar == nullptr)) delete this->lifebar;
    if (!(this->LifeLabel == nullptr))delete this->LifeLabel;
    if (!(this->lifelabel == nullptr)) delete this->lifelabel;

    if (!(this->WaveFront == nullptr)) delete this->WaveFront;
    if (!(this->WaveBar == nullptr))delete this->WaveBar;
    if (!(this->wavebar == nullptr)) delete this->wavebar;
    if (!(this->WaveLabel == nullptr)) delete this->WaveLabel;
    if (!(this->wavelabel == nullptr))delete this->wavelabel;

    if (!(this->LevelUp == nullptr)) delete this->LevelUp;
    if (!(this->levelup == nullptr)) delete this->levelup;

    if (!(this->LevelFront == nullptr)) delete this->LevelFront;
    if (!(this->levelbar == nullptr)) delete this->levelbar;
    if (!(this->LevelBar == nullptr)) delete this->LevelBar;

    if (!(this->Upgrade_MoneyFront == nullptr))delete this->Upgrade_MoneyFront;
    if (!(this->upgrade_moneybar == nullptr))delete this->upgrade_moneybar;
    if (!(this->Upgrade_MoneyBar == nullptr))delete this->Upgrade_MoneyBar;

    delete Base;
    delete base;

    delete NormalTowerPic;
    delete normalTowerPic;
    delete FireTowerPic;
    delete fireTowerPic;
    delete IceTowerPic;
    delete iceTowerPic;
    delete LaserTowerPic;
    delete laserTowerPic;

    delete currentCard;

}

void Scene::mouseMoveEvent(QMouseEvent *event)
{
    m = event->pos();
    if (this->currentCard != nullptr)
    {
        this->currentCard->move(m + QPoint(-40, 1));
    }
}

void Scene::getHpDamage(int damage)
{
    m_audioPlayer->playSound(LifeLoseSound);
    m_playerHp -= damage;
    if (m_playerHp <= 0)
        doGameOver();
}


void Scene::removedBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.removeOne(bullet);
    delete bullet;
}

void Scene::addBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.push_back(bullet);
}

void Scene::awardGold(int gold)
{
    m_playerGold += gold;
    update();
}

AudioPlayer *Scene::audioPlayer() const
{
    return m_audioPlayer;
}

void Scene::FireIceattack()
{
    foreach(Enemy *enemy, m_enemyList){
        if (enemy->fire != 0){
            enemy->fire--;
            enemy->getFireDamage(enemy->fireattack);
        }
        if(enemy->ice != 0){
            enemy->ice--;
            if (enemy->ice == 0)
            {
                enemy->m_walkingSpeed = enemy->m_normalSpeed;
                enemy->m_slowSpeed = enemy->m_normalSpeed;
            }
            else
            {
                enemy->m_walkingSpeed = enemy->m_slowSpeed;
            }
        }
    }
}

void Scene::doGameOver()
{
    if (!m_gameEnded)
    {
        m_gameEnded = true;

        m_audioPlayer->stopBGM();
        m_audioPlayer->playLoseSound();
    }
}

QList<Enemy *> Scene::enemyList() const
{
    return m_enemyList;
}

tStartScreen::tStartScreen(QWidget* parent): QLabel(parent)
{
    QUrl backgroundMusicUrl = QUrl::fromLocalFile(s_curDir + "/First Page.mp3");
    m_audioPlayer = new AudioPlayer(backgroundMusicUrl,this);
    m_audioPlayer->startBGM();
    this->setMouseTracking(true);
    this->grabKeyboard();
    this->setGeometry(0, 0, 800, 600); //界面
    this->setMovie(this->background);  //图片
    this->background->start();      //
    this->show();
    this->front->setGeometry(0, 0, 800, 600);
    this->front->show();
    this->front->setStyleSheet("background: rgba(255,0,0,1)");
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(20);
}

tStartScreen::~tStartScreen()
{
    delete this->background;
    delete this->front;
}

void tStartScreen::onTimer()
{
    if (frame > 0)
    {
        frame --;
        if (frame > 50)
        {
            this->front->setStyleSheet("background: rgba(0,0,0," + QString::number((frame - 50) / 50.0) +")");
        }
        if (frame < 30)
        {
            this->front->setStyleSheet("background: rgba(0,0,0," + QString::number((30 - frame) / 30.0) +")");
        }
    }
    else
    {
        emit toTitle();
    }
}

tStartScene::tStartScene(QWidget* parent):QLabel(parent)
{
    QUrl backgroundMusicUrl = QUrl::fromLocalFile(s_curDir + "/First Page.mp3");
    m_audioPlayer = new AudioPlayer(backgroundMusicUrl,this);
    m_audioPlayer->startBGM();
    this->setMouseTracking(true);
    this->grabKeyboard();


    this->setGeometry(0, 0, 800, 600);
    this->setMovie(this->background);
    this->background->start();
    this->show();
    btn1->setStyleSheet("QLabel{border: 0px solid #000000;} QLabel:hover{border:0px solid #EE0000;}");
    btn2->setStyleSheet("QLabel{border: 0px solid #000000;} QLabel:hover{border:0px solid #EE0000;}");
    btn1->setMovie(easy);
    easy->start();
    btn2->setMovie(hard);
    hard->start();
    btn1->setGeometry(200, 255, 80, 80);
    btn2->setGeometry(480, 255, 80, 80);
    btn1->show();
    btn2->show();


}

tStartScene::~tStartScene()
{
    delete this->background;
    delete this->easy;
    delete this->hard;
    delete this->btn1;
    delete this->btn2;
    delete this->title;
    delete this->easyStr;
    delete this->hardStr;
}

void tStartScene::mousePressEvent(QMouseEvent *event)
{
    if (QRect(200, 255, 80, 80).contains(event->pos()))
    {
        emit toEasy();
    }
    if (QRect(480, 255, 80, 80).contains(event->pos()))
    {
        emit toHard();
    }
}

easyScene::easyScene(QWidget* parent)
    : Scene(parent)
{
    QUrl backgroundMusicUrl = QUrl::fromLocalFile(s_curDir + "/easy.mp3");
    m_audioPlayer = new AudioPlayer(backgroundMusicUrl,this);
    m_audioPlayer->startBGM();

    this->setGeometry(0, 0, 800, 600);
    this->setMovie(this->background);
    this->background->start();
    this->show();

    preLoadWavesInfo(); //设置波数
    loadTowerPositions(); //调用位置函数
    addWayPoints();

    //每100ms更新一次灼烧状态
    QTimer *Firetime = new QTimer(this);
    connect(Firetime, SIGNAL(timeout()), this, SLOT(FireIceattack()));
    Firetime->start(100);

    //每30ms发送一个更新信号
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(30);
    this->uiSetup();
    // 设置300ms后游戏启动
    QTimer::singleShot(300, this, SLOT(gameStart()));
}

void easyScene::uiSetup()
{
    MoneyBar->setGeometry(120, 450, 300, 200);
    moneybar->start();
    MoneyBar->show();
    MoneyBar->setMovie(moneybar);
    MoneyFront->setGeometry(10, 535, 300, 200);
    MoneyFront->setFont(QFont("Calibri", 16));
    MoneyFront->setText("50");
    MoneyFront->setAlignment(Qt::AlignHCenter);
    MoneyFront->show();
    MoneyFront->raise();
    MoneyLabel->setGeometry(60, 450, 300, 200);
    moneylabel->start();
    MoneyLabel->show();
    MoneyLabel->setMovie(moneylabel);

    LifeBar->setGeometry(400, 450, 300, 200);
    lifebar->start();
    LifeBar->show();
    LifeBar->setMovie(lifebar);
    LifeFront->setGeometry(290, 535, 300, 200);
    LifeFront->setFont(QFont("Calibri", 16));
    LifeFront->setText("10");
    LifeFront->setAlignment(Qt::AlignHCenter);
    LifeFront->show();
    LifeFront->raise();
    LifeLabel->setGeometry(340, 450, 300, 200);
    lifelabel->start();
    LifeLabel->show();
    LifeLabel->setMovie(lifelabel);

    WaveBar->setGeometry(680, 450, 300, 200);
    wavebar->start();
    WaveBar->show();
    WaveBar->setMovie(wavebar);
    WaveFront->setGeometry(570, 535, 300, 200);
    WaveFront->setFont(QFont("Calibri", 16));
    WaveFront->setText("1");
    WaveFront->setAlignment(Qt::AlignHCenter);
    WaveFront->show();
    WaveFront->raise();
    WaveLabel->setGeometry(615, 450, 300, 200);
    wavelabel->start();
    WaveLabel->show();
    WaveLabel->setMovie(wavelabel);

    Base->setGeometry(685, 35, 228, 306);
    base->start();
    Base->show();
    Base->setMovie(base);
    Base->raise();

    LevelUp->setGeometry(100, 410, 50, 50);
    levelup->start();
    LevelUp->show();
    LevelUp->setMovie(levelup);
    LevelUp->raise();

    LevelBar->setGeometry(10, 340, 300, 200);
    levelbar->start();
    LevelBar->show();
    LevelBar->setMovie(levelbar);
    LevelBar->raise();
    LevelFront->setGeometry(-100, 420, 300, 200);
    LevelFront->setFont(QFont("Calibri", 16));
    LevelFront->setAlignment(Qt::AlignHCenter);
    LevelFront->show();
    LevelFront->raise();

    Upgrade_MoneyBar->setGeometry(170, 340, 300, 200);
    upgrade_moneybar->start();
    Upgrade_MoneyBar->show();
    Upgrade_MoneyBar->setMovie(upgrade_moneybar);
    Upgrade_MoneyBar->raise();

    Upgrade_MoneyFront->setGeometry(60, 420, 300, 200);
    Upgrade_MoneyFront->setFont(QFont("Calibri", 16));
    Upgrade_MoneyFront->setAlignment(Qt::AlignHCenter);
    Upgrade_MoneyFront->show();
    Upgrade_MoneyFront->raise();

    btn1->setStyleSheet("QLabel{border: 0px solid #000000;} QLabel:hover{border:1px solid #000000;}");
    btn1->setMovie(station);
    station->start();
    btn1->setGeometry(34,272, 60, 60);
    btn1->show();
    btn1->raise();

    btn2->setStyleSheet("QLabel{border: 0px solid #000000;} QLabel:hover{border:1px solid #000000;}");
    btn2->setMovie(station);
    station->start();
    btn2->setGeometry(147,272, 60, 60);
    btn2->show();
    btn2->raise();

    btn3->setStyleSheet("QLabel{border: 0px solid #000000;} QLabel:hover{border:1px solid #000000;}");
    btn3->setMovie(station);
    station->start();
    btn3->setGeometry(315,442, 60, 60);
    btn3->show();
    btn3->raise();

    btn4->setStyleSheet("QLabel{border: 0px solid #000000;} QLabel:hover{border:1px solid #000000;}");
    btn4->setMovie(station);
    station->start();
    btn4->setGeometry(415,442, 60, 60);
    btn4->show();
    btn4->raise();

    btn5->setStyleSheet("QLabel{border: 0px solid #000000;} QLabel:hover{border:1px solid #000000;}");
    btn5->setMovie(station);
    station->start();
    btn5->setGeometry(531,442, 60, 60);
    btn5->show();
    btn5->raise();

    btn6->setStyleSheet("QLabel{border: 0px solid #000000;} QLabel:hover{border:1px solid #000000;}");
    btn6->setMovie(station);
    station->start();
    btn6->setGeometry(644,442, 60, 60);
    btn6->show();
    btn6->raise();

    btn7->setStyleSheet("QLabel{border: 0px solid #000000;} QLabel:hover{border:1px solid #000000;}");
    btn7->setMovie(station);
    station->start();
    btn7->setGeometry(374,234, 60, 60);
    btn7->show();
    btn7->raise();

    btn8->setStyleSheet("QLabel{border: 0px solid #000000;} QLabel:hover{border:1px solid #000000;}");
    btn8->setMovie(station);
    station->start();
    btn8->setGeometry(458,234, 60, 60);
    btn8->show();
    btn8->raise();

    btn9->setStyleSheet("QLabel{border: 0px solid #000000;} QLabel:hover{border:1px solid #000000;}");
    btn9->setMovie(station);
    station->start();
    btn9->setGeometry(551,234, 60, 60);
    btn9->show();
    btn9->raise();

    btn10->setStyleSheet("QLabel{border: 0px solid #000000;} QLabel:hover{border:1px solid #000000;}");
    btn10->setMovie(station);
    station->start();
    btn10->setGeometry(545,145, 60, 60);
    btn10->show();
    btn10->raise();

    btn11->setStyleSheet("QLabel{border: 0px solid #000000;} QLabel:hover{border:1px solid #000000;}");
    btn11->setMovie(station);
    station->start();
    btn11->setGeometry(152,379, 60, 60);
    btn11->show();
    btn11->raise();

    exit->setGeometry(700, 0, 60, 60);
    exit->setFlat(true);
    exit->setIcon(QIcon(":/image/Leave.png"));
    exit->setIconSize(QSize(60,60));
    exit->setStyleSheet("background: transparent");
    exit->setCursor(Qt::PointingHandCursor);
    connect(exit, SIGNAL(clicked()), this, SLOT(leave()));
    exit->show();
    exit->raise();

    NormalTowerPic->setGeometry(180, 10, 100, 60);
    normalTowerPic->start();
    NormalTowerPic->show();
    NormalTowerPic->setMovie(normalTowerPic);

    FireTowerPic->setGeometry(280, 10 , 100, 60);
    fireTowerPic->start();
    FireTowerPic->show();
    FireTowerPic->setMovie(fireTowerPic);

    IceTowerPic->setGeometry(430, 10 , 100, 60);
    iceTowerPic->start();
    IceTowerPic->show();
    IceTowerPic->setMovie(iceTowerPic);

    LaserTowerPic->setGeometry(530, 10 , 100, 60);
    laserTowerPic->start();
    LaserTowerPic->show();
    LaserTowerPic->setMovie(laserTowerPic);

    Card *card0 = new tNormalTowerCard(this);
    card0->setGeometry(180, 10 , 100, 60);
    Cards.append(card0);
    card0->show();

    Front1 = new QLabel(this);
    Front1->setText("100");
    Front1->setGeometry(225, 40, 40, 20);
    Front1->setFont(QFont("Calibri", 11));
    Front1->show();
    Front1->raise();

    Card *card1 = new tFireTowerCard(this);
    card1->setGeometry(280, 10 , 100, 60);
    Cards.append(card1);
    card1->show();

    Front2 = new QLabel(this);
    Front2->setText("150");
    Front2->setGeometry(325, 40, 40, 20);
    Front2->setFont(QFont("Calibri", 11));
    Front2->show();
    Front2->raise();

    Card *card2 = new tIceTowerCard(this);
    card2->setGeometry(430, 10 , 100, 60);
    Cards.append(card2);
    card2->show();

    Front3 = new QLabel(this);
    Front3->setText("150");
    Front3->setGeometry(475, 40, 40, 20);
    Front3->setFont(QFont("Calibri", 11));
    Front3->show();
    Front3->raise();

    Card *card3 = new tLaserTowerCard(this);
    card3->setGeometry(530, 10 , 100, 60);
    Cards.append(card3);
    card3->show();

    Front4 = new QLabel(this);
    Front4->setText("200");
    Front4->setGeometry(575, 40, 40, 20);
    Front4->setFont(QFont("Calibri", 11));
    Front4->show();
    Front4->raise();

}

void easyScene::removedEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);

    m_enemyList.removeOne(enemy);
    delete enemy;

    if (m_enemyList.empty())
    {
        ++m_waves;
        if (!loadWave())
        {
        m_gameWin = true;
        m_audioPlayer->stopBGM();
        m_audioPlayer->playWinSound();

        }
    }
}


void easyScene::loadTowerPositions()
{
    QPoint pos[]=
    {
        QPoint(34,272),
        QPoint(147,272),
        QPoint(315,442),
        QPoint(415,442),

        QPoint(531,442),
        QPoint(644,442),
        QPoint(152,379),
        QPoint(374,234),
        QPoint(458,234),
        QPoint(551,234),
        QPoint(545,145)

    };
    int len= sizeof(pos)/sizeof (pos[0]);
    for (int i = 0;i<len;++i)
        m_towerPositionsList.push_back(pos[i]);

}

void easyScene::addWayPoints()
{

    WayPoint *wayPoint1 = new WayPoint(QPoint(787, 241));
    m_wayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(702,236));
    m_wayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3 = new WayPoint(QPoint(681, 373));
    m_wayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(321, 379));
    m_wayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(300, 207));
    m_wayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(0, 207));
    m_wayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);

}

bool easyScene::loadWave()
{
    if (m_waves >= m_wavesInfo.size())
        return false;

    WayPoint *startWayPoint = m_wayPointsList.back();
    QList<QVariant> curWavesInfo = m_wavesInfo[m_waves].toList();

    for (int i = 0; i < curWavesInfo.size(); ++i)
    {
        QMap<QString, QVariant> dict = curWavesInfo[i].toMap();
        int spawnTime = dict.value("spawnTime").toInt();

        Enemy *enemy;
        int j=i%5;
        switch(j){
        case 0:
            enemy = new normalEnemy(startWayPoint, this);
            break;
        case 1:
            enemy=new iceEnemy(startWayPoint, this);
            break;
        case 2:
            enemy=new fireEnemy(startWayPoint, this);
            break;
        case 3:
            enemy=new fastEnemy(startWayPoint, this);
            break;
        case 4:
            enemy=new bossEnemy(startWayPoint, this);
            break;
        }
        m_enemyList.push_back(enemy);
        QTimer::singleShot(spawnTime, enemy, SLOT(doActivate()));
    }

    return true;
}

bool easyScene::canBuyTower() const
{
    if (m_playerGold >= TowerCost)
        return true;
    return false;
}

void easyScene::drawWave()
{
    WaveFront->setText(QString("%1").arg(m_waves +1));
    WaveFront->setAlignment(Qt::AlignHCenter);
    WaveFront->show();
    WaveFront->raise();
}

void easyScene::drawHP()
{
    LifeFront->setText(QString("%1").arg(m_playerHp));
    LifeFront->setAlignment(Qt::AlignHCenter);
    LifeFront->show();
    LifeFront->raise();
}

void easyScene::drawPlayerGold()
{
    MoneyFront->setText(QString("%1").arg(m_playerGold));
    MoneyFront->setAlignment(Qt::AlignHCenter);
    MoneyFront->show();
    MoneyFront->raise();
}


void easyScene::preLoadWavesInfo()
{
    QFile file(":/config/Waves.plist");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition.plist");
        return;
    }

    PListReader reader;
    reader.read(&file);

    // 获取波数信息
    m_wavesInfo = reader.data();

    file.close();
}

easyScene::~easyScene()
{
    delete this->background;
    delete this->exit;
    delete this->btn1;
    delete this->btn2;
    delete this->btn3;
    delete this->btn4;
    delete this->btn5;
    delete this->btn6;
    delete this->btn7;
    delete this->btn8;
    delete this->btn9;
    delete this->btn10;
    delete this->btn11;
    delete this->btn12;
    delete this->btn13;

    foreach (Card *card, Cards)
    {
        Q_ASSERT(card);
        Cards.removeOne(card);
        delete card;
    }

    foreach (Tower *tower, m_towersList)
    {
        Q_ASSERT(tower);
        m_towersList.removeOne(tower);
        delete tower;
    }
    foreach (Enemy *enemy, m_enemyList)
    {
        Q_ASSERT(enemy);
        m_enemyList.removeOne(enemy);
        delete enemy;
    }
    foreach (Bullet *bullet, m_bulletList)
    {
        removedBullet(bullet);
    }
    delete Front1;
    delete Front2;
    delete Front3;
    delete Front4;

    //delete ui;
}


void easyScene::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Escape:
        emit toTitle();
        break;
    }
}

void easyScene::paintEvent(QPaintEvent *)
{
    if (m_gameEnded || m_gameWin)
    {
        btn1->hide();
        btn2->hide();
        btn3->hide();
        btn4->hide();
        btn5->hide();
        btn6->hide();
        btn7->hide();
        btn8->hide();
        btn9->hide();
        btn10->hide();
        btn11->hide();
        btn12->hide();
        btn13->hide();

        MoneyFront->hide();
        MoneyBar->hide();
        MoneyLabel->hide();
        LifeFront->hide();
        LifeBar->hide();
        LifeLabel->hide();
        WaveFront->hide();
        WaveBar->hide();
        WaveLabel->hide();
        Base->hide();
        Front1->hide();
        Front2->hide();
        Front3->hide();
        Front4->hide();
        LevelUp->hide();
        LevelFront->hide();
        LevelBar->hide();
        Upgrade_MoneyFront->hide();
        Upgrade_MoneyBar->hide();

        NormalTowerPic->hide();
        FireTowerPic->hide();
        IceTowerPic->hide();
        LaserTowerPic->hide();

        foreach (Card *card, Cards)
        {
            Q_ASSERT(card);
            Cards.removeOne(card);
            delete card;
        }

        foreach (Tower *tower, m_towersList)
        {
            Q_ASSERT(tower);
            m_towersList.removeOne(tower);
            delete tower;
        }
        foreach (Enemy *enemy, m_enemyList)
        {
            Q_ASSERT(enemy);
            m_enemyList.removeOne(enemy);
            delete enemy;
        }
        foreach (Bullet *bullet, m_bulletList)
        {
            removedBullet(bullet);
        }

        if(m_gameWin){
        QPixmap loseScene(":/image/success.jpg");
        QPainter painter(this);
        painter.drawPixmap(0, 0, loseScene);

        }

        if(m_gameEnded)
        {
            QPixmap loseScene(":/image/lose.jpg");
            QPainter painter(this);
            painter.drawPixmap(0, 0, loseScene);
        }
        return;
    }

    QPixmap cachePix(":/image/map1.jpg");
    QPainter cachePainter(&cachePix); //缓存，避免直接在界面上绘制而效率低下

    foreach (const Tower *tower, m_towersList)
        tower->draw(&cachePainter);

    foreach (const Enemy *enemy, m_enemyList)
        enemy->draw(&cachePainter);

    foreach (const Bullet *bullet, m_bulletList)
        bullet->draw(&cachePainter);

    drawWave();
    drawHP();
    drawPlayerGold();

    //初始化画笔
    QPainter painter(this);
    //画背景图片
    painter.drawPixmap(0, 0, cachePix);

}

void easyScene::mousePressEvent(QMouseEvent * event)
{
    //单击鼠标后的处理
    QPoint pressPos = event->pos();
    int posx = pressPos.x();
    int posy = pressPos.y();

    if (upgradestate)
    {
        if (posx >= 100 && posx <= 150 && posy >= 410 && posy <= 460 && currenttower->m_level != 5)
        {
            //升级
            int level = currenttower->m_level;
            int gold = 80 + level*100;
            if (m_playerGold >= gold)
            {
                m_playerGold -= gold;
                currenttower->levelup();

                LevelFront->setText(QString("level %1").arg(currenttower->m_level));
                LevelFront->show();
                LevelFront->raise();

                if (level != 4)
                    Upgrade_MoneyFront->setText(QString("%1").arg(gold+100));
                else {
                    Upgrade_MoneyFront->setText("---");
                }
                Upgrade_MoneyFront->show();
                Upgrade_MoneyFront->raise();

            }
        } else {
            currenttower = nullptr;
            upgradestate = 0;

            LevelFront->setText("");
            LevelFront->show();
            LevelFront->raise();

            Upgrade_MoneyFront->setText("");
            Upgrade_MoneyFront->show();
            Upgrade_MoneyFront->raise();
        }
    }


    if (currentCard == nullptr){
        auto it = m_towerPositionsList.begin();
        while (it != m_towerPositionsList.end())
        {
            if (currentCard == nullptr && it->containPoint(pressPos) && it->hasTower())
            {

                currenttower = it->m_tower;
                LevelFront->setText(QString("level %1").arg(it->m_tower->m_level));
                LevelFront->show();
                LevelFront->raise();
                switch (it->m_tower->m_level)
                {
                case 1:
                    Upgrade_MoneyFront->setText("180");
                    break;
                case 2:
                    Upgrade_MoneyFront->setText("280");
                    break;
                case 3:
                    Upgrade_MoneyFront->setText("380");
                    break;
                case 4:
                    Upgrade_MoneyFront->setText("480");
                    break;
                default:
                    Upgrade_MoneyFront->setText("---");
                    break;
                }
                Upgrade_MoneyFront->show();
                Upgrade_MoneyFront->raise();

                upgradestate = 1;
            }
            ++it;
        }
    }

    if(currentCard != nullptr){
        bool temp = 0;
    auto it = m_towerPositionsList.begin();
    while (it != m_towerPositionsList.end())
    {
        if (currentCard != nullptr && canBuyTower() && it->containPoint(pressPos) && !it->hasTower())
        {
            temp = 1;
            m_audioPlayer->playSound(TowerPlaceSound);

            it->setHasTower();
            Tower *tower;
            switch(currentIndex)
            {
            case 0:tower = new NormalTower(it->centerPos(), this);
                it->m_tower = tower;
                m_playerGold -= 100;
                it->m_towerkind = 0;
                break;
            case 1:tower = new FireTower(it->centerPos(), this);
                m_playerGold -= 150;
                it->m_tower = tower;
                it->m_towerkind = 1;
                break;
            case 2:tower = new IceTower(it->centerPos(), this);
                m_playerGold -= 150;
                it->m_towerkind = 2;
                it->m_tower = tower;
                break;
            case 3:tower = new LaserTower(it->centerPos(), this);
                m_playerGold -= 200;
                it->m_towerkind = 3;
                it->m_tower = tower;
                break;
            }
            m_towersList.push_back(tower);
            update(); //调用paintevent(),重绘画面
            currentCard->move(currentPos);
            currentCard = nullptr;
            break;
        }

        ++it;
    }
        if(temp == 0)
        {
           currentCard->move(currentPos);
           currentCard = nullptr;
        }
    }

    //if(state == 0) //空状态
    int cardindex = -1;
    if (posx >= 180 && posx <= 280 && posy >= 10 && posy <= 60)
        cardindex = 0;
    else if (posx >= 280 && posx <= 380 && posy >= 10 && posy <= 60)
        cardindex = 1;
    else if (posx >= 430 && posx <= 530 && posy >= 10 && posy <= 60)
        cardindex = 2;
    else if (posx >= 530 && posx <= 630 && posy >= 10 && posy <= 60)
        cardindex = 3;

    if (cardindex >= 0)
    {
        currentPos = Cards[cardindex]->pos();
        this->currentCard = Cards[cardindex];
        currentIndex = cardindex;
    }
}

void easyScene::onTimer()
{
    this->exit->raise();
}

void easyScene::leave()
{
    emit toTitle();
}

void easyScene::back()
{

}

void easyScene::updateMap()
{
    foreach (Enemy *enemy, m_enemyList)
        enemy->move();
    foreach (Tower *tower, m_towersList)
        tower->checkEnemyInRange();
    update();
}

void easyScene::gameStart()
{
    loadWave();
}

// 以下是对复杂地图的设计

hardScene::hardScene(QWidget* parent)
    : Scene(parent)
{
    QUrl backgroundMusicUrl = QUrl::fromLocalFile(s_curDir + "/hard.mp3");
    m_audioPlayer = new AudioPlayer(backgroundMusicUrl,this);
    m_audioPlayer->startBGM();

    this->setGeometry(0, 0, 800, 600);
    this->setMovie(this->background);
    this->background->start();
    this->show();

    preLoadWavesInfo(); //设置波数
    loadTowerPositions(); //调用位置函数

    addNormalWayPoints();
    addIceWayPoints();
    addFireWayPoints();
    addFastWayPoints();
    addBossWayPoints();

    //每30ms发送一个更新信号
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(30);
    this->uiSetup();
    // 设置300ms后游戏启动
    QTimer::singleShot(300, this, SLOT(gameStart()));
}

AudioPlayer *hardScene::audioPlayer() const
{
    return m_audioPlayer;
}

void hardScene::removedEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);

    m_enemyList.removeOne(enemy);
    delete enemy;

    if (m_enemyList.empty())
    {
        ++m_waves;
        if (!loadWave())
        {
        m_gameWin = true;
        m_audioPlayer->stopBGM();
        m_audioPlayer->playWinSound();

        }
    }
}


void hardScene::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Escape:
        emit toTitle();
        break;
    }
}

void hardScene::paintEvent(QPaintEvent *)
{
    if (m_gameEnded || m_gameWin)
    {
        btn1->hide();
        btn2->hide();
        btn3->hide();
        btn4->hide();
        btn5->hide();
        btn6->hide();
        btn7->hide();
        btn8->hide();
        btn9->hide();
        btn10->hide();
        btn11->hide();
        btn12->hide();
        btn13->hide();
        btn14->hide();

        MoneyFront->hide();
        MoneyBar->hide();
        MoneyLabel->hide();
        LifeFront->hide();
        LifeBar->hide();
        LifeLabel->hide();
        WaveFront->hide();
        WaveBar->hide();
        WaveLabel->hide();
        Base->hide();
        LevelUp->hide();
        LevelFront->hide();
        LevelBar->hide();
        Upgrade_MoneyFront->hide();
        Upgrade_MoneyBar->hide();
        Front1->hide();
        Front2->hide();
        Front3->hide();
        Front4->hide();

        NormalTowerPic->hide();
        FireTowerPic->hide();
        IceTowerPic->hide();
        LaserTowerPic->hide();

        foreach (Card *card, Cards)
        {
            Q_ASSERT(card);
            Cards.removeOne(card);
            delete card;
        }

        foreach (Tower *tower, m_towersList)
        {
            Q_ASSERT(tower);
            m_towersList.removeOne(tower);
            delete tower;
        }
        foreach (Enemy *enemy, m_enemyList)
        {
            Q_ASSERT(enemy);
            m_enemyList.removeOne(enemy);
            delete enemy;
        }
        foreach (Bullet *bullet, m_bulletList)
        {
            removedBullet(bullet);
        }



        if(m_gameWin){

        QPixmap loseScene(":/image/success.jpg");
        QPainter painter(this);
        painter.drawPixmap(0, 0, loseScene);
        }

        if(m_gameEnded)
        {
            QPixmap loseScene(":/image/lose.jpg");
            QPainter painter(this);
            painter.drawPixmap(0, 0, loseScene);
        }
        return;
    }

    QPixmap cachePix(":/image/map2.jpg");
    QPainter cachePainter(&cachePix);

    foreach (const Tower *tower, m_towersList)
        tower->draw(&cachePainter);

    foreach (const Enemy *enemy, m_enemyList)
        enemy->draw(&cachePainter);

    foreach (const Bullet *bullet, m_bulletList)
        bullet->draw(&cachePainter);

    drawWave();
    drawHP();
    drawPlayerGold();

    //初始化画笔
    QPainter painter(this);
    //画背景图片
    painter.drawPixmap(0, 0, cachePix);

}

void hardScene::mousePressEvent(QMouseEvent * event)
{
    //单击鼠标后的处理
    QPoint pressPos = event->pos();
    int posx = pressPos.x();
    int posy = pressPos.y();

    if (upgradestate)
    {
        if (posx >= 635 && posx <= 683 && posy >= 20 && posy <= 70 && currenttower->m_level != 5)
        {
            int level = currenttower->m_level;
            int gold = 80 + level*100;
            if (m_playerGold >= gold)
            {
                m_playerGold -= gold;
                currenttower->levelup();

                LevelFront->setText(QString("level %1").arg(currenttower->m_level));
                LevelFront->show();
                LevelFront->raise();

                if (level != 4)
                    Upgrade_MoneyFront->setText(QString("%1").arg(gold+100));
                else {
                    Upgrade_MoneyFront->setText("---");
                }
                Upgrade_MoneyFront->show();
                Upgrade_MoneyFront->raise();
        }
           } else {
                currenttower = nullptr;
                upgradestate = 0;

                LevelFront->setText("");
                LevelFront->show();
                LevelFront->raise();

                Upgrade_MoneyFront->setText("");
                Upgrade_MoneyFront->show();
                Upgrade_MoneyFront->raise();
            }
    }

    if (currentCard == nullptr ){
        auto it = m_towerPositionsList.begin();
        while (it != m_towerPositionsList.end())
        {
            if (currentCard == nullptr && it->containPoint(pressPos) && it->hasTower())
            {

                currenttower = it->m_tower;

                LevelFront->setText(QString("level %1").arg(it->m_tower->m_level));
                LevelFront->show();
                LevelFront->raise();
                switch (it->m_tower->m_level)
                {
                case 1:
                    Upgrade_MoneyFront->setText("180");
                    break;
                case 2:
                    Upgrade_MoneyFront->setText("280");
                    break;
                case 3:
                    Upgrade_MoneyFront->setText("380");
                    break;
                case 4:
                    Upgrade_MoneyFront->setText("480");
                    break;
                default:
                    Upgrade_MoneyFront->setText("---");
                    break;
                }
                Upgrade_MoneyFront->show();
                Upgrade_MoneyFront->raise();

                upgradestate = 1;
            }
            ++it;
        }
    }

    if(currentCard != nullptr){
        bool temp = 0;
    auto it = m_towerPositionsList.begin();
    while (it != m_towerPositionsList.end())
    {

        if (currentCard != nullptr && canBuyTower() && it->containPoint(pressPos) && !it->hasTower())
        {
            temp = 1;
            m_audioPlayer->playSound(TowerPlaceSound);

            it->setHasTower();
            Tower *tower;
            switch(currentIndex)
            {
            case 0:tower = new NormalTower(it->centerPos(), this);
                it->m_tower = tower;
                m_playerGold -= 100;
                it->m_towerkind = 0;
                break;
            case 1:tower = new FireTower(it->centerPos(), this);
                m_playerGold -= 150;
                it->m_tower = tower;
                it->m_towerkind = 1;
                break;
            case 2:tower = new IceTower(it->centerPos(), this);
                m_playerGold -= 150;
                it->m_towerkind = 2;
                it->m_tower = tower;
                break;
            case 3:tower = new LaserTower(it->centerPos(), this);
                m_playerGold -= 200;
                it->m_towerkind = 3;
                it->m_tower = tower;
                break;
            }
            m_towersList.push_back(tower);
            update(); //调用paintevent(),重绘画面
            currentCard->move(currentPos);
            currentCard = nullptr;
            break;
        }

        ++it;
    }
    if(temp == 0)
    {
       currentCard->move(currentPos);
       currentCard = nullptr;
    }

    }

    int cardindex = -1;
    if (posx >= 180 && posx <= 280 && posy >= 10 && posy <= 60)
        cardindex = 0;
    else if (posx >= 280 && posx <= 380 && posy >= 10 && posy <= 60)
        cardindex = 1;
    else if (posx >= 430 && posx <= 530 && posy >= 10 && posy <= 60)
        cardindex = 2;
    else if (posx >= 530 && posx <= 630 && posy >= 10 && posy <= 60)
        cardindex = 3;

    if (cardindex >= 0)
    {
        currentPos = Cards[cardindex]->pos();
        this->currentCard = Cards[cardindex];
        currentIndex = cardindex;
    }
}

void hardScene::onTimer()
{
    this->exit->raise();
}

void hardScene::leave()
{
    emit toTitle();
}

void hardScene::back()
{

}

void hardScene::updateMap()
{
    foreach (Enemy *enemy, m_enemyList)
        enemy->move();
    foreach (Tower *tower, m_towersList)
        tower->checkEnemyInRange();
    update();
}

void hardScene::gameStart()
{
    loadWave();
}


void hardScene::uiSetup()
{
    MoneyBar->setGeometry(80, -70, 300, 200);
    moneybar->start();
    MoneyBar->show();
    MoneyBar->setMovie(moneybar);
    MoneyFront->setGeometry(-30, 10, 300, 200);
    MoneyFront->setFont(QFont("Calibri", 16));
    MoneyFront->setText("50");
    MoneyFront->setAlignment(Qt::AlignHCenter);
    MoneyFront->show();
    MoneyFront->raise();
    MoneyLabel->setGeometry(10, -70, 300, 200);
    moneylabel->start();
    MoneyLabel->show();
    MoneyLabel->setMovie(moneylabel);

    LifeBar->setGeometry(80, -10, 300, 200);
    lifebar->start();
    LifeBar->show();
    LifeBar->setMovie(lifebar);
    LifeFront->setGeometry(-30, 70, 300, 200);
    LifeFront->setFont(QFont("Calibri", 16));
    LifeFront->setText("10");
    LifeFront->setAlignment(Qt::AlignHCenter);
    LifeFront->show();
    LifeFront->raise();
    LifeLabel->setGeometry(10, -10, 300, 200);
    lifelabel->start();
    LifeLabel->show();
    LifeLabel->setMovie(lifelabel);

    WaveBar->setGeometry(80, 50, 300, 200);
    wavebar->start();
    WaveBar->show();
    WaveBar->setMovie(wavebar);
    WaveFront->setGeometry(70, 130, 100, 50);
    WaveFront->setFont(QFont("Calibri", 16));
    WaveFront->setText("1");
    WaveFront->setAlignment(Qt::AlignHCenter);
    WaveFront->show();
    WaveFront->raise();
    WaveLabel->setGeometry(10, 50, 300, 200);
    wavelabel->start();
    WaveLabel->show();
    WaveLabel->setMovie(wavelabel);

    Base->setGeometry(685, 325, 228, 306);
    base->start();
    Base->show();
    Base->setMovie(base);
    Base->raise();

    LevelUp->setGeometry(635, 20, 50, 50);
    levelup->start();
    LevelUp->show();
    LevelUp->setMovie(levelup);
    LevelUp->raise();

    LevelBar->setGeometry(690, -15, 120, 100);
    levelbar->start();
    LevelBar->show();
    LevelBar->setMovie(levelbar);
    LevelBar->raise();
    LevelFront->setGeometry(640,20, 180, 120);
    LevelFront->setFont(QFont("Calibri", 12));
    //LevelFront->setText("5");
    LevelFront->setAlignment(Qt::AlignHCenter);
    LevelFront->show();
    LevelFront->raise();

    Upgrade_MoneyBar->setGeometry(690, 40, 100, 80);
    upgrade_moneybar->start();
    Upgrade_MoneyBar->show();
    Upgrade_MoneyBar->setMovie(upgrade_moneybar);
    Upgrade_MoneyBar->raise();
    Upgrade_MoneyFront->setGeometry(685, 65, 80, 50);
    Upgrade_MoneyFront->setFont(QFont("Calibri", 12));
    Upgrade_MoneyFront->setAlignment(Qt::AlignHCenter);
    Upgrade_MoneyFront->show();
    Upgrade_MoneyFront->raise();

    btn1->setStyleSheet("QLabel{border: 0px solid #000000;} QLabel:hover{border:1px solid #000000;}");
    btn1->setMovie(station);
    station->start();
    btn1->setGeometry(121,277, 60, 60);
    btn1->show();
    btn1->raise();

    btn2->setStyleSheet("QLabel{border: 0px solid #000000;} QLabel:hover{border:1px solid #000000;}");
    btn2->setMovie(station);
    station->start();
    btn2->setGeometry(251,293, 60, 60);
    btn2->show();
    btn2->raise();

    btn3->setStyleSheet("QLabel{border: 0px solid #000000;} QLabel:hover{border:1px solid #000000;}");
    btn3->setMovie(station);
    station->start();
    btn3->setGeometry(248,204, 60, 60);
    btn3->show();
    btn3->raise();

    btn4->setStyleSheet("QLabel{border: 0px solid #000000;} QLabel:hover{border:1px solid #000000;}");
    btn4->setMovie(station);
    station->start();
    btn4->setGeometry(414,211, 60, 60);
    btn4->show();
    btn4->raise();

    btn5->setStyleSheet("QLabel{border: 0px solid #000000;} QLabel:hover{border:1px solid #000000;}");
    btn5->setMovie(station);
    station->start();
    btn5->setGeometry(414,297, 60, 60);
    btn5->show();
    btn5->raise();

    btn6->setStyleSheet("QLabel{border:0px solid #000000;} QLabel:hover{border:1px solid #000000;}");
    btn6->setMovie(station);
    station->start();
    btn6->setGeometry(414,381, 60, 60);
    btn6->show();
    btn6->raise();

    btn7->setStyleSheet("QLabel{border: 0px solid #000000;} QLabel:hover{border:1px solid #000000;}");
    btn7->setMovie(station);
    station->start();
    btn7->setGeometry(587,203, 60, 60);
    btn7->show();
    btn7->raise();

    btn8->setStyleSheet("QLabel{border: 0px solid #000000;} QLabel:hover{border:1px solid #000000;}");
    btn8->setMovie(station);
    station->start();
    btn8->setGeometry(587,287, 60, 60);
    btn8->show();
    btn8->raise();

    btn9->setStyleSheet("QLabel{border: 0px solid #000000;} QLabel:hover{border:1px solid #000000;}");
    btn9->setMovie(station);
    station->start();
    btn9->setGeometry(719,105, 60, 60);
    btn9->show();
    btn9->raise();

    btn10->setStyleSheet("QLabel{border:0px solid #000000;} QLabel:hover{border:1px solid #000000;}");
    btn10->setMovie(station);
    station->start();
    btn10->setGeometry(719,189, 60, 60);
    btn10->show();
    btn10->raise();

    btn11->setStyleSheet("QLabel{border: 0px solid #000000;} QLabel:hover{border:1px solid #000000;}");
    btn11->setMovie(station);
    station->start();
    btn11->setGeometry(723,283, 60, 60);
    btn11->show();
    btn11->raise();

    btn12->setStyleSheet("QLabel{border: 0px solid #000000;} QLabel:hover{border:1px solid #000000;}");
    btn12->setMovie(station);
    station->start();
    btn12->setGeometry(56,466, 60, 60);
    btn12->show();
    btn12->raise();

    btn13->setStyleSheet("QLabel{border: 0px solid #000000;} QLabel:hover{border:1px solid #000000;}");
    btn13->setMovie(station);
    station->start();
    btn13->setGeometry(140,466, 60, 60);
    btn13->show();
    btn13->raise();

    btn14->setStyleSheet("QLabel{border: 0px solid #000000;} QLabel:hover{border:1px solid #000000;}");
    btn14->setMovie(station);
    station->start();
    btn14->setGeometry(224,466, 60, 60);
    btn14->show();
    btn14->raise();

    btn15->setStyleSheet("QLabel{border: 0px solid #000000;} QLabel:hover{border:1px solid #000000;}");
    btn15->setMovie(station);
    station->start();
    btn15->setGeometry(323,466, 60, 60);
    btn15->show();
    btn15->raise();

    btn16->setStyleSheet("QLabel{border: 0px solid #000000;} QLabel:hover{border:1px solid #000000;}");
    btn16->setMovie(station);
    station->start();
    btn16->setGeometry(500,466, 60, 60);
    btn16->show();
    btn16->raise();

    btn17->setStyleSheet("QLabel{border: 0px solid #000000;} QLabel:hover{border:1px solid #000000;}");
    btn17->setMovie(station);
    station->start();
    btn17->setGeometry(570,466, 60, 60);
    btn17->show();
    btn17->raise();

    btn18->setStyleSheet("QLabel{border: 0px solid #000000;} QLabel:hover{border:1px solid #000000;}");
    btn18->setMovie(station);
    station->start();
    btn18->setGeometry(640,466, 60, 60);
    btn18->show();
    btn18->raise();

    btn19->setStyleSheet("QLabel{border: 0px solid #000000;} QLabel:hover{border:1px solid #000000;}");
    btn19->setMovie(station);
    station->start();
    btn19->setGeometry(710,466, 60, 60);
    btn19->show();
    btn19->raise();


    exit->setGeometry(700, 130, 60, 60); //设置退出按钮
    exit->setFlat(true);
    exit->setIcon(QIcon(":/image/Leave.png"));
    exit->setIconSize(QSize(60,60));
    exit->setStyleSheet("background: transparent");
    exit->setCursor(Qt::PointingHandCursor);
    connect(exit, SIGNAL(clicked()), this, SLOT(leave()));
    exit->show();
    exit->raise();

    NormalTowerPic->setGeometry(180, 10, 100, 60);
    normalTowerPic->start();
    NormalTowerPic->show();
    NormalTowerPic->setMovie(normalTowerPic);

    FireTowerPic->setGeometry(280, 10 , 100, 60);
    fireTowerPic->start();
    FireTowerPic->show();
    FireTowerPic->setMovie(fireTowerPic);

    IceTowerPic->setGeometry(430, 10 , 100, 60);
    iceTowerPic->start();
    IceTowerPic->show();
    IceTowerPic->setMovie(iceTowerPic);

    LaserTowerPic->setGeometry(530, 10 , 100, 60);
    laserTowerPic->start();
    LaserTowerPic->show();
    LaserTowerPic->setMovie(laserTowerPic);

    Card *card0 = new tNormalTowerCard(this);
    card0->setGeometry(180, 10 , 100, 60);
    Cards.append(card0);
    card0->show();

    Front1 = new QLabel(this);
    Front1->setText("100");
    Front1->setGeometry(225, 40, 40, 20);
    Front1->setFont(QFont("Calibri", 11));
    Front1->show();
    Front1->raise();

    Card *card1 = new tFireTowerCard(this);
    card1->setGeometry(280, 10 , 100, 60);
    Cards.append(card1);
    card1->show();

    Front2 = new QLabel(this);
    Front2->setText("150");
    Front2->setGeometry(325, 40, 40, 20);
    Front2->setFont(QFont("Calibri", 11));
    Front2->show();
    Front2->raise();

    Card *card2 = new tIceTowerCard(this);
    card2->setGeometry(430, 10 , 100, 60);
    Cards.append(card2);
    card2->show();

    Front3 = new QLabel(this);
    Front3->setText("150");
    Front3->setGeometry(475, 40, 40, 20);
    Front3->setFont(QFont("Calibri", 11));
    Front3->show();
    Front3->raise();

    Card *card3 = new tLaserTowerCard(this);
    card3->setGeometry(530, 10 , 100, 60);
    Cards.append(card3);
    card3->show();

    Front4 = new QLabel(this);
    Front4->setText("200");
    Front4->setGeometry(575, 40, 40, 20);
    Front4->setFont(QFont("Calibri", 11));
    Front4->show();
    Front4->raise();
}

void hardScene::loadTowerPositions()
{
    QPoint pos[]=
    {
        QPoint(121,277),
        QPoint(251,293),
        QPoint(248,204),
        QPoint(414,211),
        QPoint(414,297),

        QPoint(414,381),
        QPoint(587,203),
        QPoint(587,287),
        QPoint(719,105),
        QPoint(719,189),

        QPoint(56,466),
        QPoint(140,466),
        QPoint(224,466),
        QPoint(323,466),
        QPoint(500,466),
        QPoint(570,466),
        QPoint(640,466),
        QPoint(710,466),
        QPoint(723,283)

    };
    int len= sizeof(pos)/sizeof (pos[0]);
    for (int i = 0;i<len;++i)
        m_towerPositionsList.push_back(pos[i]);


}

void hardScene::addNormalWayPoints()
{
        WayPoint *wayPoint1 = new WayPoint(QPoint(797, 404));//终点
        normalWayPointsList.push_back(wayPoint1);

        WayPoint *wayPoint2 = new WayPoint(QPoint(688,411));
        normalWayPointsList.push_back(wayPoint2);
        wayPoint2->setNextWayPoint(wayPoint1);

        WayPoint *wayPoint3 = new WayPoint(QPoint(666,162));
        normalWayPointsList.push_back(wayPoint3);
        wayPoint3->setNextWayPoint(wayPoint2);

        WayPoint *wayPoint4 = new WayPoint(QPoint(352,158));
        normalWayPointsList.push_back(wayPoint4);
        wayPoint4->setNextWayPoint(wayPoint3);

        WayPoint *wayPoint5 = new WayPoint(QPoint(347,413));
        normalWayPointsList.push_back(wayPoint5);
        wayPoint5->setNextWayPoint(wayPoint4);

        WayPoint *wayPoint6 = new WayPoint(QPoint(82,402));
        normalWayPointsList.push_back(wayPoint6);
        wayPoint6->setNextWayPoint(wayPoint5);

        WayPoint *wayPoint7 = new WayPoint(QPoint(78,283));
        normalWayPointsList.push_back(wayPoint7);
        wayPoint7->setNextWayPoint(wayPoint6);

        WayPoint *wayPoint8 = new WayPoint(QPoint(0,285));
        normalWayPointsList.push_back(wayPoint8);
        wayPoint8->setNextWayPoint(wayPoint7);
}

void hardScene::addIceWayPoints(){
    WayPoint *wayPoint1 = new WayPoint(QPoint(797,404));//终点
    iceWayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(688,411));
    iceWayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3 = new WayPoint(QPoint(666,162));
    iceWayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(220,165));
    iceWayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(202,379));
    iceWayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(82,402));
    iceWayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);

    WayPoint *wayPoint7 = new WayPoint(QPoint(78,283));
    iceWayPointsList.push_back(wayPoint7);
    wayPoint7->setNextWayPoint(wayPoint6);

    WayPoint *wayPoint8 = new WayPoint(QPoint(0,285));
    iceWayPointsList.push_back(wayPoint8);
    wayPoint8->setNextWayPoint(wayPoint7);

}

void hardScene::addFireWayPoints(){
    WayPoint *wayPoint1 = new WayPoint(QPoint(797,404));//终点
    fireWayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(560,405));
    fireWayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3 = new WayPoint(QPoint(548,163));
    fireWayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(220,165));
    fireWayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(202,397));
    fireWayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(82,402));
    fireWayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);

    WayPoint *wayPoint7 = new WayPoint(QPoint(78,283));
    fireWayPointsList.push_back(wayPoint7);
    wayPoint7->setNextWayPoint(wayPoint6);

    WayPoint *wayPoint8 = new WayPoint(QPoint(0,285));
    fireWayPointsList.push_back(wayPoint8);
    wayPoint8->setNextWayPoint(wayPoint7);

}

void hardScene::addFastWayPoints(){
    WayPoint *wayPoint1 = new WayPoint(QPoint(797,404));//终点
    fastWayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(560,405));
    fastWayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);
    WayPoint *wayPoint3 = new WayPoint(QPoint(548,163));
    fastWayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(352,158));
    fastWayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(347,413));
    fastWayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(82,402));
    fastWayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);

    WayPoint *wayPoint7 = new WayPoint(QPoint(78,283));
    fastWayPointsList.push_back(wayPoint7);
    wayPoint7->setNextWayPoint(wayPoint6);

    WayPoint *wayPoint8 = new WayPoint(QPoint(0,285));
    fastWayPointsList.push_back(wayPoint8);
    wayPoint8->setNextWayPoint(wayPoint7);

}

void hardScene::addBossWayPoints(){
    WayPoint *wayPoint1 = new WayPoint(QPoint(797,404));//终点
    bossWayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(560,405));
    bossWayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);
    WayPoint *wayPoint3 = new WayPoint(QPoint(548,163));
    bossWayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(352,158));
    bossWayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(347,413));
    bossWayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(82,402));
    bossWayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);

    WayPoint *wayPoint7 = new WayPoint(QPoint(78,283));
    bossWayPointsList.push_back(wayPoint7);
    wayPoint7->setNextWayPoint(wayPoint6);

    WayPoint *wayPoint8 = new WayPoint(QPoint(0,285));
    bossWayPointsList.push_back(wayPoint8);
    wayPoint8->setNextWayPoint(wayPoint7);

}


bool hardScene::loadWave()
{
    if (m_waves >= m_wavesInfo.size())
        return false;

    QList<QVariant> curWavesInfo = m_wavesInfo[m_waves].toList();

    for (int i = 0; i < curWavesInfo.size(); ++i)
    {
        QMap<QString, QVariant> dict = curWavesInfo[i].toMap();
        int spawnTime = dict.value("spawnTime").toInt();

        Enemy *enemy;
        int j=i%5;
        switch(j){
        case 0:
            enemy = new normalEnemy(normalWayPointsList.back(), this);
            break;
        case 1:
            enemy=new iceEnemy(iceWayPointsList.back(), this);
            break;
        case 2:
            enemy=new fireEnemy(fireWayPointsList.back(), this);
            break;
        case 3:
            enemy=new fastEnemy(fastWayPointsList.back(), this);
            break;
        case 4:
            enemy=new bossEnemy(bossWayPointsList.back(), this);
            break;
        }
        m_enemyList.push_back(enemy);
        QTimer::singleShot(spawnTime, enemy, SLOT(doActivate()));
    }

    return true;
}

bool hardScene::canBuyTower() const
{
    if (m_playerGold >= TowerCost)
        return true;
    return false;
}

void hardScene::drawWave()
{
    WaveFront->setText(QString("%1").arg(m_waves +1));
    WaveFront->setAlignment(Qt::AlignHCenter);
    WaveFront->show();
    WaveFront->raise();
}

void hardScene::drawHP()
{
    LifeFront->setText(QString("%1").arg(m_playerHp));
    LifeFront->setAlignment(Qt::AlignHCenter);
    LifeFront->show();
    LifeFront->raise();
}

void hardScene::drawPlayerGold()
{
    MoneyFront->setText(QString("%1").arg(m_playerGold));
    MoneyFront->setAlignment(Qt::AlignHCenter);
    MoneyFront->show();
    MoneyFront->raise();
}

void hardScene::preLoadWavesInfo()
{
    QFile file(":/config/Waves.plist");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition.plist");
        return;
    }

    PListReader reader;
    reader.read(&file);

    // 获取波数信息
    m_wavesInfo = reader.data();

    file.close();
}

hardScene::~hardScene()
{
    delete this->background;
    delete this->exit;
    delete this->btn1;
    delete this->btn2;
    delete this->btn3;
    delete this->btn4;
    delete this->btn5;
    delete this->btn6;
    delete this->btn7;
    delete this->btn8;
    delete this->btn9;
    delete this->btn10;
    delete this->btn11;
    delete this->btn12;
    delete this->btn13;
    delete this->btn14;

    foreach (Card *card, Cards)
    {
        Q_ASSERT(card);
        Cards.removeOne(card);
        delete card;
    }

    foreach (Tower *tower, m_towersList)
    {
        Q_ASSERT(tower);
        m_towersList.removeOne(tower);
        delete tower;
    }
    foreach (Enemy *enemy, m_enemyList)
    {
        Q_ASSERT(enemy);
        m_enemyList.removeOne(enemy);
        delete enemy;
    }
    foreach (Bullet *bullet, m_bulletList)
    {
        removedBullet(bullet);
    }
}
