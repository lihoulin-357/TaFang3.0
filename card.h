#ifndef CARD_H
#define CARD_H


#include <QLabel>
#include <QMovie>
#include <QSound>
#include <QMouseEvent>

#include "scene.h"

class Scene;

class Card : public QLabel
{
public:
    Card(QLabel* parent = 0);
    ~Card();
};

class tNormalTowerCard : public Card
{
public:
    tNormalTowerCard(QLabel* parent = 0);
    ~tNormalTowerCard();
private:
    QMovie* anim = new QMovie(":/image/normaltower.png");
};


class tFireTowerCard : public Card
{
public:
    tFireTowerCard(QLabel* parent = 0);
    ~tFireTowerCard();
private:
    QMovie* anim = new QMovie(":/image/firetower.png");
};

class tIceTowerCard : public Card
{
public:
    tIceTowerCard(QLabel* parent = 0);
    ~tIceTowerCard();
private:
    QMovie* anim = new QMovie(":/image/icetower.png");
};

class tLaserTowerCard : public Card
{
public:
    tLaserTowerCard(QLabel* parent = 0);
    ~tLaserTowerCard();
private:
    QMovie* anim = new QMovie(":/image/lasertower.png");
};

#endif // CARD_H
