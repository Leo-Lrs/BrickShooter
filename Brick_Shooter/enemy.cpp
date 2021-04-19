#include "enemy.h"
#include "game.h"

#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>
#include <iostream>

using namespace std;

extern Game * game;

Enemy::Enemy(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    // Faire apparaître de manière aléatoire
    int random_number = rand() % 750; // %700 par rapport au screen soit -->Pas de spawn en dehors de l'écran.
    setPos(random_number,0);

    //Faire connecter
    timerTest = new QTimer();
    connect(timerTest,SIGNAL(timeout()),this,SLOT(move()));

    //temps en ms
    resume();
}

Enemy::~Enemy()
{
    delete timerTest;
}

void Enemy::pause()
{
    timerTest->stop();
}

void Enemy::resume()
{
    timerTest->start(40);
}

void Enemy::move()
{
    QList<QGraphicsItem *> collisionEnemy = collidingItems();
    for (int i = 0, n = collisionEnemy.size(); i< n; i++)
    {
        if (typeid(*(collisionEnemy[i])) == typeid(Player))
        {
            game->displayEndGame();
            return;
        }
    }
    setPos(x(),y()+game->getMoveEnnemi());
    if(pos(),y() > 900){
        if(!isDead){
            scene()->removeItem(this);
            isDead = true;
        }
    }
}

void Enemy::setIsDead(bool value)
{
    isDead = value;
}

bool Enemy::getIsDead() const
{
    return isDead;
}



