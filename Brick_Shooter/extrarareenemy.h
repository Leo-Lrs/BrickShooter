#ifndef EXTRARAREENEMY_H
#define EXTRARAREENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include "enemy.h"

class Extrarareenemy : public Enemy
{
public:
    Extrarareenemy(QGraphicsItem * parent=NULL);
    ~Extrarareenemy();
};

#endif // EXTRARAREENEMY_H
