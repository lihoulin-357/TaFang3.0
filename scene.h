#ifndef SCENE_H
#define SCENE_H

#include <QWidget>
#include <QMovie>
#include <QTimer>
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
#include <QKeyEvent>
#include <waypoint.h>
#include <enemy.h>
#include <tower.h>
#include <QPaintEvent>
#include <QPainter>
#include <QList>
#include <QtGlobal>
#include <QMessageBox>
#include <QXmlStreamReader>
#include <QtDebug>

#include "card.h"
#include "bullet.h"
#include "audioplayer.h"
#include "towerposition.h"
#include "plistreader.h"


class Bullet;
class Card;
class TowerPosition;

class Scene : public QLabel
{
    Q_OBJECT
public:
    int sunPoint = 50;
    Card* currentCard = nullptr;
    QPoint currentPos;
    QList<Card*> Cards;
    QPoint m;
    int currentIndex = -1;
    int upgradestate = 0;
    Tower* currenttower;

    explicit Scene(QWidget *parent = 0);
    ~Scene();
    void mouseMoveEvent(QMouseEvent *event);

    QTimer* timer = nullptr;

    QLabel* MoneyFront = new QLabel(this);
    QLabel* MoneyBar = new QLabel(this);
    QMovie* moneybar = new QMovie(":/image/info_bar.png");
    QLabel* MoneyLabel = new QLabel(this);
    QMovie* moneylabel = new QMovie(":/image/money2.png");

    QLabel* LifeFront = new QLabel(this);
    QLabel* LifeBar = new QLabel(this);
    QMovie* lifebar = new QMovie(":/image/info_bar.png");
    QLabel* LifeLabel = new QLabel(this);
    QMovie* lifelabel = new QMovie(":/image/life2.png");

    QLabel* WaveFront = new QLabel(this);
    QLabel* WaveBar = new QLabel(this);
    QMovie* wavebar = new QMovie(":/image/info_bar.png");
    QLabel* WaveLabel = new QLabel(this);
    QMovie* wavelabel = new QMovie(":/image/wave2.png");

    QLabel* Front1 = new QLabel(this);
    QLabel* Front2 = new QLabel(this);
    QLabel* Front3 = new QLabel(this);
    QLabel* Front4 = new QLabel(this);

    QLabel* NormalTowerPic = new QLabel(this);
    QMovie* normalTowerPic = new QMovie(":/image/frame.png");
    QLabel* FireTowerPic = new QLabel(this);
    QMovie* fireTowerPic = new QMovie(":/image/frame.png");
    QLabel* IceTowerPic = new QLabel(this);
    QMovie* iceTowerPic = new QMovie(":/image/frame.png");
    QLabel* LaserTowerPic = new QLabel(this);
    QMovie* laserTowerPic = new QMovie(":/image/frame.png");


    QLabel* Base = new QLabel(this);
    QMovie* base = new QMovie(":/image/base0.png");

    QLabel* LevelUp = new QLabel(this);
    QMovie* levelup = new QMovie(":/image/upgrade.png");

    QLabel* LevelFront = new QLabel(this);
    QLabel* LevelBar = new QLabel(this);
    QMovie* levelbar = new QMovie(":/image/info_bar.png");

    QLabel* Upgrade_MoneyFront = new QLabel(this);
    QLabel* Upgrade_MoneyBar = new QLabel(this);
    QMovie* upgrade_moneybar = new QMovie(":/image/info_bar.png");

    void addBullet(Bullet *bullet);
    virtual void removedEnemy(Enemy *enemy) = 0;
    void removedBullet(Bullet *bullet);
    QList<Enemy *> enemyList() const;
    void awardGold(int gold);
    void getHpDamage(int damage);
    void doGameOver();
    AudioPlayer* audioPlayer() const;

    QList<Bullet *>			m_bulletList;
    QList<Enemy *>			m_enemyList;
    QList<Tower *>			m_towersList;
    int						m_waves;
    bool					m_gameEnded;
    bool					m_gameWin;
    int						m_playerHp;
    int						m_playerGold;
    AudioPlayer *		    m_audioPlayer;

signals:
    void toTitle(); //返回信号，返回主界面
    void toEasy();
    void toHard();

public slots:
    void FireIceattack();
};

class tStartScreen: public QLabel
{
    Q_OBJECT
public:
    explicit tStartScreen(QWidget* parent = 0);
    ~tStartScreen();
    QTimer* timer = nullptr;
private:
    QMovie* background = new QMovie(":/image/Guide.jpg");
    QWidget* front = new QWidget(this);
    int frame = 100;
private slots:
    void onTimer();
signals:
    void toTitle(); //返回信号，返回主界面

private:
    AudioPlayer *		    m_audioPlayer;
};

// 下面这个类设置选择的界面
class tStartScene : public QLabel
{
    Q_OBJECT
public:
    explicit tStartScene(QWidget* parent = 0);
    ~tStartScene();
private:
    QMovie* background = new QMovie(":/image/menu.jpg");
    QMovie* easy = new QMovie(":/image/num1.png");
    QMovie* hard = new QMovie(":/image/num2.png");
    QLabel* btn1 = new QLabel(this);
    QLabel* btn2 = new QLabel(this);
    QLabel* title = new QLabel(this);
    QLabel* easyStr = new QLabel(this);
    QLabel* hardStr = new QLabel(this);
    AudioPlayer *		    m_audioPlayer;
protected:
    void mousePressEvent(QMouseEvent *event);

signals:
    void toEasy();
    void toHard();
};


class easyScene : public Scene
{
    Q_OBJECT
public:
    explicit easyScene(QWidget* parent = 0);
    ~easyScene();
    virtual void removedEnemy(Enemy *enemy);

protected:
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *);

    void mousePressEvent(QMouseEvent *);

private:
    QMovie* background = new QMovie(":/image/map1.jpg");
    QPushButton* exit = new QPushButton(this);

    QMovie* station = new QMovie("/image/open_spot.png");
    QLabel* btn1 = new QLabel(this);
    QLabel* btn2 = new QLabel(this);
    QLabel* btn3 = new QLabel(this);
    QLabel* btn4 = new QLabel(this);
    QLabel* btn5 = new QLabel(this);
    QLabel* btn6 = new QLabel(this);
    QLabel* btn7 = new QLabel(this);
    QLabel* btn8 = new QLabel(this);
    QLabel* btn9 = new QLabel(this);
    QLabel* btn10 = new QLabel(this);
    QLabel* btn11 = new QLabel(this);
    QLabel* btn12 = new QLabel(this);
    QLabel* btn13 = new QLabel(this);

    //QPoint cell;
    void uiSetup();

    //增加代码 6-6
private:
    void loadTowerPositions();
    void addWayPoints();
    bool loadWave();
    bool canBuyTower() const;
    void drawWave();
    void drawHP();
    void drawPlayerGold();
    //void doGameOver();
    void preLoadWavesInfo();

private:
    QList<QVariant>			m_wavesInfo;
    QList<TowerPosition>	m_towerPositionsList; //√
    QList<WayPoint *>		m_wayPointsList;

private slots:
    void onTimer();
    void leave(); // emit toTitle();

    void back();

    void updateMap(); //原来的槽
    void gameStart(); //原来的槽

};


class hardScene : public Scene
{
    Q_OBJECT
public:
    explicit hardScene(QWidget* parent = 0);
    ~hardScene();
    virtual void removedEnemy(Enemy *enemy);


    AudioPlayer* audioPlayer() const;

protected:
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *);

    void mousePressEvent(QMouseEvent *);

private:
    QMovie* background = new QMovie(":/image/map2.jpg");
    QPushButton* exit = new QPushButton(this);

    QMovie* station = new QMovie("/image/open_spot.png");
    QLabel* btn1 = new QLabel(this);
    QLabel* btn2 = new QLabel(this);
    QLabel* btn3 = new QLabel(this);
    QLabel* btn4 = new QLabel(this);
    QLabel* btn5 = new QLabel(this);
    QLabel* btn6 = new QLabel(this);
    QLabel* btn7 = new QLabel(this);
    QLabel* btn8 = new QLabel(this);
    QLabel* btn9 = new QLabel(this);
    QLabel* btn10 = new QLabel(this);
    QLabel* btn11= new QLabel(this);
    QLabel* btn12 = new QLabel(this);
    QLabel* btn13= new QLabel(this);
    QLabel* btn14 = new QLabel(this);
    QLabel* btn15 = new QLabel(this);
    QLabel* btn16 = new QLabel(this);
    QLabel* btn17 = new QLabel(this);
    QLabel* btn18 = new QLabel(this);
    QLabel* btn19 = new QLabel(this);

    //QPoint cell;
    void uiSetup();

private:
    void loadTowerPositions(); //√
    void addNormalWayPoints();
    void addIceWayPoints();
    void addFireWayPoints();
    void addFastWayPoints();
    void addBossWayPoints();

    bool loadWave();
    bool canBuyTower() const; //√
    void drawWave();
    void drawHP();
    void drawPlayerGold();
    void preLoadWavesInfo();

private:
    QList<QVariant>			m_wavesInfo;
    QList<TowerPosition>	m_towerPositionsList; //√
    QList<WayPoint *>       normalWayPointsList;
    QList<WayPoint *>		iceWayPointsList;
    QList<WayPoint *>		fireWayPointsList;
    QList<WayPoint *>		fastWayPointsList;
    QList<WayPoint *>		bossWayPointsList;

private slots:
    void onTimer();
    void leave();
    void back();

    void updateMap(); //原来的槽
    void gameStart(); //原来的槽
};

#endif // SCENE_H
