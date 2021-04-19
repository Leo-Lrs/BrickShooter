#ifndef RAREENEMY_H
#define RAREENEMY_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include "enemy.h"

class RareEnemy : public Enemy
{
public:
    RareEnemy(QGraphicsItem * parent=NULL);
    ~RareEnemy();
};

#endif // RAREENEMY_H
