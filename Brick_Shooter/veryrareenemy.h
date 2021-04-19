#ifndef VERYRAREENEMY_H
#define VERYRAREENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include "enemy.h"

class VeryRareEnemy : public Enemy
{
public:
    VeryRareEnemy(QGraphicsItem * parent=NULL);
    ~VeryRareEnemy();

};

#endif // VERYRAREENEMY_H
