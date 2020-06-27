#ifndef TOWER_H
#define TOWER_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>
#include "scene.h"

class QPainter;
class Enemy;
class Enemy1;
class Enemy2;
class MainWindow;
class QTimer;
class Scene;

class Tower : public QObject
{
    Q_OBJECT
public:
    Tower(QPoint pos, Scene *game, const QPixmap &sprite = QPixmap(":/image/normaltower.png"), int attackRange = 120, int damage = 10, int fireRate = 300, int level = 1);
    ~Tower();

    virtual void draw(QPainter *painter) const;
    void checkEnemyInRange();
    void targetKilled();
    void attackEnemy();
    void chooseEnemyForAttack(Enemy *enemy);
    void damageEnemy();
    void lostSightOfEnemy();

    //炮塔升级
    virtual void levelup() = 0;
    int             m_level;        // 等级

protected slots:
    //不同派生类（不同塔）需要发射不同子弹，需要虚函数
    virtual void shootWeapon() = 0;

protected:
    bool			m_attacking;
    qreal			m_rotationSprite;

    Enemy *			m_chooseEnemy;
    Scene *        m_game;
    QTimer *		m_fireRateTimer;

    int				m_attackRange;	// 代表塔可以攻击到敌人的距离
    int				m_damage;		// 代表攻击敌人时造成的伤害
    int				m_fireRate;		// 代表再次攻击敌人的时间间隔

    const QPoint	m_pos; //塔的圆心
    const QPixmap	m_sprite;

    static const QSize ms_fixedSize;
};

class NormalTower: public Tower
{
    Q_OBJECT
public:
    NormalTower(QPoint pos, Scene *game, const QPixmap &sprite = QPixmap(":/image/normaltower.png"));
    ~NormalTower();

    void levelup();

protected slots:
    virtual void shootWeapon();
};

class FireTower : public Tower
{
    Q_OBJECT
public:
    FireTower(QPoint pos, Scene *game, const QPixmap &sprite = QPixmap(":/image/firetower.png"));
    ~FireTower();

    void levelup();

protected slots:
    virtual void shootWeapon();

private:
    int fireattack; //每秒的灼烧伤害
};

class IceTower : public Tower
{
    Q_OBJECT
public:
    IceTower(QPoint pos, Scene *game, const QPixmap &sprite = QPixmap(":/image/icetower.png"));
    ~IceTower();

    void levelup();

protected slots:
    virtual void shootWeapon();

private:
    int slowspeed; //减慢速度百分比
};

class LaserTower : public Tower
{
    Q_OBJECT
public:
    LaserTower(QPoint pos, Scene *game, const QPixmap &sprite = QPixmap(":/image/lasertower.png"));
    ~LaserTower();

    void levelup();

protected slots:
    virtual void shootWeapon();
};

#endif // TOWER_H
