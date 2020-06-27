#include "card.h"

Card::Card(QLabel* parent) : QLabel(parent)
{
    this->setCursor(Qt::PointingHandCursor);
}

Card::~Card()
{

}

tNormalTowerCard::tNormalTowerCard(QLabel *parent):Card(parent)
{
    this->setMovie(anim);
    anim->start();

}

tNormalTowerCard::~tNormalTowerCard()
{
    delete this->anim;
}

tFireTowerCard::tFireTowerCard(QLabel *parent):Card(parent)
{
    this->setMovie(anim);
    anim->start();
}

tFireTowerCard::~tFireTowerCard()
{
    delete this->anim;
}

tIceTowerCard::tIceTowerCard(QLabel *parent):Card(parent)
{
    this->setMovie(anim);
    anim->start();
}

tIceTowerCard::~tIceTowerCard()
{
    delete this->anim;
}

tLaserTowerCard::tLaserTowerCard(QLabel *parent):Card(parent)
{
    this->setMovie(anim);
    anim->start();
}

tLaserTowerCard::~tLaserTowerCard()
{
    delete this->anim;
}
