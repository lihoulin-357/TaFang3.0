#include "bullet.h"
#include "enemy.h"
#include "mainwindow.h"
#include <QPainter>
#include <QPropertyAnimation>

const QSize Bullet::ms_fixedSize(26, 26);

Bullet::Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target,
               Scene *game, int kind, int fire, qreal slow, const QPixmap &sprite)
    : m_startPos(startPos)
    , m_targetPos(targetPoint)
    , m_sprite(sprite)
    , m_currentPos(startPos)
    , m_target(target)
    , m_game(game)
    , m_damage(damage)
    , bulletKind(kind)
    , fire_attack(fire)
    , slow_speed(slow)
{}


void Bullet::draw(QPainter *painter) const{
    painter->drawPixmap(m_currentPos, m_sprite);
}

void Bullet::move(){
    static const int duration = 300;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "m_currentPos");
    animation->setDuration(duration);
    animation->setStartValue(m_startPos);
    animation->setEndValue(m_targetPos);
    connect(animation, SIGNAL(finished()), this, SLOT(hitTarget()));

    animation->start();
}

void Bullet::hitTarget(){
    if (m_game->enemyList().indexOf(m_target) != -1)
        m_target->getDamage(this);
    m_game->removedBullet(this);
}

void Bullet::setCurrentPos(QPoint pos){
    m_currentPos = pos;
}

QPoint Bullet::currentPos() const{
    return m_currentPos;
}

NormalBullet::NormalBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, Scene *game, const QPixmap &sprite)
    :Bullet(startPos, targetPoint, damage, target, game)
{

}

FireBullet::FireBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, Scene *game, int kind, int fireattack, const QPixmap &sprite)
    :Bullet(startPos, targetPoint, damage, target, game, kind, fireattack, 1, sprite)
{

}

IceBullet::IceBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, Scene *game, int kind, qreal slow, const QPixmap &sprite)
    :Bullet(startPos, targetPoint, damage, target, game, kind, 0, slow, sprite)
{

}

LaserBullet::LaserBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, Scene *game, int kind,const QPixmap &sprite)
    :Bullet(startPos, targetPoint, damage, target, game, kind, 0, 1, sprite)
{

}
