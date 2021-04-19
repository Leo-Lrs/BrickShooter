#include "health.h"
#include <QFont>


Health::Health(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    health = 0;
}

void Health::decrease()
{
    health--;
}

int Health::getHealth()
{
    return health;
}
