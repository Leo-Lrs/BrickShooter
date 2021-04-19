#ifndef COMMONENEMY_H
#define COMMONENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include "enemy.h"



class CommonEnemy : public Enemy
{
public:
    CommonEnemy(QGraphicsItem * parent=NULL);
    ~CommonEnemy();

};

#endif // COMMONENEMY_H
