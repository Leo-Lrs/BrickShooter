#include "commonenemy.h"
#include <iostream>

using namespace std;

CommonEnemy::CommonEnemy(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/images/briques.jpg"));
}

CommonEnemy::~CommonEnemy()
{

}
