#include "bullet.h"
#include "commonenemy.h"
#include "enemy.h"
#include "game.h"
#include "rareenemy.h"
#include "veryrareenemy.h"
#include "extrarareenemy.h"

#include <QTimer>
#include <QGraphicsScene>
#include <QList>

extern Game * game;

Bullet::Bullet(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/bullet.png"));

    //Faire connecter
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    //temps en ms
    timer->start(40);
}

Bullet::~Bullet()
{
    delete timer;
}

void Bullet::move()
{
    //La collision
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(CommonEnemy)){
            game->getScore()->increase();

            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            static_cast <Enemy*> (colliding_items[i])->setIsDead(true);
            delete this;
            return;
        }
        else if(typeid(*(colliding_items[i])) == typeid(RareEnemy)){
            game->getScore()->increase();
            upVitSpeed();
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            static_cast <Enemy*> (colliding_items[i])->setIsDead(true);
            delete this;
            return;
        }
        else if(typeid(*(colliding_items[i])) == typeid(VeryRareEnemy)){
            game->getScore()->increase();
            upVitSpeed2();
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            static_cast <Enemy*> (colliding_items[i])->setIsDead(true);
            delete this;
            return;
        }
        else if(typeid(*(colliding_items[i])) == typeid(Extrarareenemy)){
            game->getScore()->increase();
            upVitSpeed3();
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            static_cast <Enemy*> (colliding_items[i])->setIsDead(true);
            delete this;
            return;
        }
    }

    //depla de la bullet
    setPos(x(),y()-game->getMoveBullet());
    if(pos(),y() + QPixmap().height() < 60){
        scene()->removeItem(this);
        delete this;
    }
}


void Bullet::upVitSpeed()
{
    game->setMoveEnnemi(game->getMoveEnnemi()+1);
}

void Bullet::upVitSpeed2()
{
    game->setMoveBullet(game->getMoveBullet()-1);
}

void Bullet::upVitSpeed3()
{
    game->setMovePlayer(game->getMovePlayer()+3);
}
